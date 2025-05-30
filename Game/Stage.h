 //--------------------------------------------------------------------------------------
 // File: Stage.h
 //
 //--------------------------------------------------------------------------------------
#pragma once

#include "Blink.h"

// ステージクラス
class Stage
{
	// 列挙型の宣言 -------------------------------------------------
public:

	// タイルの種類
	enum class Tile
	{
		None = -1,
		Floor,		// 0:床
		Wall,		// 1:壁
		Chest,		// 2:宝箱
		Player,		// 3:プレイヤー
		BlinkFloor,	// 4:点滅する床
	};

	// クラス定数の宣言 -------------------------------------------------
public:

	// タイルのサイズ
	static constexpr int TILE_SIZE = 64;

	// ステージの横のタイルの数
	static constexpr int STAGE_WIDTH = 10;

	// ステージの縦のタイルの数
	static constexpr int STAGE_HEIGHT = 10;

	// データメンバの宣言 -----------------------------------------------
private:

	// ステージデータ
	Tile m_stageData[STAGE_HEIGHT][STAGE_WIDTH];

	// 点滅
	Blink m_blink;

	// メンバ関数の宣言 -------------------------------------------------
public:

	// コンストラクタ
	Stage();

	// デストラクタ
	~Stage();

	// 更新処理
	void Update();

	// 描画処理
	void Render(int ghTileset) const;

	// ステージのロード関数
	bool LoadStage(const wchar_t* fileName);

	// ステージデータを取得する関数
	Tile GetStageData(POINT position) const;

	// ステージデータを設定する関数
	void SetStageData(POINT position, Stage::Tile tile) { m_stageData[position.y][position.x] = tile; }

	// プレイヤー位置を取得する関数
	POINT GetPlayerPosition();

	// ステージ上の宝箱の数を取得する関数
	int GetChestCount() const;

	// 移動可能か調べる関数
	bool IsMovable(POINT position) const;

};

