#include "player.h"
#include "../core/math.h"

#define null 0

// DEBUG:
extern Camera2D camera;

Player* CreatePlayer (Vector2 position) {
    Player* player = (Player*)RL_MALLOC (sizeof (Player));

    player->sprite = LoadSprite ("assets/test_player.png");

    player->position = position;
    player->scale = Vector2One ();
    player->rotation = 0.0f;

    player->current_speed = 0.0f;
    player->max_speed = PLAYER_MAX_SPEED;

    return player;
}

void UpdatePlayer (Player* player) {
    float direction = Vector2Angle (player->position, GetScreenToWorld2D (GetMousePosition (), camera));
    player->rotation = SmoothLerp (player->rotation, direction, PLAYER_ROTATE_SPEED * GetFrameTime ());

    int acceleration_axis = IsKeyDown (KEY_W) - IsKeyDown (KEY_S);

    if (acceleration_axis != 0) {
        // Speed up 2 faster than player can accelerate and clamp
        player->target_speed += acceleration_axis * ((PLAYER_ACCELERATION * 1.5f) * GetFrameTime ());
        player->target_speed = Clamp (player->target_speed, 0.0f, player->max_speed);
    }

    // Accelerate and clamp?
    if (player->current_speed < player->target_speed) {
        player->current_speed += PLAYER_ACCELERATION * GetFrameTime ();
    } else if (player->current_speed > player->target_speed) {
        player->current_speed -= PLAYER_ACCELERATION * GetFrameTime ();
    }

    if (player->current_speed < 0.0f) player->current_speed = 0.0f;

    // Move player
    Vector2 velocity = LengthDirection (player->current_speed * GetFrameTime (), player->rotation);
    player->position = Vector2Add (player->position, velocity);
}

void DrawPlayer (Player* player) {
    DrawSpritePro (player->sprite, player->position, Vector2MultiplyValue (player->scale, 0.5f), player->rotation * RAD2DEG, WHITE);

    // DEBUG: Used for debugging for now
    const char* stats = TextFormat ("Target Speed: %.0f / %.0f\nCurrent Speed: %.0f", player->target_speed, player->max_speed, player->current_speed);
    DrawTextEx (GetFontDefault (), stats, Vector2AddValue (player->position, 64), 20, 2.0f, WHITE);
}

void UnloadPlayer (Player* player) {
    UnloadSprite (player->sprite);

    RL_FREE (player);
}
