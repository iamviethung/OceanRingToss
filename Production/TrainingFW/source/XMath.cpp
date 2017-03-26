#include "XMath.h"

//Vector2
//float Vector2::Length()
//{
//	return sqrt(x*x + y*y);
//}
//
//Vector2 & Vector2::Normalize()
//{
//	float lenInv = 1.0f / Length();
//	x *= lenInv;
//	y *= lenInv;
//
//	return *this;
//}
//
//Vector2 Vector2::operator + (Vector2 & vector)
//{
//	return Vector2(x + vector.x, y + vector.y);
//}
//
//Vector2 & Vector2::operator += (Vector2 & vector)
//{
//	x += vector.x;
//	y += vector.y;
//
//	return *this;
//}
//
//Vector2 Vector2::operator - ()
//{
//	return Vector2(-x, -y);
//}
//
//Vector2 Vector2::operator - (Vector2 & vector)
//{
//	return Vector2(x - vector.x, y - vector.y);
//}
//
//Vector2 & Vector2::operator -= (Vector2 & vector)
//{
//	x -= vector.x;
//	y -= vector.y;
//
//	return *this;
//}
//
//Vector2 Vector2::operator * (float k)
//{
//	return Vector2(x * k, y * k);
//}
//
//Vector2 & Vector2::operator *= (float k)
//{
//	x *= k;
//	y *= k;
//
//	return *this;
//}
//
//Vector2 Vector2::operator / (float k)
//{
//	float kInv = 1.0f / k;
//	return Vector2(x * kInv, y * kInv);
//}
//
//Vector2 & Vector2::operator /= (float k)
//{
//	return operator *= (1.0f / k);
//}
//
//Vector2 & Vector2::operator = (Vector2 & vector)
//{
//	x = vector.x;
//	y = vector.y;
//
//	return *this;
//}
//
//float Vector2::operator [] (unsigned int idx)
//{
//	return (&x)[idx];
//}
//
//Vector2 Vector2::Modulate(Vector2 & vector)
//{
//	return Vector2(x * vector.x, y * vector.y);
//}
//
//float Vector2::Dot(Vector2 & vector)
//{
//	return x * vector.x + y * vector.y;
//}
//
//void Vector2::Set(const float &_x, const float &_y)
//{
//	x = _x;
//	y = _y;
//}

//Vector3

void Vector3::Length(float& len)
{
	len = sqrt(x*x + y*y + z*z);
}

void Vector3::Normalize(Vector3& res)
{
	float len;
	Length(len);
	float lenInv = 1.0f / len;
	res.x = x * lenInv;
	res.y = y * lenInv;
	res.z = z * lenInv;
}

Vector3 Vector3::operator + (const Vector3 & vector)
{
	return Vector3(x + vector.x, y + vector.y, z + vector.z);
}

Vector3 & Vector3::operator += (const Vector3 & vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;

	return *this;
}

Vector3 Vector3::operator - ()
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator - (const Vector3 & vector)
{
	return Vector3(x - vector.x, y - vector.y, z - vector.z);
}

Vector3 & Vector3::operator -= (const Vector3 & vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;

	return *this;
}

Vector3 Vector3::operator * (const float & k)
{
	return Vector3(x * k, y * k, z * k);
}

Vector3 & Vector3::operator *= (const float & k)
{
	x *= k;
	y *= k;
	z *= k;

	return *this;
}

Vector3 Vector3::operator / (const float & k)
{
	float kInv = 1.0f / k;
	return Vector3(x * kInv, y * kInv, z * kInv);
}

Vector3 & Vector3::operator /= (const float & k)
{
	return operator *= (1.0f / k);
}

Vector3 & Vector3::operator = (const Vector3 & vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;

	return *this;
}

float Vector3::operator [] (unsigned int idx)
{
	return (&x)[idx];
}

Vector3 Vector3::Modulate(const Vector3 & vector)
{
	return Vector3(x * vector.x, y * vector.y, z * vector.z);
}

float Vector3::Dot(const Vector3 & vector)
{
	return x * vector.x + y * vector.y + z * vector.z;
}

