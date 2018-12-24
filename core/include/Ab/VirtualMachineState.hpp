#ifndef AB_VIRTUALMACHINESTATE_HPP_
#define AB_VIRTUALMACHINESTATE_HPP_

#include <omr/compiler/ilgen/VirtualMachineState.hpp>

namespace Ab {

class VirtualMachineState : public OMR::VirtualMachineState {
public:
	inline virtual auto Commit(TR::IlBuilder* b) override -> void;

	inline virtual auto Reload(TR::IlBuilder* b) override -> void;

	inline virtual auto MakeCopy() override -> OMR::VirtualMachineState*;

	inline virtual auto MergeInto(OMR::VirtualMachineState* other, TR::IlBuilder* b) -> void;

private:
};

auto VirtualMachineState Commit(TR::IlBuilder* b) -> void {
	AB_TRACE();
}

inline virtual auto Reload(TR::IlBuilder* b) override -> void {
	AB_TRACE();
}

inline virtual auto MakeCopy() override -> OMR::VirtualMachineState* {
	AB_TRACE();
}

inline virtual auto MergeInto(OMR::VirtualMachineState* other, TR::IlBuilder* b) -> void {
	AB_TRACE();
}


}  // namespace Ab

#endif  // AB_VIRTUALMACHINESTATE_HPP_
