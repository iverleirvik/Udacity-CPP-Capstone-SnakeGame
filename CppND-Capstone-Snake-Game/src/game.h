#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>
#include <memory>
#include <thread>
#include <future>
#include <algorithm>
#include <iostream>
#include <vector>
#include "controller.h"
#include "SDL.h"
#include "renderer.h"
#include "snake.h"
#include "snakelist.h"
#include "running.h"
#include "messagequeue.h"
#include <string>
//#include

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
  void threadRun(Snake &&i);
  std::shared_ptr<MessageQueue<int>> messagequeue{ new MessageQueue<int> };
  /*
  bool getRunning() const;
  void setRunning(bool variable);*/

 private:
  Snake snake;
  Snakelist snakelist;
  SDL_Point food;
  //MessageQueue<std::string> messagequeue;
  //std::shared_ptr<MessageQueue<int>> messagequeue{ new MessageQueue<int> };

  //Running running;
  std::shared_ptr<Running> running{ new Running };

  // MessageQueue<std::string> messagequeue;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;


  /*
  std::shared_ptr<bool> _running{ new bool };
  std::mutex _mutex;*/

  int score{0};

  void PlaceFood();
  void Update();
};

#endif