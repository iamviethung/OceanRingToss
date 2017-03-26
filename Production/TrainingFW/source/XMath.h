#ifndef __MATH_H__
#define __MATH_H__
#include "stdafx.h"
//#include "openGLESv2.h"

class Vector2;
class Vector3;
class Vector4;
class Matrix;

class Vector2
{
public:
	//Constructors
	Vector2() : x(0.0f), y(0.0f){}
	Vector2(float _x, float _y) : x(_x), y(_y) {}
	Vector2(float * pArg) : x(pArg[0]), y(pArg[1]) {}
	Vector2(const Vector2 & vector) : x(vector.x), y(vector.y) {}

	//Vector's operations
	//float Length();
	//Vector2 & Normalize();
	//Vector2 operator + (Vector2 & vector);
	//Vector2 & operator += (Vector2 & vector);
	//Vector2 operator - ();
	//Vector2 operator - (Vector2 & vector);
	//Vector2 & operator -= (Vector2 & vector);
	//Vector2 operator * (float k);
	//Vector2 & operator *= (float k);
	//Vector2 operator / (float k);
	//Vector2 & operator /= (float k);
	//Vector2 & operator = (Vector2 & vector);

	//Vector2 Modulate(Vector2 & vector);
	//float Dot(Vector2 & vector);
	//void Set(const float &_x, const float &_y);

	////access to elements
	//float operator [] (unsigned int idx);

	//data members
	float x;
	float y;
};

class Vector3
{
public:
	//Constructors
	Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
	Vector3(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]) {}
	Vector3(const Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z) {}

	//Vector's operations
	void Length(float &len);
	void Normalize(Vector3& res);
	Vector3 operator + (const Vector3 & vector);
	Vector3 & operator += (const Vector3 & vector);
	Vector3 operator - ();
	Vector3 operator - (const Vector3 & vector);
	Vector3 & operator -= (const Vector3 & vector);
	Vector3 operator * (const float & k);
	Vector3 & operator *= (const float & k);
	Vector3 operator / (const float & k);
	Vector3 & operator /= (const float & k);
	Vector3 & operator = (const Vector3 & vector);
	Vector3 Modulate(const Vector3 & vector);
	float Dot(const Vector3 & vector);
	Vector3 Cross(const Vector3 & vector);

	void Set(const float & x, const float & y, const float & z);
	void Set(const Vector4 &other);
	void Set(const Vector3 &other);
	void Create(const Vector3 & v3A, const Vector3 & v3B);

	void SetRotatationX(const float & angle);
	void SetRotatationY(const float & angle);
	void SetRotatationZ(const float & angle);

	//access to elements
	float operator [] (unsigned int idx);

	// data members
	float x;
	float y;
	float z;
};

class Vector4
{
public:
	//Constructors
	Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
	Vector4(float _x, float _y, float _z) : x(_x), y(_y), z(_z), w(1.0f) {}
	Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
	Vector4(float * pArg) : x(pArg[0]), y(pArg[1]), z(pArg[2]), w(pArg[3]) {}
	Vector4(Vector3 & vector) : x(vector.x), y(vector.y), z(vector.z), w(1.0f){}
	Vector4(Vector3 & vector, float _w) : x(vector.x), y(vector.y), z(vector.z), w(_w) {}
	Vector4(Vector4 & vector) : x(vector.x), y(vector.y), z(vector.z), w(vector.w) {}

	//Vector's operations
	//float Length();
	//Vector4 Normalize();
	//Vector4 operator + (Vector4 & vector);
	//Vector4 & operator += (Vector4 & vector);
	//Vector4 operator - ();
	//Vector4 operator - (Vector4 & vector);
	//Vector4 & operator -= (Vector4 & vector);
	//Vector4 operator * (float k);
	//Vector4 & operator *= (float k);
	//Vector4 operator / (float k);
	//Vector4 & operator /= (float k);
	//Vector4 & operator = (Vector4 & vector);
	//Vector4 Modulate(Vector4 & vector);
	//float Dot(Vector4 & vector);

	//void Set(const float & x, const float & y, const float & z, const float & w);
	//void Set(const Vector3 & other);

	////access to elements
	//float operator [] (unsigned int idx);

	//data members
	float x;
	float y;

	union{ float z, width; };
	union{ float w, height; };
};

//Matrix 4 X 4
class Matrix
{
public:
	//constructors
	Matrix() {}
	Matrix(float val);
	Matrix(Matrix & mat);
	Matrix(const Matrix & mat);

	// Matrix operations
	Matrix & SetZero();
	Matrix & SetIdentity();

	Matrix & SetRotationX(float angle);
	Matrix & SetRotationY(float angle);
	Matrix & SetRotationZ(float angle);
	Matrix & SetRotationAngleAxis(float angle, float x, float y, float z);

	Matrix & SetScale(float scale);
	Matrix & SetScale(float scaleX, float scaleY, float scaleZ);
	Matrix & SetScale(float * pScale);
	Matrix & SetScale(Vector3 &scaleVec);

	Matrix & SetTranslation(float x, float y, float z);
	Matrix & SetTranslation(float *pTrans);
	Matrix & SetTranslation(Vector3 &vec);

	Matrix & SetPerspective(float fovY, float aspect, float nearPlane, float farPlane);

	Matrix Transpose();
	void Inverse();

	Matrix operator + (Matrix & mat);
	Matrix & operator += (Matrix & mat);
	Matrix operator - (Matrix & mat);
	Matrix &operator -= (Matrix & mat);

	Matrix operator * (Matrix & mat);
	Matrix operator * (float k);
	Matrix & operator *= (float k);

	Vector4 operator * (Vector4 & vec);

	//Matrix & operator = (Matrix & mat);
	void operator= (const Matrix & mat);

	float* ToArray() {
		return &m[0][0];
	}

	//data members
	float m[4][4];
};
#endif