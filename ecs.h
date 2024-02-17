#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <vector>
#include <unordered_map>


enum entity_type {
    PLAYER = 0, ENEMY, COLLECTABLE, ENTITY_TYPE_MAX
};

enum system_type {
    MOVEMENT, RENDER, SYSTEM_TYPE_MAX 
};

enum component_type {
    POSITION, SPEED, COMPONENT_TYPE_MAX
};


class Entity_Manager;
typedef void(*update_function)(Entity_Manager*, int, float); 

class Entity_Manager {
public:
    Entity_Manager() {
	for (int i = 0; i < COMPONENT_TYPE_MAX; ++i) {
	    maps.push_back(std::unordered_map<int, int>());
	}
    }
    int add_entity(entity_type type);
    void add_component(int entity_id, component_type component, void* data);
    void set_component_data(component_type component, int entity_id, void* data);
    bool get_component(int entity_id, component_type component);
    int get_type(int id);
    bool get_position(int id, Vector2* out);
    bool get_speed(int id, float* out);
    void add_system(update_function update_function);
    void update(float dt);
    bool has_component(component_type type, int entity_id);
    void print();
    // all entity ids
    std::vector<int> entity_ids;
    std::vector<int> entity_types;
    std::vector<update_function> systems;
    // maps from entity_id to an index into a specific data array like position, speed etc
    std::vector<std::unordered_map<int, int>> maps;

    std::vector<Vector2> position_data;
    std::vector<float> speed_data;
    int id_counter = 0;
};
