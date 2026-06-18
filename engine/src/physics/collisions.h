#pragma once
#include "glm/glm.hpp"
#include <memory>

struct Body;

struct Sphere
{
	Body* body;
	float radius;
};

struct Box
{
	Body* body;
	float width, height, depth;
};

struct Contact
{
	glm::vec3 normal;
	float penetration;
	glm::vec3 point;
};

const float PENETRATION_MULT = 0.0166f; // TODO: Adjust this with proper behavior and calculation

class CollisionSolver
{
private:
	std::vector<std::unique_ptr<Sphere>> sphereColliders;
	int bodiesCount = 0; // TODO: Do safer implementation
	std::vector<bool> ongoingContacts;

	const float targetDt = 1.0f / 60.0f;
	const int SOLVER_ITERATIONS = 3;
	const float MIN_DISTANCE = 1e-6f;

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

	void addDebugMesh(glm::mat4& transform, float radius = 1);

	bool overlapSphereSphere(const Sphere& colA, const Sphere& colB, Contact* out = nullptr);
	void resolveSphereCollision(Sphere& colA, Sphere& colB, Contact& contact, float dt);

	bool overlapBoxBox(const Box& colA, const Box& colB, Contact* out = nullptr);

	void setupOngoinContacts(const std::vector<std::unique_ptr<Body>>& bodies);
	int contactFromPair(int bodyIdA, int bodyIdB);
};