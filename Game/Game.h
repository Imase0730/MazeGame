/**
 * @file   Game.h
 *
 * @brief  ゲーム全体に関するヘッダファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// 多重インクルードの防止 =====================================================
#pragma once




// ヘッダファイルの読み込み ===================================================

#include "Player.h"
#include "Stage.h"

// クラスの宣言 ===============================================================




// クラスの定義 ===============================================================
/**
 * @brief ゲーム
 */
class Game
{
	// 列挙型の定義 -----------------------------------------------------
private:

	// ゲームの状態
	enum class GameState
	{
		GamePlay,	// ゲームプレイ中
		GameOver,	// ゲームオーバー
		GameClear,	// ゲームオーバー
	};

// クラス定数の宣言 -------------------------------------------------
public:
	// システム関連
	static constexpr const wchar_t* TITLE = L"Maze Game";   ///< ゲームタイトル

	// 文字のサイズ
	static constexpr int FONT_SIZE = 50;

	// ゲームオーバーの文字列
	static constexpr wchar_t GAMEOVER[] = L"Game Over";

	// ゲームクリアの文字列
	static constexpr wchar_t GAMECLEAR[] = L"Game Clear";


// データメンバの宣言 -----------------------------------------------
private:
	// 入力関連
	int m_key;       ///< 現在のキー情報
	int m_oldKey;    ///< 前回のキー情報

	// 描画先のグラフィックハンドル
	int m_ghScreen;

	// ステージ
	Stage m_stage;

	// プレイヤー
	Player m_player;

	// タイルのグラフィックハンドル
	int m_ghTileset;

	// プレイヤーのグラフィックハンドル
	int m_ghPlayer;

	// ゲームの状態
	GameState m_gameState;

// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Game();

	// デストラクタ
	~Game();


// 操作
public:
	// 初期化処理
	void Initialize();

	// 更新処理
	void Update(float elapsedTime);

	// 描画処理
	void Render();

	// 終了処理
	void Finalize();

	// ゲームクリアか調べる関数
	bool IsGameOver();

	// ゲームオーバーか調べる関数
	bool IsGameClear();


// 取得/設定
public:


// 内部実装
private:


};
