#include "Skydome.h"

/// <summary>
/// 初期化
/// </summary>
void Skydome::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjectoin){ 
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// 引数の内容をメンバ変数に記録
	viewProjection_ = viewProjectoin;

	worldTransform_.Initialize();
	worldTransform_.scale_ = {10.0f, 10.0f, 10.0f};

};

/// <summary>
/// 更新
/// </summary>
void Skydome::Update() {

	//worldTransform_->matWorld_ = MakeAffineMatrix(worldTransform_->scale_, worldTransform_->rotation_, worldTransform_->translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

/// <summary>
/// 描画
/// </summary>
void Skydome::Draw() { 
	// 3Dモデルを描画
	model_->Draw(worldTransform_, *viewProjection_);
}