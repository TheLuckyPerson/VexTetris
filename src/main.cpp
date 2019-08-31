/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Tyler.Le21                                       */
/*    Created:      Tue Aug 27 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "mino.h"
#include "vector"

using namespace vex;

void displayTetrisBg() //480 by 242
{ //10 by 20 board
  for(int x = 0; x < 10*sclFactor; x+=sclFactor) {
    for(int y = 0; y < 20*sclFactor; y+=sclFactor) {
      Brain.Screen.setPenColor(color::white);
      Brain.Screen.drawRectangle(x+180, y, sclFactor, sclFactor, color::black);
    }
  }
}

int gameUpdate()
{
  while(9)
  {
    task::sleep(800);
    //test.minoFall();
  }
}

int controllerUpdate()
{
  while(10) 
  {
    task::sleep(20);
  }
}

int main() {
    //test.setColor(purple);
    displayTetrisBg();
    //test.displayMino();
    task t(gameUpdate);
    task k(controllerUpdate);  
  }
