/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/mrblack.h                                           *
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
 *   MrBlack extends the AIPlayer class and implements it's heuristics by  *
 *   by a table lookup. The heuristic was developed by Stefan Schwarz.     *
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
 *   2005-01-27-13-59-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MRBLACK_H
#define MRBLACK_H

#include <globals.h>
#include <aiplayer.h>

class MrBlack : public AIPlayer {    
public:
    MrBlack(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, PROBTYPE _probs[STONES] = 0);
    RTYPE rateBoard(Board *s);

protected:
    static INT32 posDist[SIZEX*SIZEY];
    static bool staticsInited;

    RTYPE remMoves[GETMAXIMUM(SIZEX, SIZEY)][GETMAXIMUM(SIZEX, SIZEY)][GETMAXIMUM(SIZEX, SIZEY)][GETMAXIMUM(SIZEX, SIZEY)][GETMAXIMUM(SIZEX, SIZEY)][GETMAXIMUM(SIZEX, SIZEY)];
    RTYPE calcRating(INT32 remainDist[STONES]);
    void calcRatingEnumerator(INT32 index, INT32 remainDist[STONES]);
    void flushRemMoves(INT32 index, INT32 remainDist[STONES]);
    void initRemMoves();
    
    INLINEFUNCS static INT8 pos2dist(INT8 pos);
};

#endif
