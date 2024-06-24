#pragma once

#include "Matrix4x4.h"
#include "Vector3.h"
#define _USE_MATH_DEFINES
#include <cmath>

// 代入演算子オーバーロード
// Vector3の足し算
Vector3& operator+=(Vector3& lhs, const Vector3& rhv);

Vector3 operator+(const Vector3& v1, const Vector3& v2);

// 代入演算子オーバーロード
// Vector3の掛け算
Vector3& operator*=(Vector3& v, float s);

// 2項演算子オーバーロード
// Vector3の掛け算
const Vector3 operator*(const Vector3& v, float s);

// ease In-Out
float easeInOut(float t, float x1, float x2);

// Lerp
float Lerp(float x1, float x2, float t);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);

// 1, x軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian);

// 2, y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian);

// 3, z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian);

Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);

// ３次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
