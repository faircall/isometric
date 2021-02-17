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

Vec3 vec3_add(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x + b.x;
    result.x = a.x + b.x;
    result.x = a.x + b.x;
    return result;
}

Vec3 vec3_sub(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.x - b.x;
    result.x = a.x - b.x;
    result.x = a.x - b.x;
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

float vec3_dot(Vec3 a, Vec3 b)
{
    float result = a.x*b.x + a.y*b.y + a.z*b.z;
    return result;
}

Vec3 vec3_cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = a.y*b.z - b.y*a.z;
    result.y = a.z*b.x - b.z*a.x;
    result.z = a.x*b.y - b.x*a.y;
    return result;
}

float vec3_triple(Vec3 a, Vec3 b, Vec3 c)
{
    float result = vec3_dot(vec3_cross(a,b), c);
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
    //the determinant of a 3x3 matrix
    //is equal to the scalar triple product
    //of the column vectors of the matrix

    //insane how much more
    //compact this is
    Vec3 va = vec3_from_mat3(a,0);
    Vec3 vb = vec3_from_mat3(a,1);
    Vec3 vc = vec3_from_mat3(a,2);
    float result = vec3_triple(va,vb,vc);
    return result;
}

#if 0
float mat3_det(Mat3 a)
{
    //use the explicit formula
    float t1 = mat3(a,0,0)*mat3(a,1,1)*mat3(a,2,2);
    float t2 = mat3(a,0,1)*mat3(a,1,2)*mat3(a,2,0);
    float t3 = mat3(a,0,2)*mat3(a,1,0)*mat3(a,2,1);
    
    float t4 = mat3(a,0,0)*mat3(a,1,2)*mat3(a,2,1);
    float t5 = mat3(a,0,1)*mat3(a,1,0)*mat3(a,2,2);
    float t6 = mat3(a,0,2)*mat3(a,1,1)*mat3(a,2,0);

    float result = t1 + t2 + t3 - t4 - t5 - t6;
    return result;
}
#endif

Mat3 mat3_adjugate(Mat3 a)
//I *think* this is correct but a typo is quite possible,
//better to make a function which
//generates arbitrary adjugate matrices
{
    float a00 = mat3(a,1,1)*mat3(a,2,2) - mat3(a,1,2)*mat3(a,2,1);
    float a01 = mat3(a,0,2)*mat3(a,2,1) - mat3(a,0,1)*mat3(a,2,2);
    float a02 = mat3(a,0,1)*mat3(a,1,2) - mat3(a,0,2)*mat3(a,1,1);

    float a10 = mat3(a,1,2)*mat3(a,2,0) - mat3(a,1,0)*mat3(a,2,2);
    float a11 = mat3(a,0,0)*mat3(a,2,2) - mat3(a,0,2)*mat3(a,2,0);
    float a12 = mat3(a,0,2)*mat3(a,1,0) - mat3(a,0,0)*mat3(a,1,2);

    float a20 = mat3(a,1,0)*mat3(a,2,1) - mat3(a,1,1)*mat3(a,2,0);
    float a21 = mat3(a,0,1)*mat3(a,2,0) - mat3(a,0,0)*mat3(a,2,1);
    float a22 = mat3(a,0,0)*mat3(a,1,1) - mat3(a,0,1)*mat3(a,1,0);

    Mat3 result = mat3_init_float(a00, a01, a02,
				  a10, a11, a12,
				  a20, a21, a22);
    return result;
}

Mat3 mat3_scale(Mat3 a, float scalar)
{
    Mat3 result;
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    mat3(result,i,j) = mat3(a,i,j)*scalar;
	}
    }
    return result;
}
    

Mat3 mat3_inverse(Mat3 a)
{
    //oh yeah, check if det is zero...
    float det = mat3_det(a);
    if (det == 0.0f) {
	//handle degenerate case
    }
    float inv_det = 1.0f/det;
    Mat3 adj = mat3_adjugate(a);
    Mat3 result = mat3_scale(adj, inv_det);
    return result;
}

Mat4 mat4_create_zero(void)
{
    Mat4 result;
        for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 4; j++) {
		mat4(result, i, j) = 0;
	    }
    }
    return result;    
}

Mat4 mat4_create_identity(void)
{
    Mat4 result;
    result = mat4_create_zero();
    mat4(result, 0, 0) = 1.0f;
    mat4(result, 1, 1) = 1.0f;
    mat4(result, 2, 2) = 1.0f;
    mat4(result, 3, 3) = 1.0f;
    return result;
}

Mat4 mat4_mult(Mat4 a, Mat4 b)
{
    Mat4 result;
    for (int i = 0; i < 4; i++) {
	for (int j = 0; j < 4; j++) {
	    mat4(result, i, j) = 0;
	    for (int k = 0; k < 4; k++) {
		mat4(result, i, j) += mat4(a,i,k)*mat4(b,k,j);
	    }
	}
    }

    return result;
}

Vec3 vec3_from_mat3(Mat3 a, int col)
{
    //extracts a vec3 from a column of A
    Vec3 result;
    result.x = mat3(a, 0, col);
    result.y = mat3(a, 1, col);
    result.z = mat3(a, 2, col);
    return result;
}

Vec3 vec3_from_mat4(Mat4 a, int col)
{
    //extracts a vec3 from a column of A
    Vec3 result;
    result.x = mat4(a, 0, col);
    result.y = mat4(a, 1, col);
    result.z = mat4(a, 2, col);
    return result;
}

Mat4 mat4_inverse(Mat4 a)
{
    Vec3 va = vec3_from_mat4(a, 0);
    Vec3 vb = vec3_from_mat4(a, 1);
    Vec3 vc = vec3_from_mat4(a, 2);
    Vec3 vd = vec3_from_mat4(a, 3);

    float x = mat4(a,3,0);
    float y = mat4(a,3,1);
    float z = mat4(a,3,2);
    float w = mat4(a,3,3);

    Vec3 s = vec3_cross(va, vb);
    Vec3 t = vec3_cross(vc, vd);
    Vec3 u = vec3_sub(vec3_scale(va, y), vec3_scale(vb, x));
    Vec3 v = vec3_sub(vec3_scale(vc, w), vec3_scale(vd, z));

    float det = vec3_dot(s,v) + vec3_dot(t,u);
    if (det == 0.0f) {
	//handle degenerate case
    }
    float inv_det = 1.0f/det;

    //check equation 1.99 from Lengyel
			
}
