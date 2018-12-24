#ifndef AB_CONTEXT_HPP_
#define AB_CONTEXT_HPP_

#include <Ab/Config.hpp>
#include <Ab/Runtime.hpp>
#include <OMR/Om/Context.hpp>
#include <OMR/Om/MemorySystem.hpp>

namespace Ab {

class System {
public:
	explicit System(Runtime& runtime) : runtime_(runtime), om_(runtime_.om()) {
	}

	System(const System&) = delete;

	System(System&&) = default;

	~System() = default;

	/// Obtain the global runtime this system is attached to.
	Runtime& runtime() const {
		return runtime_;
	}

	/// Obtain the om/gc subsystem.
	OMR::Om::MemorySystem& om() {
		return om_;
	}

	const OMR::Om::MemorySystem& om() const {
		return om_;
	}

private:
	Runtime& runtime_;
	OMR::Om::MemorySystem om_;
};

class Context {
public:
	explicit Context(System& system) : system_(system), om_(system.om()) {
	}

	Context(const Context&) = delete;

	Context(Context&&) = default;

	~Context() = default;

	OMR::Om::RunContext& om() {
		return om_;
	}

	const OMR::Om::RunContext& om() const {
		return om_;
	}

	System& system() const {
		return system_;
	}

private:
	System& system_;
	OMR::Om::RunContext om_;
};

class RunContext : public Context {};

}  // namespace Ab

#endif  // AB_CONTEXT_HPP_
