#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <vector>
#include <unordered_map>


enum entity_type {
    PLAYER, ENEMY, COLLECTABLE, ENTITY_TYPE_MAX
};

enum system_type {
    MOVEMENT, RENDER, SYSTEM_TYPE_MAX 
};

enum component_type {
    POSITION, SPEED, COMPONENT_TYPE_MAX
};

class Entity_Manager;
struct System {
    System(system_type type, void(*update)(Entity_Manager*, int, void*, float)):
    type(type), update(update) {};
    system_type type;
    void (*update)(Entity_Manager*, int, void*, float); 
    void* data;
};


class Entity_Manager {
public:
    Entity_Manager() {
	for (int i = 0; i < COMPONENT_TYPE_MAX; ++i) {
	    maps.push_back(std::unordered_map<int, int>());
	}
    }
    int add_entity(entity_type type);
    void add_component(int entity_id, component_type component, void* data);
    int get_type(int id);
    Vector2 get_position(int id);
    float get_speed(int id);
    void add_system(System system);
    void update(float dt);
private:
    std::vector<int> entity_ids;
    std::vector<int> entity_types;
    std::vector<System> systems;

    std::vector<std::unordered_map<int, int>> maps;

    std::vector<std::pair<Vector2, int>> position_data;
    std::vector<std::pair<float, int>> speed_data;
    int id_counter = 0;
};
