#include "Model.h"
#include "WorldTransform.h"

#pragma once
class Player {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//const ViewProjection* GetViewProjection() { return viewProjection_; }

	const WorldTransform& GetworldTransform()const { return worldTransform_; }

	// プレイヤーの速度を取得するgetter
	const Vector3& GetVelocity() const { return velocity_; }

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
	
	// 移動系
	Vector3 velocity_ = {};
	static inline const float kAcceleration = 0.02f;
	static inline const float kAttenuation = 0.2f;
	static inline const float kLimitRunSpeed = 0.6f;

	// 左右
	enum class LRDirection { 
		kRight,
		kLeft,
	};
	LRDirection lrDirection_ = LRDirection::kRight;
	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	// 旋回タイマー
	float turnTimer_ = 0.0f;
	// 旋回時間<秒>
	static inline const float kTimeTurn = 3.5f;

	// 接地状態フラグ
	bool onGround_ = true;
	// 重力加速度(下方向)
	static inline const float kGravityAcceleration = -0.02f;
	// 最大落下速度(下方向)
	static inline const float kLimitFallSpeed = 5.0f;
	// ジャンプ初速(上方向)
	static inline const float kJumpAcceleration = 0.5f;
	// 着地フラグ
	bool landing = false;

	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};
