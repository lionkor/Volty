#ifndef EVENT_H
#define EVENT_H

#include "Core/Object.h"
#include <atomic>

class Event : public Object {
    OBJNAME(Event)

private:
    std::atomic<bool> m_accepted { false };

public:
    Event();

    bool operator==(const Event& ev) {
        // TODO: this sucks, make it better
        return &ev == this;
    }

    void accept();
    [[nodiscard]] bool accepted() const;
};

#endif // EVENT_H
