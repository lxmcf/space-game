#include <raylib.h>
#include <raymath.h>

#include "sprite.h"

Sprite* LoadSprite (const char* filename) {
    Sprite* sprite = (Sprite*)RL_MALLOC (sizeof (Sprite));

    sprite->texture = LoadTexture (filename);
    sprite->colour = WHITE;

    sprite->bounds = CLITERAL(Rectangle) {
        .x = 0.0f,
        .y = 0.0f,

        .width = sprite->texture.width,
        .height = sprite->texture.height,
    };

    sprite->origin = CLITERAL(Vector2) {
        .x = sprite->texture.width / 2,
        .y = sprite->texture.height / 2,
    };

    return sprite;
}

void DrawSprite (Sprite* sprite, Vector2 position) {
    DrawTextureV (sprite->texture, Vector2Subtract (position, sprite->origin), sprite->colour);
}

void DrawSpriteEx (Sprite* sprite, Vector2 position, float rotation, float scale) {
    DrawTextureEx (sprite->texture, Vector2Subtract (position, sprite->origin), rotation, scale, sprite->colour);
}

void DrawSpritePro (Sprite* sprite, Vector2 position, Vector2 scale, float rotation, Color colour) {
    Rectangle output = CLITERAL(Rectangle) {
        .x = position.x,
        .y = position.y,

        .width = sprite->bounds.width * scale.x,
        .height = sprite->bounds.height * scale.y,
    };

    Vector2 origin = Vector2Multiply (sprite->origin, scale);

    DrawTexturePro (sprite->texture, sprite->bounds, output, origin, rotation, colour);
}

void UnloadSprite (Sprite* sprite) {
    UnloadTexture (sprite->texture);

    RL_FREE (sprite);
}
