#ifndef AB_PROCESS_HPP_
#define AB_PROCESS_HPP_

#include <Ab/Config.hpp>
#include <cstdlib>
#include <unistd.h>

namespace Ab {

struct SystemProperties {
public:
	auto init() -> void;

	/// The memory page size.
	auto pageSize() const noexcept -> std::size_t;

private:
	std::size_t pageSize_;
};

/// Global init and shutdown. Process-wide! Thread unsafe!
class Process {
public:
	/// Process-wide initialization. Must be the first pith call.
	static inline auto init() -> void;

	/// Process-wide tear down. Must be the last pith call made.
	static inline auto kill() -> void;

	/// Obtain the invariant properties of the process.
	static inline auto properties() noexcept -> const SystemProperties&;

	/// True if init() has been called.
	static inline auto initialized() noexcept -> bool;

private:
	static bool initialized_;
	static SystemProperties properties_;
};

inline auto SystemProperties::init() -> void {
	pageSize_ = sysconf(_SC_PAGESIZE);
}

inline auto SystemProperties::pageSize() const noexcept -> std::size_t {
	return pageSize_;
}

inline auto Process::init() -> void {
	properties_.init();
	initialized_ = true;
}

inline auto Process::kill() -> void {
	initialized_ = false;
}

inline auto Process::initialized() noexcept -> bool {
	return initialized_;
}

inline auto Process::properties() noexcept -> const SystemProperties& {
	return properties_;
}

}  // namespace Ab

#endif  // AB_PROCESS_HPP_
