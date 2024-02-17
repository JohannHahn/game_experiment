#include "ecs.h"
#include <cassert>
#include <iostream>

bool contains(const std::unordered_map<int, int>& map, int key) {
    return map.find(key) != map.end();
}

bool Entity_Manager::has_component(component_type type, int entity_id) {
    return contains(maps[type], entity_id); 
}

int Entity_Manager::get_type(int id) {
    return entity_types[id];
}

void Entity_Manager::set_component_data(component_type type, int entity_id, void* data) {
    int local_id = maps[type][entity_id];
    switch (type) {
	case POSITION: {
	    Vector2 position = *(Vector2*)data;
	    position_data[local_id] = position;
	}
	break;
	case SPEED: {
	    float speed = *(float*)data;
	    speed_data[local_id] = speed;
	}
	break;
	case COMPONENT_TYPE_MAX:
	default:
	assert(0 && "unreachable");
    }
}

bool Entity_Manager::get_speed(int id, float* out) {
    if (contains(maps[SPEED], id)) {
	int speed_id = maps[SPEED][id];
	*out = speed_data[speed_id];
	return true;
    }
    else {
	return false;
    }
}

bool Entity_Manager::get_position(int id, Vector2* out) {
    if (contains(maps[POSITION], id)) {
	int position_id = maps[POSITION][id];
	*out = position_data[position_id];
	return true;
    }
    else {
	out = NULL;
	return false;
    }
}

void Entity_Manager::update(float dt) {
    for (update_function update_func: systems) {
	for (int id : entity_ids) {
	    update_func(this, id, dt);
	}
    }
}

int Entity_Manager::add_entity(entity_type type) {
    int id = id_counter++;
    entity_ids.push_back(id);
    entity_types.push_back(type);
    return id;
}

void Entity_Manager::add_system(update_function update_func) {
    systems.push_back(update_func);
}

void Entity_Manager::add_component(int entity_id, component_type component, void* component_data) {
    switch (component) {
	case POSITION: {
	    Vector2 pos = *(Vector2*)component_data;
	    maps[component][entity_id] = position_data.size();
	    position_data.push_back(pos);
	}
	break;
	case SPEED: {
	    maps[component][entity_id] = speed_data.size();
	    float speed = *(float*)component_data;
	    speed_data.push_back(speed);
	}
	break;
	case COMPONENT_TYPE_MAX:
	default:
	assert(0 && "unreachable");
    }
}

void Entity_Manager::print() {
    std::cout << "\n---- Entity Manager printout ----\n";
    std::cout << "entities:\n";
    for (int id : entity_ids) {
	std::cout << "id = " << id << "\n";
	std::cout << "type = " << get_type(id) << "\n";
	std::string out = "entiy has ";
	float speed;
	bool has_speed = get_speed(id, &speed);
	Vector2 position;
	bool has_position = get_position(id, &position);
	if (has_speed) {
	    out += "a speed = "; 
	    out += speed;
	}
	else {
	    out += "no speed component\n";
	}
	out += "entity has ";
	if (has_position) {
	    out += "a position.x = "; 
	    out += position.x;
	    out += ", a position.y = "; 
	    out += position.y;
	}
	else {
	    out += "no position component\n";
	}
    }
    std::cout << "----------------";
    std::cout << "\nsystems:\n";
    for (update_function update_func: systems) {
	std::cout << "update function pointer = " << (size_t)update_func << "\n"; 
    }
}

