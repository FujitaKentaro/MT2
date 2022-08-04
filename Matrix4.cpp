#include "Matrix4.h"
#include "Affin.h"


Matrix4::Matrix4() {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = 0.0f;
		}
	}

}

Matrix4::Matrix4(float num) {

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m[i][j] = num;
		}
	}

}

// 成分を指定しての生成
Matrix4::Matrix4(
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) {
	m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
	m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
	m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
	m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Vector3 Matrix4::transform(const Vector3& v, const Matrix4& m) {

	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];

	Vector3 result{
		(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
		(v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
		(v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w,
	};

	return result;
}

// 
//// 代入演算子オーバーロード
//Matrix4& Matrix4::operator*=(const Matrix4& m2) {
//	
//	// 1
//	//	a		a			A			b			E			c		I			d			M		//
//	m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
//	//	b		a			B			"			F			"		J			"			N		//
//	m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
//	//	c		a			C			"			G			"		K			"			O		//
//	m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
//	//	d		a			D			"			H			"		L			"			P		//
//	m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];
//
//	// 2
//	//	e		e			A			f			E			g		I			h			M		//
//	m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
//	//	f		"			B			"			F			"		J			"			N		//
//	m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
//	//	g		"			C			"			G			"		K			"			O		//
//	m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
//	//	h		"			D			"			H			"		L			"			P		//
//	m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];
//
//	// 3
//	//	i		i			A			j			E			k		I			l			M		//
//	m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
//	//	j		"			B			"			F			"		J			"			N		//
//	m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
//	//	k		"			C			"			G			"		K			"			O		//
//	m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
//	//	l		"			D			"			H			"		L			"			P		//
//	m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];
//
//	// 4
//	//	m		m			A			n			E			o		I			p			M		//
//	m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
//	//	n		"			B			"			F			"		J			"			N		//
//	m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
//	//	o		"			C			"			G			"		K			"			O		//
//	m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
//	//	p		"			D			"			H			"		L			"			P		//
//	m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];
//
//	return *this;
//	/*
//	--		 --			--		 --
//	| a b c d |			| A B C D |
//	| e f g h |	   X	| E F G H |
//	| i j k l |			| I J K L |
//	| m n o p |			| M N O P |
//	--		 --			--		 --
//	*/
//}


Matrix4& operator*=(Matrix4& m1, const Matrix4& m2) {

	Matrix4 result{ 0 };

	for (int i = 0; i < 4; i++) {
		for (int k = 0; k < 4; k++) {
			result.m[i][k] =
				m1.m[i][0] * m2.m[0][k] +
				m1.m[i][1] * m2.m[1][k] +
				m1.m[i][2] * m2.m[2][k] +
				m1.m[i][3] * m2.m[3][k];
		}
	}
	m1 = result;
	return m1;
}



// 2項演算子オーバーロード ( 行列と行列の積 )
const Matrix4 operator*(const Matrix4& m1, const Matrix4& m2) {
	Matrix4 result = m1;

	return result *= m2;
}
//2項演算子オーバーロード ( ベクトルと行列の積 )
const Vector3 operator*(const Vector3& v, const Matrix4& m2) {
	Matrix4 mat = Affin::matUnit();
	Vector3 result = mat.transform(v, m2);
	return result;
}


