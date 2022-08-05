#include "game.h"
#include <iostream>
#include <random>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  //bool running = true;
  running->setRunning(true);
  //controller.setRunning(true);
  snake.mainSnake = true;

  
  std::vector<std::future<void>> threads;
  for (int i = 0; i < 2; i++) {
    Snake s(i);
    threads.emplace_back(std::async(std::launch::async, &Game::threadRun, this, std::move(s)));
  }
  
  

  while (running->getRunning()) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    //TODO: Håndtere handleinput for threads
    Update(); //TODO: ta hensyn til threads i update
    snakelist.addSnake(snake);
    renderer.Render(snakelist, food); //TODO: Håndtere flere slanger.

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
    // TODO: MessageQueue::send(); send to all threads that they are allowed another tick.
    messagequeue->send(1);


    snakelist.clearAll();
  }
  
  
  std::for_each(threads.begin(), threads.end(), [](std::future<void> &ftr) {
        ftr.wait();
  });
  
  
}

void Game::PlaceFood() {  //TODO:
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update() { //TODO:

  for(auto i = 0; i <snakelist.getNumberOfElements(); i++) {
    if(snakelist.getSnakeByIndex(i).mainSnake == false) {
      for (auto const &item: snakelist.getSnakeByIndex(i).body) {
        if((snake.head_x == item.x && snake.head_y == item.y) || (snake.head_x == snakelist.getSnakeByIndex(i).head_x && snake.head_y == snakelist.getSnakeByIndex(i).head_y)) {
          snake.alive = false;
        }
      }
    }
  }

  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }

void Game::threadRun(Snake &&i) {
  
  int chronologicalCounter = 0;
  while(running->getRunning()) {
    
    if (chronologicalCounter == 0) {
    
    // random controller input
    std::default_random_engine generatorDirection;
    std::default_random_engine generatorChronological;
    std::uniform_int_distribution<int> distributionDirection(1,4);
    std::uniform_int_distribution<int> distributionChronological(1,12);
    int direction = distributionDirection(generatorDirection);  // generates number in the range 1..6
    int chronological = distributionChronological(generatorChronological);

    chronologicalCounter = chronological;
    
    switch(direction) {
      case 1:
        if (i.direction != Snake::Direction::kUp) i.direction = Snake::Direction::kUp;
        break;
      case 2:
        if (i.direction != Snake::Direction::kDown) i.direction = Snake::Direction::kDown;
        break;
      case 3:
        if (i.direction != Snake::Direction::kLeft) i.direction = Snake::Direction::kLeft;
        break;
      case 4:
        if (i.direction != Snake::Direction::kRight) i.direction = Snake::Direction::kRight;
        break;
    }
  }
  chronologicalCounter--;
    // update
  i.Update();
  snakelist.addSnake(i);
    // render

    // Send message to main thread about enemy snakes position.

    // Communicate with main thread about ticks pr minute
    int melding = messagequeue->receive();

  }
}
