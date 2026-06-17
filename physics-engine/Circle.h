#ifndef CIRCLE_CLASS_H
#define CIRCLE_CLASS_H

class Circle {
public:
	float x,y;


	float vx,vy;

	float fx, fy;

	float radius;
	float mass;

	Circle(float startX, float startY, float startRadius);
	void update(float dt);

	void checkWallCollision(float left, float right, float top, float bottom);

	void AddForce(float ForceX, float ForceY);

	void Draw();
};




#endif // !CIRCLE_CLASS_H
