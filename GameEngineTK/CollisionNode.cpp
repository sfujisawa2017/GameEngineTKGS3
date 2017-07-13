#include "CollisionNode.h"

using namespace DirectX::SimpleMath;

bool CollisionNode::m_DebugVisible = false;

/// <summary>
/// CollisionNode�̃����o�֐�
/// </summary>

void CollisionNode::SetParent(Obj3d * parent)
{
	m_Obj.SetParent(parent);
}

/// <summary>
/// SphereNode�̃����o�֐�
/// </summary>

SphereNode::SphereNode()
{
	// �f�t�H���g���a��1���[�g���ɂ���
	m_LocalRadius = 1.0f;
}

void SphereNode::Initialize()
{
	// �f�o�b�O�\���p���f����ǂݍ���
	m_Obj.LoadModel(L"Resources/SphereNode.cmo");
}

void SphereNode::Update()
{
	m_Obj.SetTranslation(m_Trans);
	m_Obj.SetScale(Vector3(m_LocalRadius));

	// ���[���h�s��̍X�V
	m_Obj.Update();

	{// ���[���h���W�ł̓����蔻�苅���v�Z
		// �v�Z�ς݂̃��[���h�s����擾
		const Matrix& worldm = m_Obj.GetWorld();

		// ���f�����W�n�ł̒��S�_
		Vector3 center(0, 0, 0);
		// ���f�����W�n�ł̉E�[
		Vector3 right(1, 0, 0);

		// ���[���h���W�ɕϊ�
		center = Vector3::Transform(center, worldm);
		right = Vector3::Transform(right, worldm);

		// �����蔻�苅�Ɍ��ʂ���
		Sphere::Center = center;
		Sphere::Radius = Vector3::Distance(center, right);
	}
}

void SphereNode::Draw()
{
	m_Obj.Draw();
}
