/// <summary>
/// 衝突判定ライブラリ
/// </summary>
#pragma once

//#include <Windows.h>
#include <d3d11_1.h>
#include <SimpleMath.h>

// 球
class Sphere
{
public:
	// 中心座標
	DirectX::SimpleMath::Vector3 Center;
	// 半径
	float Radius;
	// コンストラクタ
	Sphere()
	{
		// 半径１メートル
		Radius = 1.0f;
	}
};

// 線分
class Segment
{
public:
	// 始点
	DirectX::SimpleMath::Vector3 Start;
	// 終点
	DirectX::SimpleMath::Vector3 End;
};

bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
