//--------------------------------------------------------------------------------------
// File: Stage.cpp
//
//--------------------------------------------------------------------------------------
#include "Stage.h"
#include <fstream>
#include <sstream>

// コンストラクタ
Stage::Stage()
	: m_stageData{}
	, m_blink{ 120 }
{
}

// デストラクタ
Stage::~Stage()
{
}

void Stage::Update()
{
	m_blink.Update();
}

// ステージのロード関数
bool Stage::LoadStage(const wchar_t* fileName)
{
	// ファイルオープン
	std::ifstream ifs(fileName);

	// ファイルのオープン成功？
	if (!ifs)
	{
		OutputDebugString(L"file open error!（%s)", fileName);
		return false;
	}

	// ステージのロード
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		// 1行読み込む
		std::string line;
		getline(ifs, line);
		std::istringstream iss(line);
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			std::string item;
			getline(iss, item, ',');
			m_stageData[i][j] = static_cast<Tile>(std::stoi(item));
		}
	}

	// ファイルクローズ
	ifs.close();

	return true;
}

// ステージデータを取得する関数
Stage::Tile Stage::GetStageData(POINT position) const
{
	// ステージ外なら
	if ( (position.x < 0) || (position.x >= STAGE_WIDTH)
	  || (position.y < 0) || (position.y >= STAGE_HEIGHT)
	   )
	{
		return Tile::None;
	}

	return m_stageData[position.y][position.x];
}

// プレイヤー位置を取得する関数
POINT Stage::GetPlayerPosition()
{
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (m_stageData[i][j] == Tile::Player)
			{
				m_stageData[i][j] = Tile::Floor;
				return POINT{ j, i };
			}
		}
	}
	return POINT{ 0, 0 };
}

// ステージ上の宝箱の数を取得する関数
int Stage::GetChestCount() const
{
	int count = 0;

	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			if (m_stageData[i][j] == Tile::Chest) count++;
		}
	}
	return count;
}

// 描画処理
void Stage::Render(int ghTileset) const
{
	// ステージの描画
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			// 点滅する床の場合
			if (m_stageData[i][j] == Tile::BlinkFloor)
			{
				// 明るさを設定
				int col = static_cast<int>(100.0f + 155.0f * m_blink.GetBlinkRate());
				SetDrawBright(col, col, col);
			}

			// 描画するタイルの絵を決める
			int tile = 0;
			switch (m_stageData[i][j])
			{
			case Tile::Wall:
				tile = 1;
				break;
			case Tile:: Chest:
				tile = 2;
				break;
			default:
				break;
			}
			
			// タイルの描画
			DrawRectGraph(j * TILE_SIZE, i * TILE_SIZE
				, tile * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE,
				ghTileset, FALSE
			);

			// 明るさを戻す
			SetDrawBright(255, 255, 255);
		}
	}
}

// 移動可能か調べる関数
bool Stage::IsMovable(POINT position) const
{
	int x = position.x;
	int y = position.y;

	if ((x < 0) || (x >= STAGE_WIDTH) || (y < 0) || (y >= STAGE_HEIGHT)) return false;
	if (m_stageData[y][x] == Stage::Tile::Wall) return false;
	if (m_stageData[y][x] == Stage::Tile::BlinkFloor) return false;

	return true;
}
