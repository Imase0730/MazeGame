 //--------------------------------------------------------------------------------------
 // File: Stage.h
 //
 //--------------------------------------------------------------------------------------
#pragma once

#include "Blink.h"

// �X�e�[�W�N���X
class Stage
{
	// �񋓌^�̐錾 -------------------------------------------------
public:

	// �^�C���̎��
	enum class Tile
	{
		None = -1,
		Floor,		// 0:��
		Wall,		// 1:��
		Chest,		// 2:��
		Player,		// 3:�v���C���[
		BlinkFloor,	// 4:�_�ł��鏰
	};

	// �N���X�萔�̐錾 -------------------------------------------------
public:

	// �^�C���̃T�C�Y
	static constexpr int TILE_SIZE = 64;

	// �X�e�[�W�̉��̃^�C���̐�
	static constexpr int STAGE_WIDTH = 10;

	// �X�e�[�W�̏c�̃^�C���̐�
	static constexpr int STAGE_HEIGHT = 10;

	// �f�[�^�����o�̐錾 -----------------------------------------------
private:

	// �X�e�[�W�f�[�^
	Tile m_stageData[STAGE_HEIGHT][STAGE_WIDTH];

	// �_��
	Blink m_blink;

	// �����o�֐��̐錾 -------------------------------------------------
public:

	// �R���X�g���N�^
	Stage();

	// �f�X�g���N�^
	~Stage();

	// �X�V����
	void Update();

	// �`�揈��
	void Render(int ghTileset) const;

	// �X�e�[�W�̃��[�h�֐�
	bool LoadStage(const wchar_t* fileName);

	// �X�e�[�W�f�[�^���擾����֐�
	Tile GetStageData(POINT position) const;

	// �X�e�[�W�f�[�^��ݒ肷��֐�
	void SetStageData(POINT position, Stage::Tile tile) { m_stageData[position.y][position.x] = tile; }

	// �v���C���[�ʒu���擾����֐�
	POINT GetPlayerPosition();

	// �X�e�[�W��̕󔠂̐����擾����֐�
	int GetChestCount() const;

	// �ړ��\�����ׂ�֐�
	bool IsMovable(POINT position) const;

};

