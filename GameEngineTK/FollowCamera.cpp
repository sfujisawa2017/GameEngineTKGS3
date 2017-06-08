#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̏�����
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0;
	m_keyboard = nullptr;
	m_isFPS = false;
	m_player = nullptr;
}

void FollowCamera::Update()
{
	// �L�[�{�[�h�̏�Ԏ擾
	Keyboard::State keyboardstate = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboardstate);

	// C�L�[���������Ƃ�FPS/TPS��؂�ւ�
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		// �t���O��؂�ւ�
		m_isFPS = !m_isFPS;
		if (m_isFPS)
		{

		}
	}

	if (m_player)
	{
		// �ڕW���W�̐ݒ�
		SetTargetPos(m_player->GetTrans());
		SetTargetAngle(m_player->GetRot().y);
	}

	// ���_�A�Q�Ɠ_���W
	Vector3 eyepos, refpos;
	if (m_isFPS)
	{// FPS�J����
	 // ���@�̖ڂ̈ʒu����������_�Ƃ���
		Vector3 position;

		position = m_targetPos + Vector3(0, 0.2f, 0);
		// �Q�Ɠ_�Ǝ��_�̍����x�N�g��
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		// ���@�̌��ɉ�荞�ނ��߂̉�]�s��𐶐�
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// �����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV * 0.1f;
		// �Q�Ɠ_���W���v�Z
		refpos = position + cameraV;
	}
	else
	{// TPS�J����
		// ���@�̏��Q�����Q�Ɠ_�Ƃ���
		refpos = m_targetPos + Vector3(0, 2, 0);
		// �Q�Ɠ_�Ǝ��_�̍����x�N�g��
		Vector3 cameraV(0, 0, CAMERA_DISTANCE);
		// ���@�̌��ɉ�荞�ނ��߂̉�]�s��𐶐�
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// �����x�N�g������]������
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		// ���_���W���v�Z
		eyepos = refpos + cameraV;
		// ���_�����݈ʒu�����Ԃ���
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		// �Q�Ɠ_�����݈ʒu�����Ԃ���
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;
	}



	SetEyePos(eyepos);
	SetRefPos(refpos);

	// ���N���X�̍X�V
	Camera::Update();
}

void FollowCamera::SetTargetPos(const DirectX::SimpleMath::Vector3 & targetpos)
{
	m_targetPos = targetpos;
}

void FollowCamera::SetTargetAngle(float targetangle)
{
	m_targetAngle = targetangle;
}

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
