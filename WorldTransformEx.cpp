#include "WorldTransform.h"
#include "MathUtilityForText.h"

void WorldTransform::UpdateMatrix() { 
	// スケール、回転、平行移動を合成して行列を計算する
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);
	// 変数バッファに転送する
	TransferMatrix();
}