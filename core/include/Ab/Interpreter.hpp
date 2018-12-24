#ifndef AB_INTERPRETER_HPP_
#define AB_INTERPRETER_HPP_

#include <Ab/Config.hpp>
#include <Ab/Instruction.hpp>
#include <Ab/Assert.hpp>
#include <iostream>

namespace Ab {

enum class Operator {

};

struct InterpreterState {
public:
	Instruction* program_;
	uintptr_t* stack_;
	std::size_t pc_;
	std::uint8_t* stackPointer_;
	std::uint8_t* basePointer_;
	bool trap_;
};

struct Frame {
public:
	InterpreterState state_;
};

class Stack {};

class Interpreter {
public:
	auto inline operator()(InterpreterState& state) -> void;

private:
	auto next(InterpreterState& state) -> Instruction;
};

auto Interpreter::next(InterpreterState& state) -> Instruction {
	return state.program_[state.pc_];
}

auto Interpreter::operator()(InterpreterState& state) -> void {
	auto instruction = next(state);
	switch (instruction) {
	case Instruction::UNREACHABLE:
		AB_ASSERT_UNREACHABLE();
		break;
	case Instruction::NOP:
		break;
	};
	state.pc_ += 1;
}

}  // namespace Ab

#endif  // AB_INTERPRETER_HPP_
