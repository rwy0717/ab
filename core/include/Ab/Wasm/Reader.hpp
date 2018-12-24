#ifndef AB_WASM_BINARY_READER_HPP_
#define AB_WASM_BINARY_READER_HPP_

#include <Ab/Config.hpp>

#include <Ab/Maybe.hpp>
#include <Ab/Wasm/ExprReader.hpp>
#include <Ab/Wasm/Expression.hpp>
#include <Ab/Wasm/Ir.hpp>
#include <Ab/Wasm/OpCode.hpp>
#include <Ab/Wasm/Section.hpp>
#include <Ab/Wasm/TypeCode.hpp>
#include <Ab/Wasm/Visitor.hpp>
#include <cstddef>
#include <cstdint>
#include <istream>
#include <memory>
#include <stdexcept>
#include <vector>

namespace Ab {
namespace Wasm {

class InvalidHeader : public ReaderError {
public:
	InvalidHeader() : ReaderError{"Invalid Header"} {};
};

class InvalidSection : public ReaderError {
public:
	InvalidSection() : ReaderError{"Bad section"} {
	}
};

struct SetInitExpr {
	template <typename E>
	auto operator()(const E& e, InitExpr&) const -> void {
		std::string m =
			std::string{"Unexpected expression in initialization expression: "} +
			OP_NAME<E::OP>;
		throw ReaderError{m};
	}

	auto operator()(GetGlobalExpr& e, InitExpr& out) const -> void {
		out.getGlobal = e;
	}

	auto operator()(I32ConstExpr& e, InitExpr& out) const -> void {
		out.i32Const = e;
	}

	auto operator()(I64ConstExpr& e, InitExpr& out) const -> void {
		out.i64Const = e;
	}

	auto operator()(F32ConstExpr& e, InitExpr& out) const -> void {
		out.f32Const = e;
	}

	auto operator()(F64ConstExpr& e, InitExpr& out) const -> void {
		out.f64Const = e;
	}
};

/// Binary file reader.
/// https://github.com/WebAssembly/design/blob/master/BinaryEncoding.md
/// https://github.com/WebAssembly/design/blob/master/Modules.md
class Reader {
public:
	Reader(Visitor& visitor, std::istream& src) : visitor_{visitor}, in_{src} {
	}

	/// Read the istream, notify the visitor.
	template <typename... Args>
	void operator()(Args&&... args) {
		return module(args...);
	}

private:
	/// Header and Initialization

	template <typename... Args>
	auto module(Args&&... args) {
		visitor_.moduleStart(args...);
		header(args...);
		sections(args...);
		return visitor_.moduleEnd(args...);
	}

	template <typename... Args>
	auto header(Args&&... args) -> void {
		auto m = magic();
		auto v = version();
		visitor_.header(m, v, args...);
	}

	auto magic() -> std::uint32_t {
		auto magic = uint32();
		if (magic != ModuleHeader::MAGIC) {
			throw InvalidHeader{};
		}
		return magic;
	}

	auto version() -> std::uint32_t {
		auto version = uint32();
		if (version != ModuleHeader::VERSION) {
			throw InvalidHeader{};
		}
		return version;
	}

	/// Misc Section Handling

	template <typename... Args>
	auto sections(Args&&... args) -> void {
		while (!in_.eof()) {
			auto code = sectionCode();
			if (in_.eof()) {
				break;
			}
			section(code, std::forward<Args>(args)...);
		}
	}

	auto sectionCode() -> SectionCode {
		auto n = varuint7();
		return SectionCode(n);
	}

	template <typename... Args>
	auto section(SectionCode code, Args&&...) -> void {
		Section section;
		section.code   = code;
		section.length = varuint32();

		if (section.code == SectionCode::NAME) {
			section.name = string();
		}

		visitor_.sectionStart(section);

		switch (section.code) {
		case SectionCode::TYPE:
			typeSection(section);
			break;
		case SectionCode::IMPORT:
			importSection(section);
			break;
		case SectionCode::NAME:
			customSection(section);
			break;
		case SectionCode::FUNCTION:
			functionSection(section);
			break;
		case SectionCode::TABLE:
			tableSection(section);
			break;
		case SectionCode::MEMORY:
			memorySection(section);
			break;
		case SectionCode::GLOBAL:
			globalSection(section);
			break;
		case SectionCode::EXPORT:
			exportSection(section);
			break;
		case SectionCode::START:
			startSection(section);
			break;
		case SectionCode::ELEMENT:
			elementSection(section);
			break;
		case SectionCode::CODE:
			codeSection(section);
			break;
		case SectionCode::DATA:
			dataSection(section);
			break;
		default:
			throw InvalidSection();
			break;
		}

		visitor_.sectionEnd(section);
	}

