#include "audio_manager.h"

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
        for (size_t i = 0; i < playingSounds.getUsedAmount(); i++)
        {
            if (ma_sound_at_end(&playingSounds[i]))
            {
                // Remove finished sound instance
                ma_sound_uninit(&playingSounds[i]);
                playingSounds.remove(&playingSounds[i]);
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
            ma_engine_uninit(&engine);
            loadedSounds.erase(name);
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

    void AudioManager::playSound(ma_sound& sound)
    {
        // Create sound copy
        ma_sound* instance = playingSounds.allocate();

        if (ma_sound_init_copy(&engine, &sound, 0, nullptr, instance) != MA_SUCCESS)
        {
            playingSounds.remove(instance);
            std::cout << "Audio manager failed to create sound copy";
            assert(false);
        }

        // Play
        if (ma_sound_start(instance) != MA_SUCCESS)
        {
            ma_sound_uninit(instance);
            playingSounds.remove(instance);
            std::cout << "Failed to play sound";
            assert(false);
        }
    }
}