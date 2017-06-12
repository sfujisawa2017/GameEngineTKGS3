//--------------------------------------------------------------------------------------
// �t�@�C����: Player.cpp
// �쐬��:
// �쐬��:
// ����:
//--------------------------------------------------------------------------------------

#include "Player.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Player::Player(DirectX::Keyboard* keyboard)
{
	m_pKeyboard = keyboard;

	m_sinAngle = 0.0f;

	Initialize();
}

Player::~Player()
{
}

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
void Player::Initialize()
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
}

//-----------------------------------------------------------------------------
// �X�V
//-----------------------------------------------------------------------------
void Player::Update()
{
	// �L�[�{�[�h�̍X�V
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

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

	// A�L�[��������Ă�����
	if (keystate.A)
	{
		// ���@�̊p�x����]������
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	// D�L�[��������Ă�����
	if (keystate.D)
	{
		// ���@�̊p�x����]������
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	// W�L�[��������Ă�����
	if (keystate.W)
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

	// S�L�[��������Ă�����
	if (keystate.S)
	{
		// �ړ��ʂ̃x�N�g��
		Vector3 moveV(0, 0, +0.1f);
		// �ړ��ʃx�N�g�������@�̊p�x����]������
		//moveV = Vector3::TransformNormal(moveV, tank_world);
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// ���@�̍��W���ړ�������
		Vector3 pos = m_Obj[0].GetTranslation();
		m_Obj[0].SetTranslation(pos + moveV);
	}

	// �e�ۂ�O�i������
	{
		// ���@�̍��W���ړ�������
		Vector3 pos = m_Obj[PARTS_DRILL].GetTranslation();
		m_Obj[PARTS_DRILL].SetTranslation(pos + m_BulletVel);
	}
	
	Calc();

	FireBullet();
}

//-----------------------------------------------------------------------------
// �s��X�V
//-----------------------------------------------------------------------------
void Player::Calc()
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
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}
}

void Player::FireBullet()
{
	// ���˂���p�[�c�̃��[���h�s����擾
	Matrix worldm = m_Obj[PARTS_DRILL].GetWorld();

	// ���[���h�s�񂩂�e�v�f�𒊏o
	Vector3 scale;			// ���[���h�X�P�[�����O
	Quaternion rotation;	// ���[���h��]
	Vector3 translation;	// ���[���h���W

	worldm.Decompose(scale, rotation, translation);

	// ���˃p�[�c��e���番�����ēƗ�
	m_Obj[PARTS_DRILL].SetParent(nullptr);
	m_Obj[PARTS_DRILL].SetScale(scale);
	m_Obj[PARTS_DRILL].SetRotationQ(rotation);
	m_Obj[PARTS_DRILL].SetTranslation(translation);

	// �e�ۂ̑��x��ݒ�
	m_BulletVel = Vector3(0, 0, -0.1f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);
}

void Player::ResetBullet()
{
}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	// �^���N�p�[�c�̍��W��Ԃ�
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Player::GetRot()
{
	// �^���N�p�[�c�̉�]��Ԃ�
	return m_Obj[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// �^���N�p�[�c�̍��W��ݒ�
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	// �^���N�p�[�c�̃��[���h�s���Ԃ�
	return m_Obj[0].GetWorld();
}
