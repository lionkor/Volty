#ifndef IEVENTRECEIVER_H
#define IEVENTRECEIVER_H

#include <boost/atomic.hpp>
#include <cstdint>

#include "Core/Object.h"
#include "EventDispatcher.h"

// Interfaces do not inherit from Object
class IEventReceiver {
private:
    EventDispatcher& m_dispatcher;

public:
    explicit IEventReceiver(EventDispatcher& dispatcher);
    virtual ~IEventReceiver();

    bool operator==(const IEventReceiver& disp) {
        return this == &disp; // TODO: this sucks.
    }

    // Will reveice all events. Events received here are guaranteed to not yet be accepted.
    virtual void handle(Event&);
};

#endif // IEVENTRECEIVER_H
