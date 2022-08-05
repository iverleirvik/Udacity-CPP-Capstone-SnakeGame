#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "running.h"
#include <mutex>
#include <memory>
//#include "game.h"

class Controller {
 public:
  void HandleInput(std::shared_ptr<Running> &running/*Running &running*/, Snake &snake) const;

  // bool getRunning();
  // void setRunning(bool variable);

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

  //std::shared_ptr<bool> _running{ new bool };
  //std::mutex _mutex;
};

#endif