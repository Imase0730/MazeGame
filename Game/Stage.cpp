//--------------------------------------------------------------------------------------
// File: Stage.cpp
//
//--------------------------------------------------------------------------------------
#include "Stage.h"
#include <fstream>
#include <sstream>

// �R���X�g���N�^
Stage::Stage()
	: m_stageData{}
	, m_blink{ 120 }
{
}

// �f�X�g���N�^
Stage::~Stage()
{
}

void Stage::Update()
{
	m_blink.Update();
}

// �X�e�[�W�̃��[�h�֐�
bool Stage::LoadStage(const wchar_t* fileName)
{
	// �t�@�C���I�[�v��
	std::ifstream ifs(fileName);

	// �t�@�C���̃I�[�v�������H
	if (!ifs)
	{
		OutputDebugString(L"file open error!�i%s)", fileName);
		return false;
	}

	// �X�e�[�W�̃��[�h
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		// 1�s�ǂݍ���
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

	// �t�@�C���N���[�Y
	ifs.close();

	return true;
}

// �X�e�[�W�f�[�^���擾����֐�
Stage::Tile Stage::GetStageData(POINT position) const
{
	// �X�e�[�W�O�Ȃ�
	if ( (position.x < 0) || (position.x >= STAGE_WIDTH)
	  || (position.y < 0) || (position.y >= STAGE_HEIGHT)
	   )
	{
		return Tile::None;
	}

	return m_stageData[position.y][position.x];
}

// �v���C���[�ʒu���擾����֐�
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

// �X�e�[�W��̕󔠂̐����擾����֐�
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

// �`�揈��
void Stage::Render(int ghTileset) const
{
	// �X�e�[�W�̕`��
	for (int i = 0; i < STAGE_HEIGHT; i++)
	{
		for (int j = 0; j < STAGE_WIDTH; j++)
		{
			// �_�ł��鏰�̏ꍇ
			if (m_stageData[i][j] == Tile::BlinkFloor)
			{
				// ���邳��ݒ�
				int col = static_cast<int>(100.0f + 155.0f * m_blink.GetBlinkRate());
				SetDrawBright(col, col, col);
			}

			// �`�悷��^�C���̊G�����߂�
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
			
			// �^�C���̕`��
			DrawRectGraph(j * TILE_SIZE, i * TILE_SIZE
				, tile * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE,
				ghTileset, FALSE
			);

			// ���邳��߂�
			SetDrawBright(255, 255, 255);
		}
	}
}

// �ړ��\�����ׂ�֐�
bool Stage::IsMovable(POINT position) const
{
	int x = position.x;
	int y = position.y;

	if ((x < 0) || (x >= STAGE_WIDTH) || (y < 0) || (y >= STAGE_HEIGHT)) return false;
	if (m_stageData[y][x] == Stage::Tile::Wall) return false;
	if (m_stageData[y][x] == Stage::Tile::BlinkFloor) return false;

	return true;
}
