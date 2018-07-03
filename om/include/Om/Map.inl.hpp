#ifndef OM_MAP_INL_HPP_
#define OM_MAP_INL_HPP_

#include <Om/Map.hpp>

namespace Om {

Map::Map(Ref<MapMap> map, MapKind kind) : Cell(map) {
}

MapMap::MapMap() : Map(this, MapKind::MAP) {
}

ObjectMap::ObjectMap(Context& cx)
	: Map(cx.system().emptyObjectMap(), MapKind::OBJECT) {
}

} // namespace Om

#endif // OM_MAP_INL_HPP_
