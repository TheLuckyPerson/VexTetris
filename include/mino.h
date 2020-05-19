#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_triport.h"
#include "vex.h"
#include <vector>
using namespace vex;
using namespace std;

bool testBlockOverlap(int x_, int y_);
void startClear();
void displayAll();
//vector<vector<int>> placedMinos;


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
      inUse = false;
    }

    Mino(int x_, int y_, color c, int width_ = sclFactor, int height_ = sclFactor) 
    {
      x= x_;
      y = y_;
      width = width_;
      height = height_;
      col = c;
      inUse = false;
    }

    void displayMino()
    {
      Brain.Screen.setPenColor(color::white);
      Brain.Screen.setFillColor(col);
      Brain.Screen.drawRectangle(x, y, width, height, col);
    }

    void clearMino()
    {
      Brain.Screen.setPenColor(color::white);
      if(!testOverlap(x, y, false))
        Brain.Screen.drawRectangle(x, y, width, height, color::black);
      ///*
      else {
        Brain.Screen.setFillColor(color::black);
        Brain.Screen.setPenColor(color::black);
        Brain.Screen.drawRectangle(x, y, width, height, color::black);
      }//*/
    }

    void unuseMino()
    {
      inUse = false;
      clearMino();
    }

    void useMino()
    {
      inUse = true;
    }

    void minoFall()
    {
      y=y+sclFactor;
    }

    bool getUse()
    {
      return inUse;
    }

    void rotate(bool dir, int curX, int curY)
    {
      if(dir && col != color::yellow) {
        int temp = x;
        x = -(y-curY)+curX;
        y = temp-curX+curY;
      } else if(col!=color::yellow){
        int temp = x;
        x = (y-curY)+curX;
        y = -(temp-curX)+curY;
      }
    }

    friend bool testBlockOverlap(int x_, int y_);

    /**
      @return true if overlap with something that should not overlap 
    */
    bool testOverlap(int x_, int y_, bool b = true)
    {
      return (x_ < 180 || x_ > 180+9*sclFactor || y_ > 240-sclFactor) || (b && testBlockOverlap(x_, y_));
    }

    bool testRotate(bool dir, int curX, int curY)
    {
      int newX;
      int newY;
      if(dir) {
        newX = -(y-curY)+curX;
        newY = x-curX+curY;
      } else {
        newX = y-curY+curX;
        newY = -(x-curY)+curX;
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

    bool testMoveMino(bool dir)
    {
      return testOverlap(dir ? x+sclFactor : x-sclFactor, y);
    }

    void moveMino(bool dir)
    {
      setX(dir ? x+sclFactor : x-sclFactor);
    }

    void setColor(color c)
    {
      col = c;
    }

    void positionPrint()
    {
      printf("x: %i   y: %i\n", x, y);
    }

    void reset(int x_, int y_, color c)
    {
      inUse = true;
      setX(x_);
      setY(y_);
      setColor(c);
    }

  private:
    int x;
    int y;
    int width;
    int height;
    color col;
    bool inUse;
};

void solidify(Mino *m);

class Tetrimino
{
  public:
    Tetrimino()
    {
      solid = true;
    }

    Tetrimino(Mino * minos_[4])
    {
      for(int i = 0; i < 4; i++) {
        minos[i] = minos_[i];
      }
      x = 0;
      y = 0;
      solid = false;
      spawn(240, 0);
    }

    void spawn(int xPos, int yPos)
    {      
      x = xPos;
      y = yPos;
      for(int i = 0; i < 4; i++) {
        minos[i]->setX(minos[i]->getX()+xPos);
        minos[i]->setY(minos[i]->getY()+yPos);
      }
    }

    void displayBlock()
    {
      for(int i = 0; i < 4; i++) {
        minos[i]->displayMino();
      }
    }

    void clearBlock()
    {
      for(int i = 0; i < 4; i++) {
        minos[i]->clearMino();
      }
    }

    bool blockFall()
    {
      if(!solid) {
        // test
        for(int i = 0; i < 4; i++) {
          if (minos[i]->testOverlap(minos[i]->getX(), minos[i]->getY()+sclFactor)) {
            solidifyBlock(); 
            return false;
          }
        }

        clearBlock();
        // do
        if(!solid) {
          for(int i = 0; i < 4; i++) {
            minos[i]->minoFall();
          }
          y += sclFactor;
        }
        displayBlock();
        displayAll();
      }
      return true;
    }

    void rotateBlock(bool dir)
    {
      if(!solid) {
        // test
        for(int i = 0; i < 4; i++) {
          if (minos[i]->testRotate(dir, x, y)) return;
        }
        // do
        clearBlock();
        for(int i = 0; i < 4; i++) {
          minos[i]->rotate(dir, x, y);
        }
        displayBlock();
      }
    }

    void move(bool dir)
    {
      if(!solid) {
        // test
        for(int i = 0; i < 4; i++) {
          if (minos[i]->testMoveMino(dir)) return;
        }
        // do
        x += dir ? sclFactor : -sclFactor;
        clearBlock();
        for(int i = 0; i < 4; i++) {
          minos[i]->moveMino(dir);
        }
        displayBlock();
      }
    }

    Mino** getBlocks()
    {
      return minos;
    }

    bool getSolid()
    {
      return solid;
    }

    void BlockPrint()
    {
      for(int i = 0; i < 4; i++) {
        minos[i]->positionPrint();
      }
    }

  private:
    Mino * minos[4];
    int x = 0;
    int y = 0;
    bool solid = false;

    void solidifyBlock()
    {
      if(!solid) {
        solid = true;
        for(int i = 0; i < 4; i++) {
          solidify(minos[i]);
        }
        startClear();
        //displayAll();
      }
    }
};


vector<Mino *> placedMinos[20];

bool empty = true;

void displayAll()
{
  for(int i = 0; i < 20; i++) {
    for(int j = 0; j < placedMinos[i].size(); j++) {
      placedMinos[i][j]->displayMino();
    }
  }
}

void printAll()
{
  for(int i = 0; i < 20; i++) {
    for(int j = 0; j < placedMinos[i].size(); j++) {
      placedMinos[i][j]->positionPrint();
      placedMinos[i][j]->displayMino();
    }
  }
}

void clearMinoLine(int linePosition)
{  
  //set all in line to unused
  for(int i = 0; i < 10; i++) {
    placedMinos[linePosition][i]->unuseMino();
    placedMinos[linePosition][i]->setX(-sclFactor);
    placedMinos[linePosition][i]->setY(-sclFactor);
  }
  placedMinos[linePosition] = vector<Mino*>();
  // move above down
  for(int i = linePosition; i > 0; i--) { // line where minos are
    for(int j = 0; j < placedMinos[i].size(); j++) { // minos in line
      placedMinos[i][j]->setY(placedMinos[i][j]->getY()+sclFactor);
      //placedMinos[i][j]->
      /*printf("new Y: %i\n", placedMinos[i][j]->getY());
      printf("new X: %i\n", placedMinos[i][j]->getX());*/
    }
    placedMinos[i] = placedMinos[i-1];
    //placedMinos[i] = placedMinos[i-1];
  }

  printAll();
}

void startClear()
{
  for(int i = 0; i < 20; i++) {
    if(placedMinos[i].size() == 10) {
      clearMinoLine(i);
    }
  }
}

bool testBlockOverlap(int x_, int y_)
{
  if(empty) {
    return false;
  }
  for(int i = 0; i < 20; i++)
  {
    for(int j = 0; j < placedMinos[i].size(); j++)
    {
      if(placedMinos[i].at(j)->getX() == x_ && placedMinos[i].at(j)->getY() == y_) {
        return true;
      }
    }
  }
  return false;
}

void solidify(Mino* m)
{
  empty = false;
  int linePosition = m->getY()/sclFactor;
  printf("Lin: %i, Pos: %i\n", linePosition, m->getY());
  placedMinos[linePosition].push_back(m);
}