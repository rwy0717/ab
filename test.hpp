#ifndef AB_WASM_OPCODE_HPP_
#define AB_WASM_OPCODE_HPP_

#include <cstddef>
#include <cstdint>
#include <ostream>

namespace Ab {
namespace Wasm {

using RawOpCode = std::uint8_t;

enum class OpCode : RawOpCode {
	/// Trap immediately
	UNREACHABLE = 0,

	/// no operation
	NOP = 1,

	/// begin a sequence of expressions, yielding 0 or 1 values
	BLOCK = 2
};

}  // namespace Wasm
}  // namespace Ab

#endif  // AB_WASM_BYTECODE_HPP_
