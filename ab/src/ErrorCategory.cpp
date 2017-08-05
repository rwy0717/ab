#include <Ab/Error.hpp>
#include <Ab/ErrorCategory.hpp>

namespace Ab {

auto ErrorCategory::name() const noexcept -> const char* {
	return name_;
}

auto ErrorCategory::message(int code) const noexcept -> std::string {
	auto e = static_cast<Error>(code);
	switch (e) {
		case Error::NONE: return "none";
		case Error::FAIL: return "fail";
	}
}

const ErrorCategory ERROR_CATEGORY;

} // namespace Ab
