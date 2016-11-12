#pragma once

#include <thread>
#include <unordered_map>

namespace util
{

class ThreadId
{
public:
    static ThreadId& instance()
    {
        static ThreadId thread_id;
        return thread_id;
    }

    size_t get_id()
    {
        auto thread_id = hasher(std::this_thread::get_id());  

        if (ids.find(thread_id) == ids.end())
            ids[thread_id] = counter++;

        return ids[thread_id];
    }
    
private:
    std::hash<std::thread::id> hasher;
    std::unordered_map<size_t, size_t> ids;
    size_t counter{0};
};

}
