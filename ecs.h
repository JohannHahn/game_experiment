#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <vector>
#include <unordered_map>


class Entity_Manager;
typedef void(*update_function)(Entity_Manager*, int, float); 

struct System {
    update_function update;
    std::vector<int> entities;
};


class Entity_Manager {
public:
    int add_entity(int type);
    void add_component(int entity_id, int component);
    void set_component_data(int component, int entity_id, void* data, size_t size);
    bool get_component(int entity_id, int component);
    int get_type(int id);
    bool get_position(int id, Vector2* out);
    bool get_speed(int id, float* out);
    void add_system(System* system);
    void update(float dt);
    bool has_component(int type, int entity_id);
    void print();
    // all entity ids
    std::vector<int> components;
    std::vector<int> entity_ids;
    std::vector<int> entity_types;
    std::vector<System*> systems;
    // maps from entity_id to an index into a specific data array like position, speed etc
    std::vector<std::unordered_map<int, int>> maps;
    // data arrays, to be set and sized/typed from outside 
    std::vector<std::vector<void*>> data;

    //std::vector<Vector2> position_data;
    //std::vector<float> speed_data;
    int id_counter = 0;
};
