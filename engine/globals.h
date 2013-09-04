/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/globals.h                                           *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                         *
 *                                                                         *
 *   Description:                                                          *
 *                                                                         *
 *   Here we define essential constants used in the rockNroll engine.      *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 *                                                                         *
 *   Todo List:                                                            *
 *                                                                         *
 *   remove outcommented sections                                          *
 *                                                                         *
 *                                                                         *
 *   Change Log:                                                           *
 *                                                                         *
 *   2005-01-27-09-17-00 (by gentryx)                                      *
 *     * introduced maxpopulation constant                                 *
 *                                                                         *
 *   2005-01-26-19-39-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/


#ifndef GLOBALS_H
#define GLOBALS_H

//INCLUDES:
#include <string>

//TYPE DEFS:
#define RTYPE    float
#define PROBTYPE double
#define INT8     signed char
#define UINT8    unsigned char
#define INT32    signed int
#define UINT32   unsigned int
#define INT64    signed long long
#define UINT64   unsigned long long
typedef std::string string;

//FUNCTION DEFS:
//#define RANDFUNC genrand_int31
//#define RANDFUNC32 genrand_int32
#define DEBUGOUT(message) //std::cout << message
//#define INLINEFUNCS inline
#define INLINEFUNCS
#define GETMAXIMUM(a, b) (a > b? a : b)
#define GETMINIMUM(a, b) (a < b? a : b)

//CONST DEFS:
#define MAXPOPULATION 128
#define WIN_VAL 1000
#define LOS_VAL -WIN_VAL
#define INFTY 2000
#define MINUS_INFTY -INFTY
#define PLAYERS 2
#define STONES 6 
#define SIZEX 5
#define SIZEY 5
#define OFF_BOARD -1
#define EAST 1
#define SOUTH SIZEY
#define SOUTH_EAST EAST+SOUTH
#define GOAL SIZEX*SIZEY - 1

#endif