	auto resizableLimits(ResizableLimits& out) -> void {
		out.hasMax  = varuint1();
		out.initial = varuint32();
		if (out.hasMax) {
			out.max = varuint32();
		} else {
			out.max = 0;
		}
	}

	/// Read a utf8 string
	/// Strings are represented in the module as a size and an array.
	auto string() -> std::string {
		std::string result;

		auto n = varuint32();
		std::vector<char> buffer;
		buffer.resize(n + 1);
		in_.read(buffer.data(), n);
		buffer[n] = '\0';

		result.reserve(n);
		result = buffer.data();

		return result;
	}

	auto globalType(GlobalType& out) -> void {
		out.contentType = valueType();
		out.isMutable   = varuint1();
	}

	auto tableType(TableType& out) -> void {
		out.elementType = elementType();
		resizableLimits(out.limits);
	}

	auto memoryType(MemoryType& out) -> void {
		resizableLimits(out.limits);
	}

	auto valueType() -> TypeCode {
		return typeCode();
	}

	auto blockType() -> TypeCode {
		return typeCode();
	}

	auto elementType() -> TypeCode {
		return typeCode();
	}

	auto typeCode() -> TypeCode {
		// Note that while typecodes are actually leb128 encoded, we don't convert the
		// constant to it's proper value. We leave the typecodes encoded.
		auto n = uint8();
		return (TypeCode)n;
	}

	/// Read bytes from input to construct an unsigned integer of type Integer.
	/// An example:
	///    uint<std::uint32_t, 3>(); // Read 3 bytes as an LE
	template <typename Integer, std::size_t bytes = sizeof(Integer)>
	auto uint() -> Integer {
		if (in_.fail())
			throw BadNumber();

		Integer result = 0;
		auto buffer    = (char*)&result;
		in_.read(buffer, bytes);
		return result;
	}

	auto uint8() -> std::uint8_t {
		return uint<std::uint8_t>();
	}

	auto uint16() -> std::uint16_t {
		return uint<std::uint16_t>();
	}

	auto uint32() -> std::uint32_t {
		return uint<std::uint32_t>();
	}

	auto uint64() -> std::uint64_t {
		return uint<std::uint64_t>();
	}

	auto leb128() -> std::int64_t {
		return ::Ab::leb128(in_);
	}

	auto varint7() -> std::int64_t {
		return leb128();
	}

	auto varint32() -> std::int64_t {
		return leb128();
	}

	auto varint64() -> std::int64_t {
		return leb128();
	}

	auto uleb128() -> std::uint64_t {
		return ::Ab::uleb128(in_);
	}

	auto varuint1() -> std::uint64_t {
		return uleb128();
	}

	auto varuint7() -> std::uint64_t {
		return uleb128();
	}

	auto varuint32() -> std::uint64_t {
		return uleb128();
	}

	auto importSection(const Section& section) -> void {
		auto count = varuint32();
		visitor_.importSection(count);
		for (std::size_t i = 0; i < count; i++) {
			importEntry();
		}
	}

	auto importEntry() -> void {
		ImportEntry entry;

		entry.module = string();
		entry.field  = string();
		entry.kind   = externalKind();

		switch (entry.kind) {
		case ExternalKindCode::FUNCTION:
			entry.type.function = varuint32();
			break;
		case ExternalKindCode::TABLE:
			tableType(entry.type.table);
			break;
		case ExternalKindCode::MEMORY:
			memoryType(entry.type.memory);
			break;
		case ExternalKindCode::GLOBAL:
			globalType(entry.type.global);
			break;
		default:
			throw ReaderError{"Unknown external kind code"};
			break;
		}

		visitor_.importEntry(entry);
	}

	auto externalKind() -> ExternalKindCode {
		return (ExternalKindCode)uint8();
	}

	auto functionSection(const Section& section) -> void {
		auto count = varuint32();
		for (std::size_t i = 0; i < count; i++) {
			auto type = varuint32();
			visitor_.functionEntry(i, type);
		}
	}

	auto customSection(const Section& section) -> void {
		std::cerr << "Warning: Skipping custom section: " << section.name;
		in_.seekg(section.length, std::ios::cur);
	}

	/// Table Section
	auto tableSection(const Section& section) -> void {
	}

	/// Memory Section
	auto memorySection(const Section& section) -> void {
	}

