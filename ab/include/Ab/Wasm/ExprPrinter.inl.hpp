#ifndef AB_WASM_EXPRPRINTER_INL_HPP_
#define AB_WASM_EXPRPRINTER_INL_HPP_

#include <Ab/Wasm/ExprPrinter.hpp>

namespace Ab {
namespace Wasm {

inline auto operator<<(Pith::SexprPrinter& out, const AnyExpr& any) -> Pith::SexprPrinter& {
	return exprDispatch(any, SexprPrint(), out);
}

inline auto operator<<(Pith::SexprPrinter& out, const BranchTableImmediate::Value& imm)
	-> Pith::SexprPrinter& {
	out << "default" << imm.defaultTarget;
	for (const auto& target : imm.targetTable) {
		return out << target;
	}
	return out;
}

inline auto operator<<(Pith::SexprPrinter& out, const MemoryImmediate::Value& immediate)
	-> Pith::SexprPrinter& {
	out << immediate.flags << immediate.offset;
	return out;
}

template <OpCode op>
inline auto operator<<(std::ostream& out, const Expr<op>& expr) -> std::ostream& {
	return out << OP_NAME<op>;
}

template <OpCode op>
inline auto operator<<(Pith::SexprPrinter& out, const NullaryExpr<op>& expr)
	-> Pith::SexprPrinter& {
	return out << OP_NAME<op>;
}


template <OpCode op, typename Immediate>
inline auto operator<<(Pith::SexprPrinter& out, const UnaryExpr<op, Immediate>& expr)
	-> Pith::SexprPrinter& {
	return out << OP_NAME<op> << expr.immediate();
}

template <typename Expr>
inline auto PrintOp::operator()(const Expr& x, std::ostream& out) const -> std::ostream& {
	return out << OP_NAME<Expr::OP_CODE>;
}

inline ExprPrinter::ExprPrinter(Pith::SexprPrinter& out) : out_(out), blockDepth_(0) {
}

template <typename Expr>
inline auto ExprPrinter::operator()(const Expr& e) -> void {
	out_ << Pith::freshLine << e;
}

template <>
inline auto ExprPrinter::operator()(const IfExpr& e) -> void {
	out_ << Pith::freshLine << e;
	++out_.indent();
	++blockDepth_;
}

template <>
inline auto ExprPrinter::operator()(const BlockExpr& e) -> void {

	/// Crappy inline validator.
	switch(e.immediate()) {
	case TypeCode::I32:
	case TypeCode::I64:
	case TypeCode::F32:
	case TypeCode::F64:
	case TypeCode::ANYFUNC:
	case TypeCode::FUNC:
	case TypeCode::EMPTY:
		break;
	default:
		throw std::runtime_error{"Bad typecode"};
	}
	out_ << Pith::freshLine << e;
	++out_.indent();
	++blockDepth_;
}

template <>
inline auto ExprPrinter::operator()(const LoopExpr& e) -> void {
	out_ << Pith::freshLine << e;
	++out_.indent();
	++blockDepth_;
}

template <>
inline auto ExprPrinter::operator()(const EndExpr& e) -> void {
	if (blockDepth_ > 0) {
		--out_.indent();
		--blockDepth_;
	}
	out_ << Pith::freshLine << e;
}

template <>
inline auto ExprPrinter::operator()(const ElseExpr& e) -> void {
	--out_.indent();
	out_ << Pith::freshLine << e;
	++out_.indent();
}

}  // namespace Wasm
}  // namespace Ab

#endif // AB_WASM_EXPRPRINTER_INL_HPP_
