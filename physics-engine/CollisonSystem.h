#ifndef COLLISON_SYSTEM_H
#define COLLISON_SYSTEM_H

class Rigidbody;

class CollisonSystem {
	public:
		static void Solve(Rigidbody* body);
};

#endif // !COLLISON_SYSTEM_H