	/// Global Section
	auto globalSection(const Section& section) -> void {
		auto count = varuint32();
		for (std::size_t i = 0; i < count; i++) {
			globalEntry();
		}
	}

	auto globalEntry() -> void {
		GlobalType type;
		InitExpr expr;

		globalType(type);
		// Ab::debug_out << Ab::freshLine << type;

		initExpr(expr);
		// Ab::debug_out << Ab::freshLine << type;

		visitor_.globalEntry(type, expr);
	};

	/// The type section contains the types of all functions.
	/// Every func
	auto typeSection(const Section& section) -> void {
		auto count = varuint32();
		visitor_.typeSection(count);
		for (std::size_t i = 0; i < count; i++) {
			functionType();
		}
	}

	auto functionType() -> void {
		FunctionType result;
		result.hasReturnType = false;
		result.returnType    = TypeCode::EMPTY;

		auto type = typeCode();

		if (type != TypeCode::FUNC)
			throw ReaderError{"Expected function type, got something else."};

		auto paramCount = varuint32();

		result.paramTypes.resize(paramCount);

		for (std::size_t i = 0; i < paramCount; i++) {
			auto paramType       = valueType();
			result.paramTypes[i] = paramType;
		}

		auto hasReturnType = varuint1();

		if (hasReturnType) {
			auto returnType      = valueType();
			result.hasReturnType = true;
			result.returnType    = returnType;
		}

		visitor_.functionType(result);
	}

	inline auto initExpr(InitExpr& expr) -> void {
		ExprReader reader;
		SetInitExpr setInitExpr;

		ReaderInput input(in_);
		reader(input, std::size_t(0), setInitExpr, expr);  // Read one expression
		reader(input, std::size_t(0), [](AnyExpr&) -> void {
		});  // Read the end expression, and do nothing with it.
	}

	/// Export Section
	inline auto exportSection(const Section& section) -> void {
		std::size_t count = varuint32();
		for (std::size_t i = 0; i < count; i++) {
			exportEntry();
		}
	}

	inline auto exportEntry() -> void {
		ExportEntry entry;
		entry.field = string();
		entry.kind  = externalKind();
		entry.index = varuint32();
		visitor_.exportEntry(entry);
	}

	/// Start Section
	inline auto startSection(const Section& section) -> void {
	}

	/// Element Section

	inline auto elementSection(const Section& section) -> void {
		std::size_t count = varuint32();
		for (std::size_t i = 0; i < count; i++) {
			elementEntry();
		}
	}

	inline auto elementEntry() -> void {
		ElementEntry entry;
		entry.index = varuint32();
		initExpr(entry.offset);
		entry.elementCount = varuint32();
		visitor_.elementEntry(entry);
		for (std::size_t i = 0; i < entry.elementCount; i++) {
			auto index = varuint32();
			visitor_.element(entry, index);
		}
		visitor_.elementEntryEnd(entry);
	}

	/// Code Section
	inline auto codeSection(const Section& section) -> void {
		std::size_t count = varuint32();
		for (std::size_t i = 0; i < count; i++) {
			functionBody(i);
		}
	}

	inline auto functionBody(std::size_t index) -> void {
		FunctionBody body;
		body.size = varuint32();

		ReaderInput in{in_};
		auto localCount = ::Ab::varuint32(in);

		body.locals.resize(localCount);
		for (std::size_t i = 0; i < localCount; i++) {
			body.locals[i] = localEntry(in);
		}

		visitor_.functionBody(index, body, in);

		visitor_.functionBodyEnd(body);
	}

	inline auto localEntry(ReaderInput& in) -> LocalEntry {
		LocalEntry entry;
		entry.count = ::Ab::varuint32(in);
		entry.type  = ::Ab::typeCode(in);  // TODO: Wrong type should be valueType
		return entry;
	}

	/// Data Section

	inline auto dataSection(const Section& section) -> void {
		auto count = varuint32();
		for (std::size_t i = 0; i < count; i++) {
			dataSegment();
		}
	}

	inline auto dataSegment() -> void {
		DataSegment segment;
		segment.index = varuint32();
		initExpr(segment.initExpr);
		auto size = varuint32();
		segment.data.resize(size);
		in_.read(segment.data.data(), size);
		visitor_.dataSegment(segment);
	}

	Visitor& visitor_;
	std::istream& in_;
};

template <typename Visitor>
auto visit(std::istream& in, Visitor& visitor) {
	Reader reader(in, visitor);
	return reader();
}

}  // namespace Wasm
}  // namespace Ab

#endif  // AB_WASM_BINARY_READER_HPP_
