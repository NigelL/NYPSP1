#pragma once
#include "Class.h"
#include <cctype>
class Character : public Class {
public:
	short int m_speed = 1;
	short int m_dirX, m_dirY, m_prevDirX, m_prevDirY;
	short int m_damage;

	void SetDirection(const short int& x, const short int& y);
	
	

	void SetPosition(const short int& x, const short int& y);



	
	

	void Move(const short int& x, const short int& y,Entity** mapdata);
		//Check Collision 
	
	Character(short int charHealth,short int damage) : Class(){
		m_CharHealth = charHealth;
		m_damage = damage;
	}

	


};