#if !defined(AB_STATICPOLY_HPP_)
#define AB_STATICPOLY_HPP_

namespace Ab {

template <typename DerivedT, typename UnderlyingT>
class StaticPoly {
private:
	friend DerivedT;

	UnderlyingT* self() noexcept { return static_cast<UnderlyingT*>(this); }

	const UnderlyingT* cself() const noexcept { return static_cast<const UnderlyingT*>(this); }

	const UnderlyingT* self() const noexcept { return cself(); }
};

}  // namespace Ab

#endif // AB_STATICPOLY_HPP_
