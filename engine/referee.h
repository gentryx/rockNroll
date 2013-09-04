/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/referee.h                                           *
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
 *   Referee supervises one or many games of one Player versus another.    *
 *   It returns a simple statistic.                                        *
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
 *   2005-01-27-13-15-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef REFEREE_H
#define REFEREE_H

class Referee {
 private:
    //returns true iff player0 - original red - has won
    static INLINEFUNCS bool run(RandGen *randGen, Player *red, Player *blu, Board *s);
 public:
    static INLINEFUNCS INT32 multiRun(Player *red, Player *blu, INT32 num,           PROBTYPE _probs[STONES] = 0);
    static INLINEFUNCS INT32 multiRun(Player *red, Player *blu, INT32 num, Board *s, PROBTYPE _probs[STONES] = 0);
};

#endif
