// NOTE: Why the hell does this not work...
// #define RAYMATH_IMPLEMENTATION
#include "math.h"

// NOTE: Only used to keep code consistant
#define CLITERAL(type) (type)

float LengthDirectionX (float length, float direction) {
    return length * cosf (direction);
}

float LengthDirectionY (float length, float direction) {
    return length * sinf (direction);
}

Vector2 LengthDirection (float length, float direction) {
    return CLITERAL (Vector2){
        .x = LengthDirectionX (length, direction),
        .y = LengthDirectionY (length, direction)
     };
}

float SmoothLerp (float start, float end, float value) {
    return start + (sinf (end - start) * value);
}

Vector2 Vector2MultiplyValue (Vector2 vector, float value) {
    return CLITERAL (Vector2){
        .x = vector.x * value,
        .y = vector.y * value
    };
}

Vector2 Vector2DivideValue (Vector2 vector, float value) {
    return CLITERAL (Vector2){
        .x = vector.x / value,
        .y = vector.y / value
    };
}
