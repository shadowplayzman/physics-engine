#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

class Circle {
public:
	float x;
	float y;

	float vx;
	float vy;
	
	float radius;

	Circle(float startX, float startY, float startRadius);
	void update(float dt);

	void ApplyGravity(float gravity, float dt);

	void checkWallCollision(float left, float right, float top, float bottom);

	void Draw();
};




#endif // !CIRCLE_CLASS_H
