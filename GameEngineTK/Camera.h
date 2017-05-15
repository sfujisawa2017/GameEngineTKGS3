//--------------------------------
//	�J�����𐧌䂷��N���X
//--------------------------------
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	// �����o�֐�
	// �R���X�g���N�^
	Camera(int width, int height);
	// �f�X�g���N�^
	virtual ~Camera();

	// �X�V
	virtual void Update();

	// �r���[�s����擾
	const DirectX::SimpleMath::Matrix& GetView();

	// �ˉe�s����擾
	const DirectX::SimpleMath::Matrix& GetProj();

	// ���_���Z�b�g
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);

	// �Q�Ɠ_���Z�b�g
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);

	// ������x�N�g�����Z�b�g
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);

	// ������������p���Z�b�g
	void SetFovY(float fovY);

	// ������������p���Z�b�g
	void SetAspect(float aspect);

	// ������������p���Z�b�g
	void SetNearClip(float nearclip);

	// ������������p���Z�b�g
	void SetFarClip(float farclip);

protected:
	// �ޗ��͂����Ɂi�����o�ϐ��j
	// �r���[�s��
	DirectX::SimpleMath::Matrix m_view;
	// �ǂ����猩��̂��i���_�j
	DirectX::SimpleMath::Vector3 m_eyepos;
	// �ǂ�������̂��i�����_/�Q�Ɠ_)
	DirectX::SimpleMath::Vector3 m_refpos;
	// �ǂ��炪��ʏ�������i������x�N�g���j
	DirectX::SimpleMath::Vector3 m_upvec;
	// �v���W�F�N�V�����s��
	DirectX::SimpleMath::Matrix m_proj;
	// ������������p
	float m_fovY;
	// �A�X�y�N�g��i���E�c�̔䗦�j
	float m_aspect;
	// ��O�̕\�����E����
	float m_nearclip;
	// ���̕\�����E����
	float m_farclip;
};