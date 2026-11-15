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

	public:
		AudioManager();
		~AudioManager();

		void init();
		void update(float dt);

		bool loadSound(std::string name, std::string path);
		ma_sound* getSound(std::string name);
		bool removeSound(std::string name);
		void playSound(ma_sound& sound);
	};
}