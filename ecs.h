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

struct Entity{
    Vector2 position; 
    float speed;
    Vector2 direction;
    entity_type type;
};

struct System {
    system_type type;
    void (*update)(void*, size_t, float);
};

class Entity_Manager {
public:
    int add_entity(entity_type type, Vector2 position);
    entity_type get_type(int id);
    Vector2 get_position(int id);
    void add_system(system_type type, void (*update(void*, size_t, float)));
    void update(float dt);
private:
    std::vector<int> entities;
    std::vector<entity_type> types;
    std::vector<Vector2> positions;
    std::vector<System> systems;
    std::unordered_map<int, int> entity_pos_map;
    std::unordered_map<int, int> entity_type_map;
    int id_counter = 0;
};
