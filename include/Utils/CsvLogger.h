#ifndef CSVLOGGER_H
#define CSVLOGGER_H

#include "Common.h"
#include "DebugTools.h"
#include <atomic>
#include <fstream>
#include <mutex>
#include <queue>
#include <thread>

namespace V {

class CsvLogger {
private:
    std::string m_filename;
    std::ofstream m_os;
    std::queue<std::string> m_queue;
    std::thread m_thread;
    bool m_kill_thread { false };
    std::mutex m_mutex;

public:
    explicit CsvLogger(const std::string& filename);
    ~CsvLogger();

    bool ok() const { return m_os.is_open(); }
    const std::string& filename() const { return m_filename; }

    template<typename T>
    void log(const T& value) {
        std::scoped_lock lock(m_mutex);
        m_queue.emplace(fmt::format("{}\n", value));
    }
};

}

#endif // CSVLOGGER_H
