#ifndef AB_WASM_PRINTING_INL_HPP_
#define AB_WASM_PRINTING_INL_HPP_

#include <Ab/Wasm/Printing.hpp>

namespace Ab {
namespace Wasm {

inline auto toString(OpCode op) -> const char* {
	return opDispatch<OpName>(op);
}

inline auto operator<<(std::ostream& out, OpCode code) -> std::ostream& {
	return out << toString(code);
}

inline auto toString(TypeCode code) -> const char* {
	switch (code) {
	case TypeCode::I32:
		return "i32";
	case TypeCode::I64:
		return "i64";
	case TypeCode::F32:
		return "f32";
	case TypeCode::F64:
		return "f64";
	case TypeCode::ANYFUNC:
		return "anyfunc";
	case TypeCode::FUNC:
		return "func";
	case TypeCode::EMPTY:
		return "empty";
	default:
		return "UNKNOWN_TYPECODE";
	}
};

inline auto operator<<(std::ostream& out, TypeCode code) -> std::ostream& {
	return out << toString(code);
}

inline auto toString(SectionCode code) -> const char* {
	switch (code) {
	case SectionCode::NAME:
		return "NAME";
	case SectionCode::TYPE:
		return "TYPE";
	case SectionCode::IMPORT:
		return "IMPORT";
	case SectionCode::FUNCTION:
		return "FUNCTION";
	case SectionCode::TABLE:
		return "TABLE";
	case SectionCode::MEMORY:
		return "MEMORY";
	case SectionCode::GLOBAL:
		return "GLOBAL";
	case SectionCode::EXPORT:
		return "EXPORT";
	case SectionCode::START:
		return "START";
	case SectionCode::ELEMENT:
		return "ELEMENT";
	case SectionCode::CODE:
		return "CODE";
	case SectionCode::DATA:
		return "DATA";
	default:
		return "UNKNOWN_SECTION_CODE";
	}
}

inline auto operator<<(std::ostream& out, SectionCode code) -> std::ostream& {
	return out << toString(code);
}

inline auto operator<<(Ab::SexprPrinter& out, const Section& section) -> Ab::SexprPrinter& {
	out << Ab::sexprStart << "section";
	out << Ab::sexprStart << "code" << section.code << Ab::sexprEnd;

	if (section.code == SectionCode::NAME) {
		out << Ab::sexprStart << "name" << section.name << Ab::sexprEnd;
	}

	out << Ab::sexprStart << "size" << section.length << Ab::sexprEnd;

	out << Ab::sexprEnd;

	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const ResizableLimits& limits)
	-> Ab::SexprPrinter& {
	out << limits.initial;
	if (limits.hasMax) {
		out << limits.max;
	}
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const MemoryType& type) -> Ab::SexprPrinter& {
	out << Ab::sexprStart << "memory" << type.limits << Ab::sexprEnd;
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const TableType& type) -> Ab::SexprPrinter& {
	out << Ab::sexprStart << "table" << type.limits << type.elementType << Ab::sexprEnd;
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const FunctionType& ft) -> Ab::SexprPrinter& {
	out << Ab::freshLine;
	out << Ab::sexprStart;
	out << "func";
	if (ft.paramTypes.size() != 0) {
		out << Ab::sexprStart << "param";
		for (auto pt : ft.paramTypes)
			out << pt;
		out << Ab::sexprEnd;
	}
	if (ft.hasReturnType) {
		out << Ab::sexprStart << "result" << ft.returnType << Ab::sexprEnd;
	}
	out << Ab::sexprEnd;
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const GlobalType& global) -> Ab::SexprPrinter& {
	out << Ab::sexprStart;
	if (global.isMutable) {
		out << "mut";
	}
	out << global.contentType;
	out << Ab::sexprEnd;
	return out;
}

inline auto toString(ExternalKindCode kind) -> const char* {
	switch (kind) {
	case ExternalKindCode::FUNCTION:
		return "func";
	case ExternalKindCode::TABLE:
		return "table";
	case ExternalKindCode::MEMORY:
		return "memory";
	case ExternalKindCode::GLOBAL:
		return "global";
	default:
		return "UNKNOWN_EXTERNAL_KIND_CODE";
	}
}

inline auto operator<<(std::ostream& out, ExternalKindCode kind) -> std::ostream& {
	return out << toString(kind);
}

inline auto operator<<(Ab::SexprPrinter& out, const ExportEntry& entry) -> Ab::SexprPrinter& {
	out << Ab::sexprStart;
	out << "export";
	out << Ab::stringify << entry.field;
	out << Ab::sexprStart << entry.kind << entry.index << Ab::sexprEnd;
	out << Ab::sexprEnd;
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const ImportEntry& entry) -> Ab::SexprPrinter& {
	out << Ab::sexprStart;
	out << "import";
	out << Ab::stringify << entry.module;
	out << Ab::stringify << entry.field;
	out << "(;"
	    << "kind" << (std::uint32_t)entry.kind << ";)";

	switch (entry.kind) {
	case ExternalKindCode::FUNCTION:
		out << Ab::sexprStart << "type" << entry.type.function << Ab::sexprEnd;
		break;
	case ExternalKindCode::TABLE:
		out << entry.type.table;
		break;
	case ExternalKindCode::MEMORY:
		out << entry.type.memory;
		break;
	case ExternalKindCode::GLOBAL:
		out << entry.type.global;
		break;
	default:
		out << "UNKNOWN_EXTERNAL_KIND_CODE";
		break;
	}

	out << Ab::sexprEnd;
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const InitExpr& expr) -> Ab::SexprPrinter& {
	return out << expr.any;
}

inline auto operator<<(Ab::SexprPrinter& out, const LocalEntry& entry) -> Ab::SexprPrinter& {
	for (std::size_t i = 0; i < entry.count; i++) {
		out << entry.type;
	}
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const FunctionBody& body) -> Ab::SexprPrinter& {
	out << Ab::sexprStart << "local" << body.locals.size();
	for (const auto& local : body.locals) {
		out << local;
	}
	out << Ab::sexprEnd;
	return out;
}

inline auto operator<<(Ab::SexprPrinter& out, const DataSegment& segment) -> Ab::SexprPrinter& {
	out << Ab::sexprStart << "data" << segment.initExpr;
	auto raw = out << Ab::rawStart << '\"';
	for (auto c : segment.data) {
		if (c > 32 && c < 127) {
			raw << c;
		} else {
			raw << '\\' << (int)c;
		}
	}
	return raw << '\"' << Ab::rawEnd;
}


struct SexprPrint {
	/// Print to SexprPrinter.
	template <typename Expr>
	auto operator()(const Expr& expr, Ab::SexprPrinter& out) const -> Ab::SexprPrinter& {
		return out << expr;
	}
};

/// Print to std::ostream.
struct Print {
	template <typename T>
	auto operator()(T x, std::ostream& out) const -> std::ostream& {
		return out << x;
	}
};

} // namespace Wasm
} // namespace Ab

#endif // AB_WASM_PRINTING_INL_HPP_
