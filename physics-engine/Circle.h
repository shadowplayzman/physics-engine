#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

class Circle {
public:
	float x,y;


	float vx,vy;

	float radius;
	float mass;

	Circle(float startX, float startY, float startRadius);
	void update(float dt);

	void ApplyGravity(float gravity, float dt);

	void checkWallCollision(float left, float right, float top, float bottom);

	void Draw();
};




#endif // !CIRCLE_CLASS_H
