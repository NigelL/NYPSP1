#include "Character.h"
#include "Values.h"




void Character::SetDirection(const short int& x, const short int& y) {
	if (m_dirX != 0) {
		m_prevDirX = m_dirX;
	}
	m_prevDirY = m_dirY;
	m_dirX = x;
	m_dirY = y;
}

void Character::SetPosition(const short int& x, const short int& y) {
	m_Position.X = x;
	m_Position.Y = y;

}



void Character::Move(const short int& x, const short int& y,Entity** entireMapChar) {
	//Check Collision 
	if (entireMapChar[m_Position.Y + y][m_Position.X + x] == E_BLANK) {
		entireMapChar[m_Position.Y][m_Position.X] = E_BLANK;
		
		//mapData[m_Position.Y][m_Position.X].m_ColorInHex = 0x0;
		m_Position.X += x*m_speed;
		m_Position.Y += y*m_speed;
		entireMapChar[m_Position.Y][m_Position.X].m_Character = this->m_Character;
		entireMapChar[m_Position.Y][m_Position.X].m_ColorInHex = this->m_ColorInHex;
		entireMapChar[m_Position.Y][m_Position.X].m_CharHealth = this->m_CharHealth;
	}

	m_dirX = x;
	m_dirY = y;
}