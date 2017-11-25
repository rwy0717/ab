#ifndef AB_WASM_BINARY_IR_HPP_
#define AB_WASM_BINARY_IR_HPP_

#include <Ab/Config.hpp>
#include <Ab/Wasm/OpCode.hpp>
#include <Ab/Wasm/Section.hpp>
#include <Ab/Wasm/TypeCode.hpp>
#include <cstdint>
#include <string>
#include <vector>

// https://github.com/WebAssembly/spec/tree/master/interpreter/#s-expression-syntax

namespace Ab {
namespace Wasm {

struct ModuleHeader {
	/// The magic constant at the beginning of every module.
	/// in LE, it's also the char array "\0asm".
	static constexpr std::uint32_t MAGIC = 0x6d736100;

	/// The WASM version. We only support 1.
	static constexpr std::uint32_t VERSION = 0x1;

	std::uint32_t magic;
	std::uint32_t version;
};

struct FunctionType {
	std::vector<TypeCode> paramTypes;
	bool hasReturnType;
	TypeCode returnType;
};

struct GlobalType {
	TypeCode contentType;
	bool isMutable;
};

struct ResizableLimits {
	std::uint32_t initial;
	std::uint32_t max;
	bool hasMax;
};

struct MemoryType {
	ResizableLimits limits;
};

struct TableType {
	TypeCode elementType;
	ResizableLimits limits;
};

enum class ExternalKindCode : std::uint8_t { FUNCTION = 0, TABLE = 1, MEMORY = 2, GLOBAL = 3 };

struct ImportEntry {
	std::string module;
	std::string field;
	ExternalKindCode kind;
	union ImportEntryType {
		std::uint32_t function;
		GlobalType global;
		TableType table;
		MemoryType memory;
	} type;
};

struct ExportEntry {
	std::string field;
	ExternalKindCode kind;
	std::uint32_t index;
};

union InitExpr {
	InitExpr() : any(OpCode::UNREACHABLE) {
	}
	union {
		AnyExpr any;
		GetGlobalExpr getGlobal;
		I32ConstExpr i32Const;
		I64ConstExpr i64Const;
		F32ConstExpr f32Const;
		F64ConstExpr f64Const;
	};
};

struct ElementEntry {
	std::uint32_t index;
	InitExpr offset;
	std::uint32_t elementCount;
};

struct LocalEntry {
	std::uint32_t count;
	TypeCode type;
};

struct FunctionBody {
	std::vector<LocalEntry> locals;
	std::uint32_t size;
};


struct DataSegment {
	std::uint32_t index;
	InitExpr initExpr;
	std::vector<char> data;
};

}  // namespace Wasm
}  // namespace Ab

#include <Ab/Wasm/Ir.inl.hpp>

#endif  // AB_WASM_BINARY_IR_HPP_
