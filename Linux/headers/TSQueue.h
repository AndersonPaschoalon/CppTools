#ifndef __TS_QUEUE_H__
#define __TS_QUEUE_H__ 1


#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdio>    // For remove()
#include <fstream>   // For ifstream
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>


template<typename T>
class TSQueue 
{
    public:
        void push(T const& value) 
        {
            // printf("push lock(m_mutex);\n");
            std::unique_lock<std::mutex> lock(m_mutex);
            // printf("m_queue.push(value);\n");
            m_queue.push(value);
            // printf("lock.unlock();\n");
            lock.unlock();
            // printf("m_cond.notify_one();\n");
            m_cond.notify_one();
        }

        bool empty() const 
        {
            // printf("\n");
            std::unique_lock<std::mutex> lock(m_mutex);
            // printf("\n");
            return m_queue.empty();
        }

        bool try_pop(T& popped_value) 
        {
            // printf("try_pop lock(m_mutex)\n");
            std::unique_lock<std::mutex> lock(m_mutex);
            if (m_queue.empty()) 
            {
                return false;
            }

            // printf("m_queue.front()\n");
            popped_value = m_queue.front();

            // printf("m_queue.pop();\n");
            m_queue.pop();

            return true;
        }

        void wait_and_pop(T& popped_value) 
        {
            std::unique_lock<std::mutex> lock(m_mutex);
            while (m_queue.empty()) 
            {
                m_cond.wait(lock);
            }

            popped_value = m_queue.front();
            m_queue.pop();
        }

    private:
        std::queue<T> m_queue;
        mutable std::mutex m_mutex;
        std::condition_variable m_cond;
};



#endif // __TS_QUEUE_H__