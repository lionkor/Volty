#ifndef EVENT_H
#define EVENT_H

#include "Core/Object.h"
#include <boost/atomic.hpp>

class Event : public Object {
    OBJNAME(Event)

private:
    boost::atomic<bool> m_accepted { false };

public:
    Event();

    void accept();
    bool accepted() const;

    // Object interface
public:
    virtual std::stringstream to_stream() const override;
};

#endif // EVENT_H
