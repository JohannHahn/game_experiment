#include "raylib/src/raylib.h"
#include "raylib/src/raymath.h"
#include <cassert>
#include <iostream>
#include <vector>
#include "ecs.h"


enum entity_type {
    PLAYER, ENEMY, COLLECTABLE, ENTITY_TYPE_MAX
};

enum data_type {
    POSITION, SPEED, DATA_TYPE_MAX
};

void render_update(Entity_Manager* self, int entity_id, float dt) {
    Vector2 position;
    if (!self->get_position(entity_id, &position)) return;
    Vector2 size = {10, 10};
    int type = self->get_type(entity_id);
    Color col = type == PLAYER ? WHITE : BLACK;
    DrawRectangleV(position, size, col);	
}
void movement_update(Entity_Manager* self, int entity_id, float dt) {
    Vector2 position;
    float speed;
    self->get_data(entity_id, POSITION);
    if (!self->get_position(entity_id, &position) || !self->get_speed(entity_id, &speed)) {
	assert(0 && "not all components");
	return;
    }
    int entity_type = self->get_type(entity_id);
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
    }
    else if (entity_type == ENEMY) {
	Vector2 player_pos;
	self->get_position(0, &player_pos);
	position = Vector2Add(position, Vector2Scale(Vector2Normalize(Vector2Subtract(player_pos, position)), speed * dt));
    }
    self->set_component_data(POSITION, entity_id, &position);
}

int main() {
    InitWindow(800, 600, "Game");
    Entity_Manager ecs;
    int player_id = ecs.add_entity(PLAYER);
    int enemy_id = ecs.add_entity(ENEMY);
    Vector2 player_pos = {100, 100};
    Vector2 enemy_pos = {200, 200};
    float speed = 100;
    float enemy_speed = 90;
    // Position
    ecs.add_data_array(2, sizeof(Vector2));
    // Speed
    ecs.add_data_array(2, sizeof(float));
    ecs.set_data(POSITION, player_id, &player_pos);
    ecs.set_data(POSITION, enemy_id, &enemy_pos);
    System render_system = {.update = render_update, .entities = {player_id, enemy_id}};
    ecs.add_system(&render_system);
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

