#pragma once

#include "SDL.h"
#include "Component.h"
#include "CoordComponent.h"
class PositionComponent : public Component
{
public:
	CoordComponent position;
	CoordComponent velocity;
	static int speed;

	PositionComponent() { position.set(0, 0); velocity.set(0, 0); speed = 5; }; //vom lasa standard speed pe 5
	~PositionComponent() {};

	void init()override;
	void update()override;
	void draw()override;

	//Update la coordonatele player-ului
	static CoordComponent PositionFromVelocity(CoordComponent position, CoordComponent velocity);
};