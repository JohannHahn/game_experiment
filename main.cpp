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
void render_update(Entity_Manager* self, int entity_id, float dt) {
    Vector2 position;
    if (!self->get_position(entity_id, &position)) return;
    Vector2 size = {10, 10};
    int type = self->get_type(entity_id);
    Color col = type == PLAYER ? WHITE : BLACK;
    DrawRectangleV(position, size, col);	
}
void movement_update(Entity_Manager* self, int entity_id, float dt) {
    std::cout << "movement update \n";
    int entity_type = self->get_type(entity_id);
    Vector2 position;
    if (!self->get_position(entity_id, &position)) return;
    std::cout << "has position\n";
    float speed;
    if (!self->get_speed(entity_id, &speed)) return;
    std::cout << "movement update: entity_id = " << entity_id << ", dt = " << dt << ", speed = " << speed << "\n";
    std::cout << "x = " << position.x << ", y = " << position.y << "\n";
    if (entity_type == PLAYER) {
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
	    position.x -= speed * dt; 
	}
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
	    position.x += speed * dt; 
	}
	if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
	    position.y -= speed * dt; 
	}
	if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
	    position.y += speed * dt; 
	}
	std::cout << "after the check " << "x = " << position.x << ", y = " << position.y << "\n";
    }
}


int main() {
    std::cout << "hi\n";
    InitWindow(800, 600, "Game");
    Entity_Manager ecs;
    int player_id = ecs.add_entity(PLAYER);
    int enemy_id = ecs.add_entity(ENEMY);
    Vector2 player_pos = {100, 100};
    Vector2 enemy_pos = {200, 200};
    float speed = 100;
    ecs.add_component(player_id, POSITION, &player_pos);
    ecs.add_component(player_id, SPEED, &speed);
    ecs.add_component(enemy_id, POSITION, &enemy_pos);
    ecs.add_component(enemy_id, SPEED, &speed);
    ecs.add_system(render_update);
    ecs.add_system(movement_update);
    ecs.print();

    while (!WindowShouldClose()) {
	float dt = GetFrameTime();
	BeginDrawing();
	ClearBackground(RED);
	ecs.update(dt);
	EndDrawing();
    }
    return 0;
}

