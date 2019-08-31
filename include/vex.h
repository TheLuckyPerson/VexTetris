/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       vex.h                                                     */
/*    Author:       Vex Robotics                                              */
/*    Created:      1 Feb 2019                                                */
/*    Description:  Default header for V5 projects                            */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "v5.h"
#include "v5_vcs.h"
#include "vector"

using namespace::std;

#ifndef MY_GLOBALS_H
#define MY_GLOBALS_H

extern vex::brain       Brain;
extern vex::controller Controller;

extern int sclFactor;

extern void makeTetrimino();

#endif