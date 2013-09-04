/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/mrmonte.cpp                                         *
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
 *   see /rockNroll/engine/mrmonte.h                                       *
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
 *                                                                         *
 *   Change Log:                                                           *
 *                                                                         *
 *   2005-01-27-14-28-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/


#include <mrmonte.h>
#include <globals.h>
#include <referee.h>

MrMonte::MrMonte(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, INT32 _iterations, Player *_red, Player *_blu, PROBTYPE _probs[STONES]) : AIPlayer(_maxDepth, hashSizeHi, hashSizeLo, _probs) {
    iterations = _iterations;
    red = _red;
    blu = _blu;
}


RTYPE
MrMonte::rateBoard(Board *s) {
    DEBUGOUT("MrMonte::rateBoard()\n");

    RTYPE res = (Referee::multiRun(red, blu, iterations, s, probs) - iterations / 2) * (1.) / (iterations / 2.);

    return -res;
}

