#include "Events/Event.h"

Event::Event() {
}

void Event::accept() {
    m_accepted.store(true);
}

bool Event::accepted() const {
    return m_accepted.load();
}