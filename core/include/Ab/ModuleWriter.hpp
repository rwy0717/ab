#ifndef AB_MODULEWRITER_HPP_
#define AB_MODULEWRITER_HPP_

#include <Ab/Config.hpp>
#include <Ab/ByteBuffer.hpp>
#include <Ab/Bytes.hpp>
#include <Ab/ModuleVisitation.hpp>
#include <Ab/Opcode.hpp>
#include <Ab/Types.hpp>
#include <Ab/VarInt.hpp>
#include <Ab/VectorUtilities.hpp>
#include <limits>
#include <span>
#include <utility>
#include <vector>

namespace Ab {

inline void append_type(ByteBuffer& buffer, const FuncType& type) {
	buffer.append(ValType::FUNC);
	append_varuint32(buffer, type.args.size());
	for (auto arg : type.args) {
		buffer.append(arg);
	}
	append_varuint32(buffer, type.rets.size());
	for (auto ret : type.rets) {
		buffer.append(ret);
	}
}

/// A simple function visitor.
///
class CodeWriter final : public CodeVisitor {
public:
	CodeWriter() {}

	virtual ~CodeWriter() = default;

	virtual void enter_code(std::uint32_t nregs) override { nregs_ = nregs; }

	virtual void leave_code() override {}

	virtual void on_unreachable() override { body_.append(Opcode::UNREACHABLE); }

	virtual void on_nop() override { body_.append(Opcode::NOP); }

	virtual void on_halt() override { body_.append(Opcode::HALT); }

	virtual void on_i32_add(std::uint8_t dst, std::uint8_t lhs, std::uint8_t rhs) override {
		body_.append(Opcode::I32_ADD);
		body_.append(dst);
		body_.append(lhs);
		body_.append(rhs);
	}

	virtual void on_return() override { body_.append(Opcode::RETURN); }

	virtual void on_x32_return(std::uint8_t src) override {
		body_.append(Opcode::X32_RETURN);
		body_.append(src);
	}

	virtual void on_x64_return(std::uint8_t src) override {
		body_.append(Opcode::X64_RETURN);
		body_.append(src);
	}

	void append_to(ByteBuffer& buffer) const {
		ByteBuffer content;

		append_varuint32(content, nregs_);
		content.append(body_);

		append_varuint32(buffer, content.size());
		buffer.append(content);
	}

private:
	std::uint32_t nregs_;
	ByteBuffer body_;
};

/// The module writer is itself a visitor.
///
class ModuleWriter final : public ModuleVisitor {
public:
	virtual ~ModuleWriter() override = default;

	/// Create the module.
	///
	std::span<Byte> finalize() {
		ByteBuffer buffer;
		append_module(buffer);
		return buffer.release_span();
	}

	// General

	virtual void enter_module() override {}

	virtual void leave_module() override {}

	// Type Section

	virtual void enter_type_section() override {}

	virtual void leave_type_section() override {}

	virtual void on_type(const FuncType& type) override { type_entries_.push_back(type); }

	// Func Section

	virtual void enter_func_section() override {}

	virtual void leave_func_section() override {}

	virtual void on_func(std::uint32_t type_idx) override { func_entries_.push_back(type_idx); }

	// Export Section

	virtual void enter_export_section() override {}

	virtual void leave_export_section() override {}

	// Code Section

	virtual void enter_code_section() override {}

	virtual void leave_code_section() override {}

	virtual void on_code(CodeModel& model) override { model.accept(push(code_entries_)); }

private:
	void append_module(ByteBuffer& buffer) const {
		buffer.append(MODULE_MAGIC);
		buffer.append(MODULE_VERSION);
		append_type_section(buffer);
		append_func_section(buffer);
		append_code_section(buffer);
	}

	void append_type_section(ByteBuffer& buffer) const {
		if (type_entries_.size() == 0) {
			return;
		}

		ByteBuffer content;

		append_varuint32(content, type_entries_.size());
		for (const FuncType& type : type_entries_) {
			append_type(content, type);
		}

		buffer.append(SectionCode::TYPE);
		append_varuint32(buffer, content.size());
		buffer.append(content);
	}

	void append_func_section(ByteBuffer& buffer) const {
		if (func_entries_.size() == 0) {
			return;
		}

		ByteBuffer content;

		append_varuint32(content, func_entries_.size());
		for (std::uint32_t typeidx : func_entries_) {
			append_varuint32(content, typeidx);
		}

		buffer.append(SectionCode::FUNC);
		append_varuint32(buffer, content.size());
		buffer.append(content);
	}

	void append_code_section(ByteBuffer& buffer) const {
		if (code_entries_.size() == 0) {
			return;
		}

		ByteBuffer content;

		append_varuint32(content, code_entries_.size());
		for (auto& code : code_entries_) {
			code.append_to(content);
		}

		buffer.append(SectionCode::CODE);
		append_varuint32(buffer, content.size());
		buffer.append(content);
	}

	std::vector<FuncType> type_entries_;
	std::vector<std::uint32_t> func_entries_;
	std::vector<CodeWriter> code_entries_;
};

template <typename M>
inline std::span<Byte> write(M& model) {
	static_assert(std::is_base_of_v<ModuleModel, M>);
	ModuleWriter writer;
	model.accept(writer);
	return writer.finalize();
}

}  // namespace Ab

#endif  // AB_MODULEWRITER_HPP_
