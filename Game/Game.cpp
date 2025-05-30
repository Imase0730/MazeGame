/**
 * @file   Game.cpp
 *
 * @brief  ゲーム全体に関するソースファイル
 *
 * @author 制作者名
 *
 * @date   日付
 */

// ヘッダファイルの読み込み ===================================================
#include "Game.h"

#include "Game/Screen.h"




// メンバ関数の定義 ===========================================================
/**
 * @brief デフォルトコンストラクタ
 *
 * @param なし
 */
Game::Game()
	: m_key{ 0 }
	, m_oldKey{ 0 }
	, m_ghScreen{ -1 }
	, m_stage{}
	, m_player{}
	, m_ghTileset{ -1 }
	, m_ghPlayer{ -1 }
	, m_gameState{ GameState::GamePlay }
{
	// 乱数の初期値を設定
	SRand(static_cast<int>(time(nullptr)));

	// 描画先のグラフィックを作成する
	m_ghScreen = MakeScreen(Screen::GAME_WIDTH, Screen::GAME_HEIGHT, false);

	// ステージのタイルのテクスチャの読み込み
	m_ghTileset = LoadGraph(L"Resources/Textures/tileset.png");

	// プレイヤーのテクスチャの読み込み
	m_ghPlayer = LoadGraph(L"Resources/Textures/player.png");
}



/**
 * @brief デストラクタ
 */
Game::~Game()
{

}



/**
 * @brief 初期化処理
 *
 * @param なし
 *
 * @return なし
 */
void Game::Initialize()
{
	// ゲームの初期化

	// マップデータを管理するオブジェクトを作成
	m_stage.LoadStage(L"Resources/StageData/stage_01.csv");

	// プレイヤーの初期化
	m_player.Initialize(m_stage.GetPlayerPosition());
}



/**
 * @brief 更新処理
 *
 * @param なし
 *
 * @return なし
 */
void Game::Update(float elapsedTime)
{
	// キー入力の取得
	m_oldKey = m_key;
	m_key    = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	int keyTrigger = ~m_oldKey & m_key;

	// ゲームの更新
	
	// ステージの更新
	m_stage.Update();

	// ゲームの状態により処理を分ける
	switch (m_gameState)
	{
	case Game::GameState::GamePlay:

		// プレイヤーの更新
		m_player.Update(m_key, keyTrigger, m_stage);

		// 宝があれば宝を取る
		if (m_stage.GetStageData(m_player.GetPosition()) == Stage::Tile::Chest)
		{
			// 宝箱のタイルを床にする
			m_stage.SetStageData(m_player.GetPosition(), Stage::Tile::Floor);
		}

		// ゲームクリア？
		if (IsGameClear())
		{
			m_gameState = GameState::GameClear;
		}
		// ゲームオーバー？
		else if (IsGameOver())
		{
			m_gameState = GameState::GameOver;
		}

		break;
	case Game::GameState::GameOver:
	case Game::GameState::GameClear:
		if (keyTrigger & PAD_INPUT_10)
		{
			// ゲームをもう一度プレイする
			m_gameState = GameState::GamePlay;
			// ゲームを初期化
			Initialize();
		}
		break;
	default:
		break;
	}

}



/**
 * @brief 描画処理
 *
 * @param[in] なし
 *
 * @return なし
 */
void Game::Render()
{
	// ゲームの描画

	// 作成した画像を描画対象にする
	SetDrawScreen(m_ghScreen);

	// 描画対象をクリア
	ClearDrawScreen();

	// ----- 描画（始まり）----- //
	
	// 文字のサイズを変更する
	SetFontSize(FONT_SIZE);

	// ステージの描画
	m_stage.Render(m_ghTileset);

	// プレイヤーの描画
	m_player.Render(m_ghPlayer);

	// 各文字列の描画
	switch (m_gameState)
	{
	case Game::GameState::GameOver:
		DrawFormatString(Screen::GAME_WIDTH / 2 - GetDrawStringWidth(GAMEOVER, static_cast<int>(wcslen(GAMEOVER))) / 2
			, Screen::GAME_HEIGHT / 2 - FONT_SIZE / 2
			, GetColor(255, 255, 255), GAMEOVER);
		break;
	case Game::GameState::GameClear:
		DrawFormatString(Screen::GAME_WIDTH / 2 - GetDrawStringWidth(GAMECLEAR, static_cast<int>(wcslen(GAMECLEAR))) / 2
			, Screen::GAME_HEIGHT / 2 - FONT_SIZE / 2
			, GetColor(255, 255, 255), GAMECLEAR);
		break;
	default:
		break;
	}

	// ----- 描画（終わり） ----- //

	// 描画対象を裏画面にする
	SetDrawScreen(DX_SCREEN_BACK);

	// 描画対象画像を描画する
	int width = static_cast<int>(Screen::GAME_WIDTH);
	int height = static_cast<int>(Screen::GAME_HEIGHT);
	int x = Screen::WIDTH / 2 - width / 2;
	int y = Screen::HEIGHT / 2 - height / 2;
	DrawExtendGraph(x, y, x + width, y + height, m_ghScreen, FALSE);
}



/**
 * @brief 終了処理
 *
 * @param なし
 *
 * @return なし
 */
void Game::Finalize()
{
	// ゲームの終了処理
	
	// 絵のデータをメモリから削除
	DeleteGraph(m_ghScreen);
	DeleteGraph(m_ghTileset);
	DeleteGraph(m_ghPlayer);
}

// ゲームクリアか調べる関数
bool Game::IsGameOver()
{
	int x = m_player.GetPosition().x;
	int y = m_player.GetPosition().y;

	// 上下左右どこにも移動できない
	if (m_stage.IsMovable(POINT{ x, y - 1 })) return false;
	if (m_stage.IsMovable(POINT{ x, y + 1 })) return false;
	if (m_stage.IsMovable(POINT{ x - 1, y })) return false;
	if (m_stage.IsMovable(POINT{ x + 1, y })) return false;

	return true;
}

// ゲームオーバーか調べる関数
bool Game::IsGameClear()
{
	// ステージ上の宝箱の数が０なら
	if (m_stage.GetChestCount() == 0) return true;

	return false;
}
