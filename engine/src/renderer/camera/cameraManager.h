class Camera;
class Window;

namespace CameraManager
{
	void init(Window& window);
	Camera* getActiveCamera();
	void useFreeCamera(bool use);
	bool isUsingFreeCamera();

	Camera* getMainCamera();
	Camera* getFreeCamera();
}