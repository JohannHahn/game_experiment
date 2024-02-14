#include "ecs.h"

entity_type Entity_Manager::get_type(int id) {
    int type_id = entity_type_map[id];
    return types[type_id];
}

Vector2 Entity_Manager::get_position(int id) {
    int type_id = entity_pos_map[id];
    return positions[type_id];
}

int Entity_Manager::add_entity(entity_type type, Vector2 pos) {
    int id = id_counter++;
    entities.push_back(id);
    entity_type_map[id] = id;
    types.push_back(type);
    entity_pos_map[id] = id;
    positions.push_back(pos);
    return id;
}
