#ifndef OM_BARRIER_HPP_
#define OM_BARRIER_HPP_

namespace Barrier {
template <typename Object, typename Field, typename Value>
write(Context& cx, Object& [[gnu::unused]] object, Field& field, Value&& value) {
	field = std::forward<Value>(value);
}

}

Barrier::write(cx, *object, object->map, newMap);

/// A barriered wrapper
template <typename T>
class Barrier {
public:
	template <typename... Args>
	inline Barrier(Args&&... args);

	inline auto get(Context& cx) -> T&;

	template <typename U>
	inline auto set(Context& cx, U&& u) -> void;
};

template <typename T>
template <typename... Args>
inline Barrier<T>::Barrier(Args&&... args)
	: value_(std::forward<Args>(args)...) {
}

template <typename T>
ReadBarrier {
}

WriteBarrier

#endif // OM_BARRIER_HPP_