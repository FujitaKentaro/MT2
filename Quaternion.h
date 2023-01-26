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

	//単項演算子オーバーロード
	Quaternion operator+() const;
	Quaternion operator-() const;

	//代入演算子オーバーロード
	Quaternion& operator+=(const Quaternion& v);
	Quaternion& operator-=(const Quaternion& v);
	Quaternion& operator*=(float s);
	Quaternion& operator/=(float s);
};

//任意軸回転を表すQuaternionの生成
Quaternion MakeAxisAngle(const Vector3& axsi, float angle);
//球面線形補間
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);

//2項演算子オーバーロード
const Quaternion operator+(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator-(const Quaternion& v1, const Quaternion& v2);
const Quaternion operator*(const Quaternion& v, float s);
const Quaternion operator*(float s, const Quaternion& v);

const Quaternion operator/(const Quaternion& v, float s);

