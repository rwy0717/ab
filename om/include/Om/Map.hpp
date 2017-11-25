#ifndef OM_MAP_HPP_
#define OM_MAP_HPP_

#include <Om/Config.hpp>
#include <Om/Cell.hpp>
#include <Om/Context.hpp>
#include <Om/Id.hpp>
#include <Pith/Maybe.hpp>
#include <cstdint>

namespace Om {

enum class SlotKind {
	ACCESSOR,
} struct Type {
	uint8_t dummy_;
};

struct SlotDescriptor {
	Id id_;
};

class SlotLookup {};

enum class MapKind : std::uint8_t { MAP, OBJECT, DATA };

/// A low tagged
class NextMapPointer {
	static constexpr uintptr_t TABLE_TAG = 0x1;

	tablePointer() const {
		return table_;
	}

	mapPointer() const {
		return map_;
	}

	auto isTable() const {
		return (value_.raw_ & TABLE_TAG);
	}

	auto isMap() const {
		return (value_.raw_ & TABLE_TAG) == 0;
	}

	union {
		uintptr_t raw_;
		Map* map_;
		ChildTable* table_;
	} value_;
};

/// An immutable description of the layout of an object.
/// The shape of an object. Maps slot-id's to slot indexes.
class Map : public Cell {
public:
	class Map(Ref<MapMap> map, MapKind kind);

	auto search(Context& cx, Id id) const -> Pith::Maybe<SlotLookup>;

protected:
	friend class Cell;

	instanceSize(Context& cx, Ref<Cell> cell);

private:
	std::size_t slotCount_;
	MapKind kind_;
	mutable bool shared_;
	SlotDescriptor slotDescriptors_[0];
};

struct MapLineage : public Cell {
	Ref<Map> map_;
	const Map* parent_;
	MapTable children_;
	const Map map_;
};

/// The MapMap. The Map type that describes the layout of Map Objects. The MapMap is it's own map.
class MapMap : public Map {
public:
	MapMap();
};

class ObjectMap : public ObjectMap {
public:
	ObjectMap(Context& cx);

	ObjectMap(Context& cx, SlotList& slots);
};

}  // namespace Om

#include <Om/Map.inl.hpp>

#endif  // OM_MAP_HPP_
