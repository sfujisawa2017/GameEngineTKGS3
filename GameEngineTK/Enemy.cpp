//--------------------------------------------------------------------------------------
// �t�@�C����: Enemy.cpp
// �쐬��:
// �쐬��:
// ����:
//--------------------------------------------------------------------------------------

#include "Enemy.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Enemy::Enemy(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
}

Enemy::~Enemy()
{
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Enemy::Initialize()
{
	// ���@�p�[�c�̓ǂݍ���
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_Obj[PARTS_COCKPIT].LoadModel(L"Resources/cockpit.cmo");
	m_Obj[PARTS_LAUNCHER].LoadModel(L"Resources/launcher.cmo");
	m_Obj[PARTS_SHIELD].LoadModel(L"Resources/shield.cmo");
	m_Obj[PARTS_DRILL].LoadModel(L"Resources/drill.cmo");

	// �p�[�c�̐e�q�֌W���Z�b�g
	m_Obj[PARTS_COCKPIT].SetParent(
		&m_Obj[PARTS_BODY]);

	m_Obj[PARTS_DRILL].SetParent(
		&m_Obj[PARTS_COCKPIT]);

	m_Obj[PARTS_LAUNCHER].SetParent(
		&m_Obj[PARTS_BODY]);

	m_Obj[PARTS_SHIELD].SetParent(
		&m_Obj[PARTS_BODY]);

	// �e����̃I�t�Z�b�g�i���W�̂��炵���j���Z�b�g
	m_Obj[PARTS_COCKPIT].SetTranslation(
		Vector3(0, 0.37f, -0.4f));
	m_Obj[PARTS_COCKPIT].SetRotation(
		Vector3(0, XM_PI, 0));

	m_Obj[PARTS_DRILL].SetTranslation(
		Vector3(0, 0.1f, 0.8f));

	m_Obj[PARTS_LAUNCHER].SetTranslation(
		Vector3(0, 0.37f, 0.4f));

	m_Obj[PARTS_SHIELD].SetTranslation(
		Vector3(-0.8f, 0.37f, 0));
	m_Obj[PARTS_SHIELD].SetScale(
		Vector3(2, 2, 2));
	m_Obj[PARTS_SHIELD].SetRotation(
		Vector3(0, 0, XM_PIDIV2));

	// �����z�u
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;

	this->SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Enemy::Update()
{
	//// �L�[�{�[�h�̍X�V
	//Keyboard::State keystate = m_pKeyboard->GetState();
	//m_KeyboardTracker.Update(keystate);

	// ���@�p�[�c�̃M�~�b�N
	//{
	//	m_sinAngle += 0.1f;

	//	Vector3 angle;
	//	angle = m_Obj[PARTS_DRILL].GetRotation();

	//	m_Obj[PARTS_DRILL].SetRotation(
	//		Vector3(0, 0, sinf(m_sinAngle)*10.0f));

	//	Vector3 pos;

	//	//pos = m_Obj[PARTS_DRILL].GetTranslation();
	//	//m_Obj[PARTS_DRILL].SetTranslation(
	//	//	pos += Vector3(0, 0, 0.03f));


	//	//m_Obj[PARTS_SHIELD].SetTranslation(
	//	//	Vector3(-0.8f, 0.37f, 0)+
	//	//	Vector3(0, 0, sinf(m_sinAngle)));

	//	m_Obj[PARTS_SHIELD].SetTranslation(
	//		Vector3(-0.8f, 0.37f, 0) +
	//		Vector3(cosf(m_sinAngle)*10.0f, 0, sinf(m_sinAngle)*5.0f));
	//}

	m_Timer--;
	if (m_Timer < 0)
	{
		m_Timer = 60;
		// -0.5�`+0.5�̗���
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// ���@�̊p�x����]������
		Vector3 rotv = m_Obj[0].GetRotation();
		
		float angle = m_DistAngle - rotv.y;

		// 180�x�𒴂��Ă����ꍇ�A�t���̕����߂�
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// ���
		rotv.y += angle * 0.05f;

		SetRot(rotv);
	}

	// �@�̂������Ă�������ɐi��
	{
		// �ړ��ʂ̃x�N�g��
		Vector3 moveV(0, 0, -0.1f);
		// �ړ��ʃx�N�g�������@�̊p�x����]������
		//moveV = Vector3::TransformNormal(moveV, tank_world);
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�������
		Vector3 pos = m_Obj[0].GetTranslation();
		m_Obj[0].SetTranslation(pos + moveV);
	}
	
	Calc();
}

//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void Enemy::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}
}

//-----------------------------------------------------------------------------
// �`��
//-----------------------------------------------------------------------------
void Enemy::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}
}

const DirectX::SimpleMath::Vector3& Enemy::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Enemy::GetRot()
{
	// �^���N�p�[�c�̉�]��Ԃ�
	return m_Obj[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Enemy::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_Obj[0].GetWorld();
}