Vector3 Vector3::Cross(const Vector3 & vector)
{
	return Vector3(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
}

void Vector3::Create(const Vector3 &v3A, const Vector3 &v3B)
{
	x = v3B.x - v3A.x;
	y = v3B.y - v3A.y;
	z = v3B.z - v3A.z;
}

void Vector3::SetRotatationX(const float &angle)
{
	float sinAngle = sinf((angle));
	float cosAngle = cosf((angle));

	float y2 = y*cosAngle - z*sinAngle;
	float z2 = y*sinAngle + z*cosAngle;
	y = y2;
	z = z2;
}

void Vector3::SetRotatationY(const float &angle)
{
	float sinAngle = sinf((angle));
	float cosAngle = cosf((angle));

	float x2 = x*cosAngle + z*sinAngle;
	float z2 = -x*sinAngle + z*cosAngle;
	x = x2;
	z = z2;
}

void Vector3::SetRotatationZ(const float &angle)
{
	float sinAngle = sinf((angle));
	float cosAngle = cosf((angle));

	float x2 = x*cosAngle - y*sinAngle;
	float y2 = x*sinAngle + y*cosAngle;
	x = x2;
	y = y2;
}

void Vector3::Set(const float & x, const float & y, const float & z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector3::Set(const Vector4 & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

void Vector3::Set(const Vector3 & other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}


//Vector4
//float Vector4::Length()
//{
//	return sqrt(x*x + y*y + z*z + w*w);
//}
//
//Vector4 Vector4::Normalize()
//{
//	Vector4 res;
//	float lenInv = 1.0f / Length();
//	res.x = x *lenInv;
//	res.y = y *lenInv;
//	res.z = z *lenInv;
//	res.w = w *lenInv;
//
//	return res;
//}
//
//Vector4 Vector4::operator + (Vector4 & vector)
//{
//	return Vector4(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
//}
//
//Vector4 & Vector4::operator += (Vector4 & vector)
//{
//	x += vector.x;
//	y += vector.y;
//	z += vector.z;
//	w += vector.w;
//
//	return *this;
//}
//
//Vector4 Vector4::operator - ()
//{
//	return Vector4(-x, -y, -z, -w);
//}
//
//Vector4 Vector4::operator - (Vector4 & vector)
//{
//	return Vector4(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
//}
//
//Vector4 & Vector4::operator -= (Vector4 & vector)
//{
//	x -= vector.x;
//	y -= vector.y;
//	z -= vector.z;
//	w -= vector.w;
//
//	return *this;
//}
//
//Vector4 Vector4::operator * (float k)
//{
//	return Vector4(x * k, y * k, z * k, w * k);
//}
//
//Vector4 & Vector4::operator *= (float k)
//{
//	x *= k;
//	y *= k;
//	z *= k;
//	w *= k;
//
//	return *this;
//}
//
//Vector4 Vector4::operator / (float k)
//{
//	float kInv = 1.0f / k;
//	return Vector4(x * kInv, y * kInv, z * kInv, w * kInv);
//}
//
//Vector4 & Vector4::operator /= (float k)
//{
//	return operator *= (1.0f / k);
//}
//
//Vector4 & Vector4::operator = (Vector4 & vector)
//{
//	x = vector.x;
//	y = vector.y;
//	z = vector.z;
//	w = vector.w;
//	return *this;
//}
//
//float Vector4::operator [] (unsigned int idx)
//{
//	return (&x)[idx];
//}
//
//Vector4 Vector4::Modulate(Vector4 & vector)
//{
//	return Vector4(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
//}
//
//float Vector4::Dot(Vector4 & vector)
//{
//	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
//}
//
//void Vector4::Set(const float & x, const float & y, const float & z, const float & w)
//{
//	this->x = x;
//	this->y = y;
//	this->z = z;
//	this->w = w;
//}
//
//void Vector4::Set(const Vector3 & other)
//{
//	this->x = other.x;
//	this->y = other.y;
//	this->z = other.z;
//	this->w = 1.0f;
//}

//Matrix 4 X 4
Matrix::Matrix(float val)
{
	m[0][0] = val; m[0][1] = val; m[0][2] = val; m[0][3] = val;
	m[1][0] = val; m[1][1] = val; m[1][2] = val; m[1][3] = val;
	m[2][0] = val; m[2][1] = val; m[2][2] = val; m[2][3] = val;
	m[3][0] = val; m[3][1] = val; m[3][2] = val; m[3][3] = val;
}

Matrix::Matrix(Matrix & mat)
{
	m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2]; m[0][3] = mat.m[0][3];
	m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2]; m[1][3] = mat.m[1][3];
	m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2]; m[2][3] = mat.m[2][3];
	m[3][0] = mat.m[3][0]; m[3][1] = mat.m[3][1]; m[3][2] = mat.m[3][2]; m[3][3] = mat.m[3][3];
}

