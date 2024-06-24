#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <vector>
#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>
#include "DebugCamera.h"
#include "Skydome.h"
#include "MathUtilityForText.h"
#include "Player.h"
#include "MapChipField.h"
#include "CameraController.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	//ワールドトランスフォーム
	//WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	//デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// 追従カメラ
	CameraController* cameraController_ = nullptr;

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	Player* player_ = nullptr;


	Model* model_ = nullptr;

	Model* modelSkydome_ = nullptr;

	Skydome* skyDome_ = nullptr;
	
	uint32_t texturehandle_ = 0;

	// マップチップフィールド
	MapChipField* mapChipField_;

	void GenerateBlocks();



	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
