#ifndef OM_VALUE_HPP_
#define OM_VALUE_HPP_

#include <Om/Config.hpp>
#include <Pith/Address.hpp>
#include <cstdint>

namespace Om {

enum class ValueTag : std::uint8_t {
	REF,
	SYMBOL,
	CONSTANT
#if 0
    JSVAL_TYPE_DOUBLE              = 0x00,
    JSVAL_TYPE_INT32               = 0x01,
    JSVAL_TYPE_UNDEFINED           = 0x02,
    JSVAL_TYPE_NULL                = 0x03,
    JSVAL_TYPE_BOOLEAN             = 0x04,
    JSVAL_TYPE_MAGIC               = 0x05,
    JSVAL_TYPE_STRING              = 0x06,
    JSVAL_TYPE_SYMBOL              = 0x07,
    JSVAL_TYPE_PRIVATE_GCTHING     = 0x08,
    JSVAL_TYPE_OBJECT              = 0x0c,

    /* These never appear in a jsval; they are only provided as an out-of-band value. */
    JSVAL_TYPE_UNKNOWN             = 0x20,
    JSVAL_TYPE_MISSING             = 0x21
#endif
};

/// A single-slot value. Pointer width.
/// https://wingolog.org/archives/2011/05/18/value-representation-in-javascript-implementations
/// https://dxr.mozilla.org/mozilla-central/source/js/public/Value.h
/// NaN boxed values

/// 00 00 00 00 00 00 00 00
///  |  |  |  |  |  |  |  | low tag
///                    | value
class Value {
public:
	constexpr inline Value();

	constexpr inline Value(Pith::Address addr);

	/// Cast this to Type.
	template <typename Type>
	constexpr auto to() const -> Type const;

private:
	static constexpr std::uintptr_t VALUE_MASK = 0x00007FFFFFFFFFFF;
	static constexpr std::uintptr_t TAG_MASK   = ~VALUE_MASK;

	std::uintptr_t value_{0};
};

}  // namespace Om

#include <Om/Value.inl.hpp>

#endif  // OM_VALUE_HPP_
