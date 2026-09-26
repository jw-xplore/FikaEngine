#include "editor_camera.h"
#include "core/fika_servers.h"

namespace FikaEditor
{
	EditorCamera::EditorCamera()
	{

	}

	EditorCamera::EditorCamera(Camera* camera, Window* window) : camera(camera), window(window)
	{

	}

	void EditorCamera::update(float dt)
	{
		keyboardControl(dt);
		mouseControl(dt);
	}

	void EditorCamera::keyboardControl(float dt)
	{
		InputManager input = FikaServers::getInputManager();

		if (!input.isMouseHeld(Mouse::RightButton))
			return;

		glm::vec3 front = camera->getDirection();
		glm::vec3 rightVec = camera->getRightVector();
		const glm::vec3 upVec = glm::vec3(0, 1, 0);

		// Adjust speed
		float scroll = input.mouseScroll();

		if (scroll > 0 && speed < maxSpeed)
			speed += speedChange;
		else if (scroll < 0 && speed > minSpeed)
			speed -= speedChange;

		// Forwards - backwards
		float forward = 0;
		if (input.isKeyHeld(Key::W))
			forward = 1;
		if (input.isKeyHeld(Key::S))
			forward = -1;

		// Sides
		float right = 0;
		if (input.isKeyHeld(Key::D))
			right = 1;
		if (input.isKeyHeld(Key::A))
			right = -1;

		// Up - Down
		float up = 0;
		if (input.isKeyHeld(Key::E))
			up = 1;
		if (input.isKeyHeld(Key::Q))
			up = -1;

		// Boost
		float boost = 1;
		if (input.isKeyHeld(Key::LeftShift))
			boost = 3;

		float velocity = speed * dt * boost;

		glm::vec3 change = front * forward * velocity;
		change += rightVec * right * velocity;
		change.y += up * velocity;

		camera->translate(change);
	}

	void EditorCamera::mouseControl(float dt)
	{
		InputManager input = FikaServers::getInputManager();

		if (!input.isMouseHeld(Mouse::RightButton))
			return;

		glm::vec2 change = input.getMouse().positionDelta * sensitivity;
		camera->rotate(change.x, -change.y, pitchLimit);
	}
}