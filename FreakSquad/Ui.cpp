#include "Ui.h"

Ui::Ui()
{
	m_playerNbr = 0;
}

Ui::~Ui()
{
}

void Ui::update()
{
}

int Ui::getPlayerNumber()
{

	return m_playerNbr;
}

void Ui::setPlayerNumber(int _m_playerNbr)
{
	m_playerNbr = _m_playerNbr;
}

int Ui::getFirstPlayerType()
{
	return m_firstPlayerType;
}

void Ui::setFirstPlayerType(int _m_firstPlayerType)
{
	m_firstPlayerType = _m_firstPlayerType;
}

int Ui::getSecondPlayerType()
{
	return m_secondPlayerType;
}

void Ui::setSecondPlayerType(int _m_secondPlayerType)
{
	m_secondPlayerType = _m_secondPlayerType;
}

void Ui::draw()
{
}
