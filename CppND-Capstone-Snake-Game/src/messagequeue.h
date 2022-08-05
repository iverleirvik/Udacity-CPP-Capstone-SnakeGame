#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include <iostream>
#include <thread>
#include <queue>
#include <future>
#include <mutex>
#include <algorithm>

template <class T>
class MessageQueue {
    public:
        T receive();
        void send(T &&msg);

    private:
        std::mutex _mutex;
        std::condition_variable _cond;
        std::deque<T> _messages;
};

#endif

