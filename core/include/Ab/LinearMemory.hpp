#ifndef AB_MEMORY_HPP_
#define AB_MEMORY_HPP_

#include <Ab/Address.hpp>
#include <Ab/Assert.hpp>
#include <Ab/Bytes.hpp>
#include <Ab/Page.hpp>
#include <Ab/Result.hpp>
#include <Ab/Span.hpp>
#include <cstdint>

namespace Ab {

class LinearMemoryError : public std::runtime_error {
	using std::runtime_error::runtime_error;
};

struct LinearMemoryConfig {
	Ab::Address address{nullptr};
	std::size_t minPageCount{1};
	std::size_t maxPageCount{4};

	inline auto verify() const -> void {
		if (minPageCount > maxPageCount) {
			throw LinearMemoryError("LinearMemoryConfig validation error: minPageCount greater than max");
		}
	}
};

/// The WASM contiguous raw memory subsystem.
/// web assembly gives programs low level access to a contiguous region of memory.
/// The LinearMemory class manages that giant blob of memory. Per the spec, LinearMemory can be
/// grown, but does not shrink. Each call
class LinearMemory {
public:
	/// The size of a memory page.
	static auto pageSize() -> std::size_t;

	/// Bring up the memory subsystem with the default config.
	LinearMemory();

	/// Bring up the memory subsytem.
	LinearMemory(const LinearMemoryConfig& config);

	~LinearMemory();

	/// The address.
	inline auto addresss() const -> Ab::Address;

	/// The size of the allocated memory.
	inline auto size() const -> std::size_t;

	/// Grow the memory by n pages.
	auto grow(std::size_t n = 1) -> void;

	/// Shrink the memory by n pages.
	auto shrink(std::size_t n = 1) -> void;

	auto config() const noexcept -> const LinearMemoryConfig& { return config_; }

private:
	auto reserve(const Ab::Address address, std::size_t n) -> Ab::Address;

	auto activate(const Ab::Address address, const std::size_t n) -> void;

	auto deactivate(const Ab::Address address, const std::size_t n) -> void;

	auto release(const Ab::Address address, const std::size_t n) -> void;

	Ab::Address address_;
	std::size_t pageCount_;
	const LinearMemoryConfig config_;
};

inline LinearMemory::LinearMemory() : LinearMemory{LinearMemoryConfig{}} {
}

inline LinearMemory::LinearMemory(const LinearMemoryConfig& config)
	: address_{nullptr}, pageCount_{0}, config_{config} {
	config_.verify();
	address_ = reserve(config.address, config.maxPageCount);
	grow(config.minPageCount);
}

inline LinearMemory::~LinearMemory() {
	// TODO: release(address_, reservedPages_);
}

inline auto LinearMemory::grow(std::size_t n) -> void {
	// TODO: worry about overflow / underflow
	if (config_.maxPageCount - pageCount_ < n) {
		throw LinearMemoryError{"Failed to grow, not enough reserved pages."};
	}
	// TODO: Activate new region
}

inline auto LinearMemory::shrink(std::size_t n) -> void {
	if (pageCount_ < n) {
		throw LinearMemoryError{"Failed to shrink: not enough active pages."};
	}
	/// TODO: Deactivate region
}

inline auto LinearMemory::reserve(const Ab::Address address, std::size_t n) -> Ab::Address {
	return Ab::Page::map(address, n);
}
inline auto LinearMemory::activate(const Ab::Address address, const std::size_t n) -> void {
	// activate the memory region by requesting read/write permissions.
	auto permissions = Ab::PagePermission::read | Ab::PagePermission::write;
	Ab::Page::setPermissions(address, n * Ab::Page::size(), permissions);
}

inline auto LinearMemory::deactivate(const Ab::Address address, const std::size_t n) -> void {
	// deactivate the memory region by disabling all permissions. this should hopefully cause
	// the OS to unmap the memory.
	auto permissions = Ab::PagePermission::none;
	Ab::Page::setPermissions(address, n * Ab::Page::size(), permissions);
}

inline auto LinearMemory::release(const Ab::Address address, const std::size_t n) -> void {
	Ab::Page::unmap(address, n * Ab::Page::size());
}

}  // namespace Ab

#endif  // AB_MEMORY_HPP_
