#include <gtest/gtest.h>

#include <Ab/InternalOpCode.hpp>
#include <Ab/InternalFunctionBuilder.hpp>

namespace Ab {

TEST(InternalFunctionBuilder, EmptyFunction) {
	InternalFunctionBuilder func;

	func.emit_nop();
	func.emit_nop();
}

}  // namespace Ab