Matrix::Matrix(const Matrix & mat){
	m[0][0] = mat.m[0][0]; m[0][1] = mat.m[0][1]; m[0][2] = mat.m[0][2]; m[0][3] = mat.m[0][3];
	m[1][0] = mat.m[1][0]; m[1][1] = mat.m[1][1]; m[1][2] = mat.m[1][2]; m[1][3] = mat.m[1][3];
	m[2][0] = mat.m[2][0]; m[2][1] = mat.m[2][1]; m[2][2] = mat.m[2][2]; m[2][3] = mat.m[2][3];
	m[3][0] = mat.m[3][0]; m[3][1] = mat.m[3][1]; m[3][2] = mat.m[3][2]; m[3][3] = mat.m[3][3];
}

Matrix & Matrix::SetZero()
{
	m[0][0] = 0.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 0.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 0.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 0.0f;

	return *this;
}

Matrix & Matrix::SetIdentity()
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetRotationX(float angle)
{
	//angle = RADIAN(angle);
	float s = sinf(angle);
	float c = cosf(angle);
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = c; m[1][2] = s; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = -s; m[2][2] = c; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	return *this;
}

Matrix & Matrix::SetRotationY(float angle)
{
	//angle = RADIAN(angle);
	float s = sinf(angle);
	float c = cosf(angle);
	m[0][0] = c; m[0][1] = 0.0f; m[0][2] = -s; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = s; m[2][1] = 0.0f; m[2][2] = c; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	return *this;
}

Matrix & Matrix::SetRotationZ(float angle)
{
	//angle = RADIAN(angle);
	float s = sinf(angle);
	float c = cosf(angle);
	m[0][0] = c; m[0][1] = s; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = -s; m[1][1] = c; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = 0.0f; m[3][1] = 0.0f; m[3][2] = 0.0f; m[3][3] = 1.0f;
	return *this;
}

Matrix & Matrix::SetRotationAngleAxis(float angle, float x, float y, float z)
{
	float sinAngle, cosAngle;
	float mag = sqrtf(x * x + y * y + z * z);

	sinAngle = sinf((angle));
	cosAngle = cosf((angle));
	if (mag > 0.0f)
	{
		float xx, yy, zz, xy, yz, zx, xs, ys, zs;
		float oneMinusCos;
		float magInv = 1.0f / mag;

		x *= magInv;
		y *= magInv;
		z *= magInv;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinAngle;
		ys = y * sinAngle;
		zs = z * sinAngle;
		oneMinusCos = 1.0f - cosAngle;

		m[0][0] = (oneMinusCos * xx) + cosAngle;
		m[1][0] = (oneMinusCos * xy) - zs;
		m[2][0] = (oneMinusCos * zx) + ys;
		m[3][0] = 0.0F;

		m[0][1] = (oneMinusCos * xy) + zs;
		m[1][1] = (oneMinusCos * yy) + cosAngle;
		m[2][1] = (oneMinusCos * yz) - xs;
		m[3][1] = 0.0F;

		m[0][2] = (oneMinusCos * zx) - ys;
		m[1][2] = (oneMinusCos * yz) + xs;
		m[2][2] = (oneMinusCos * zz) + cosAngle;
		m[3][2] = 0.0F;

		m[0][3] = 0.0F;
		m[1][3] = 0.0F;
		m[2][3] = 0.0F;
		m[3][3] = 1.0F;
		return *this;
	}
	else
		return SetIdentity();
}

