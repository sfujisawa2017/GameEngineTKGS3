//--------------------------------
//	カメラを制御するクラス
//--------------------------------
#pragma once

#include <d3d11.h>
#include <SimpleMath.h>

class Camera
{
public:
	// メンバ関数
	// コンストラクタ
	Camera(int width, int height);
	// デストラクタ
	virtual ~Camera();

	// 更新
	virtual void Update();

	// ビュー行列を取得
	const DirectX::SimpleMath::Matrix& GetView();

	// 射影行列を取得
	const DirectX::SimpleMath::Matrix& GetProj();

	// 視点をセット
	void SetEyePos(const DirectX::SimpleMath::Vector3& eyepos);

	// 参照点をセット
	void SetRefPos(const DirectX::SimpleMath::Vector3& refpos);

	// 上方向ベクトルをセット
	void SetUpVec(const DirectX::SimpleMath::Vector3& upvec);

	// 垂直方向視野角をセット
	void SetFovY(float fovY);

	// 垂直方向視野角をセット
	void SetAspect(float aspect);

	// 垂直方向視野角をセット
	void SetNearClip(float nearclip);

	// 垂直方向視野角をセット
	void SetFarClip(float farclip);

protected:
	// 材料はここに（メンバ変数）
	// ビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// どこから見るのか（視点）
	DirectX::SimpleMath::Vector3 m_eyepos;
	// どこを見るのか（注視点/参照点)
	DirectX::SimpleMath::Vector3 m_refpos;
	// どちらが画面上方向か（上方向ベクトル）
	DirectX::SimpleMath::Vector3 m_upvec;
	// プロジェクション行列
	DirectX::SimpleMath::Matrix m_proj;
	// 垂直方向視野角
	float m_fovY;
	// アスペクト比（横・縦の比率）
	float m_aspect;
	// 手前の表示限界距離
	float m_nearclip;
	// 奥の表示限界距離
	float m_farclip;
};