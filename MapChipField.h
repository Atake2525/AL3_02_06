#pragma once
#include "Model.h"

enum class MapChipType {
	kBlank, // 空白
	KBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

//std::unordered_map<std::string, MapChipType> mapChipTable = {
//    {"0", MapChipType::kBlank},
//    {"1", MapChipType::KBlock},
//};

class MapChipField {
public:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;
	// ブロックの個数
	static inline const uint32_t  kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	const uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; }

	const uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }

	MapChipData mapChipData_;

	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

	MapChipType GetMapChiptypeByIndex(uint32_t xIndex, uint32_t yIndex);

	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
	
};
