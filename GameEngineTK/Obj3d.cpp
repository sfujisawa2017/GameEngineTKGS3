#include "Obj3d.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// �ÓI�����o�ϐ��̎���
// �f�o�C�X
Microsoft::WRL::ComPtr<ID3D11Device>            Obj3d::m_d3dDevice;
// �f�o�C�X�R���e�L�X�g
Microsoft::WRL::ComPtr<ID3D11DeviceContext>     Obj3d::m_d3dContext;
// �J����
Camera* Obj3d::m_Camera;
// �ėp�`��X�e�[�g
std::unique_ptr<DirectX::CommonStates> Obj3d::m_states;
// �G�t�F�N�g�t�@�N�g��
std::unique_ptr<DirectX::EffectFactory> Obj3d::m_factory;

void Obj3d::InitializeStatic(Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice, Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3dContext, Camera * camera)
{
	m_d3dDevice = d3dDevice;
	m_d3dContext = d3dContext;
	m_Camera = camera;

	// �ėp�`��X�e�[�g����
	m_states = std::make_unique<CommonStates>(m_d3dDevice.Get());

	// �G�t�F�N�g�t�@�N�g������
	m_factory = std::make_unique<EffectFactory>(m_d3dDevice.Get());
	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	m_factory->SetDirectory(L"Resources");
}

Obj3d::Obj3d()
{
}

void Obj3d::LoadModel(const wchar_t * fileName)
{
}

void Obj3d::Update()
{
	// ��ɍs��̌v�Z

}

void Obj3d::Draw()
{

}
