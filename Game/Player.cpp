//--------------------------------------------------------------------------------------
// File: Player.cpp
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Player.h"
#include "Stage.h"

// コンストラクタ
Player::Player()
	: m_position{ 0, 0 }
{
}

// デストラクタ
Player::~Player()
{
}

// 初期化処理
void Player::Initialize(POINT position)
{
	// 位置を設定
	m_position = position;
}

// 更新処理
void Player::Update(int keyCondition, int keyTrigger, Stage& stage)
{
	// 上キーが押されたら壁でなければ上へ移動する
	if ((keyTrigger & PAD_INPUT_UP)
		&& (stage.IsMovable(POINT{ m_position.x, m_position.y - 1 }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.y--;
	}

	// 下キーが押されたら壁でなければ下へ移動する
	if ((keyTrigger & PAD_INPUT_DOWN)
		&& (stage.IsMovable(POINT{ m_position.x, m_position.y + 1 }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.y++;
	}

	// 左キーが押されたら壁でなければ左へ移動する
	if ((keyTrigger & PAD_INPUT_LEFT)
		&& (stage.IsMovable(POINT{ m_position.x - 1, m_position.y }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.x--;
	}

	// 右キーが押されたら壁でなければ右へ移動する
	if ((keyTrigger & PAD_INPUT_RIGHT)
		&& (stage.IsMovable(POINT{ m_position.x + 1, m_position.y }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.x++;
	}
}

// 描画処理
void Player::Render(int ghTexture) const
{
	// プレイヤーの描画
	DrawGraph(m_position.x * 64, m_position.y * 64, ghTexture, TRUE);
}

