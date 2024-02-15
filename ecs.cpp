#include "ecs.h"
#include <cassert>
#include <iostream>

bool contains(std::unordered_map<int, int> map, int key) {
    return map.find(key) != map.end();
}

int Entity_Manager::get_type(int id) {
    return entity_types[id];
}

float Entity_Manager::get_speed(int id) {
    if (contains(maps[SPEED], id)) {
	int speed_id = maps[SPEED][id];
	return speed_data[speed_id].first;
    }
    else {
	return 0.f;
    }
}

Vector2 Entity_Manager::get_position(int id) {
    if (contains(maps[POSITION], id)) {
	int position_id = maps[POSITION][id];
	return position_data[position_id].first;
    }
    else {
	return {-1, -1};
    }
}

void Entity_Manager::update(float dt) {
    for (System& system : systems) {
	for (int id : entity_ids) {
	    system.update(this, id, system.data, dt);
	}
    }
}

int Entity_Manager::add_entity(entity_type type) {
    int id = id_counter++;
    entity_ids.push_back(id);
    entity_types.push_back(type);
    return id;
}

void Entity_Manager::add_system(System system) {
    void* data;
    switch (system.type) {
	case RENDER:
	    data = (void*)position_data.data();
	break;
	case MOVEMENT:
	    data = (void*)position_data.data();
	break;

	case SYSTEM_TYPE_MAX:
	default:
	assert(0 && "unreachable");
    
    }
    system.data = data;
    systems.push_back(system);
}

void Entity_Manager::add_component(int entity_id, component_type component, void* component_data) {
    int type = entity_types[entity_id];
    switch (component) {
	case POSITION: {
	    Vector2 pos = *(Vector2*)component_data;
	    maps[component][entity_id] = position_data.size();
	    position_data.push_back(std::pair<Vector2, int>(pos, type));
	}
	break;
	case SPEED: {
	    maps[component][entity_id] = speed_data.size();
	    float speed = *(float*)component_data;
	    speed_data.push_back(std::pair<float, int>(speed, type));
	}
	case COMPONENT_TYPE_MAX:
	default:
	assert(0 && "unreachable");
    }
}
