#ifndef OM_ID_HPP_
#define OM_ID_HPP_

#include <Om/Config.hpp>
#include <cstdint>

namespace Om {

using RawId = std::uintptr_t;

enum IdKind : RawId { CELL, IMMEDIATE, SYMBOL };

/// A unique identifier for any value.
/// NOT GC Safe. Not safe to hold across some Map mutations which change the Id.
class Id {
public:
	inline constexpr explicit Id() noexcept;

	inline constexpr explicit Id(RawId value) noexcept;

	inline constexpr explicit Id(RawId value, IdKind kind) noexcept;

	inline constexpr auto value() const noexcept -> RawId;

	inline constexpr auto kind() const noexcept -> IdKind;

	inline constexpr auto raw() const noexcept -> RawId;

	inline constexpr auto raw(RawId raw) noexcept -> Id&;

	inline constexpr auto operator==(const Id& other) const noexcept -> bool;

	inline constexpr auto operator!=(const Id& other) const noexcept -> bool;

private:
	RawId value_;
};

}  // namespace Om

#include <Om/Id.inl.hpp>

#endif  // OM_ID_HPP_
