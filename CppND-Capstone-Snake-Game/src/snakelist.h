#ifndef SNAKELIST_H
#define SNAKELIST_H

#include <memory>
#include <mutex>
#include "snake.h"

class Snakelist {
    public:
        void addSnake(Snake &snake);
        void clearAll();
        Snake getSnakeByIndex(int index) const;
        int getNumberOfElements();

    private:
        std::vector<Snake> _snakes;
        mutable std::mutex _mutex;

};

#endif