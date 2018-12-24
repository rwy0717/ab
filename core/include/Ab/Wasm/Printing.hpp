#ifndef AB_WASM_PRINTING_HPP_
#define AB_WASM_PRINTING_HPP_

#include <Ab/Config.hpp>
#include <Ab/Wasm/Expression.hpp>
#include <Ab/Wasm/Ir.hpp>
#include <Ab/Wasm/OpCode.hpp>
#include <Ab/SexprPrinter.hpp>

// https://github.com/WebAssembly/spec/tree/master/interpreter/#s-expression-syntax

namespace Ab {
namespace Wasm {

/// OpCode

inline auto toString(OpCode op) -> const char*;

inline auto operator<<(std::ostream& out, OpCode code) -> std::ostream&;

/// Expression

/// Print an expression. This will use the OpCode and opDispatch to cast itself to the accurate
/// expression before printing.
inline auto operator<<(Ab::SexprPrinter& out, const AnyExpr& any) -> Ab::SexprPrinter&;

inline auto operator<<(std::ostream& out, ExternalKindCode kind) -> std::ostream&;

inline auto operator<<(Ab::SexprPrinter& out, const ImportEntry& entry) -> Ab::SexprPrinter&;

inline auto operator<<(Ab::SexprPrinter& out, const ExportEntry& entry) -> Ab::SexprPrinter&;

inline auto operator<<(Ab::SexprPrinter& out, const GlobalType& global) -> Ab::SexprPrinter&;

inline auto operator<<(Ab::SexprPrinter& out, const FunctionType& ft) -> Ab::SexprPrinter&;

}  // namespace Wasm
}  // namespace Ab

#include <Ab/Wasm/Printing.inl.hpp>

#endif  // AB_WASM_PRINTING_HPP_
