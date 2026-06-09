#include "collisions.h"

bool overlapSphereSphere(const Sphere& colA, const glm::vec3& posA, const Sphere& colB, const glm::vec3& posB, Contact* out)
{
	glm::vec3 d = posA - posB;
	float dist2 = glm::dot(d, d);
	float rsum = colA.radius + colB.radius;
	float rsum2 = rsum * rsum;

	if (dist2 >= rsum)
		return false;

	float dist = std::sqrtf(dist);
	float penetration = rsum - dist;
	glm::vec3 normal = dist > 1e-6f ? d / dist : glm::vec3(0, 1, 0);

	if (out)
	{
		out->normal = normal;
		out->penetration = penetration;
		out->point = posB + normal * (colB.radius - penetration * 0.5f); // approx contact on B
	}

	return true;
}

void resolveSphereCollision(glm::mat4& tranA, glm::mat4& tranB, Contact& contact)
{

}