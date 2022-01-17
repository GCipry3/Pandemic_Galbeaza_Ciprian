#include "PositionComponent.h"
int PositionComponent::speed;
void PositionComponent::init()
{
	position.set(0, 0);
	velocity.set(0, 0);
	speed = 5;

}


void PositionComponent::update()
{
	//position.set(position.X() + speed * velocity.X(), position.Y() + speed * velocity.Y());
}

void PositionComponent::draw()
{}

CoordComponent PositionComponent::PositionFromVelocity(CoordComponent position, CoordComponent velocity)
{
	CoordComponent temp;
	temp.set(position.X() + speed * velocity.X(), position.Y() + speed * velocity.Y());
	return temp;
}
