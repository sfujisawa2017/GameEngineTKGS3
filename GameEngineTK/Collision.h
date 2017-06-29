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

// 法線付き三角形（反時計回りが表面） 
class Triangle
{
public:
	DirectX::SimpleMath::Vector3	P0;
	DirectX::SimpleMath::Vector3	P1;
	DirectX::SimpleMath::Vector3	P2;
	DirectX::SimpleMath::Vector3	Normal;	// 法線ベクトル 
};


bool CheckSphere2Sphere(const Sphere & sphereA, const Sphere & sphereB);
