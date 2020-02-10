#include "Particle.h"



Particle::Particle() {

}


Particle::Particle(Entity _particle) : particle(_particle) {

}

Particle::Particle(Entity _particle,COORD _speed) : particle(_particle),m_Speed(_speed){

}



void Particle::Update()  {
	
	Move(m_Speed);
	
}

void Particle::Move(COORD nextCOORD) {
	particle.m_Position.X += nextCOORD.X;
	particle.m_Position.Y += nextCOORD.Y;
	/*
	if (this->Collision(particle)) {
		particle.m_Position.X -= nextCOORD.X;
		particle.m_Position.Y -= nextCOORD.Y;
		COORD newNextCOORD;
		newNextCOORD.X = nextCOORD.X != 0 ? nextCOORD.X - (nextCOORD.X / abs(nextCOORD.X)): nextCOORD.X;
		newNextCOORD.Y = nextCOORD.Y != 0 ? nextCOORD.Y - (nextCOORD.Y / abs(nextCOORD.Y)) : nextCOORD.Y;
		Move(newNextCOORD);
	}
	*/
	
}




