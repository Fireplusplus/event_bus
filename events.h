#pragma once

#include "log.h"
#include <memory>
#include <list>


template <typename EventClass>
class EventBus {
public:
	EventBus() = default;
	~EventBus() = default;

	static void Register(std::weak_ptr<EventClass> event) {
		for (auto& ev : events_) {
			auto ev_ptr = ev.lock();
			auto event_ptr = event.lock();
			if (ev_ptr == event_ptr) {
				INFO("skip exist event!");
				return;
			}
		}
		events_.emplace_back(event);
	}
	
	static void Unregister(std::weak_ptr<EventClass> event) {
		for (auto ev_it = events_.begin(); ev_it != events_.end(); ++ev_it) {
			auto ev_ptr = ev_it->lock();
			auto event_ptr = event.lock();
			if (ev_ptr == event_ptr) {
				events_.erase(ev_it);
				return;
			}
		}
	}

	template<typename EventFun, typename... EventArgs>
	static void OnEvent(EventFun fun, EventArgs&&... args) {
		for (const auto& ev : events_) {
			auto ptr = ev.lock();
			if (!ptr) {
				ERROR("skip not exist event!");
				continue;
			}

		 	auto obj = ptr.get();
			(obj->*fun)(args...);
		}
	}

private:
	static std::list<std::weak_ptr<EventClass>> events_;
};

template <typename EventClass>
std::list<std::weak_ptr<EventClass>> EventBus<EventClass>::events_;



