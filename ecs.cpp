#include "ecs.h"
#include <cassert>
#include <iostream>

bool contains(const std::vector<int>& map, int key) {
    for (int i: map) {
	if (i == key) return true;
    }
    return false;
}

bool Entity_Manager::has_component(int component, int entity_id) {
    return contains(entity_components[entity_id], component); 
}

int Entity_Manager::get_type(int id) {
    return entity_types[id];
}

void* Entity_Manager::get_data(int entity_id, int data_id) {
    assert(contains(index_map[data_id], entity_id));
    return 
}

void Entity_Manager::add_data_array(size_t size, char size_elem_byte) {
    index_map.push_back(std::vector<int>());
    data.push_back(Array(size, size*2, size_elem_byte));
}

void Entity_Manager::update(float dt) {
    for (System* system: systems) {
	for (int id : system->entities) {
	    system->update(this, id, dt);
	}
    }
}

int Entity_Manager::add_entity(int type) {
    int id = id_counter++;
    entity_ids.push_back(id);
    entity_types.push_back(type);
    return id;
}

void Entity_Manager::add_system(System* system) {
    systems.push_back(system);
}

void Entity_Manager::add_component(int entity_id, int component) {
    assert(entity_components.size() > entity_id);
    entity_components[entity_id].push_back(component);
    //maps.push_back(std::unordered_map<int, int>());
    //maps[component][entity_id] = data[component].size();
    //switch (component) {
    //    case POSITION: {
    //        Vector2 pos = *(Vector2*)component_data;
    //        maps[component][entity_id] = position_data.size();
    //        position_data.push_back(pos);
    //    }
    //    break;
    //    case SPEED: {
    //        maps[component][entity_id] = speed_data.size();
    //        float speed = *(float*)component_data;
    //        speed_data.push_back(speed);
    //    }
    //    break;
    //    case COMPONENT_TYPE_MAX:
    //    default:
    //    assert(0 && "unreachable");
    //}
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
    for (System* system: systems) {
	std::cout << "update function pointer = " << (size_t)system->update<< "\n"; 
    }
}

