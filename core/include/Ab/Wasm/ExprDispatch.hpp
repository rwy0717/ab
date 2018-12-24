#ifndef AB_WASM_EXPRDISPATCH_HPP_
#define AB_WASM_EXPRDISPATCH_HPP_

#include <Ab/Config.hpp>
#include <Ab/Wasm/Expression.hpp>

namespace Ab {
namespace Wasm {

/// A functor that will cast the AnyExpr to a concrete expression type, and call function(expr,
/// args...);
//// The expression type is obtained as OpTraits<Op>::Expr.
template <OpCode op>
struct ExprCastDispatch {
	///
	template <typename Function, typename... Args>
	decltype(auto) operator()(Function&& function, AnyExpr& expr, Args&&... args) {
		using Expr = typename OpTraits<op>::ExprType;
		return function(static_cast<Expr&>(expr), std::forward<Args>(args)...);
	}

	template <typename Function, typename... Args>
	decltype(auto) operator()(Function&& function, const AnyExpr& expr, Args&&... args) {
		using Expr = typename OpTraits<op>::ExprType;
		return function(static_cast<const Expr&>(expr), std::forward<Args>(args)...);
	}
};

/// Apply a function to an expression.
/// This function will downcast the AnyExpr to the concrete expression type, calling function on it.
/// The dispatcher will look at the opcode, and dispatch to the function.
/// This dispatch function performs run-time dispatching. For generating switch statements, or your
/// own runtime dispatch, see opDispatch.
template <typename Function, typename... Args>
decltype(auto) exprDispatch(AnyExpr& expr, Function&& function, Args&&... args) {
	return opDispatch<ExprCastDispatch>(
		expr.op(), std::forward<Function>(function), expr, std::forward<Args>(args)...);
}

template <typename Function, typename... Args>
decltype(auto) exprDispatch(const AnyExpr& expr, Function&& function, Args&&... args) {
	return opDispatch<ExprCastDispatch>(
		expr.op(), std::forward<Function>(function), expr, std::forward<Args>(args)...);
}

}  // namespace Wasm
}  // namespace Ab

#endif  // AB_WASM_EXPRDISPATCH_HPP_
