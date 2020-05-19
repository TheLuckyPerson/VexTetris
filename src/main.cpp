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
#include <algorithm>

using namespace vex;
/*
Tetrimino tetriminoPool[7] =
{
  //T piece
  Tetrimino( new Mino[4]
  {
    Mino(0, 0, color::purple),
    Mino(-sclFactor, 0, color::purple),
    Mino(sclFactor, 0, color::purple),
    Mino(0, -sclFactor, color::purple),
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
*/

Mino minoPool[204];
vector<int> bag;


bool aWasPressed = false;
bool bWasPressed = false;
bool leftWasPressed = false;
bool rightWasPressed = false;

void createMinoPool()
{
  for(int i = 0; i < 204; i++) {
    minoPool[i] = (Mino(0, 0, color::purple));
  }
}

int constructMinoFromPool(int x, int y, color c)
{
  int index = -1;
  for(int i = 0; i < 204; i++) {
    if(!minoPool[i].getUse()) {
      index = i;
      //printf("USED INDEX: %i\n", i);
      break;
    }
  }
  minoPool[index].reset(x, y, c);
  return index;
}

Tetrimino createTPiece(
  int x1 = 0, int y1 = 0, 
  int x2 = -sclFactor, int y2 = 0, 
  int x3 = sclFactor, int y3 = 0, 
  int x4 = 0, int y4 = -sclFactor, 
  color c = color::purple)
{
  Mino * temp[4] = {
    &minoPool[constructMinoFromPool(x1, y1, c)],
    &minoPool[constructMinoFromPool(x2, y2, c)],
    &minoPool[constructMinoFromPool(x3, y3, c)],
    &minoPool[constructMinoFromPool(x4, y4, c)],
  };

  return Tetrimino(temp);
}
void remakeBag()
{
  for(int i = 0; i < 7; i++)
  {
    bag.push_back(i);
  }
}

void removeFromBag(int index)
{
  vector<int> newBag;
  for(int i = 0; i < bag.size(); i++) {
    if(bag[i]!=index) newBag.push_back(bag[i]);
  }
  bag = newBag;
}

Tetrimino generatePiece()
{
  srand(Brain.Battery.voltage(voltageUnits::mV) + Brain.timer(timeUnits::msec));
  if(bag.size() <= 0) remakeBag();
  int random = rand() % bag.size();
  int pieceNum = bag.at(random);
  removeFromBag(pieceNum);
  printf("bag size: %i\n", bag.size());
  //random = 6;
  switch (pieceNum) {
    case 0:
      return createTPiece();
      break;
    case 1:
      return createTPiece(sclFactor, sclFactor, 0, sclFactor, sclFactor, 0,
      0, 0, color::yellow);
      break;
    case 2:
      return createTPiece(0, 0, sclFactor, 0, -sclFactor, 0,
      -sclFactor*2, 0, color(100, 100, 255));
      break;
    case 3:
      return createTPiece(0, 0, -sclFactor, 0, sclFactor, 0,
      sclFactor, -sclFactor, color::orange);
      break;
    case 4:
      return createTPiece(0, 0, -sclFactor, 0, sclFactor, 0,
      -sclFactor, -sclFactor, color::blue);
      break;
    case 5:
      return createTPiece(0, 0, sclFactor, 0, -sclFactor, -sclFactor,
      0, -sclFactor, color::red);
      break;
    case 6:
      return createTPiece(0, 0, -sclFactor, 0, sclFactor, -sclFactor,
      0, -sclFactor, color::green);
      break;
    default:
      return createTPiece();
      break;
  } 
}

Tetrimino mainPiece = Tetrimino();

void displayTetrisBg() //480 by 242
{ //10 by 20 board
  if(Brain.SDcard.isInserted()) Brain.Screen.drawImageFromFile("tetris.png", 80, 30);
  for(int x = 0; x < 10*sclFactor; x+=sclFactor) {
    for(int y = 0; y < 20*sclFactor; y+=sclFactor) {
      Brain.Screen.setPenColor(color::white);
      Brain.Screen.drawRectangle(x+180, y, sclFactor, sclFactor, color::black);
    }
  }
}

int baseFramesToFall = 40;
int framesToFall = 40;

int currentFrames = 0;
int gameUpdate()
{
  if(mainPiece.getSolid()) {
    mainPiece = generatePiece();
    //mainPiece.spawn(240, 0);
  }
  if(currentFrames > framesToFall) {
    currentFrames = 0;;
    mainPiece.blockFall();
  } else {
    currentFrames++;
  }
  return 0;
}

int controllerUpdate()
{
  while(10) 
  {
    if(Controller.ButtonA.pressing() && !aWasPressed) {
      aWasPressed = true;
      mainPiece.rotateBlock(true);
    } else if(!Controller.ButtonA.pressing()) aWasPressed = false;
    if(Controller.ButtonB.pressing() && !bWasPressed) {
      bWasPressed = true;
      mainPiece.rotateBlock(false);
    } else if(!Controller.ButtonB.pressing()) bWasPressed = false;

    if(Controller.ButtonLeft.pressing() && !leftWasPressed) {
      leftWasPressed = true;
      mainPiece.move(false);
    } else if(!Controller.ButtonLeft.pressing()) leftWasPressed = false;
    if(Controller.ButtonRight.pressing() && !rightWasPressed) {
      rightWasPressed = true;
      mainPiece.move(true);
    } else if(!Controller.ButtonRight.pressing()) rightWasPressed = false;

    if(Controller.ButtonDown.pressing()) {
      framesToFall = 1;
    } else if(!Controller.ButtonDown.pressing()) framesToFall = baseFramesToFall;

    if(Controller.ButtonR1.pressing()) {
      framesToFall = 100000000;
    }
    task::sleep(20);
  }
  return 0;
}

int main() {
  displayTetrisBg();
  createMinoPool();
  //mainPiece.BlockPrint();
  task k(controllerUpdate);  
  while(true) {
    gameUpdate();
    task::sleep(20);
  }
}
