#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "Events/Event.h"
#include <boost/container/deque.hpp>

class IEventReceiver;

class EventDispatcher {
private:
    boost::container::deque<IEventReceiver*> m_receivers;

public:
    EventDispatcher();

    EventDispatcher(EventDispatcher&&) = delete;
    EventDispatcher(const EventDispatcher&) = delete;
    EventDispatcher& operator=(const EventDispatcher&) = delete;

    void register_receiver(IEventReceiver&);
    void unregister_receiver(IEventReceiver&);
    void dispatch(Event&);
};

#endif // EVENTDISPATCHER_H
