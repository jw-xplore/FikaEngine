#include "audio_manager.h"
#include <algorithm>

namespace FikaEngine
{
    AudioManager::AudioManager()
    {

    }

    AudioManager::~AudioManager()
    {
        ma_engine_uninit(&engine);
    }

    void AudioManager::init()
    {
        playingSounds.init("Playing sounds", 64);
        audioSources.init("Audio sources", 64);

        ma_result result;

        result = ma_engine_init(NULL, &engine);
        if (result != MA_SUCCESS)
        {
            // Init fail
            return;
        }
    }

    void AudioManager::update(float dt)
    {
        glm::vec3 normListenerRight = glm::normalize(listener.rightVector);

        // Update source-listeners
        for (size_t i = 0; i < audioSources.getUsedAmount(); i++)
        {
            ma_sound* sound = audioSources[i].soundInstance;

            if (!sound)
            {
                continue;
            }

            if (ma_sound_at_end(sound))
            {
                // Remove and ignore finished sound instance
                ma_sound_uninit(sound);
                audioSources.remove(&audioSources[i]);
                playingSounds.remove(sound);
                i--;

                continue;
            }

            // Adjust volume to distance
            glm::vec3 diff = audioSources[i].position - listener.position;
            float distSqr = glm::dot(diff, diff);

            float minDistSqr = audioSources[i].minDistance * audioSources[i].minDistance;
            float maxDistSqr = audioSources[i].maxDistance * audioSources[i].maxDistance;

            float distVolume = 1.0f - ((distSqr - minDistSqr) / distSqr);
            if (distSqr > maxDistSqr)
            {
                distVolume = 0.0f;
            }

            distVolume = std::clamp(distVolume, 0.0f, 1.0f);
            ma_sound_set_volume(sound, distVolume);

            // Panning
            glm::vec3 normDiff = glm::normalize(diff);
            float pan = glm::dot(normListenerRight, normDiff);

            ma_sound_set_pan(sound, pan);
        }

        // Update sound instances
        for (size_t i = 0; i < playingSounds.getUsedAmount(); i++)
        {
            if (ma_sound_at_end(&playingSounds[i]))
            {
                // Remove finished sound instance
                ma_sound_uninit(&playingSounds[i]);
                playingSounds.remove(&playingSounds[i]);
                i--;
            }
        }
    }

    bool AudioManager::loadSound(std::string name, std::string path)
    {
        auto [it, inserted] = loadedSounds.try_emplace(name);
        if (!inserted)
        {
            // Already exists
            return &it->second;
        }

        if (ma_sound_init_from_file(
            &engine,
            path.c_str(),
            MA_SOUND_FLAG_DECODE,
            nullptr,
            nullptr,
            &it->second) != MA_SUCCESS)
        {
            // Fail to init file
            //ma_engine_uninit(&engine);
            loadedSounds.erase(name);
            std::cout << "Failed to load: " << path << "\n";

            return false;
        }

        return true;
    }

    ma_sound* AudioManager::getSound(std::string name)
    {
        if (loadedSounds.find(name) != loadedSounds.end())
        {
            return &loadedSounds[name];
        }

        return nullptr;
    }

    bool AudioManager::removeSound(std::string name)
    {
        if (loadedSounds.find(name) != loadedSounds.end())
        {
            loadedSounds.erase(name);
            return true;
        }

        return false;
    }

    ma_sound* AudioManager::playSound(ma_sound& sound)
    {
        // Create sound copy
        ma_sound* instance = playingSounds.allocate();

        if (ma_sound_init_copy(&engine, &sound, 0, nullptr, instance) != MA_SUCCESS)
        {
            playingSounds.remove(instance);
            std::cout << "Audio manager failed to create sound copy";
            return nullptr;
        }

        // Play
        if (ma_sound_start(instance) != MA_SUCCESS)
        {
            ma_sound_uninit(instance);
            playingSounds.remove(instance);
            std::cout << "Failed to play sound";
            return nullptr;
        }

        return instance;
    }

    bool AudioManager::loadStreamable(std::string name, std::string path)
    {
        auto [it, inserted] = loadedStreamables.try_emplace(name);
        if (!inserted)
        {
            // Already exists
            return &it->second;
        }

        if (ma_sound_init_from_file(
            &engine,
            path.c_str(),
            MA_SOUND_FLAG_STREAM,
            nullptr,
            nullptr,
            &it->second) != MA_SUCCESS)
        {
            // Fail to init file
            //ma_engine_uninit(&engine);
            loadedStreamables.erase(name);
            return false;
        }

        return true;
    }

    ma_sound* AudioManager::getStreamable(std::string name)
    {
        if (loadedStreamables.find(name) != loadedStreamables.end())
        {
            return &loadedStreamables[name];
        }

        return nullptr;
    }

    bool AudioManager::removeStreamable(std::string name)
    {
        if (loadedStreamables.find(name) != loadedStreamables.end())
        {
            loadedStreamables.erase(name);
            return true;
        }

        return false;
    }

    ma_sound* AudioManager::playStreamable(std::string name)
    {
        auto it = loadedStreamables.find(name);
        if (it == loadedStreamables.end())
        {
            return nullptr;
        }

        ma_sound_start(&it->second);
        return &it->second;
    }

    AudioSource* AudioManager::playfromAudioSource(ma_sound& sound, glm::vec3 position)
    {
        AudioSource* source = audioSources.allocate();
        source->soundInstance = playSound(sound);
        source->position = position;

        return source;
    }

    void AudioManager::setListenerPosition(glm::vec3 position)
    {
        listener.position = position;
    }

    void AudioManager::setListenerRightVector(glm::vec3 right)
    {
        listener.rightVector = right;
    }
}