//--------------------------------------------------------------------------------------
// File: Blink.cpp
//
//--------------------------------------------------------------------------------------
#include "Blink.h"

// �R���X�g���N�^
Blink::Blink(int intervalFrame)
	: m_intervalFrame{ intervalFrame }
	, m_timer{}
{
}

// �X�V����
void Blink::Update()
{
	// �^�C�}�[���Z
	if (++m_timer > m_intervalFrame)
	{
		m_timer = 0;
	}
}

// �_�ł̊������擾����֐�
float Blink::GetBlinkRate() const
{
	// 0.0 �� 1.0 �� 0.0
	if (m_timer <= m_intervalFrame / 2)
	{
		return m_timer / (m_intervalFrame / 2.0f);
	}
	return (m_intervalFrame - m_timer) / (m_intervalFrame / 2.0f);
}
