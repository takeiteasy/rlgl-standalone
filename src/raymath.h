#ifndef RAYMATH_H
#define RAYMATH_H

#ifndef RMAPI
#define RMAPI
#endif

#include <math.h>

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
#ifndef PI
    #define PI 3.14159265358979323846f
#endif

#ifndef DEG2RAD
    #define DEG2RAD (PI/180.0f)
#endif

#ifndef RAD2DEG
    #define RAD2DEG (180.0f/PI)
#endif

// Get float vector for Matrix
#ifndef MatrixToFloat
    #define MatrixToFloat(mat) (MatrixToFloatV(mat).v)
#endif

// Get float vector for Vector3
#ifndef Vector3ToFloat
    #define Vector3ToFloat(vec) (Vector3ToFloatV(vec).v)
#endif

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
#if !defined(RL_VECTOR2_TYPE)
// Vector2 type
typedef struct Vector2 {
    float x;
    float y;
} Vector2;
#define RL_VECTOR2_TYPE
#endif

#if !defined(RL_VECTOR3_TYPE)
// Vector3 type
typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;
#define RL_VECTOR3_TYPE
#endif

#if !defined(RL_VECTOR4_TYPE)
// Vector4 type
typedef struct Vector4 {
    float x;
    float y;
    float z;
    float w;
} Vector4;
#define RL_VECTOR4_TYPE
#endif

#if !defined(RL_QUATERNION_TYPE)
// Quaternion type
typedef Vector4 Quaternion;
#define RL_QUATERNION_TYPE
#endif

#if !defined(RL_MATRIX_TYPE)
// Matrix type (OpenGL style 4x4 - right handed, column major)
typedef struct Matrix {
    float m0, m4, m8, m12;      // Matrix first row (4 components)
    float m1, m5, m9, m13;      // Matrix second row (4 components)
    float m2, m6, m10, m14;     // Matrix third row (4 components)
    float m3, m7, m11, m15;     // Matrix fourth row (4 components)
} Matrix;
#define RL_MATRIX_TYPE
#endif

// NOTE: Helper types to be used instead of array return types for *ToFloat functions
typedef struct float3 {
    float v[3];
} float3;

typedef struct float16 {
    float v[16];
} float16;

