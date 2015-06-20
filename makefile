all:
  g++ -I/usr/include -L/usr/lib/x86_64-linux-gnu -o PROGRAM main.cpp Program.cpp Interface.cpp Segment.cpp Point.cpp Collection.cpp CollisionDetector.cpp InputManager.cpp Utilities.cpp MessageHandler.cpp -std=c++11 -lGL -lglut

