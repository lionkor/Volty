#include "IEventReceiver.h"
#include "Utils/DebugTools.h"

IEventReceiver::IEventReceiver(EventDispatcher& dispatcher)
    : m_dispatcher(dispatcher) {
}

IEventReceiver::~IEventReceiver() = default;

void IEventReceiver::handle(Event&) {
}
