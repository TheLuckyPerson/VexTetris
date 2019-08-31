#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/gcc/include/sys/features.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_color.h"
#include "C:/Program Files (x86)/VEX Robotics/VEXcode/sdk/vexv5/include/vex_global.h"
#include "vex.h"
using namespace vex;
using namespace std;

class Mino
{
  public:
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

  private:
    int x;
    int y;
    int width;
    int height;
    color col;
};

#include "vex.h"

extern vector<vector<Mino>> tetriminos;
extern vector<Mino> tTetrimino;

void makeTetrimino()
{
  //T block - purple
  tTetrimino.push_back(Mino(0, 0, purple));
  tTetrimino.push_back(Mino(sclFactor, 0, purple));
  tTetrimino.push_back(Mino(-sclFactor, 0, purple));
  tTetrimino.push_back(Mino(0, sclFactor, purple));
}