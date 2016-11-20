#pragma once

#include <mutex>
#include <thread>
#include <unordered_map>

namespace util
{

/*
 * Returns normalized thread ids. Each thread gets his own
 * thread id starting from 0.
 */
template <class Lock = std::mutex>
class ThreadId
{
public:
    /*
     * Singleton because normalized thread ids are
     * the global across execution
     */
    static ThreadId& instance()
    {
        static ThreadId thread_id;
        return thread_id;
    }

    /*
     * The return value can be used as a thread id or index that
     * represents the thread.
     *
     * returns: normalized thread id (every thread id is integer
     * from 0 to some upper number); thread ids are incremented by
     * FCFS rule;
     */
    auto get_id()
    {
        // get current thread id
        auto thread_id = hasher(std::this_thread::get_id());  

        // hold all threads because unordered_map has to be updated
        std::lock_guard<Lock> hold(lock);

        if (ids.find(thread_id) == ids.end())
            ids[thread_id] = counter++;

        return ids[thread_id];
    }
    
private:
    int counter{0};
    std::hash<std::thread::id> hasher;
    // TODO: use more appropriate lock
    //       OR
    //       use concurrent data structure
    std::unordered_map<int, int> ids;
    Lock lock;
};

}
