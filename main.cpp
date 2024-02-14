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


int main() {
    std::cout << "hi\n";
    InitWindow(800, 600, "Game");
    Entity_Manager ecs;
    ecs.add_entity(PLAYER, {100, 100});
    ecs.add_system(RENDER, void (*(*apply)(void *, size_t)))

    while (!WindowShouldClose()) {
	BeginDrawing();
	ClearBackground(RED);
	EndDrawing();
    }
    return 0;
}

