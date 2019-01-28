#if !defined AB_PTRLIKE_HPP_
#define AB_PTRLIKE_HPP_

#include <Ab/StaticPoly.hpp>
#include <type_traits>

namespace Ab {

template <typename DerivedT, T>
class PtrLike : StaticPoly<PtrLike, DerivedT> {
public:
	template <typename U = T, typename = typename std::enable_if_t<!std::is_void_v<U>>>
	constexpr U& operator*() const {
		return self()->get();
	}

	template <typename U = T, typename = typename std::enable_if_t<!std::is_void_v<U>>>
	constexpr U* operator->() const {
		return self()->get();
	}
};

}  // namespace Ab

#endif // AB_PTRLIKE_HPP_
