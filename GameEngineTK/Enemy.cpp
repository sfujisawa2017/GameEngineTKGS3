//--------------------------------------------------------------------------------------
// ファイル名: Enemy.cpp
// 作成者:
// 作成日:
// 説明:
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
// 初期化
//-----------------------------------------------------------------------------
void Enemy::Initialize()
{
	// 自機パーツの読み込み
	m_Obj.resize(PARTS_NUM);
	m_Obj[PARTS_BODY].LoadModel(L"Resources/body.cmo");
	m_Obj[PARTS_COCKPIT].LoadModel(L"Resources/cockpit.cmo");
	m_Obj[PARTS_LAUNCHER].LoadModel(L"Resources/launcher.cmo");
	m_Obj[PARTS_SHIELD].LoadModel(L"Resources/shield.cmo");
	m_Obj[PARTS_DRILL].LoadModel(L"Resources/drill.cmo");

	// パーツの親子関係をセット
	m_Obj[PARTS_COCKPIT].SetParent(
		&m_Obj[PARTS_BODY]);

	m_Obj[PARTS_DRILL].SetParent(
		&m_Obj[PARTS_COCKPIT]);

	m_Obj[PARTS_LAUNCHER].SetParent(
		&m_Obj[PARTS_BODY]);

	m_Obj[PARTS_SHIELD].SetParent(
		&m_Obj[PARTS_BODY]);

	// 親からのオフセット（座標のずらし分）をセット
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

	// 初期配置
	Vector3 pos;
	pos.x = rand() % 10;
	pos.z = rand() % 10;

	this->SetTrans(pos);

	m_Timer = 0;
	m_DistAngle = 0;
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void Enemy::Update()
{
	//// キーボードの更新
	//Keyboard::State keystate = m_pKeyboard->GetState();
	//m_KeyboardTracker.Update(keystate);

	// 自機パーツのギミック
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
		// -0.5～+0.5の乱数
		float rnd = (float)rand() / RAND_MAX - 0.5f;
		rnd *= 180.0f;

		rnd = XMConvertToRadians(rnd);

		m_DistAngle += rnd;
	}

	{
		// 自機の角度を回転させる
		Vector3 rotv = m_Obj[0].GetRotation();
		
		float angle = m_DistAngle - rotv.y;

		// 180度を超えていた場合、逆回りの方が近い
		if (angle > XM_PI)
		{
			angle -= XM_2PI;
		}

		if (angle < -XM_PI)
		{
			angle += XM_2PI;
		}

		// 補間
		rotv.y += angle * 0.05f;

		SetRot(rotv);
	}

	// 機体が向いている方向に進む
	{
		// 移動量のベクトル
		Vector3 moveV(0, 0, -0.1f);
		// 移動量ベクトルを自機の角度分回転させる
		//moveV = Vector3::TransformNormal(moveV, tank_world);
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動させる
		Vector3 pos = m_Obj[0].GetTranslation();
		m_Obj[0].SetTranslation(pos + moveV);
	}
	
	Calc();
}

//-----------------------------------------------------------------------------
// 行列更新
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
// 描画
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
	// タンクパーツの座標を返す
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Enemy::GetRot()
{
	// タンクパーツの回転を返す
	return m_Obj[0].GetRotation();
}

void Enemy::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_Obj[0].SetTranslation(trans);
}

void Enemy::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Enemy::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_Obj[0].GetWorld();
}
