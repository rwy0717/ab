#ifndef AB_WASM_BINARY_EXPRESSION_INL_HPP_
#define AB_WASM_BINARY_EXPRESSION_INL_HPP_

#include <Ab/Wasm/Expression.hpp>

namespace Ab {
namespace Wasm {

inline AnyExpr::AnyExpr(OpCode op) : op_(op) {
}

inline auto AnyExpr::op() const -> OpCode {
	return op_;
}

inline auto AnyExpr::op(OpCode op) -> AnyExpr& {
	op_ = op;
	return *this;
}

}  // namespace Wasm
}  // namespace Ab

#endif  // AB_WASM_BINARY_EXPRESSION_INL_HPP_
