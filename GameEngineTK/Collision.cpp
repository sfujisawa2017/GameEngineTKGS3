#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ‹…‚Æ‹…‚Ì‚ ‚½‚è”»’è
/// </summary>
/// <param name="sphereA">‹…‚`</param>
/// <param name="sphereB">‹…‚a</param>
/// <returns>true: ƒqƒbƒg	false: ƒqƒbƒg‚¹‚¸</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// ‹…‚`‚Æ‚a‚Ì’†SÀ•W‚Ì·‚ðŒvŽZ‚·‚é
	Vector3 sub = sphereB.Center - sphereA.Center;

	// ‹——£‚Ì“ñæ
	float distanceSquare;
	// ŽO•½•û‚Ì’è—‚Å‹——£‚ðŽZo
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	// ”¼Œa‚Ì˜a‚Ì“ñæ
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	// ‹——£‚ª”¼Œa‚Ì˜a‚æ‚è‘å‚«‚¯‚ê‚Î“–‚½‚Á‚Ä‚¢‚È‚¢
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}