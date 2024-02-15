#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <cassert>
#include <iostream>
#include <vector>
#include "ecs.h"

//struct System {
//    std::vector<Entity*> entities;
//    system_type type;
//    void do_thing(float dt) {
//	for (Entity* e: entities) {
//	    if (type == MOVEMENT) {
//		if (e->type == PLAYER) {
//		    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
//			e->position.x -= e->speed * dt; 
//		    }
//		    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
//			e->position.x += e->speed * dt; 
//		    }
//		    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
//			e->position.y -= e->speed * dt; 
//		    }
//		    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
//			e->position.y += e->speed * dt; 
//		    }
//		}
//	    }
//	    if (type == GRAPHICS) { 
//		if (e->type == PLAYER) {
//		    DrawRectangleV(e->position, {10, 10}, WHITE);	
//		    DrawLineV(e->position, Vector2Add(e->position, e->direction), BLACK);
//		}
//	    }
//	}
//    }
//};
//
void render_update(Entity_Manager* self, int entity_id, void* data, float dt) {
    std::pair<Vector2, int>* position_type_data = (std::pair<Vector2, int>*)data;
    Vector2 position = position_type_data->first;
    Vector2 size = {10, 10};
    DrawRectangleV(position, size, WHITE);	
}
void movement_update(Entity_Manager* self, int entity_id, void* data, float dt) {
    std::pair<Vector2, int>* position_type_data = (std::pair<Vector2, int>*)data;
    Vector2* position = &position_type_data->first;
    int type = position_type_data->second;
    float speed = self->get_speed(entity_id);
    if (type == PLAYER) {
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
	    position->x -= speed * dt; 
	}
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
	    position->x += speed * dt; 
	}
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
	    position->y -= speed * dt; 
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
	    position->y += speed * dt; 
	}
	std::cout << "x = " << position->x << ", y = " << position->y << "\n";
    }
}


int main() {
    std::cout << "hi\n";
    InitWindow(800, 600, "Game");
    Entity_Manager ecs;
    int player_id = ecs.add_entity(PLAYER);
    std::cout << "after add entity\n";
    Vector2 player_pos = {100, 100};
    ecs.add_component(player_id, POSITION, &player_pos);
    std::cout << "after add component\n";
    ecs.add_system(System(RENDER, render_update));
    ecs.add_system(System(MOVEMENT, movement_update));

    std::cout << "before loop\n";
    while (!WindowShouldClose()) {
	float dt = GetFrameTime();
	BeginDrawing();
	ClearBackground(RED);
	ecs.update(dt);
	EndDrawing();
    }
    return 0;
}

