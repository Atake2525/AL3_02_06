#define NOMINMAX
#include "Player.h"
#include <numbers>
#include "TextureManager.h"
#include <cassert>
#include <algorithm>
#include "MathUtilityForText.h"
#include "Input.h"

void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection, const Vector3& position) {
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	viewProjection_ = viewProjection;
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;


	/* worldTransform_.translation_.x = 2;
	worldTransform_.translation_.y = 2;*/
};

void Player::Update() { 

	landing = false;

		// 地面との当たり判定
		// 落下中か
		if (velocity_.y < 0) {
			// Y座標が地面以下になったら着地
			if (worldTransform_.translation_.y <= 2.0f) {
				landing = true;
			}
		}
	
	// 移動入力
	// 接地状態
	if (onGround_) {
		// 左右移動操作
		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {
			Vector3 acceleration = {};
			
			if (Input::GetInstance()->PushKey(DIK_D)) {
				acceleration.x += kAcceleration;
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_= worldTransform_.rotation_.y;
					turnTimer_ = 0.01f;
				}
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
			} else if (Input::GetInstance()->PushKey(DIK_A)) {
				acceleration.x -= kAcceleration;
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = 0.01f;
				}
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
			}
			// 加速 // 減速
			velocity_.x += acceleration.x;
			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		} else {
			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAttenuation);
		}
		if (turnTimer_ > 0.0f) {
			turnTimer_ += kTimeTurn / 60;

			// 左右の自キャラ角度テーブル
			float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
			// 状態に応じた角度を取得する
			float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
			// 自キャラの角度を設定する
			worldTransform_.rotation_.y = easeInOut(turnTimer_, turnFirstRotationY_, destinationRotationY);
		}
		if (turnTimer_ > 1.0f) {
			turnTimer_ = 0.0f;
		}
		
		if (Input::GetInstance()->PushKey(DIK_SPACE)) {
			Vector3 jumpAcceleration = {0, kJumpAcceleration, 0};
			// ジャンプ初速
			velocity_ += jumpAcceleration;
		}
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			// 空中状態に移行
			onGround_ = false;
		}
	} else {
		// 着地
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 2.0f;
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAttenuation);
			// 下方向速度をリセット
			velocity_.y = 0.0f;
			// 接地状態に移行
			onGround_ = true;
		}
	}
	if (onGround_ == false) {
		velocity_.y += kGravityAcceleration;
	}
	



	// 移動
	worldTransform_.translation_ += velocity_;

	// 行列計算
	worldTransform_.UpdateMatrix();
	

};

void Player::Draw() { model_->Draw(worldTransform_, *viewProjection_, textureHandle_); };

