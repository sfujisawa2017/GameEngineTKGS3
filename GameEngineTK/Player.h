/**
*	@file	Player.h
*
*	@brief	���@
*
*	@date	2015/05/08
*
*	@author	���V�@�L��
*/
#pragma once

#include <d3d11_1.h>
#include <SimpleMath.h>
#include <Keyboard.h>
#include <vector>
#include "Obj3D.h"
#include "CollisionNode.h"

// ���@
class Player
{
public:
	// ���{�b�g�p�[�c
	// ���@�p�[�c
	enum PARTS
	{
		PARTS_BODY,
		PARTS_COCKPIT,
		PARTS_LAUNCHER,
		PARTS_SHIELD,
		PARTS_DRILL,

		PARTS_NUM
	};

	// �R���X�g���N�^
	Player(DirectX::Keyboard* keyboard);
	// �f�X�g���N�^
	~Player();
	// ������
	void Initialize();
	// ���t���[���X�V
	void Update();
	// �s��̌v�Z
	void Calc();
	// �`��
	void Draw();
	// �e�ۂ𔭎�
	void FireBullet();
	// �e�ۂ��đ����i���Z�b�g�j
	void ResetBullet();

	// ���W���擾
	const DirectX::SimpleMath::Vector3& GetTrans();
	// ��]���擾
	const DirectX::SimpleMath::Vector3& GetRot();
	// ���W��ݒ�
	void SetTrans(const DirectX::SimpleMath::Vector3& trans);
	// ��]��ݒ�
	void SetRot(const DirectX::SimpleMath::Vector3& rot);
	// ���[���h�s����擾
	const DirectX::SimpleMath::Matrix& GetLocalWorld();
	// �e�ۗp�����蔻����擾
	const SphereNode& GetCollisionNodeBullet() { return m_CollisionNodeBullet; }

protected:
	// �����o�ϐ�
	// ���{�b�g�̍\���p�[�c
	std::vector<Obj3d>	m_Obj;
	// �L�[�{�[�h
	DirectX::Keyboard* m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker m_KeyboardTracker;

	// �T�C���p�̈����ƂȂ�p�x
	float m_sinAngle;

	// �e�ۂ̑��x�x�N�g��
	DirectX::SimpleMath::Vector3 m_BulletVel;
	// �e�۔��˒��t���O
	bool m_FireFlag;

	// �e�ۗp�̓����蔻��
	SphereNode m_CollisionNodeBullet;
};

