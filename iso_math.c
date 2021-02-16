#include <math.h>
#include "iso_math.h"

Vec2 vec2_init(float x, float y)
{
    Vec2 result;
    result.x = x;
    result.y = y;
    return result;
}

Vec2 vec2_add(Vec2 a, Vec2 b)
{
    Vec2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

Vec2 vec2_sub(Vec2 a, Vec2 b)
{
    Vec2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

Vec2 vec2_scale(Vec2 a, float scalar)
{
    Vec2 result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;
    return result;
}

float vec2_dot(Vec2 a, Vec2 b)
{
    float result = a.x*b.x + a.y*b.y;
    return result;
}

float vec2_mag(Vec2 a)
{
    float result = sqrt(a.x*a.x + a.y*a.y);
    return result;
}

Vec2 vec2_normalize(Vec2 a)
{
    Vec2 result;
    float mag = vec2_mag(a);
    float inv_mag = 1.0/mag;
    result = vec2_scale(a, inv_mag);
    return result;
}

Mat2 mat2_init_vec2(Vec2 a, Vec2 b)
{
    Mat2 result;
    mat2(result, 0, 0) = a.x;
    mat2(result, 0, 1) = b.x;
    mat2(result, 1, 0) = a.y;
    mat2(result, 1, 1) = b.y;
    return result;
}

Mat2 mat2_init_float(float a00, float a01,
		     float a10, float a11)
{
    Mat2 result;

    mat2(result, 0, 0) = a00;
    mat2(result, 0, 1) = a01;
    mat2(result, 1, 0) = a10;
    mat2(result, 1, 1) = a11;
    return result;
}

Mat2 mat2_scale(Mat2 a, float scalar)
{
    Mat2 result;
    for (int i = 0; i < 2; i++) {
	for (int j = 0; j < 2; j++) {
	    mat2(result,i,j) = scalar*mat2(a,i,j);
	}
    }
    return result;
}

float mat2_det(Mat2 a)
{
    float result = mat2(a,0,0)*mat2(a,1,1) - mat2(a,0,1)*mat2(a,1,0);
    return result;
}

Mat2 mat2_inverse(Mat2 a)
{
    float det = mat2_det(a);
    Mat2 result;
    mat2(result,0,0) = mat2(a,1,1);
    mat2(result,1,1) = mat2(a,0,0);
    mat2(result,0,1) = -mat2(a,0,1);
    mat2(result,1,0) = -mat2(a,1,0);
    result = mat2_scale(result, det);
    return result;
}

Vec3 vec3_init(float x, float y, float z)
{
    Vec3 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

Vec3 vec3_scale(Vec3 a, float scalar)
{
    Vec3 result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;
    result.z = a.z * scalar;
    return result;
}

float vec3_mag(Vec3 a)
{
    float result = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
    return result;
}

Vec3 vec3_normalize(Vec3 a)
{
    Vec3 result;
    float mag = vec3_mag(a);
    float inv_mag = 1.0/mag;
    result = vec3_scale(a, inv_mag);
    return result;
}

Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.y*b.z - b.y*a.z;
    result.y = a.x*b.z - b.x*a.z;
    result.z = a.x*b.y - b.x*a.y;
    return result;
}

Mat3 mat3_init_float(float a00, float a01, float a02,
		     float a10, float a11, float a12,
		     float a20, float a21, float a22)
{
    Mat3 result;
    mat3(result, 0, 0) = a00;
    mat3(result, 0, 1) = a01;
    mat3(result, 0, 2) = a02;

    mat3(result, 1, 0) = a10;
    mat3(result, 1, 1) = a11;
    mat3(result, 1, 2) = a12;

    mat3(result, 2, 0) = a20;
    mat3(result, 2, 1) = a21;
    mat3(result, 2, 2) = a22;

    return result;
}

Mat3 mat3_init_vec3(Vec3 a, Vec3 b, Vec3 c)		    
{
    Mat3 result;
    mat3(result, 0, 0) = a.x;
    mat3(result, 0, 1) = b.x;
    mat3(result, 0, 2) = c.x;

    mat3(result, 1, 0) = a.y;
    mat3(result, 1, 1) = b.y;
    mat3(result, 1, 2) = c.y;

    mat3(result, 2, 0) = a.z;
    mat3(result, 2, 1) = b.z;
    mat3(result, 2, 2) = c.z;

    return result;
}

Mat3 mat3_create_zero(void)
{
    Mat3 result;
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    mat3(result, i, j) = 0;
	}
    }
    return result;
}

Mat3 mat3_create_identity(void)
{
    Mat3 result;
    result = mat3_create_zero();
    mat3(result, 0, 0) = 1;
    mat3(result, 1, 1) = 1;
    mat3(result, 2, 2) = 1;
    return result;
}

void mat3_print_elements(Mat3 m)
{
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    printf("row %d col %d has element %f\n", i, j, mat3(m, i, j));
	}
    }
}

Mat3 mat3_mult(Mat3 a, Mat3 b)
{
    //this is easy to code but probably slow atm
    //so do an optimization pass later
    Mat3 result;
    //result = mat3_create_zero();
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    mat3(result, i, j) = 0;
	    for (int k = 0; k < 3; k++) {
		mat3(result, i, j) += mat3(a,i,k)*mat3(b,k,j);
	    }
	}
    }

    return result;
}

Mat3 mat3_transpose(Mat3 a)
{
    Mat3 result;
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    mat3(result, i, j) = mat3(a, j, i);
	}
    }
    return result;
}

float mat3_det(Mat3 a)
{
}
