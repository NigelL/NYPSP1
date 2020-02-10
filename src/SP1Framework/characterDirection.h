#include <iostream>

class characterDirection
{
public:
	characterDirection();
	~characterDirection();
	enum charDirection
	{
		K_UP = 1,
		K_DOWN = 2,
		K_LEFT = 4,
		K_RIGHT = 8
	};
};

