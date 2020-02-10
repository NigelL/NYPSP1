#include "PresetParticles.h"

double Deg2Rad(double angle) {
	return  angle * (3.14156 / 180);
}

void UpdateParticleDir(COORD _dir,std::vector<COORD>& allDirs,bool justFlip) {
	
	//x 
	// 1,0      1,1       1,-1 
	// -1,0     -1,1      -1,-1 

	//y 
	// 0,1     1,1      -1, 1
	// 0,-1    1,-1      -1,-1 

	if (_dir.X == 0) {
		if (!justFlip) {
			for (int i = 0; i < (int)allDirs.size(); i++) {
				allDirs[i].Y = _dir.Y;
				allDirs[i].X = i + ((i == 2) ? -3 : 0);
			}
		}
		else {
			for (int i = 0; i < (int)allDirs.size(); i++) {
				allDirs[i].Y = _dir.Y;
			}
		}
	}
	else if (_dir.Y == 0) {
		if (!justFlip) {
			for (int i = 0; i < (int)allDirs.size(); i++) {
				allDirs[i].X = _dir.X;
				allDirs[i].Y = i + ((i == 2) ? -3 : 0);
			}
		}
		else {
			for (int i = 0; i < (int)allDirs.size(); i++) {
				allDirs[i].X = _dir.X;
//				allDirs[i].Y = i + ((i == 2) ? -3 : 0);
			}
		}
	}

}

void FlipParticles(std::vector<Particle>& particlesToFlip, COORD _dir) {
	for (int i = 0; i < (int)particlesToFlip.size(); i++) {
		if (_dir.X < 0) {
			if (-particlesToFlip[i].particle.m_Position.X + 179 <= 179) {
				particlesToFlip[i].particle.m_Position.X =  179 - particlesToFlip[i].particle.m_Position.X;
			}
		}
		else {
			if (particlesToFlip[i].particle.m_Position.X  >= 90) {
				particlesToFlip[i].particle.m_Position.X = abs(particlesToFlip[i].particle.m_Position.X - 179);
			}
		}
	}
}

std::vector<COORD> BreakWallParticleSetup() {

	std::vector<COORD> allParticleDirs =  std::vector<COORD>(3);
	allParticleDirs[0].X = 1;
	allParticleDirs[0].Y = 0;

	allParticleDirs[1].X = 1;
	allParticleDirs[1].Y = 1;

	allParticleDirs[2].X = 1;
	allParticleDirs[2].Y = -1;
	return allParticleDirs;

}
std::vector<Particle> EzrealParticleSetup(int radius,Entity ezParticle) {
	std::vector<Particle> particleLocation;
	COORD ezDirParticle = { 1 ,0 };
	for (int j = 0; j < 2; j++) {
		for (int i = 1; i < radius; i++) {
			if ((i > (radius / 2) - 5 && i  < (radius / 2) + 5 ) && i % 2 == 0) {
				continue;
			}

			COORD partLocation;
			partLocation.X = (SHORT)(sin(Deg2Rad((i) * (180 / (radius)))) * (radius * 0.5f) - (j));
			partLocation.Y = i;
			ezParticle.m_Position = partLocation;
			particleLocation.push_back(Particle(ezParticle, ezDirParticle));
		}
	}
	return particleLocation;
}
