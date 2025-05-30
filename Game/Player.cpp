//--------------------------------------------------------------------------------------
// File: Player.cpp
//
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "Player.h"
#include "Stage.h"

// �R���X�g���N�^
Player::Player()
	: m_position{ 0, 0 }
{
}

// �f�X�g���N�^
Player::~Player()
{
}

// ����������
void Player::Initialize(POINT position)
{
	// �ʒu��ݒ�
	m_position = position;
}

// �X�V����
void Player::Update(int keyCondition, int keyTrigger, Stage& stage)
{
	// ��L�[�������ꂽ��ǂłȂ���Ώ�ֈړ�����
	if ((keyTrigger & PAD_INPUT_UP)
		&& (stage.IsMovable(POINT{ m_position.x, m_position.y - 1 }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.y--;
	}

	// ���L�[�������ꂽ��ǂłȂ���Ή��ֈړ�����
	if ((keyTrigger & PAD_INPUT_DOWN)
		&& (stage.IsMovable(POINT{ m_position.x, m_position.y + 1 }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.y++;
	}

	// ���L�[�������ꂽ��ǂłȂ���΍��ֈړ�����
	if ((keyTrigger & PAD_INPUT_LEFT)
		&& (stage.IsMovable(POINT{ m_position.x - 1, m_position.y }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.x--;
	}

	// �E�L�[�������ꂽ��ǂłȂ���ΉE�ֈړ�����
	if ((keyTrigger & PAD_INPUT_RIGHT)
		&& (stage.IsMovable(POINT{ m_position.x + 1, m_position.y }))
		)
	{
		stage.SetStageData(m_position, Stage::Tile::BlinkFloor);
		m_position.x++;
	}
}

// �`�揈��
void Player::Render(int ghTexture) const
{
	// �v���C���[�̕`��
	DrawGraph(m_position.x * 64, m_position.y * 64, ghTexture, TRUE);
}

