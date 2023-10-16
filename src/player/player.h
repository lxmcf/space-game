#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#include "../graphics/sprite.h"

// NOTE: Temp until more advanced ship customisation comes into play
#define PLAYER_MAX_SPEED 1000.0f
#define PLAYER_ROTATE_SPEED 2.5f
#define PLAYER_ACCELERATION 200.0f

typedef struct Player {
    Sprite* sprite;

    Vector2 position;
    Vector2 scale;

    // Stored in RADIANS
    float rotation;

    float current_speed;
    float target_speed;
    float max_speed;
} Player;


#ifdef __cplusplus
extern "C" {
#endif

Player* CreatePlayer (Vector2 position);
void UpdatePlayer (Player* player);
void DrawPlayer (Player* player);

void UnloadPlayer (Player* player);

#ifdef __cplusplus
}
#endif


#endif // PLAYER_H
