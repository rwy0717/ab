#ifndef AB_WASM_EXPRREADER_INL_HPP_
#define AB_WASM_EXPRREADER_INL_HPP_

#include <Ab/Wasm/ExprReader.hpp>

namespace Ab {
namespace Wasm {

template <typename Function, typename... Args>
inline auto ExprReader::
operator()(ReaderInput& in, std::size_t size, Function&& function, Args&&... args) -> void {
	OpCode op = OpCode::END;
	do {
		op = (OpCode)in.get();
		opDispatch<ReadExpr>(op, in, function, std::forward<Args>(args)...);
	} while (in.offset() < size);
}

} // namespace Wasm
} // namespace Ab

#endif // AB_WASM_EXPRREADER_INL_HPP_
