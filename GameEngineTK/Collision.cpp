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

/// <summary>
/// �O�_�̍��W����O�p�`���v�Z�i�����v���ɒ��_���w��j
/// </summary>
/// <param name="_p0">�_�O</param>
/// <param name="_p1">�_�P</param>
/// <param name="_p2">�_�Q</param>
/// <param name="_triangle">�O�p�`�i���ʏo�͗p�j</param>
void ComputeTriangle(const Vector3& _p0, const Vector3& _p1, const Vector3& _p2, Triangle* _triangle)
{
	// ���W���R�s�[
	_triangle->P0 = _p0;
	_triangle->P1 = _p1;
	_triangle->P2 = _p2;

	// �@���x�N�g�����v�Z
	//Vector3 
}