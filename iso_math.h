#ifndef ISO_MATH_H
#define ISO_MATH_H

#include <stdio.h>

typedef struct {
    float x;
    float y;
} Vec2;

typedef struct {
    float x;
    float y;
    float z;
} Vec3;

//I'm unsure if this is actually
//getting around the issue of a bunch of
//heap allocs
//but it *will* make the code much easier to write
//and I suppose I could go back and do a perf pass
//to make these stack alloc'd if that's the better
//option, or add that option with some extra code
typedef struct {
    float elements[2][2];
} Mat2;


//here's where we make it column major
#define mat2(mat,a,b) mat.elements[b][a]

typedef struct {
    float elements[3][3];
} Mat3;


//here's where we make it column major
#define mat3(mat,a,b) mat.elements[b][a]





Vec2 vec2_init(float x, float y);

Vec2 vec2_add(Vec2 a, Vec2 b);

Vec2 vec2_sub(Vec2 a, Vec2 b);

Vec2 vec2_scale(Vec2 a, float scalar);

float vec2_dot(Vec2 a, Vec2 b);

float vec2_mag(Vec2 a);

Vec2 vec2_normalize(Vec2 a);

Mat2 mat2_init_vec2(Vec2 a, Vec2 b);
Mat2 mat2_init_float(float a00, float a01,
		     float a10, float a11);

Mat2 mat2_scale(Mat2 a, float scalar);

float mat2_det(Mat2 a);

Mat2 mat2_inverse(Mat2 a);

Vec3 vec3_init(float x, float y, float z);


Vec3 vec3_scale(Vec3 a, float scalar);


float vec3_mag(Vec3 a);

Vec3 vec3_normalize(Vec3 a);


Vec3 vec3_cross(Vec3 a, Vec3 b);


Mat3 mat3_create_zero(void);

Mat3 mat3_create_identity(void);


void mat3_print_elements(Mat3 m);



Mat3 mat3_init_vec3(Vec3 a, Vec3 b, Vec3 c);
Mat3 mat3_init_float(float a00, float a01, float a02,
		     float a10, float a11, float a12,
		     float a20, float a21, float a22);

Mat3 mat3_mult(Mat3 a, Mat3 b);


Mat3 mat3_transpose(Mat3 a);

float mat3_det(Mat3 a);

#endif
