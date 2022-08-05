#include "snakelist.h"

#include <mutex>
#include <memory>


void Snakelist::addSnake(Snake &snake) {
    std::lock_guard<std::mutex> uLock(_mutex);
    _snakes.push_back(snake);
}

void Snakelist::clearAll() {
    std::lock_guard<std::mutex> uLock(_mutex);
    _snakes.clear();
}

Snake Snakelist::getSnakeByIndex(int index) const{
    std::lock_guard<std::mutex> uLock(_mutex);
    return _snakes[index];
}

int Snakelist::getNumberOfElements() {
    std::lock_guard<std::mutex> uLock(_mutex);
    return _snakes.size();
}