#ifndef MUTEXED_H
#define MUTEXED_H

#include <mutex>

// TODO: rewrite with pairs of T& and unique_lock or shared_lock

template<class T>
class Mutexed {
private:
    std::mutex m_mutex;
    T m_value;

public:
    explicit Mutexed(T&& value)
        : m_value(std::move(value)) { }

    ~Mutexed() {
        m_mutex.unlock();
    }

    void lock() {
        m_mutex.lock();
    }

    bool try_lock() {
        return m_mutex.try_lock();
    }

    void unlock() {
        m_mutex.unlock();
    }

    std::mutex& mutex() { return m_mutex; }

    T& value() { return m_value; }
};

#endif // MUTEXED_H
