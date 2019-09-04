#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/gcc/include/sys/features.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_color.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
#include "vex.h"
#include <algorithm>
#include <vector>
using namespace vex;
using namespace std;

class Mino
{
  public:
    Mino()
    {
      x = 0;
      y = 0;
      width = sclFactor;
      height = sclFactor;
      col = purple;
    }

    Mino(int x_, int y_, color c, int width_ = sclFactor, int height_ = sclFactor) 
    {
      x= x_;
      y = y_;
      width = width_;
      height = height_;
      col = c;
    }

    void displayMino()
    {
      Brain.Screen.setPenColor(color::white);
      Brain.Screen.drawRectangle(x, y, width, height, col);
    }

    void clearMino()
    {
      Brain.Screen.setPenColor(color::white);
      Brain.Screen.drawRectangle(x, y, width, height, color::black);
    }

    void minoFall()
    {
      clearMino();
      y+=sclFactor;
      displayMino();
    }

    void rotate(bool dir, int curX, int curY)
    {
      clearMino();
      if(dir) {
        x = y-curY+curX;
        y = -(x-curX)+curY;
      } else {
        x = -(y-curY)+curX;
        y = x-curY+curX;
      }
      displayMino();
    }

    bool testOverlap(int x_, int y_)
    {
      return (x_ > 10*sclFactor || x_ < 180 || y_ < 0);
    }

    bool testRotate(bool dir, int curX, int curY)
    {
      int newX;
      int newY;
      if(dir) {
        newX = y-curY+curX;
        newY = -(x-curX)+curY;
      } else {
        newX = -(y-curY)+curX;
        newY = x-curY+curX;
      }

      return testOverlap(newX, newY);
    }

    int getX() {return x;}
    int getY() {return y;}

    void setX(int x_) 
    {
      clearMino(); 
      x=x_;
      displayMino();
    }
    void setY(int y_) 
    {
      clearMino();
      y=y_;
      displayMino();
    }

  private:
    int x;
    int y;
    int width;
    int height;
    color col;
};

class Tetrimino
{
  public:
    Tetrimino(Mino minos_[])
    {
      for(int i = 0; i < 4; i++) {
        minos[i] = minos_[i];
      }
    }

    void spawn(int xPos, int yPos)
    {
      x = xPos;
      y = yPos;
      for(Mino m : minos) {
        m.setX(m.getX()+xPos);
        m.setY(m.getY()+yPos);
      }
    }

    void displayBlock()
    {
      for(Mino m : minos) {
        m.displayMino();
      }
    }

    bool blockFall(bool dir)
    {
      if(!solid) {
        // test
        for(Mino m : minos) {
          if (m.testOverlap(m.getX(), m.getY()-sclFactor)) solidify(); return false;
        }
        // do
        for(Mino m : minos) 
          m.minoFall();
      }
      return true;
    }

    void rotateBlock(bool dir)
    {
      if(!solid) {
        // test
        for(Mino m : minos) {
          if (m.testRotate(dir, x, y)) return;
        }
        // do
        for(Mino m : minos) {
          m.rotate(dir, x, y);
        }
      }
    }

    vector<Mino> getBlocks()
    {
      vector<Mino> mins;
      for(int i = 0; i<4; i++) mins.push_back(minos[i]);
      return mins;
    }

  private:
    Mino minos[4];
    int x = 0;
    int y = 0;
    bool solid = false;

    void solidify()
    {
      solid = true;
    }
};