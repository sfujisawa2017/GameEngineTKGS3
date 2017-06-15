#include "Collision.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// ���Ƌ��̂����蔻��
/// </summary>
/// <param name="sphereA">���`</param>
/// <param name="sphereB">���a</param>
/// <returns>true: �q�b�g	false: �q�b�g����</returns>
bool CheckSphere2Sphere(const Sphere& sphereA, const Sphere& sphereB)
{
	// ���`�Ƃa�̒��S���W�̍����v�Z����
	Vector3 sub = sphereB.Center - sphereA.Center;

	// �����̓��
	float distanceSquare;
	// �O�����̒藝�ŋ������Z�o
	distanceSquare = sub.x * sub.x + sub.y * sub.y + sub.z * sub.z;

	// ���a�̘a�̓��
	float radiusSquare;

	radiusSquare = sphereA.Radius + sphereB.Radius;
	radiusSquare = radiusSquare * radiusSquare;

	// ���������a�̘a���傫����Γ������Ă��Ȃ�
	if (distanceSquare > radiusSquare)
	{
		return false;
	}

	return true;
}