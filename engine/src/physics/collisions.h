#pragma once
#include "glm/glm.hpp"
#include <memory>

struct Body;

struct Sphere
{
	Body* body;
	float radius;
};

struct Contact
{
	glm::vec3 normal;
	float penetration;
	glm::vec3 point;
};

bool overlapSphereSphere(const Sphere& colA, const Sphere& colB, Contact* out = nullptr);
void resolveSphereCollision(Sphere& colA, Sphere& colB, Contact& contact, float dt);

class CollisionSolver
{
private:
	std::vector<std::unique_ptr<Sphere>> sphereColliders;

	const float targetDt = 1.0f / 60.0f;
	const int SOLVER_ITERATIONS = 3;

public:
	CollisionSolver();
	~CollisionSolver();

	void update(float dt);

	/**
	 * @brief Adds collider based on given shape type
	 * @tparam T Needs to be a valid shape type from - TODO: Create unified space for collider shape types
	 * @return 
	 */
	template<typename T>
	T* addCollider()
	{
		if (std::is_same<T, Sphere>::value)
		{
			// Sphere
			auto collider = std::make_unique<T>();
			sphereColliders.push_back(std::move(collider));

			return sphereColliders[sphereColliders.size() - 1].get();
		}

		return nullptr;
	}
};