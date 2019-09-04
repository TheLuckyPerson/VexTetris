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
Tetrimino tetriminoPool[7] = 
{
  //T piece
  Tetrimino( new Mino[4]
  {
    Mino(0, 0, color::purple),
    Mino(-sclFactor, 0, color::purple),
    Mino(sclFactor, 0, color::purple),
    Mino(0, sclFactor, color::purple),
  }),

  //I piece
  Tetrimino( new Mino[4]
  {
    Mino(-sclFactor/2, 0, color(50, 50, 255)),
    Mino(sclFactor/2, 0, color(50, 50, 255)),
    Mino(-sclFactor-sclFactor/2, 0, color(50, 50, 255)),
    Mino(sclFactor+sclFactor/2, 0, color(50, 50, 255)),
  }),

  //L Piece
  Tetrimino( new Mino[4] 
  {
    Mino(0, 0, color::orange),
    Mino(-sclFactor, 0, color::orange),
    Mino(sclFactor, 0, color::orange),
    Mino(sclFactor, sclFactor, color::orange),
  }),

  //J Piece
  Tetrimino( new Mino[4] 
  {
    Mino(0, 0, color::blue),
    Mino(sclFactor, 0, color::blue),
    Mino(sclFactor, 0, color::blue),
    Mino(-sclFactor, sclFactor, color::blue),
  }),

  // S Piece
  Tetrimino( new Mino[4] 
  {
    Mino(0, 0, color::green),
    Mino(-sclFactor, 0, color::green),
    Mino(sclFactor, sclFactor, color::green),
    Mino(0, sclFactor, color::green),
  }),

  // Z Piece
  Tetrimino( new Mino[4] 
  {
    Mino(0, 0, color::red),
    Mino(sclFactor, 0, color::red),
    Mino(-sclFactor, -sclFactor, color::red),
    Mino(0, sclFactor, color::red),
  }),

  // O Piece
  Tetrimino( new Mino[4]  
  {
    Mino(sclFactor/2, sclFactor/2, color::yellow),
    Mino(-sclFactor/2, sclFactor/2, color::yellow),
    Mino(-sclFactor/2, -sclFactor/2, color::yellow),
    Mino(sclFactor/2, -sclFactor/2, color::yellow),
  }),
};

Tetrimino mainPiece = tetriminoPool[0];
bool aWasPressed = false;
bool xWasPressed = false;

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
    if(Controller.ButtonA.pressing() && !aWasPressed) {
      aWasPressed = true;
      mainPiece.rotateBlock(true);
    } else if(!Controller.ButtonA.pressing()) aWasPressed = false;
    if(Controller.ButtonX.pressing() && !xWasPressed) {
      xWasPressed = true;
      mainPiece.rotateBlock(false);
    } else if(!Controller.ButtonX.pressing()) xWasPressed = false;
    task::sleep(20);
  }
}

int main() {
    //test.setColor(purple);
    displayTetrisBg();
    mainPiece.spawn(240, 0);
    task t(gameUpdate);
    task k(controllerUpdate);  
  }
