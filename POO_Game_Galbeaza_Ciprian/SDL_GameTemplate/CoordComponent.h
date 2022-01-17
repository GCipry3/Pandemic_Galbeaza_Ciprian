#pragma once
#include "Component.h"

class CoordComponent :public Component
{
private:
	float x;
	float y;
public:
	CoordComponent() : x(0), y(0) {}
	inline float X() { return x; };
	inline float Y() { return y; };

	void init() override {set(0, 0);}
	void update() override {};
	void draw() override {};

	void set(float x, float y) { this->x = x; this->y = y; };
	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
};