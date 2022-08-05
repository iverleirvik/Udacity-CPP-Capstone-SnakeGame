#include "running.h"

bool Running::getRunning() {
    std::lock_guard<std::mutex> uLock(_mutex);

    return _running;
    
}

void Running::setRunning(int variable) {
  	std::lock_guard<std::mutex> uLock(_mutex);
  
    _running = variable;
}
/*
Running::Running(int variable) {
    _running = variable;
}
*/
