#include"PhysicsWorld.h"


PhysicsWorld::PhysicsWorld(float gravityValue) {
	gravity = gravityValue;
}

void PhysicsWorld::update(float dt) {
	// gravity movemnt and friction
	for (Circle& ball : balls) {
		bool onground = (balls[0].y - balls[0].radius <= -1.0f + 0.001f);
		float floorfriction = 0.4f;
		ball.ApplyGravity(gravity, dt);
		if (onground == true) {
			float friction = floorfriction * fabs(gravity);

			if (ball.vx > 0) {
				ball.vx -= friction * dt;
				if (ball.vx == 0) {
					ball.vx = 0;
				}
			}
			if (ball.vy > 0) {
				ball.vy -= friction * dt;
				if (ball.vy == 0) {
					ball.vy = 0;
				}
			}
		}

		ball.update(dt);
		ball.checkWallCollision(-1.0f, 1.0f, 1.0f, -1.0f);

	}
	// ball ball collisons

	for (int i = 0;i < balls.size(); i++) {
		for (int j = i + 1;j < balls.size(); j++) {

			Circle& A = balls[i];
			Circle& B = balls[j];

			float dx = B.x - A.x;
			float dy = B.y - A.y;


			float distance = sqrt(dx * dx + dy * dy);


			if (distance < A.radius + B.radius && distance>0.00001f) {
				float overlap = (A.radius + B.radius) - distance;
				float nx = dx / distance;
				float ny = dy / distance;
				float totalMass = A.mass + B.mass;

				float rvx = A.vx - B.vx;
				float rvy = A.vy - B.vy;

				float velAlongNormal = rvx * nx + rvy * ny;


				A.x -= nx * overlap * (B.mass / totalMass);
				A.y -= ny * overlap * (B.mass / totalMass);

				B.x += nx * overlap * (B.mass / totalMass);
				B.y += ny * overlap * (B.mass / totalMass);

				if (velAlongNormal < 0) {
					float e = 0.8f;

					float j = -(1.0f + e) * velAlongNormal;

					j /= (1 / A.mass) + (1 / B.mass);

					float impluseX = j * nx;
					float impluseY = j * ny;

					A.vx -= impluseX / A.mass;
					A.vy -= impluseY / A.mass;

					B.vx -= impluseX / B.mass;
					B.vy -= impluseY / B.mass;
				}

			}
		}
	}
}