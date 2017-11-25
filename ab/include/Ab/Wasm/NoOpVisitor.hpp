#ifndef AB_WASM_NOOPVISITOR_HPP_
#define AB_WASM_NOOPVISITOR_HPP_

#include <Ab/Config.hpp>
#include <Ab/Wasm/Visitor.hpp>
#include <Ab/Wasm/Ir.hpp>
#include <Ab/Wasm/OpCode.hpp>
#include <Ab/Wasm/
namespace Ab {
namespace Wasm {

///  The NoOp Visitor
class NoOpVisitor : public Visitor {
public:
	/// Initialization
	virtual ~NoOpVisitor() override {}

	virtual auto moduleStart() -> void override {}

	virtual auto moduleEnd() -> void override {}

	virtual auto header(std::uint32_t magic, std::uint32_t version) -> void override {}

	/// Any section

	virtual auto sectionStart(const Section& section) -> void override {}

	virtual auto sectionEnd(const Section& section) -> void override {}

	/// Type Section

	virtual auto typeSection(std::size_t count) -> void override {}

	virtual auto functionType(const FunctionType& type) -> void override {}

	/// Import Section

	virtual auto importSection(std::size_t count) -> void override {}

	virtual auto importEntry(const ImportEntry& entry) -> void override {}

	/// Function Section

	virtual auto functionSection(std::size_t count) -> void override {}

	virtual auto functionEntry(std::size_t i, std::uint32_t type) -> void override {}

	/// Global Section

	virtual auto globalSection(std::size_t count) -> void override {
	}

	virtual auto globalEntry(const GlobalType& type, const InitExpr& expr) -> void override {
	}

	/// Export Section

	virtual auto exportSection(std::size_t count) -> void override {
	}

	virtual auto exportEntry(const ExportEntry& entry) -> void override {
	}

	/// Element Section

	virtual auto elementSection(std::size_t count) -> void override {
	}

	virtual auto elementEntry(const ElementEntry& entry) -> void override {
	}

	virtual auto element(const ElementEntry& entry, std::uint32_t index) -> void override {
	}

	virtual auto elementEntryEnd(const ElementEntry& entry) -> void override {
	}

	/// Code Section

	virtual auto codeSection(std::size_t count) -> void override {
	}

	virtual auto functionBody(std::size_t index, const FunctionBody& entry, ReaderInput& in)
		-> void override {
	}

	virtual auto functionBodyEnd(const FunctionBody& entry) -> void override {
	}

	/// Custom Section

	/// Data Section

	virtual auto dataSegment(const DataSegment& segment) -> void override {
	}

	// virtual auto customSection(const Section& section) -> void override {}
};

}  // namespace Wasm
}  // namespace Ab

#endif // AB_WASM_NOOPVISITOR_HPP_