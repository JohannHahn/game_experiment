#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <cassert>
#include <iostream>
#include <vector>

enum entity_type {
    PLAYER, ENEMY, COLLECTABLE, ENTITY_TYPE_MAX
};

enum system_type {
    MOVEMENT, GRAPHICS, SYSTEM_TYPE_MAX 
};

struct Entity {
    Vector2 position; 
    float speed;
    Vector2 direction;
    entity_type type;
};

struct System {
    std::vector<Entity*> entities;
    system_type type;
    void do_thing(float dt) {
	for (Entity* e: entities) {
	    if (type == MOVEMENT) {
		if (e->type == PLAYER) {
		    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
			e->position.x -= e->speed * dt; 
		    }
		    if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
			e->position.x += e->speed * dt; 
		    }
		    if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
			e->position.y -= e->speed * dt; 
		    }
		    if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
			e->position.y += e->speed * dt; 
		    }
		}
	    }
	    if (type == GRAPHICS) { 
		if (e->type == PLAYER) {
		    DrawRectangleV(e->position, {10, 10}, WHITE);	
		    DrawLineV(e->position, Vector2Add(e->position, e->direction), BLACK);
		}
	    }
	}
    }
};


int main() {
    std::cout << "hi\n";
    InitWindow(800, 600, "Game");
    System movement_system = {{}, MOVEMENT};
    System render_system = {{}, GRAPHICS};
    Entity player = {{0,0}, 1.f, {0,0}, PLAYER};
    movement_system.entities.push_back(&player);
    render_system.entities.push_back(&player);

    while (!WindowShouldClose()) {
	movement_system.do_thing(GetFrameTime());
	BeginDrawing();
	ClearBackground(RED);
	render_system.do_thing(GetFrameTime());
	EndDrawing();
    }
    return 0;
}

