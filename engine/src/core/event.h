#pragma once
#include <functional>
#include <utility>
#include <vector>

namespace FikaEngine
{
    template<class Signature>
    class Event;

    template<class... Args>
    class Event<void(Args...)>
	{
    public:
        using Listener = std::function<void(Args...)>;

        void addListener(Listener listener) {
            listeners.push_back(std::move(listener));
        }

        void broadcast(Args... args) {
            for (auto& listener : listeners) {
                listener(args...);
            }
        }

    private:
        std::vector<Listener> listeners;
	};
}