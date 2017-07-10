//--------------------------------------------------------------------------------------
// ファイル名: Player.cpp
// 作成者:
// 作成日:
// 説明:
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
// 初期化
//-----------------------------------------------------------------------------
void Player::Initialize()
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

	// 最初は発射状態ではない
	m_FireFlag = false;

	{// 弾丸用の当たり判定を設定
		m_CollisionNodeBullet.Initialize();
		// 親パーツを指定
		m_CollisionNodeBullet.SetParent(&m_Obj[PARTS_DRILL]);
		m_CollisionNodeBullet.SetTrans(Vector3(0, 0, 0));
		m_CollisionNodeBullet.SetLocalRadius(0.5f);
	}
	{// 全身用の当たり判定を設定
		m_CollisionNodeBody.Initialize();
		// 親パーツを指定
		m_CollisionNodeBody.SetParent(&m_Obj[0]);
		m_CollisionNodeBody.SetTrans(Vector3(0, 0.5f, 0));
		m_CollisionNodeBody.SetLocalRadius(1.0f);
	}
}

//-----------------------------------------------------------------------------
// 更新
//-----------------------------------------------------------------------------
void Player::Update()
{
	// キーボードの更新
	Keyboard::State keystate = m_pKeyboard->GetState();
	m_KeyboardTracker.Update(keystate);

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

	// Aキーが押されていたら
	if (keystate.A)
	{
		// 自機の角度を回転させる
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle + 0.03f, 0));
	}

	// Dキーが押されていたら
	if (keystate.D)
	{
		// 自機の角度を回転させる
		float angle = m_Obj[0].GetRotation().y;
		m_Obj[0].SetRotation(Vector3(0, angle - 0.03f, 0));
	}

	// Wキーが押されていたら
	if (keystate.W)
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

	// Sキーが押されていたら
	if (keystate.S)
	{
		// 移動量のベクトル
		Vector3 moveV(0, 0, +0.1f);
		// 移動量ベクトルを自機の角度分回転させる
		//moveV = Vector3::TransformNormal(moveV, tank_world);
		float angle = m_Obj[0].GetRotation().y;
		Matrix rotmat = Matrix::CreateRotationY(angle);
		moveV = Vector3::TransformNormal(moveV, rotmat);
		// 自機の座標を移動させる
		Vector3 pos = m_Obj[0].GetTranslation();
		m_Obj[0].SetTranslation(pos + moveV);
	}

	// スペースキーを押した
	if (m_KeyboardTracker.IsKeyPressed(Keyboard::Keys::Space))
	{
		// 弾丸発射中なら
		if (m_FireFlag)
		{
			// リセット
			ResetBullet();
		}
		else
		{
			// 発射
			FireBullet();
		}
	}

	// 弾丸を前進させる
	if ( m_FireFlag)
	{
		// 自機の座標を移動させる
		Vector3 pos = m_Obj[PARTS_DRILL].GetTranslation();
		m_Obj[PARTS_DRILL].SetTranslation(pos + m_BulletVel);
	}
	
	Calc();

	
}

//-----------------------------------------------------------------------------
// 行列更新
//-----------------------------------------------------------------------------
void Player::Calc()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Update();
	}

	// 当たり判定の更新
	m_CollisionNodeBullet.Update();
	// 当たり判定の更新
	m_CollisionNodeBody.Update();
}

//-----------------------------------------------------------------------------
// 描画
//-----------------------------------------------------------------------------
void Player::Draw()
{
	for (std::vector<Obj3d>::iterator it = m_Obj.begin();
		it != m_Obj.end();
		it++)
	{
		it->Draw();
	}

	m_CollisionNodeBullet.Draw();
	m_CollisionNodeBody.Draw();
}

void Player::FireBullet()
{
	m_FireFlag = false;

	// 発射するパーツのワールド行列を取得
	Matrix worldm = m_Obj[PARTS_DRILL].GetWorld();

	// ワールド行列から各要素を抽出
	Vector3 scale;			// ワールドスケーリング
	Quaternion rotation;	// ワールド回転
	Vector3 translation;	// ワールド座標

	worldm.Decompose(scale, rotation, translation);

	// 発射パーツを親から分離して独立
	m_Obj[PARTS_DRILL].SetParent(nullptr);
	m_Obj[PARTS_DRILL].SetScale(scale);
	m_Obj[PARTS_DRILL].SetRotationQ(rotation);
	m_Obj[PARTS_DRILL].SetTranslation(translation);

	// 弾丸の速度を設定
	m_BulletVel = Vector3(0, 0, 0.1f);
	m_BulletVel = Vector3::Transform(m_BulletVel, rotation);

	m_FireFlag = true;
}

void Player::ResetBullet()
{
	if (!m_FireFlag) return;

	// 親子関係とオフセットを初期値に戻す
	m_Obj[PARTS_DRILL].SetParent(
		&m_Obj[PARTS_COCKPIT]);

	m_Obj[PARTS_DRILL].SetScale(Vector3(1,1,1));
	m_Obj[PARTS_DRILL].SetRotation(Vector3(0,0,0));
	m_Obj[PARTS_DRILL].SetTranslation(Vector3(0, 0.1f, 0.8f));

	m_FireFlag = false;
}

const DirectX::SimpleMath::Vector3& Player::GetTrans()
{
	// タンクパーツの座標を返す
	return m_Obj[0].GetTranslation();
}

const DirectX::SimpleMath::Vector3 & Player::GetRot()
{
	// タンクパーツの回転を返す
	return m_Obj[0].GetRotation();
}

void Player::SetTrans(const DirectX::SimpleMath::Vector3& trans)
{
	// タンクパーツの座標を設定
	m_Obj[0].SetTranslation(trans);
}

void Player::SetRot(const DirectX::SimpleMath::Vector3& rot)
{
	// タンクパーツの座標を設定
	m_Obj[0].SetRotation(rot);
}

const DirectX::SimpleMath::Matrix& Player::GetLocalWorld()
{
	// タンクパーツのワールド行列を返す
	return m_Obj[0].GetWorld();
}
