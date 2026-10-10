#include <iostream>
#include <fika_engine.h>

#include "core/content_manager.h"
#include "components/player_component.h"
#include "components/bullet_component.h"
#include "components/enemy_component.h"
#include "components/health_component.h"
#include "components/spawner_component.h"
#include "glm/gtc/random.hpp"

/*
Project Fika Mayhem
*/

using namespace FikaEngine;

void componentsInit()
{
    // Engine components
    TransformComponentUpdater::init(POOL_DEFAULT_SIZE);
    RigidBodyComponentUpdater::init(POOL_DEFAULT_SIZE);
    MeshComponentUpdater::init(POOL_DEFAULT_SIZE);

    // Custom components
    PlayerComponentUpdater::init(1);
    BulletComponentUpdater::init(POOL_DEFAULT_SIZE);
    EnemyComponentUpdater::init(POOL_DEFAULT_SIZE);
    HealthComponentUpdater::init(POOL_DEFAULT_SIZE);
    SpawnerComponentUpdater::init(POOL_DEFAULT_SIZE);
}

Transform* playerTransform;
HealthComponent* playerHealth;

void start()
{
    componentsInit();
    //ContentManager::buildPrefabs();

    Entity& player = ContentManager::createPlayer();
    playerTransform = FikaServers::getECSManager().findEntityTransform(player);
    playerHealth = static_cast<HealthComponent*>(FikaServers::getECSManager().findComponent(player, HealthComponent::componentId));
    
    //ContentManager::createBox(glm::vec3(2, 0, 0));

    //ContentManager::createEnemy(glm::vec3(4, 0, 3));

    ContentManager::createSpawner(glm::vec3(10, 0, 3), 2, 5, 1);
}

float playTime = 0;
float spawnTimer = 0;
float spawnDelay = 3;

void spawnEnemies(float dt)
{
    if (spawnTimer > 0)
    {
        spawnTimer -= dt;
        return;
    }

    const float min = -10;
    const float max = 10;

    // Spawn
    float x = 0;
    while (abs(x) < max * 0.5)
    {
        x = glm::linearRand(min, max);
    }

    float z = 0;
    while (abs(z) < max * 0.5)
    {
        z = glm::linearRand(min, max);
    }

    glm::vec3 pos = playerTransform->getLocalPosition();
    ContentManager::createEnemy(pos + glm::vec3(x, 0, z));

    spawnTimer = spawnDelay;

    if (spawnDelay > 0.6f)
        spawnDelay -= 0.1f;
}

void debugUI(GLFWwindow* window)
{
    // TODO: Cleanup and make into general purpose
    ImGuiIO& io = ImGui::GetIO();
    int fb_w = 0, fb_h = 0;
    glfwGetFramebufferSize(window, &fb_w, &fb_h);
    if (fb_w > 0 && fb_h > 0) {
        io.DisplaySize = ImVec2(static_cast<float>(fb_w), static_cast<float>(fb_h));

        int win_w = 0, win_h = 0;
        glfwGetWindowSize(window, &win_w, &win_h);
        io.DisplayFramebufferScale = ImVec2(
            win_w > 0 ? static_cast<float>(fb_w) / static_cast<float>(win_w) : 1.0f,
            win_h > 0 ? static_cast<float>(fb_h) / static_cast<float>(win_h) : 1.0f
        );
    }

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();

    ImGui::Begin("Stats");

    std::string strHp = "HP: " + std::to_string(playerHealth->getHp());
    ImGui::Text(strHp.c_str());
    std::string strTime = "Time: " + std::to_string(playTime);
    ImGui::Text(strTime.c_str());

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void update(float dt)
{
    if (ContentManager::getPlayerEntity() && playerHealth->isAlive())
    {
        playTime += dt;
        //spawnEnemies(dt);
    }
}

void postUpdate(float dt)
{
    if (playTime > 0)
        debugUI(glfwGetCurrentContext());
}

int main()
{
    FikaEngine::Game game;
    game.setup(start, update, postUpdate);
    game.run();
}