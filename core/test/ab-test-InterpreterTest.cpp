#include <Ab/Config.hpp>
#include "Ab/Test/BasicTest.hpp"
#include <Ab/Instruction.hpp>
#include <Ab/Interpreter.hpp>
#include <gtest/gtest.h>

namespace Ab {
namespace Test {

class TestInterpreter : public BasicTest {};


class ModuleBuidlder {

};

class FunctionBuilder {

};

class TypeBuilder {
};


TEST_F(TestInterpreter, basic) {

    EXPECT_TRUE(runtime.initialized());

    ModuleBuilder mb;

    auto type = mb.fntype({}, Wasm::Uint32);

    auto& fb = mb.createFunction(type);

    fb.instructions
        << {
            push_int(1),
            push_int(2),
            add(),
            ret()
        };

    Module module = module.finalize();

    Wasm::Uint32 value = runtime.execute(module);

    EXPECT_EQ(value, 3);
}

}  // namespace Test
}  // namespace Ab
