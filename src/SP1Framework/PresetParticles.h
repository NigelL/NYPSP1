#pragma once

#include <Windows.h>
#include "Particle.h"
#include "Entity.h"
#include <vector>


std::vector<COORD> BreakWallParticleSetup();
std::vector<Particle> EzrealParticleSetup(int radius, Entity ezParticle);
void UpdateParticleDir(COORD _dir, std::vector<COORD>& allDirs, bool _justFlip);
void FlipParticles(std::vector<Particle>& particlesToFlip, COORD _dir);