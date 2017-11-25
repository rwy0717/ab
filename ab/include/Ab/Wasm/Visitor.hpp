#ifndef AB_WASM_BINARY_VISITOR_HPP_
#define AB_WASM_BINARY_VISITOR_HPP_

#include <Ab/Wasm/Expression.hpp>
#include <Ab/Wasm/Ir.hpp>
#include <Ab/Wasm/Section.hpp>
#include <Ab/leb128.hpp>
#include <Pith/SexprPrinter.hpp>
#include <cstddef>
#include <cstdint>
#include <memory>

namespace Ab {
namespace Wasm {

struct FunctionType;

///  The Pure-virtual base class. See also: the No-Op base visitor.
class Visitor {
public:
	virtual ~Visitor() noexcept {}

	// Initialization

	virtual auto moduleStart() -> void = 0;

	virtual auto moduleEnd() -> void = 0;

	virtual auto header(::std::uint32_t magic, ::std::uint32_t version) -> void = 0;

	/// The beginning of any section
	virtual auto sectionStart(const Section& section) -> void = 0;

	virtual auto sectionEnd(const Section& section) -> void = 0;

	/// Type Section

	virtual auto typeSection(std::size_t count) -> void = 0;

	virtual auto functionType(const FunctionType& type) -> void = 0;

	/// Import Section

	virtual auto importSection(std::size_t count) -> void = 0;

	virtual auto importEntry(const ImportEntry& entry) -> void = 0;

	/// Function Section

	virtual auto functionSection(std::size_t count) -> void = 0;

	virtual auto functionEntry(std::size_t i, std::uint32_t type) -> void = 0;

	/// Global Sectopm

	virtual auto globalSection(std::size_t count) -> void = 0;

	virtual auto globalEntry(const GlobalType& type, const InitExpr& expr) -> void = 0;

	/// Export Section

	virtual auto exportSection(std::size_t count) -> void = 0;

	virtual auto exportEntry(const ExportEntry& entry) -> void = 0;

	/// Element Section

	virtual auto elementSection(std::size_t count) -> void = 0;

	virtual auto elementEntry(const ElementEntry& entry) -> void = 0;

	virtual auto element(const ElementEntry& entry, std::uint32_t index) -> void = 0;

	virtual auto elementEntryEnd(const ElementEntry& entry) -> void = 0;

	/// Code Section

	virtual auto codeSection(std::size_t count) -> void = 0;

	/// This is a weird part of the code. The function body parsing works very differently from
	/// the main parser. For now, we hand off the input to the visitor. The visitor can bring up
	/// it's own function parser and do whatever. The visitor must read to the end of the
	/// function. This is a temporary way of life.
	virtual auto functionBody(std::size_t index, const FunctionBody& entry, ReaderInput& in)
		-> void = 0;

	virtual auto functionBodyEnd(const FunctionBody& entry) -> void = 0;

	/// Data Section

	virtual auto dataSegment(const DataSegment& segment) -> void = 0;
};

} // namespace Wasm
} // namespace Ab

#endif  // AB_WASM_BINARY_VISITOR_HPP_