Matrix & Matrix::SetScale(float scale)
{
	m[0][0] = scale; m[0][1] = 0.0f;  m[0][2] = 0.0f;  m[0][3] = 0.0f;
	m[1][0] = 0.0f;  m[1][1] = scale; m[1][2] = 0.0f;  m[1][3] = 0.0f;
	m[2][0] = 0.0f;  m[2][1] = 0.0f;  m[2][2] = scale; m[2][3] = 0.0f;
	m[3][0] = 0.0f;  m[3][1] = 0.0f;  m[3][2] = 0.0f;  m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetScale(float scaleX, float scaleY, float scaleZ)
{
	m[0][0] = scaleX; m[0][1] = 0.0f;   m[0][2] = 0.0f;   m[0][3] = 0.0f;
	m[1][0] = 0.0f;   m[1][1] = scaleY; m[1][2] = 0.0f;   m[1][3] = 0.0f;
	m[2][0] = 0.0f;   m[2][1] = 0.0f;   m[2][2] = scaleZ; m[2][3] = 0.0f;
	m[3][0] = 0.0f;   m[3][1] = 0.0f;   m[3][2] = 0.0f;   m[3][3] = 1.0f;
	return *this;
}

Matrix & Matrix::SetScale(float * pScale)
{
	m[0][0] = pScale[0];   m[0][1] = 0.0f;        m[0][2] = 0.0f;        m[0][3] = 0.0f;
	m[1][0] = 0.0f;        m[1][1] = pScale[1];   m[1][2] = 0.0f;        m[1][3] = 0.0f;
	m[2][0] = 0.0f;        m[2][1] = 0.0f;        m[2][2] = pScale[2];   m[2][3] = 0.0f;
	m[3][0] = 0.0f;        m[3][1] = 0.0f;        m[3][2] = 0.0f;        m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetScale(Vector3 & scaleVec)
{
	m[0][0] = scaleVec.x; m[0][1] = 0.0f;       m[0][2] = 0.0f;       m[0][3] = 0.0f;
	m[1][0] = 0.0f;       m[1][1] = scaleVec.y; m[1][2] = 0.0f;       m[1][3] = 0.0f;
	m[2][0] = 0.0f;       m[2][1] = 0.0f;       m[2][2] = scaleVec.z; m[2][3] = 0.0f;
	m[3][0] = 0.0f;       m[3][1] = 0.0f;       m[3][2] = 0.0f;       m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetTranslation(float x, float y, float z)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = x; m[3][1] = y; m[3][2] = z; m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetTranslation(float *pTrans)
{
	m[0][0] = 1.0f;      m[0][1] = 0.0f;      m[0][2] = 0.0f;      m[0][3] = 0.0f;
	m[1][0] = 0.0f;      m[1][1] = 1.0f;      m[1][2] = 0.0f;      m[1][3] = 0.0f;
	m[2][0] = 0.0f;      m[2][1] = 0.0f;      m[2][2] = 1.0f;      m[2][3] = 0.0f;
	m[3][0] = pTrans[0]; m[3][1] = pTrans[1]; m[3][2] = pTrans[2]; m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetTranslation(Vector3 &vec)
{
	m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f; m[0][3] = 0.0f;
	m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f; m[1][3] = 0.0f;
	m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f; m[2][3] = 0.0f;
	m[3][0] = vec.x; m[3][1] = vec.y; m[3][2] = vec.z; m[3][3] = 1.0f;

	return *this;
}

Matrix & Matrix::SetPerspective(float fovY, float aspect, float nearPlane, float farPlane)
{
	float height = 2.0f * nearPlane * tanf(fovY * 0.5f);
	float width = height * aspect;
	float n2 = 2.0f * nearPlane;
	float rcpnmf = 1.f / (nearPlane - farPlane);

	m[0][0] = n2 / width;
	m[1][0] = 0;
	m[2][0] = 0;
	m[3][0] = 0;

	m[0][1] = 0;
	m[1][1] = n2 / height;
	m[2][1] = 0;
	m[3][1] = 0;

	m[0][2] = 0;
	m[1][2] = 0;
	m[2][2] = (farPlane + nearPlane) * rcpnmf;
	m[3][2] = farPlane * rcpnmf * n2;

	m[0][3] = 0;
	m[1][3] = 0;
	m[2][3] = -1.f;
	m[3][3] = 0;

	return *this;
}

Matrix Matrix::Transpose()
{
	Matrix res;
	res.m[0][0] = m[0][0]; res.m[0][1] = m[1][0]; res.m[0][2] = m[2][0]; res.m[0][3] = m[3][0];
	res.m[1][0] = m[0][1]; res.m[1][1] = m[1][1]; res.m[1][2] = m[2][1]; res.m[1][3] = m[3][1];
	res.m[2][0] = m[0][2]; res.m[2][1] = m[1][2]; res.m[2][2] = m[2][2]; res.m[2][3] = m[3][2];
	res.m[3][0] = m[0][3]; res.m[3][1] = m[1][3]; res.m[3][2] = m[2][3]; res.m[3][3] = m[3][3];
	return res;
}

void Matrix::Inverse()
{
	Matrix res;
	res.SetIdentity();

	double det;
	double d12, d13, d23, d24, d34, d41;
	double tmp[16];

	// Inverse = adjoint / det. (See linear algebra texts.)
	// pre-compute 2x2 dets for last two rows when computing
	// cofactors of first two rows.
	d12 = (m[0][2] * m[1][3] - m[0][3] * m[1][2]);
	d13 = (m[0][2] * m[2][3] - m[0][3] * m[2][2]);
	d23 = (m[1][2] * m[2][3] - m[1][3] * m[2][2]);
	d24 = (m[1][2] * m[3][3] - m[1][3] * m[3][2]);
	d34 = (m[2][2] * m[3][3] - m[2][3] * m[3][2]);
	d41 = (m[3][2] * m[0][3] - m[3][3] * m[0][2]);

	tmp[0] = (m[1][1] * d34 - m[2][1] * d24 + m[3][1] * d23);
	tmp[1] = -(m[0][1] * d34 + m[2][1] * d41 + m[3][1] * d13);
	tmp[2] = (m[0][1] * d24 + m[1][1] * d41 + m[3][1] * d12);
	tmp[3] = -(m[0][1] * d23 - m[1][1] * d13 + m[2][1] * d12);

	// Compute determinant as early as possible using these cofactors.
	det = m[0][0] * tmp[0] + m[1][0] * tmp[1] + m[2][0] * tmp[2] + m[3][0] * tmp[3];

	// Run singularity test.
	/*
	if (det == 0.0) {
	printf("invert_matrix: Warning: Singular matrix.\n");
	return res;
	}*/
	//else {
	double invDet = 1.0 / det;
	// Compute rest of inverse.
	tmp[0] *= invDet;
	tmp[1] *= invDet;
	tmp[2] *= invDet;
	tmp[3] *= invDet;

	tmp[4] = -(m[1][0] * d34 - m[2][0] * d24 + m[3][0] * d23) * invDet;
	tmp[5] = (m[0][0] * d34 + m[2][0] * d41 + m[3][0] * d13) * invDet;
	tmp[6] = -(m[0][0] * d24 + m[1][0] * d41 + m[3][0] * d12) * invDet;
	tmp[7] = (m[0][0] * d23 - m[1][0] * d13 + m[2][0] * d12) * invDet;

	// Pre-compute 2x2 dets for first two rows when computing
	// cofactors of last two rows.
	d12 = m[0][0] * m[1][1] - m[0][1] * m[1][0];
	d13 = m[0][0] * m[2][1] - m[0][1] * m[2][0];
	d23 = m[1][0] * m[2][1] - m[1][1] * m[2][0];
	d24 = m[1][0] * m[3][1] - m[1][1] * m[3][0];
	d34 = m[2][0] * m[3][1] - m[2][1] * m[3][0];
	d41 = m[3][0] * m[0][1] - m[3][1] * m[0][0];

	tmp[8] = (m[1][3] * d34 - m[2][3] * d24 + m[3][3] * d23) * invDet;
	tmp[9] = -(m[0][3] * d34 + m[2][3] * d41 + m[3][3] * d13) * invDet;
	tmp[10] = (m[0][3] * d24 + m[1][3] * d41 + m[3][3] * d12) * invDet;
	tmp[11] = -(m[0][3] * d23 - m[1][3] * d13 + m[2][3] * d12) * invDet;
	tmp[12] = -(m[1][2] * d34 - m[2][2] * d24 + m[3][2] * d23) * invDet;
	tmp[13] = (m[0][2] * d34 + m[2][2] * d41 + m[3][2] * d13) * invDet;
	tmp[14] = -(m[0][2] * d24 + m[1][2] * d41 + m[3][2] * d12) * invDet;
	tmp[15] = (m[0][2] * d23 - m[1][2] * d13 + m[2][2] * d12) * invDet;

	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			res.m[i][j] = (float)tmp[i * 4 + j];
	//}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = res.m[i][j];
		}
	}
}

Matrix Matrix::operator + (Matrix & mat)
{
	Matrix res(*this);
	res += mat;
	return res;
}

Matrix & Matrix::operator += (Matrix & mat)
{
	m[0][0] += mat.m[0][0]; m[0][1] += mat.m[0][1]; m[0][2] += mat.m[0][2]; m[0][3] += mat.m[0][3];
	m[1][0] += mat.m[1][0]; m[1][1] += mat.m[1][1]; m[1][2] += mat.m[1][2]; m[1][3] += mat.m[1][3];
	m[2][0] += mat.m[2][0]; m[2][1] += mat.m[2][1]; m[2][2] += mat.m[2][2]; m[2][3] += mat.m[2][3];
	m[3][0] += mat.m[3][0]; m[3][1] += mat.m[3][1]; m[3][2] += mat.m[3][2]; m[3][3] += mat.m[3][3];

	return *this;
}

Matrix Matrix::operator - (Matrix & mat)
{
	Matrix res(*this);
	res -= mat;
	return res;
}

Matrix & Matrix::operator -= (Matrix & mat)
{
	m[0][0] -= mat.m[0][0]; m[0][1] -= mat.m[0][1]; m[0][2] -= mat.m[0][2]; m[0][3] -= mat.m[0][3];
	m[1][0] -= mat.m[1][0]; m[1][1] -= mat.m[1][1]; m[1][2] -= mat.m[1][2]; m[1][3] -= mat.m[1][3];
	m[2][0] -= mat.m[2][0]; m[2][1] -= mat.m[2][1]; m[2][2] -= mat.m[2][2]; m[2][3] -= mat.m[2][3];
	m[3][0] -= mat.m[3][0]; m[3][1] -= mat.m[3][1]; m[3][2] -= mat.m[3][2]; m[3][3] -= mat.m[3][3];

	return *this;
}

Matrix Matrix::operator * (Matrix & mat)
{
	Matrix res;
	res.m[0][0] = m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0] + m[0][3] * mat.m[3][0];
	res.m[0][1] = m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1] + m[0][3] * mat.m[3][1];
	res.m[0][2] = m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2] + m[0][3] * mat.m[3][2];
	res.m[0][3] = m[0][0] * mat.m[0][3] + m[0][1] * mat.m[1][3] + m[0][2] * mat.m[2][3] + m[0][3] * mat.m[3][3];

	res.m[1][0] = m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0] + m[1][3] * mat.m[3][0];
	res.m[1][1] = m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1] + m[1][3] * mat.m[3][1];
	res.m[1][2] = m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2] + m[1][3] * mat.m[3][2];
	res.m[1][3] = m[1][0] * mat.m[0][3] + m[1][1] * mat.m[1][3] + m[1][2] * mat.m[2][3] + m[1][3] * mat.m[3][3];

	res.m[2][0] = m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0] + m[2][3] * mat.m[3][0];
	res.m[2][1] = m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1] + m[2][3] * mat.m[3][1];
	res.m[2][2] = m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2] + m[2][3] * mat.m[3][2];
	res.m[2][3] = m[2][0] * mat.m[0][3] + m[2][1] * mat.m[1][3] + m[2][2] * mat.m[2][3] + m[2][3] * mat.m[3][3];

	res.m[3][0] = m[3][0] * mat.m[0][0] + m[3][1] * mat.m[1][0] + m[3][2] * mat.m[2][0] + m[3][3] * mat.m[3][0];
	res.m[3][1] = m[3][0] * mat.m[0][1] + m[3][1] * mat.m[1][1] + m[3][2] * mat.m[2][1] + m[3][3] * mat.m[3][1];
	res.m[3][2] = m[3][0] * mat.m[0][2] + m[3][1] * mat.m[1][2] + m[3][2] * mat.m[2][2] + m[3][3] * mat.m[3][2];
	res.m[3][3] = m[3][0] * mat.m[0][3] + m[3][1] * mat.m[1][3] + m[3][2] * mat.m[2][3] + m[3][3] * mat.m[3][3];

	return res;
}

Matrix Matrix::operator * (float k)
{
	Matrix mat(*this);
	mat *= k;
	return mat;
}

Matrix & Matrix::operator *= (float k)
{
	m[0][0] *= k; m[0][1] *= k; m[0][2] *= k; m[0][3] *= k;
	m[1][0] *= k; m[1][1] *= k; m[1][2] *= k; m[1][3] *= k;
	m[2][0] *= k; m[2][1] *= k; m[2][2] *= k; m[2][3] *= k;
	m[3][0] *= k; m[3][1] *= k; m[3][2] *= k; m[3][3] *= k;

	return *this;
}

Vector4 Matrix::operator * (Vector4 & vec)
{
	Vector4 res;
	res.x = vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + vec.w * m[3][0];
	res.y = vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + vec.w * m[3][1];
	res.z = vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + vec.w * m[3][2];
	res.w = vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + vec.w * m[3][3];

	return res;
}

void Matrix::operator=(const Matrix &matrix)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = matrix.m[i][j];
		}
	}
}
