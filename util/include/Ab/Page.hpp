#ifndef AB_PAGE_HPP_
#define AB_PAGE_HPP_

#include <Ab/Config.hpp>
#include <Ab/Address.hpp>
#include <Ab/Bytes.hpp>
#include <Ab/Process.hpp>
#include <Ab/Result.hpp>
#include <errno.h>
#include <sys/mman.h>
#include <system_error>
#include <unistd.h>

namespace Ab {

struct PagePermission {
	static const constexpr int execute = PROT_EXEC;
	static const constexpr int write   = PROT_WRITE;
	static const constexpr int read    = PROT_READ;
	static const constexpr int none    = PROT_NONE;
};

struct PageError : public std::runtime_error {
	using std::runtime_error::runtime_error;
};

class Page {
public:
	Page() = delete;

	/// The size of a page. Must be determined at run time.
	static auto size() noexcept -> std::size_t;

	/// Will bring a page into memory, with no permissions.
	static auto map(const std::size_t n, const int permissions = PagePermission::none)
		-> Address;

	/// Will bring a page into memory, with no permissions.
	static auto
	map(const Address address, const std::size_t size,
	    const int permissions = PagePermission::none) -> Address;

	/// Unmap a page from memory.
	/// Returns 0 on success.
	static auto unmap(const Address address, const std::size_t size) -> void;

	static auto
	setPermissions(const Address address, const std::size_t size, const int permissions)
		-> void;
};

inline auto Page::size() noexcept -> std::size_t {
	return Process::properties().pageSize();
}

inline auto Page::map(const std::size_t size, const int permissions) -> Address {
	return map(nullptr, size, permissions);
}

inline auto Page::map(const Address address, const std::size_t size, const int permissions)
	-> Address {
	auto p = mmap(toPointer(address), size, permissions, MAP_ANON | MAP_PRIVATE, 0, 0);

	if (p == nullptr) {
		throw PageError{"Failed to map pages"};
	}

	return static_cast<Address>(p);
}

inline auto Page::unmap(const Address address, const std::size_t size) -> void {
	auto e = munmap(toPointer(address), size);
	if (e != 0) {
		throw PageError{"Failed to unmap pages"};
	}
}

inline auto
Page::setPermissions(const Address address, const std::size_t size, const int permissions) -> void {
	auto e = mprotect(toPointer(address), size, permissions);
	if (e != 0) {
		throw PageError{"Failed to set page permissions"};
	}
}

}  // namespace Ab

#endif  // AB_PAGE_HPP_
