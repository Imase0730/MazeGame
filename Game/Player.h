//--------------------------------------------------------------------------------------
// File: Player.h
//
//--------------------------------------------------------------------------------------
#pragma once

#include "Stage.h"

// �v���C���[
class Player
{
	// �N���X�萔�̐錾 -------------------------------------------------
public:


	// �f�[�^�����o�̐錾 -----------------------------------------------
private:

	// �ʒu
	POINT m_position;

	// �����o�֐��̐錾 -------------------------------------------------
public:

	// �R���X�g���N�^
	Player();

	// �f�X�g���N�^
	~Player();

	// ����������
	void Initialize(POINT position);

	// �X�V����
	void Update(int keyCondition, int keyTrigger, Stage& stage);

	// �`�揈��
	void Render(int ghTexture) const;

	// �ʒu��ݒ肷��֐�
	void SetPosition(POINT position) { m_position = position; }

	// �ʒu���擾����֐�
	POINT GetPosition() const { return m_position; }

};

