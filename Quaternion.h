#pragma once
#include"vector3.h"
#include"Matrix4.h"
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion();
	Quaternion(float x,float y,float z,float w);

	//Quaternionの積
	Quaternion Multiply(Quaternion r);
	//単位Quaternionを返す
	Quaternion IdentityQuaternion();
	//共役Quaternionを返す
	Quaternion Conjugate();
	//Quaternionのnormを返す
	float Norm() const;
	//正規化したQuaternionを返す
	Quaternion Normalize();
	//逆Quaternionを返す
	Quaternion INverse();
	//ベクトルをQuaternionで回転させた結果のベクトルを求める
	Vector3 RotateVector(const Vector3& vector);
	//Quaternionから回転行列を求める
	Matrix4 MakeRotateMatrix();
};

//任意軸回転を表すQuaternionの生成
Quaternion MakeAxisAngle(const Vector3& axsi, float angle);

const Quaternion operator/(const Quaternion& v, float s);

