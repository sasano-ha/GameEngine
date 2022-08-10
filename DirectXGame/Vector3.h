#pragma once
#include <DirectXmath.h>

using namespace DirectX;

class Vector3
{
public:
	float x;
	float y;
	float z;

	// �R���X�g���N�^
	Vector3();
	Vector3(float x, float y, float z);

	// �����o�֐�
	float lenght() const;
	Vector3& normalize();	// ���K������
	float dot(const Vector3& v) const;	// ���ς����߂�
	Vector3 cross(const Vector3& v) const;	// �O�ς����߂�

	// �P�����Z�q�I�[�o�[���[�h
	Vector3 operator+() const;
	Vector3 operator-() const;

	// ������Z�q�I�[�o�[���[�h
	Vector3& operator+=(const Vector3& v);
	Vector3& operator-=(const Vector3& v);
	Vector3& operator*=(float s);
	Vector3& operator/=(float s);
};

// 2�����Z�q�I�[�o�[���[�h
const Vector3 operator+(const Vector3& v1, const Vector3& v2);
const Vector3 operator-(const Vector3& v1, const Vector3& v2);
const Vector3 operator*(const Vector3& v, float s);
const Vector3 operator*(float s, const Vector3& v);
const Vector3 operator/(const Vector3& v, float s);