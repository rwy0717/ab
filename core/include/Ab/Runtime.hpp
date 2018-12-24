#ifndef AB_RUNTIME_HPP_
#define AB_RUNTIME_HPP_

#include <OMR/Om/Runtime.hpp>

namespace Ab {

/// Global init and shutdown.
/// Process-wide! Thread unsafe!
class Runtime {
public:
	bool initialized() const {
		return om().initialized();
	}

	int init() {
		return om().init();
	}

	void kill() noexcept {
		return om().kill();
	}

	OMR::Om::Runtime& om() { return om_; }

	const OMR::Om::Runtime& om() const { return om_; }

private:
	OMR::Om::Runtime om_;
};

class AutoRuntime : public Runtime {
public:
	AutoRuntime() {
		auto e = init();
		if (e) throw std::exception();
	}

	~AutoRuntime() {
		kill();
	}
};

}  // namespace Ab

#endif  // AB_RUNTIME_HPP_
