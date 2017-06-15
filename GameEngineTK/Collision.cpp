#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// 球と球のあたり判定
/// </summary>
/// <param name="sphereA">球Ａ</param>
/// <param name="sphereB">球Ｂ</param>
/// <returns>true: ヒット	false: ヒットせず</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// 球ＡとＢの中心座標の差を計算する
	Vector3 sub = sphereB.Center - sphereA.Center;

	// 距離の二乗
	float distanceSquare;
	// 三平方の定理で距離を算出
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	// 半径の和の二乗
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	// 距離が半径の和より大きければ当たっていない
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}