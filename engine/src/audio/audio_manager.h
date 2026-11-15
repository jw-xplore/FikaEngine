#pragma once

#include <stdio.h>
#include <map>
#include <string>
#include <assert.h>

#include "miniaudio.h"
#include "core/pool_allocator.h"

namespace FikaEngine
{
	class AudioManager
	{
	private:
		ma_engine engine;
		std::map<std::string, ma_sound> loadedSounds;
		PoolAllocator<ma_sound> playingSounds;

		// Used for large audio files (Music)
		std::map<std::string, ma_sound> loadedStreamables;
		PoolAllocator<ma_sound> playingStreamables;

	public:
		AudioManager();
		~AudioManager();

		void init();
		void update(float dt);

		/**
		 * @brief Load sound into map in order to be used later.
		 * @param name - Identifier inside sounds map.
		 * @param path - Sound file path.
		 * @return Loading succesful
		 */
		bool loadSound(std::string name, std::string path);
		ma_sound* getSound(std::string name);
		bool removeSound(std::string name);
		void playSound(ma_sound& sound);

		bool loadStreamable(std::string name, std::string path);
		ma_sound* getStreamable(std::string name);
		bool removeStreamable(std::string name);
		void playStreamable(std::string name);
	};
}