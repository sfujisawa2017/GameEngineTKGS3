#include "FollowCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

// 静的メンバ変数の初期化
const float FollowCamera::CAMERA_DISTANCE = 5.0f;

FollowCamera::FollowCamera(int width, int height)
	:Camera(width, height)
{
	m_targetPos = Vector3::Zero;
	m_targetAngle = 0.0;
}

void FollowCamera::Update()
{
	// 視点、参照点座標
	Vector3 eyepos, refpos;
	// 自機の上空２ｍを参照点とする
	refpos = m_targetPos + Vector3(0, 2, 0);
	// 参照点と視点の差分ベクトル
	Vector3 cameraV(0, 0, CAMERA_DISTANCE);
	// 自機の後ろに回り込むための回転行列を生成
	Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
	// 差分ベクトルを回転させる
	cameraV = Vector3::TransformNormal(cameraV, rotmat);
	// 視点座標を計算
	eyepos = refpos + cameraV;

	SetEyePos(eyepos);
	SetRefPos(refpos);

	// 基底クラスの更新
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
