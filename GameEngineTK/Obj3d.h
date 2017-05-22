/// <summary>
/// 3Dオブジェクトのクラス
/// </summary>
#pragma once

#include <windows.h>
#include <wrl/client.h>
#include <d3d11_1.h>
#include <Effects.h>
#include <CommonStates.h>
#include <SimpleMath.h>
#include <Model.h>

#include "Camera.h"

class Obj3d
{
	// 静的メンバ
public:
	// 静的メンバ変数の初期化
	static void InitializeStatic(
		Microsoft::WRL::ComPtr<ID3D11Device>            d3dDevice,
		Microsoft::WRL::ComPtr<ID3D11DeviceContext>     d3dContext,
		Camera* camera);
private:
	// デバイス
	static Microsoft::WRL::ComPtr<ID3D11Device>            m_d3dDevice;
	// デバイスコンテキスト
	static Microsoft::WRL::ComPtr<ID3D11DeviceContext>     m_d3dContext;
	// カメラ
	static Camera* m_Camera;
	// 汎用描画ステート
	static std::unique_ptr<DirectX::CommonStates> m_states;
	// エフェクトファクトリ
	static std::unique_ptr<DirectX::EffectFactory> m_factory;

public:
	// コンストラクタ
	Obj3d();

	// モデルをロード
	void LoadModel(const wchar_t* fileName);

	// 更新
	void Update();

	// 描画
	void Draw();

	// setter
	// スケーリング(XYZ)

	// 回転角（XYZ)

	// 平行移動(XYZ)

	// getter
	// スケーリング(XYZ)

	// 回転角（XYZ)

	// 平行移動(XYZ)

	// ワールド行列

private:
	// メンバ変数
	// 3Dモデル

	// スケーリング(XYZ)

	// 回転角（XYZ)

	// 平行移動(XYZ)

	// ワールド行列

};