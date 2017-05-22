/// <summary>
/// ���@�ɒǏ]����J�����N���X
/// </summary>
#pragma once

#include "Camera.h"
#include <Keyboard.h>

class FollowCamera : public Camera
{
public:
	// �Ǐ]�ΏۂƃJ�����̋���
	static const float CAMERA_DISTANCE;
	// �R���X�g���N�^
	FollowCamera(int width, int height);
	// ���t���[���X�V
	void Update() override;

	// �Ǐ]�Ώۂ̍��W���Z�b�g
	void SetTargetPos(const DirectX::SimpleMath::Vector3& targetpos);

	// �Ǐ]�Ώۂ̊p�x���Z�b�g
	void SetTargetAngle(float targetangle);

	// �L�[�{�[�h���Z�b�g
	void SetKeyboard(DirectX::Keyboard* keyboard);

protected:
	// �Ǐ]�Ώۂ̍��W
	DirectX::SimpleMath::Vector3 m_targetPos;
	// �Ǐ]�Ώۂ̉�]�p
	float m_targetAngle;
	// �L�[�{�[�h
	DirectX::Keyboard* m_keyboard;
	// �L�[�{�[�h�g���b�J�[
	DirectX::Keyboard::KeyboardStateTracker m_keyboardTracker;
	// FPS�J�����t���O
	bool m_isFPS;
};