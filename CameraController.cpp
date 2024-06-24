#include "CameraController.h"
#include "Player.h"
#include "MathUtilityForText.h"
#include <algorithm>

void CameraController::Initialize() { 
	viewProjection_.Initialize();
	movableArea_ = {1, 100, 2, 100};
};

void CameraController::Update() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetworldTransform();
	const Vector3& targetVelocity = target_->GetVelocity();
	// 追従対象とオフセットと追従対象の速度カメラの目標座標を計算
	movePoint_ = targetWorldTransform.translation_ + targetOffset_  + targetVelocity * kVelocityBias;

	// 座標保管によりゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, movePoint_, kInterpolationRate);
	
	// 移動範囲制限
	viewProjection_.translation_.x = (std::max)(viewProjection_.translation_.x, movableArea_.left);
	viewProjection_.translation_.x = (std::min)(viewProjection_.translation_.x, movableArea_.right);
	viewProjection_.translation_.y = (std::max)(viewProjection_.translation_.y, movableArea_.bottom);
	viewProjection_.translation_.y = (std::min)(viewProjection_.translation_.y, movableArea_.top);

	// 行列を更新する
	viewProjection_.UpdateMatrix();
};

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetworldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}