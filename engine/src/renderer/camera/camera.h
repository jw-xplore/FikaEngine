#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace FikaEngine
{
    class Window;

    /*
    namespace Input
    {
        struct Keyboard;
        struct Mouse;
    }
    */

    class Camera
    {
    private:
        // TODO: Remove these
        void processMouse(float dt);
        void processKeyboard(float dt);

    public:
        Camera() {}
        Camera(Window& window);

        void updateVectors();

        /**
         * @brief Set direction toward given target.
         * @param target vec3 position to look at.
         */
        void lookAt(glm::vec3 target);

        /**
         * @brief Update camera position and direction.
         * @param position 
         * @param direction 
         */
        void move(glm::vec3 position, glm::vec3 direction);

        void translate(glm::vec3 move);
        void rotate(float yaw, float pitch);

        /**
         * @brief Updates free flying camera, including keyboard and mouse controls.
         * @param dt 
         */
        void flycamUpdate(float dt);

        void setPosition(glm::vec3 position)
        {
            this->position = position;
            updateVectors();
            lookAt(position + direction);
        }

        glm::mat4 getView() { return view; }
        glm::mat4 getProjection() { return projection; }
        glm::mat4 getViewProjection() { return projection * view; }
        glm::vec3 getPosition() { return position; }
        glm::vec3 getDirection() { return direction; }
        glm::vec3 getRightVector() { return rightVec; }
        float getFov() { return fov; }

    private:
        Window* window;
        // NOTE: Camera should not know about input devices
        //Input::Keyboard* keyboard;
        //Input::Mouse* mouse;

        float yaw = 90;
        float pitch = 0;

        /*
        float speed = 5.0f;
        float minSpeed = 1.0f, maxSpeed = 20.0f, speedChange = 1.0f;
        float sensitivity = 10.1f;
        */

        glm::vec3 rotation;

        float fov = 45.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;

        glm::vec3 position{ 0, 0, -5 };
        glm::vec3 direction = { 0, 0, 1};
        glm::vec3 front{ 0,0,-1 };
        glm::vec3 rightVec{ 1,0,0 };
        glm::vec3 upVec{ 0,1,0 };

        glm::mat4 view;
        glm::mat4 projection;
        //bool freeControls = true;
    };
} // namespace FikaEngine
