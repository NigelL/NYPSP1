#pragma once
#include <Windows.h>
#include "Values.h"
class Entity {
public:
	COORD m_Position;
	unsigned char m_Character;
	WORD m_ColorInHex;
	short int m_CharHealth;
	short int IDENTIFIER;

	Entity() {

	}

	Entity(COORD pos, unsigned char chars, WORD color) {
		m_Position = pos;
		m_Character = chars;
		m_ColorInHex = color;
		
	}
	Entity(unsigned char chars, WORD color,short int identifier) {
		
		m_Character = chars;
		m_ColorInHex = color;
		IDENTIFIER = identifier;
		
	}

	void TakeDamage(short int damage)
	{
		m_CharHealth -= damage;
		if (m_CharHealth <= 0) {
			m_CharHealth = 0;
			this->m_Character = 32;
		}
	}


	bool operator==(const Entity& other) {
		if (this == nullptr) {
			return false;
		}
		return (this->m_Character == other.m_Character) && (this->m_ColorInHex == other.m_ColorInHex) && (this->IDENTIFIER == other.IDENTIFIER);
	}
};
