#ifndef SPRITE_H
#define SPRITE_H

#include <raylib.h>

typedef struct Sprite {
    Texture2D texture;

    Rectangle bounds;
    Vector2 origin;
    Color colour;
} Sprite;


#ifdef __cplusplus
extern "C" {
#endif

Sprite* LoadSprite (const char* filename);
void DrawSprite (Sprite* sprite, Vector2 position);
void DrawSpriteEx (Sprite* sprite, Vector2 position, float rotation, float scale);
void DrawSpritePro (Sprite* sprite, Vector2 position, Vector2 scale, float rotation, Color colour);

void UnloadSprite (Sprite* sprite);


#ifdef __cplusplus
}
#endif


#endif // SPRITE_H
