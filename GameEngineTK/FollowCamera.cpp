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
	m_keyboard = nullptr;
	m_isFPS = false;
	m_player = nullptr;
}

void FollowCamera::Update()
{
	// キーボードの状態取得
	Keyboard::State keyboardstate = m_keyboard->GetState();
	m_keyboardTracker.Update(keyboardstate);

	// Cキーを押すごとにFPS/TPSを切り替え
	if (m_keyboardTracker.IsKeyPressed(Keyboard::Keys::C))
	{
		// フラグを切り替え
		m_isFPS = !m_isFPS;
		if (m_isFPS)
		{

		}
	}

	if (m_player)
	{
		// 目標座標の設定
		SetTargetPos(m_player->GetTrans());
		SetTargetAngle(m_player->GetRot().y);
	}

	// 視点、参照点座標
	Vector3 eyepos, refpos;
	if (m_isFPS)
	{// FPSカメラ
	 // 自機の目の位置あたりを視点とする
		Vector3 position;

		position = m_targetPos + Vector3(0, 0.2f, 0);
		// 参照点と視点の差分ベクトル
		Vector3 cameraV(0, 0, -CAMERA_DISTANCE);
		// 自機の後ろに回り込むための回転行列を生成
		Matrix rotmat = Matrix::CreateRotationY(m_targetAngle);
		// 差分ベクトルを回転させる
		cameraV = Vector3::TransformNormal(cameraV, rotmat);
		eyepos = position + cameraV * 0.1f;
		// 参照点座標を計算
		refpos = position + cameraV;
	}
	else
	{// TPSカメラ
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
		// 視点を現在位置から補間する
		eyepos = m_eyepos + (eyepos - m_eyepos) * 0.05f;
		// 参照点を現在位置から補間する
		refpos = m_refpos + (refpos - m_refpos) * 0.2f;
	}



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

void FollowCamera::SetKeyboard(DirectX::Keyboard * keyboard)
{
	m_keyboard = keyboard;
}
