#include <raylib.h>

#include "core/math.h"
#include "player/player.h"

#define CAP_FPS 1

// DEBUG: Used for testing
static Player* player;
static Texture2D stars_1;
static Texture2D stars_2;
static Texture2D stars_3;

float target_zoom;

Camera2D camera;

void DrawTextureTiled (Texture2D texture, Vector2 offset, Color colour);

int main (int argc, const char* argv[]) {
    InitWindow (960, 540, "[Space Game]");
    InitAudioDevice ();

    #if CAP_FPS
        int current_monitor = GetCurrentMonitor ();
        int fps_cap = GetMonitorRefreshRate (current_monitor);

        SetTargetFPS (fps_cap);
    #endif

    stars_1 = LoadTexture ("assets/test_stars_1.png");
    stars_2 = LoadTexture ("assets/test_stars_2.png");
    stars_3 = LoadTexture ("assets/test_stars_3.png");

    player = CreatePlayer (CLITERAL(Vector2){ 128.0f, 128.0f });

    target_zoom = 1.0f;

    camera = CLITERAL(Camera2D){ 0 };
    camera.offset = CLITERAL(Vector2){ GetScreenWidth () / 2, GetScreenHeight () / 2 };
    camera.zoom = target_zoom;
    camera.target = Vector2Zero ();

    while (!WindowShouldClose ()) {
        UpdatePlayer (player);
        float speed_percentage = player->current_speed / player->max_speed;

        camera.target = Vector2Add (player->position, LengthDirection (speed_percentage * 128.0f, player->rotation));

        float mouse_wheel = GetMouseWheelMove ();
        if (mouse_wheel != 0) {
            const float zoom_increment = 0.125f;

            target_zoom += zoom_increment * mouse_wheel;

            target_zoom = Clamp (target_zoom, zoom_increment, 1.0f);
        }

        if (camera.zoom < target_zoom) {
            camera.zoom += 1.0f * GetFrameTime ();
        } else if (camera.zoom > target_zoom) {
            camera.zoom -= 1.0f * GetFrameTime ();
        }

        camera.zoom = Clamp (camera.zoom, 0.125f, 1.0f);

        BeginDrawing ();
            ClearBackground (CLITERAL(Color){ 18, 16, 18, 255 });

            DrawTextureTiled (stars_1, Vector2MultiplyValue (player->position, 0.25f), WHITE);
            DrawTextureTiled (stars_2, Vector2MultiplyValue (player->position, 0.50f), WHITE);
            DrawTextureTiled (stars_3, Vector2MultiplyValue (player->position, 0.75f), WHITE);

            BeginMode2D (camera);
                DrawPlayer (player);
            EndMode2D ();

            DrawFPS (8, 8);
        EndDrawing ();
    }

    UnloadTexture (stars_1);
    UnloadTexture (stars_2);
    UnloadTexture (stars_3);

    UnloadPlayer (player);

    CloseAudioDevice ();
    CloseWindow ();

    return 0;
}

void DrawTextureTiled (Texture2D texture, Vector2 offset, Color colour) {
    // CAP WITHIN TEXTURE BOUNDS
    Vector2 adjusted_offset = CLITERAL(Vector2){
        .x = (int)offset.x % texture.width,
        .y = (int)offset.y % texture.height
    };

    for (int x = -texture.width; x < GetScreenWidth () + texture.width; x += texture.width) {
        for (int y = -texture.height; y < GetScreenHeight () + texture.height; y += texture.height) {
            Vector2 position = CLITERAL(Vector2){ .x = x, .y = y };

            DrawTextureV (texture, Vector2Subtract (position, adjusted_offset), colour);
        }
    }
}
