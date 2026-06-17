#include"Circle.h"

Circle::Circle(float startX,float startY,float startRadius) {
	x = startX;
	y = startY;

	vx = 0.0f;
	vy = 0.0f;

    fx = 0.0f;
    fy = 0.0f;

	radius = startRadius;
    mass = radius*radius;
}
void Circle::AddForce(float ForceX, float ForceY) {
    fx += ForceX;
    fy += ForceY;
}

void Circle::update(float dt) {
    float ax = fx / mass;
    float ay = fy / mass;

    vx += ax * dt;
    vy += ay * dt;

    x += vx * dt;
    y += vy * dt;

    fx = 0.0f;
    fy = 0.0f;
}


void Circle::checkWallCollision(float left, float right, float top, float bottom) {
	// floor
    if (x - radius < left)
    {
        x = left + radius;
        vx *= -0.8f;
    }

    if (x + radius > right)
    {
        x = right - radius;
        vx *= -0.8f;
    }

    if (y - radius < bottom)
    {
        y = bottom + radius;
        vy *= -0.8f;
    }

    if (y + radius > top)
    {
        y = top - radius;
        vy *= -0.8f;
    }
}