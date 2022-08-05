#ifndef RUNNING_H
#define RUNNING_H

#include <mutex>
#include <memory>

class Running {
    public:
        //Running(int variable);
        bool getRunning();
        void setRunning(int variable);

    private:
        bool _running{false};
        std::mutex _mutex;

};

#endif