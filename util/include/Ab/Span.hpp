#ifndef AB_SPAN_HPP_
#define AB_SPAN_HPP_

#include <Ab/Config.hpp>
#include <cstddef>

namespace Ab {

/// A span of memory. Pointer and length pair.
template <typename Type>
class Span {
public:
	// Zeroing constructor.
	inline constexpr Span() : value_{nullptr}, length_{0} {
	}

	/// Full initialization.
	inline constexpr Span(Type* value, std::size_t length) : value_{value}, length_{length} {
	}

	/// Init from pointer. Span has zero length.
	explicit inline constexpr Span(Type* value) : value_{value}, length_{0} {
	}

	/// Init from length. Value is nullptr.
	explicit inline constexpr Span(std::size_t length) : value_{nullptr}, length_{length} {
	}

	/// Assignment from span.
	inline constexpr Span(const Span<Type>& other)
		: value_{other.value()}, length_{other.length()} {
	}

	/// Get the pointer.
	inline constexpr auto operator()() const -> Type* {
		return value_;
	}

	/// Get the pointer.
	inline constexpr auto value() const -> Type* {
		return value_;
	}

	/// Set the pointer value.
	inline auto value(Type* value) -> Span<Type>& {
		value_ = value;
		return *this;
	}

	/// Number of elements in the span.
	inline constexpr auto length() const -> std::size_t {
		return length_;
	}

	/// Set the number of elements in the span.
	inline auto length(std::size_t length) -> Span<Type>& {
		length_ = length;
		return *this;
	}

	/// The last instance of Type in this Span.
	inline auto end() -> Type* {
		return value_ + (length_ - 1);
	}

	/// Size of the referred span. Equal to sizeof(T)*length.
	inline constexpr auto size() const -> std::size_t {
		return length() * sizeof(Type);
	}

	inline auto operator=(Span<Type>& rhs) -> Span<Type>& {
		value_  = rhs.value();
		length_ = rhs.length();
		return *this;
	}

	inline constexpr auto operator==(const Span<Type>& rhs) const -> bool {
		return (value() == rhs.value()) && (length() == rhs.length());
	}

	inline constexpr auto operator!=(const Span<Type>& rhs) const -> bool {
		return (value() != rhs.value()) || (length() != rhs.length());
	}

	/// True if this entire Span is lower in memory than the rhs. False if the spans overlap.
	inline constexpr auto operator<(const Span<Type>& rhs) const -> bool {
		return (value() + length()) < rhs.value();
	}

	/// True if this entire Span is higher in memory than the rhs. False if the spans overlap.
	inline constexpr auto operator>(const Span<Type>& rhs) const -> bool {
		return value() > rhs.end();
	}

	/// True if the end of this Span is lower than or equal to the end of .
	inline constexpr auto operator<=(const Span<Type>& rhs) const -> bool {
		return end() <= rhs.end();
	}

	/// True if the end of this Span is higher than or equal to the end of the rhs.
	inline constexpr auto operator>=(const Span<Type>& rhs) const -> bool {
		return end() >= rhs.end();
	}

protected:
	Type* value_;
	std::size_t length_;
};

}  // namespace Ab

#endif  // AB_SPAN_HPP_