#if defined(__cplusplus)
extern "C" {
#endif
RMAPI float Clamp(float value, float min, float max);
RMAPI float Lerp(float start, float end, float amount);
RMAPI float Normalize(float value, float start, float end);
RMAPI float Remap(float value, float inputStart, float inputEnd, float outputStart, float outputEnd);
RMAPI Vector2 Vector2Zero(void);
RMAPI Vector2 Vector2One(void);
RMAPI Vector2 Vector2Add(Vector2 v1, Vector2 v2);
RMAPI Vector2 Vector2AddValue(Vector2 v, float add);
RMAPI Vector2 Vector2Subtract(Vector2 v1, Vector2 v2);
RMAPI Vector2 Vector2SubtractValue(Vector2 v, float sub);
RMAPI float Vector2Length(Vector2 v);
RMAPI float Vector2LengthSqr(Vector2 v);
RMAPI float Vector2DotProduct(Vector2 v1, Vector2 v2);
RMAPI float Vector2Distance(Vector2 v1, Vector2 v2);
RMAPI float Vector2Angle(Vector2 v1, Vector2 v2);
RMAPI Vector2 Vector2Scale(Vector2 v, float scale);
RMAPI Vector2 Vector2Multiply(Vector2 v1, Vector2 v2);
RMAPI Vector2 Vector2Negate(Vector2 v);
RMAPI Vector2 Vector2Divide(Vector2 v1, Vector2 v2);
RMAPI Vector2 Vector2Normalize(Vector2 v);
RMAPI Vector2 Vector2Transform(Vector2 v, Matrix mat);
RMAPI Vector2 Vector2Lerp(Vector2 v1, Vector2 v2, float amount);
RMAPI Vector2 Vector2Reflect(Vector2 v, Vector2 normal);
RMAPI Vector2 Vector2Rotate(Vector2 v, float angle);
RMAPI Vector2 Vector2MoveTowards(Vector2 v, Vector2 target, float maxDistance);
RMAPI Vector3 Vector3Zero(void);
RMAPI Vector3 Vector3One(void);
RMAPI Vector3 Vector3Add(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3AddValue(Vector3 v, float add);
RMAPI Vector3 Vector3Subtract(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3SubtractValue(Vector3 v, float sub);
RMAPI Vector3 Vector3Scale(Vector3 v, float scalar);
RMAPI Vector3 Vector3Multiply(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3CrossProduct(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3Perpendicular(Vector3 v);
RMAPI float Vector3Length(const Vector3 v);
RMAPI float Vector3LengthSqr(const Vector3 v);
RMAPI float Vector3DotProduct(Vector3 v1, Vector3 v2);
RMAPI float Vector3Distance(Vector3 v1, Vector3 v2);
RMAPI float Vector3Angle(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3Negate(Vector3 v);
RMAPI Vector3 Vector3Divide(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3Normalize(Vector3 v);
RMAPI void Vector3OrthoNormalize(Vector3 *v1, Vector3 *v2);
RMAPI Vector3 Vector3Transform(Vector3 v, Matrix mat);
RMAPI Vector3 Vector3RotateByQuaternion(Vector3 v, Quaternion q);
RMAPI Vector3 Vector3Lerp(Vector3 v1, Vector3 v2, float amount);
RMAPI Vector3 Vector3Reflect(Vector3 v, Vector3 normal);
RMAPI Vector3 Vector3Min(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3Max(Vector3 v1, Vector3 v2);
RMAPI Vector3 Vector3Barycenter(Vector3 p, Vector3 a, Vector3 b, Vector3 c);
RMAPI Vector3 Vector3Unproject(Vector3 source, Matrix projection, Matrix view);
RMAPI float3 Vector3ToFloatV(Vector3 v);
RMAPI float MatrixDeterminant(Matrix mat);
RMAPI float MatrixTrace(Matrix mat);
RMAPI Matrix MatrixTranspose(Matrix mat);
RMAPI Matrix MatrixInvert(Matrix mat);
RMAPI Matrix MatrixNormalize(Matrix mat);
RMAPI Matrix MatrixIdentity(void);
RMAPI Matrix MatrixAdd(Matrix left, Matrix right);
RMAPI Matrix MatrixSubtract(Matrix left, Matrix right);
RMAPI Matrix MatrixMultiply(Matrix left, Matrix right);
RMAPI Matrix MatrixTranslate(float x, float y, float z);
RMAPI Matrix MatrixRotate(Vector3 axis, float angle);
RMAPI Matrix MatrixRotateX(float angle);
RMAPI Matrix MatrixRotateY(float angle);
RMAPI Matrix MatrixRotateZ(float angle);
RMAPI Matrix MatrixRotateXYZ(Vector3 ang);
RMAPI Matrix MatrixRotateZYX(Vector3 ang);
RMAPI Matrix MatrixScale(float x, float y, float z);
RMAPI Matrix MatrixFrustum(double left, double right, double bottom, double top, double near, double far);
RMAPI Matrix MatrixPerspective(double fovy, double aspect, double near, double far);
RMAPI Matrix MatrixOrtho(double left, double right, double bottom, double top, double near, double far);
RMAPI Matrix MatrixLookAt(Vector3 eye, Vector3 target, Vector3 up);
RMAPI float16 MatrixToFloatV(Matrix mat);
RMAPI Quaternion QuaternionAdd(Quaternion q1, Quaternion q2);
RMAPI Quaternion QuaternionAddValue(Quaternion q, float add);
RMAPI Quaternion QuaternionSubtract(Quaternion q1, Quaternion q2);
RMAPI Quaternion QuaternionSubtractValue(Quaternion q, float sub);
RMAPI Quaternion QuaternionIdentity(void);
RMAPI float QuaternionLength(Quaternion q);
RMAPI Quaternion QuaternionNormalize(Quaternion q);
RMAPI Quaternion QuaternionInvert(Quaternion q);
RMAPI Quaternion QuaternionMultiply(Quaternion q1, Quaternion q2);
RMAPI Quaternion QuaternionScale(Quaternion q, float mul);
RMAPI Quaternion QuaternionDivide(Quaternion q1, Quaternion q2);
RMAPI Quaternion QuaternionLerp(Quaternion q1, Quaternion q2, float amount);
RMAPI Quaternion QuaternionNlerp(Quaternion q1, Quaternion q2, float amount);
RMAPI Quaternion QuaternionSlerp(Quaternion q1, Quaternion q2, float amount);
RMAPI Quaternion QuaternionFromVector3ToVector3(Vector3 from, Vector3 to);
RMAPI Quaternion QuaternionFromMatrix(Matrix mat);
RMAPI Matrix QuaternionToMatrix(Quaternion q);
RMAPI Quaternion QuaternionFromAxisAngle(Vector3 axis, float angle);
RMAPI void QuaternionToAxisAngle(Quaternion q, Vector3 *outAxis, float *outAngle);
RMAPI Quaternion QuaternionFromEuler(float pitch, float yaw, float roll);
RMAPI Vector3 QuaternionToEuler(Quaternion q);
RMAPI Quaternion QuaternionTransform(Quaternion q, Matrix mat);
#if defined(__cplusplus)
}
#endif
#endif // RAYMATH_H