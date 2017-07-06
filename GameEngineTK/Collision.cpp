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
	Vector3 P0_P1 = _p1 - _p0;
	Vector3 P1_P2 = _p2 - _p1;

	// �O�ς�2�x�N�g���ɐ����ȃx�N�g�����Z�o
	_triangle->Normal = P0_P1.Cross(P1_P2);
	_triangle->Normal.Normalize();
}

/// <summary>
/// �_�Ɩ@���t���O�p�`�̍ŋߐړ_
/// </summary>
/// <param name="_point">�_</param>
/// <param name="_tri">�O�p�`</param>
/// <param name="_closest">�ŋߐړ_�i�o�́j</param>
void ClosestPtPoint2Triangle(const Vector3& _point, const Triangle& _tri, Vector3* _closest)
{
	// _point��P0�̊O���̒��_�̈�̒��ɂ��邩�`�F�b�N
	Vector3 P0_P1 = _tri.P1 - _tri.P0;
	Vector3 P0_P2 = _tri.P2 - _tri.P0;
	Vector3 P0_PT = _point - _tri.P0;

	float d1 = P0_P1.Dot(P0_PT);
	float d2 = P0_P2.Dot(P0_PT);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// P0����ԋ߂�
		*_closest = _tri.P0;
		return;
	}

	// _point��P1�̊O���̒��_�̈�̒��ɂ��邩�`�F�b�N
	Vector3 P1_PT = _point - _tri.P1;

	float d3 = P0_P1.Dot(P1_PT);
	float d4 = P0_P2.Dot(P1_PT);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// P1����ԋ߂�
		*_closest = _tri.P1;
		return;
	}

	// _point��P0_P1�̕ӗ̈�̒��ɂ��邩�ǂ����`�F�b�N���A�����
	// _point��P0_P1��ɑ΂���ˉe��Ԃ�
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{

	}

}

/// <summary>
/// ���Ɩ@���t���O�p�`�̓�����`�F�b�N
/// </summary>
/// <param name="_sphere">��</param>
/// <param name="_tri">�O�p�`</param>
/// <param name="_inter">��_���W�i�o�́j</param>
/// <returns></returns>
bool CheckSphere2Triangle(const Sphere& _sphere, const Triangle& _tri, Vector3* _inter)
{
	Vector3 p;

	// ���̒��S�ɑ΂���ŋߐړ_�ł���O�p�`�ɂ���_p��������
	ClosestPtPoint2Triangle(_sphere.Center, _tri, &p);


}