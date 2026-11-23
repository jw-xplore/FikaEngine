#pragma once
#include <functional>
#include <utility>
#include <list>

namespace FikaEngine
{
    template<class Signature>
    class Event;

    template<class... Args>
    class Event<void(Args...)>
	{
    public:
        using Listener = std::function<void(Args...)>;

        Listener* addListener(Listener listener)
        {
            listeners.push_back(std::move(listener));
            return &listeners.back();
        }

        bool removeListener(Listener& listener)
        {
            auto it = std::find(listeners.begin(), listeners.end(), listener);

            if (it == listeners.end())
            {
                return false;
            }

            listeners.erase(it);
            return true;
        }

        void broadcast(Args... args)
        {
            for (auto& listener : listeners)
            {
                listener(args...);
            }
        }

    private:
        std::list<Listener> listeners;
        int lastFreeElement = 0;
	};
}