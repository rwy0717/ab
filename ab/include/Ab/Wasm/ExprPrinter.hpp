#ifndef AB_WASM_EXPRPRINTER_HPP_
#define AB_WASM_EXPRPRINTER_HPP_

#include <Ab/Config.hpp>
#include <Ab/Wasm/Expression.hpp>
#include <Ab/Wasm/ExprDispatch.hpp>
#include <Ab/Wasm/Printing.hpp>
#include <Pith/SexprPrinter.hpp>

namespace Ab {
namespace Wasm {

inline auto operator<<(Pith::SexprPrinter& out, const AnyExpr& any) -> Pith::SexprPrinter&;

inline auto operator<<(Pith::SexprPrinter& out, const BranchTableImmediate::Value& imm)
	-> Pith::SexprPrinter&;

inline auto operator<<(Pith::SexprPrinter& out, const MemoryImmediate::Value& immediate)
	-> Pith::SexprPrinter&;

template <OpCode op>
inline auto operator<<(std::ostream& out, const Expr<op>& expr) -> std::ostream&;

template <OpCode op>
inline auto operator<<(Pith::SexprPrinter& out, const NullaryExpr<op>& expr)
	-> Pith::SexprPrinter&;


template <OpCode op, typename Immediate>
inline auto operator<<(Pith::SexprPrinter& out, const UnaryExpr<op, Immediate>& expr)
	-> Pith::SexprPrinter&;

/// Print to std::ostream.
struct PrintOp {
	template <typename Expr>
	auto operator()(const Expr& x, std::ostream& out) const -> std::ostream&;
};

/// A WASM expression printer.
class ExprPrinter {
public:
	inline ExprPrinter(Pith::SexprPrinter& out);

	/// Accepts any expr type, and prints it.
	template <typename Expr>
	inline auto operator()(const Expr& e) -> void;

private:
	Pith::SexprPrinter& out_;
	std::size_t blockDepth_;
};

} // namespace Wasm
} // namespace Ab

#include <Ab/Wasm/ExprPrinter.inl.hpp>

#endif // AB_WASM_EXPRPRINTER_HPP_
