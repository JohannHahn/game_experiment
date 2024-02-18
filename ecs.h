#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <unordered_map>


class Entity_Manager;
typedef void(*update_function)(Entity_Manager*, int, float); 

struct System {
    update_function update;
    std::vector<int> entities;
};

struct Array {
    Array(size_t size, size_t capacity, size_t size_elem_byte):
    size(size), capacity(capacity), size_elem_byte(size_elem_byte) {
	assert(size <= capacity);
	data = (char*)malloc(size);
    }
    char* data;
    size_t size;
    size_t capacity;
    char size_elem_byte;
    void append(void* new_data, size_t num_elem) {	
	size_t new_size = size + num_elem * size_elem_byte;
	if (new_size >= capacity) {
	    realloc();
	}
	memcpy(data + size, new_data, num_elem * size_elem_byte);
	size = new_size;
    }
    void realloc() {
	void* new_data = malloc(size * 2); 
	memcpy(new_data, data, size);
	free(data);
	capacity = size * 2;
    }
};


class Entity_Manager {
public:
    int add_entity(int type);
    void add_component(int entity_id, int component);
    void add_data_array(size_t size, char size_elem_byte);
    void set_data(int data_id, int entity_id, void* data, size_t num_elements = 1);
    void* get_data(int entity_id, int data_id);
    int get_type(int id);
    void add_system(System* system);
    void update(float dt);
    bool has_component(int type, int entity_id);
    void print();
    // all entity ids
    std::vector<int> entity_ids;
    std::vector<int> entity_types;
    std::vector<std::vector<int>> entity_components;
    std::vector<System*> systems;
    // maps from entity_id to an index into a specific data array like position, speed etc
    // position_id = index_map[DATA_ID][ENTITY_ID];
    std::vector<std::vector<int>> index_map;
    // data arrays, to be set and sized/typed from outside 
    std::vector<Array> data;

    //std::vector<Vector2> position_data;
    //std::vector<float> speed_data;
    int id_counter = 0;
};
