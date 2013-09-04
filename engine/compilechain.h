/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/compilechain.h                                      *
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
 *   For performance reasons the engine should be compiled alltogether     *
 *   one single .o file. This file manages the order, in which the header  *
 *   and code files are included.
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 *                                                                         *
 *   Todo List:                                                            *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef COMPILECHAIN_H
#define COMPILECHAIN_H

#include <headers.h> 
//#include <threadwrapper.cpp> 
#include <mersenne.cpp>
#include <hashmap.cpp>
#include <board.cpp>
#include <boardfactory.cpp>
#include <player.cpp>
#include <stdinplayer.cpp>
#include <aiplayer.cpp>
#include <mrrandom.cpp>
#include <mrmonte.cpp>
#include <mrblack.cpp>
#include <farmerboy.cpp>
#include <referee.cpp>

#endif
