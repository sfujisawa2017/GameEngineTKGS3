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

/// <summary>
/// 三点の座標から三角形を計算（反時計回りに頂点を指定）
/// </summary>
/// <param name="_p0">点０</param>
/// <param name="_p1">点１</param>
/// <param name="_p2">点２</param>
/// <param name="_triangle">三角形（結果出力用）</param>
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	// 座標をコピー
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// 法線ベクトルを計算
	Vector3 P0_P1 = _p1 - _p0;
	Vector3 P1_P2 = _p2 - _p1;

	// 外積で2ベクトルに垂直なベクトルを算出
	_triangle->Normal = P0_P1.Cross(P1_P2);
	_triangle->Normal.Normalize();
}

/// <summary>
/// 点と法線付き三角形の最近接点
/// </summary>
/// <param name="_point">点</param>
/// <param name="_tri">三角形</param>
/// <param name="_closest">最近接点（出力）</param>
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _tri, Vector3* _closest)
{
	// _pointがP0の外側の頂点領域の中にあるかチェック
	Vector3 P0_P1 = _tri.P1 - _tri.P0;
	Vector3 P0_P2 = _tri.P2 - _tri.P0;
	Vector3 P0_PT = _point - _tri.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0が一番近い
		*_closest = _tri.P0;
		return;
	}

	// _pointがP1の外側の頂点領域の中にあるかチェック
	Vector3 P1_PT = _point - _tri.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1が一番近い
		*_closest = _tri.P1;
		return;
	}

	// _pointがP0_P1の辺領域の中にあるかどうかチェックし、あれば
	// _pointのP0_P1上に対する射影を返す
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{

	}

}

/// <summary>
/// 球と法線付き三角形の当たりチェック
/// </summary>
/// <param name="_sphere">球</param>
/// <param name="_tri">三角形</param>
/// <param name="_inter">交点座標（出力）</param>
/// <returns></returns>
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _tri, Vector3* _inter)
{
	Vector3 p;

	// 球の中心に対する最近接点である三角形にある点pを見つける
	ClosestPtPoint2Triangle(_sphere.Center, _tri, &p);


}