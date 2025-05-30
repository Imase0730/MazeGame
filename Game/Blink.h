//--------------------------------------------------------------------------------------
// File: Blink.h
//
//--------------------------------------------------------------------------------------
#pragma once

// �_�ŃN���X
class Blink
{
private:

	// �_�ŊԊu
	int m_intervalFrame;

	// �^�C�}�[
	int m_timer;

public:

	// �R���X�g���N�^
	Blink(int intervalFrame);

	// �X�V����
	void Update();

	// �_�ł̊������擾����֐�
	float GetBlinkRate() const;

	// �_�ŊԊu�̐ݒ�֐�
	void SetInterval(int intervalFrame) { m_intervalFrame = intervalFrame; }

};