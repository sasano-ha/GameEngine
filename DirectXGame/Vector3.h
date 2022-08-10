#pragma once
#include <DirectXmath.h>

using namespace DirectX;

class Vector3
{
public:
	float x;
	float y;
	float z;

	// コンストラクタ
	Vector3();
	Vector3(float x, float y, float z);

	// メンバ関数
	float lenght() const;
	Vector3& normalize();	// 正規化する
	float dot(const Vector3& v) const;	// 内積を求める
	Vector3 cross(const Vector3& v) const;	// 外積を求める

	// 単項演算子オーバーロード
	Vector3 operator+() const;
	Vector3 operator-() const;

	// 代入演算子オーバーロード
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

// 2項演算子オーバーロード
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);