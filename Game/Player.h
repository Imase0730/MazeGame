//--------------------------------------------------------------------------------------
// File: Player.h
//
//--------------------------------------------------------------------------------------
#pragma once

#include "Stage.h"

// プレイヤー
class Player
{
	// クラス定数の宣言 -------------------------------------------------
public:


	// データメンバの宣言 -----------------------------------------------
private:

	// 位置
	POINT m_position;

	// メンバ関数の宣言 -------------------------------------------------
public:

	// コンストラクタ
	Player();

	// デストラクタ
	~Player();

	// 初期化処理
	void Initialize(POINT position);

	// 更新処理
	void Update(int keyCondition, int keyTrigger, Stage& stage);

	// 描画処理
	void Render(int ghTexture) const;

	// 位置を設定する関数
	void SetPosition(POINT position) { m_position = position; }

	// 位置を取得する関数
	POINT GetPosition() const { return m_position; }

};

