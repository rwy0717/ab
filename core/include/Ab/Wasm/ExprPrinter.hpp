#ifndef AB_WASM_EXPRPRINTER_HPP_
#define AB_WASM_EXPRPRINTER_HPP_

#include <Ab/Config.hpp>
#include <Ab/SexprPrinter.hpp>
#include <Ab/Wasm/ExprDispatch.hpp>
#include <Ab/Wasm/Expression.hpp>
#include <Ab/Wasm/Printing.hpp>

namespace Ab {
namespace Wasm {

inline auto operator<<(Ab::SexprPrinter& out, const AnyExpr& any) -> Ab::SexprPrinter&;

inline auto operator<<(Ab::SexprPrinter& out, const BranchTableImmediate::Value& imm)
	-> Ab::SexprPrinter&;

inline auto operator<<(Ab::SexprPrinter& out, const MemoryImmediate::Value& immediate)
	-> Ab::SexprPrinter&;

template <OpCode op>
inline auto operator<<(std::ostream& out, const Expr<op>& expr) -> std::ostream&;

template <OpCode op>
inline auto operator<<(Ab::SexprPrinter& out, const NullaryExpr<op>& expr) -> Ab::SexprPrinter&;

template <OpCode op, typename Immediate>
inline auto operator<<(Ab::SexprPrinter& out, const UnaryExpr<op, Immediate>& expr)
	-> Ab::SexprPrinter&;

/// Print to std::ostream.
struct PrintOp {
	template <typename Expr>
	auto operator()(const Expr& x, std::ostream& out) const -> std::ostream& {
		return out << OP_NAME<Expr::OP_CODE>;
	}
};

/// A WASM expression printer.
class ExprPrinter {
public:
	ExprPrinter(Ab::SexprPrinter& out) : out_(out), blockDepth_(0) {}

	/// Accepts any expr type, and prints it.
	template <typename Expr>
	auto operator()(const Expr& e) -> void {
		out_ << Ab::freshLine << e;
	}

	auto operator()(const IfExpr& e) -> void {
		out_ << Ab::freshLine << e;
		++out_.indent();
		++blockDepth_;
	}

	auto operator()(const BlockExpr& e) -> void {
		/// Crappy inline validator.
		switch (e.immediate()) {
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
		out_ << Ab::freshLine << e;
		++out_.indent();
		++blockDepth_;
	}

	auto operator()(const LoopExpr& e) -> void {
		out_ << Ab::freshLine << e;
		++out_.indent();
		++blockDepth_;
	}

	auto operator()(const EndExpr& e) -> void {
		if (blockDepth_ > 0) {
			--out_.indent();
			--blockDepth_;
		}
		out_ << Ab::freshLine << e;
	}

	auto operator()(const ElseExpr& e) -> void {
		--out_.indent();
		out_ << Ab::freshLine << e;
		++out_.indent();
	}

private:
	Ab::SexprPrinter& out_;
	std::size_t blockDepth_;
};

inline auto operator<<(Ab::SexprPrinter& out, const AnyExpr& any) -> Ab::SexprPrinter& {
	SexprPrint print;
	exprDispatch(any, print, out);
	return out; // todo: should be able to return exprDispatch, but return type inference is busted.
}

inline auto operator<<(Ab::SexprPrinter& out, const BranchTableImmediate::Value& imm)
	-> Ab::SexprPrinter& {
	out << "default" << imm.defaultTarget;
	for (const auto& target : imm.targetTable) {
		return out << target;
	}
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const MemoryImmediate::Value& immediate)
	-> Ab::SexprPrinter& {
	out << immediate.flags << immediate.offset;
	return out;
}

template <OpCode op>
inline auto operator<<(std::ostream& out, const Expr<op>& expr) -> std::ostream& {
	return out << OP_NAME<op>;
}

template <OpCode op>
inline auto operator<<(Ab::SexprPrinter& out, const NullaryExpr<op>& expr) -> Ab::SexprPrinter& {
	return out << OP_NAME<op>;
}

template <OpCode op, typename Immediate>
inline auto operator<<(Ab::SexprPrinter& out, const UnaryExpr<op, Immediate>& expr)
	-> Ab::SexprPrinter& {
	return out << OP_NAME<op> << expr.immediate();
}

}  // namespace Wasm
}  // namespace Ab

#endif  // AB_WASM_EXPRPRINTER_HPP_
