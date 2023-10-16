#ifndef MATH_H
#define MATH_H

#include <raymath.h>


#ifdef __cplusplus
extern "C" {
#endif

float LengthDirectionX (float length, float direction);
float LengthDirectionY (float length, float direction);

Vector2 LengthDirection (float length, float direction);

float SmoothLerp (float start, float end, float value);

Vector2 Vector2MultiplyValue (Vector2 vector, float value);
Vector2 Vector2DivideValue (Vector2 vector, float value);

#ifdef __cplusplus
}
#endif


#endif // MATH_H
