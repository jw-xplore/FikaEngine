#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include <assert.h>
#include "glm/glm.hpp"

#include "miniaudio.h"
#include "core/pool_allocator.h"

namespace FikaEngine
{
	struct AudioListener
	{
		glm::vec3 position = glm::vec3(0.0f);
	};

	struct AudioSource
	{
		glm::vec3 position = glm::vec3(0.0f);
		ma_sound* soundInstance = nullptr;
		float maxDistance = 20.0f;
	};

	class AudioManager
	{
	private:
		ma_engine engine;
		std::map<std::string, ma_sound> loadedSounds;
		PoolAllocator<ma_sound> playingSounds;

		// Used for large audio files (Music)
		std::map<std::string, ma_sound> loadedStreamables;

		AudioListener listener;
		PoolAllocator<AudioSource> audioSources;

	public:
		AudioManager();
		~AudioManager();

		void init();
		void update(float dt);

		/**
		 * @brief Load short sound into map in order to be used later.
		 * @param name - Identifier inside sounds map.
		 * @param path - Sound file path.
		 * @return Loading succesful
		 */
		bool loadSound(std::string name, std::string path);
		ma_sound* getSound(std::string name);
		bool removeSound(std::string name);
		ma_sound* playSound(ma_sound& sound);

		bool loadStreamable(std::string name, std::string path);
		ma_sound* getStreamable(std::string name);
		bool removeStreamable(std::string name);
		void playStreamable(std::string name);

		AudioSource* playfromAudioSource(ma_sound& sound, glm::vec3 position);
		void setAudioListenerPosition(glm::vec3 position);
	};
}