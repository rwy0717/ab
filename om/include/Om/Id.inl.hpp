#ifndef OM_ID_INL_HPP_
#define OM_ID_INL_HPP_

#include <Om/Id.hpp>

namespace Om {

inline constexpr Id::Id() noexcept : value_{0} {
}

inline constexpr Id::Id(RawId value) noexcept : value_{value} {
}

inline constexpr auto value() const noexcept -> RawId {
	return value_;
}

inline constexpr auto raw() const noexcept -> RawId {
	return value_;
}

inline constexpr auto raw(RawId raw) noexcept -> Id& {
	value_ = raw;
	return *this;
}

inline constexpr auto Id::operator==(const Id& other) const noexcept -> bool {
	return value_ == other.value_;
}

inline constexpr auto Id::operator!=(const Id& other) const noexcept -> bool {
	return value_ != other.value_;
}

}  // namespace Om

#endif  // OM_ID_INL_HPP_
