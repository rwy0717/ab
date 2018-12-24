#ifndef AB_ADDRESS_HPP_
#define AB_ADDRESS_HPP_

#include <Ab/Config.hpp>
#include <cstdint>

namespace Ab {

using Byte    = std::uint8_t;
using Address = const Byte*;

template <typename T = void>
inline constexpr T* toPointer(const Address address) {
	return (T*)(address);
}

}  // namespace Ab

#endif  // AB_ADDRESS_HPP_
