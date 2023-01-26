#include "Quaternion.h"
#include <cmath>
#include "Affin.h"

Quaternion::Quaternion()
{
	this->w = 1;
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion Quaternion::Multiply(Quaternion r)
{
	Quaternion result;

	/*Vector3 vq = {x,y,z};
	Vector3 vr = {r.x,r.y,r.z};

	result.w = w * r.w - vq.dot(vr);
	Vector3 qrv = vq.cross(vr) + r.w * vq + w * vr;
	result.x = qrv.x;
	result.x = qrv.y;
	result.x = qrv.z;*/

	result.w = w * r.w - x * r.x - y * r.y - z * r.z;
	result.x = y * r.z - z * r.y + r.w * x + w * r.x;
	result.y = z * r.x - x * r.z + r.w * y + w * r.y;
	result.z = x * r.y - y * r.x + r.w * z + w * r.z;

	return result;
}

Quaternion Quaternion::IdentityQuaternion()
{
	Quaternion result;

	result.w = 1;
	result.x = 0;
	result.y = 0;
	result.z = 0;

	return result;
}

Quaternion Quaternion::Conjugate()
{
	Quaternion result;

	result.w = w;
	result.x = -x;
	result.y = -y;
	result.z = -z;

	return result;
}

float Quaternion::Norm() const
{
	return sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Quaternion Quaternion::Normalize()
{
	Quaternion result = *this;

	float len = this->Norm();

	result = result / len;

	return result;
}

Quaternion Quaternion::INverse()
{
	Quaternion result = this->Conjugate() / pow(this->Norm(), 2);

	return result;
}

Quaternion MakeAxisAngle(const Vector3& axsi, float angle)
{
	Quaternion result;

	result.w = cos(angle / 2);

	Vector3 VecResult = axsi * sin(angle / 2);

	result.x = VecResult.x;
	result.y = VecResult.y;
	result.z = VecResult.z;

	return result;
}

Vector3 Quaternion::RotateVector(const Vector3& vector)
{
	Quaternion result;

	Quaternion VecQua;

	VecQua.w = 0;
	VecQua.x = vector.x;
	VecQua.y = vector.y;
	VecQua.z = vector.z;

	Quaternion conQuaternion = this->Conjugate();

	result = this->Multiply(VecQua);

	result = result.Multiply(conQuaternion);

	return { result.x,result.y,result.z };
}

Matrix4 Quaternion::MakeRotateMatrix()
{
	Matrix4 result = Affin::matUnit();

	result.m[0][0] = this->w * this->w + this->x * this->x - this->y * this->y - this->z * this->z;
	result.m[0][1] = 2 * (this->x * this->y + this->w * this->z);
	result.m[0][2] = 2 * (this->x * this->z - this->w * this->y);
	result.m[1][0] = 2 * (this->x * this->y - this->w * this->z);
	result.m[1][1] = this->w * this->w - this->x * this->x + this->y * this->y - this->z * this->z;
	result.m[1][2] = 2 * (this->y * this->z + this->w * this->x);
	result.m[2][0] = 2 * (this->x * this->z + this->w * this->y);
	result.m[2][1] = 2 * (this->y * this->z - this->w * this->x);
	result.m[2][2] = this->w * this->w - this->x * this->x - this->y * this->y + this->z * this->z;

	return result;
}

const Quaternion operator/(const Quaternion& v, float s)
{
	Quaternion result;

	result.w = v.w / s;
	result.x = v.x / s;
	result.y = v.y / s;
	result.z = v.z / s;

	return result;
}
