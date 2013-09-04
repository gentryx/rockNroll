/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/mrblack.cpp                                         *
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
 *   see /rockNroll/engine/mrblack.h                                       *
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
 *   2005-01-27-13-57-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/

#include <mrblack.h>

bool MrBlack::staticsInited = false;
INT32 MrBlack::posDist[25];

#define REMMOVES_AT_REMAINDIST remMoves[remainDist[0]][remainDist[1]][remainDist[2]][remainDist[3]][remainDist[4]][remainDist[5]]

/**
 *
 * remainDist[i] = 0 means that stone i is not on the board anymore.
 * remainDist[i] = j > 0 means that stone i needs j moves to the goal.
 * 
 * will produce wrong results, when remainDist[i] == 0 for all i, so don't use it for that!
 *
 */
RTYPE
MrBlack::calcRating(INT32 remainDist[STONES]) {
    for (int i = 0; i < STONES; i++) {
        if (remainDist[i] >= GETMAXIMUM(SIZEX, SIZEY)) {
            std::cout << "calcRating overflow!\n";
        }
        if (remainDist[i] < 0) {
            std::cout << "calcRating underflow!\n";
        }
    }

    RTYPE tempRem = REMMOVES_AT_REMAINDIST;
    if (tempRem != 0.) {
        return tempRem;
    }
         
    RTYPE rem = 0.; 
    RTYPE last = 1000.;
    RTYPE p = 0.;

    for (int i = 0; i < STONES; i++) {        
        if (remainDist[i] == 0) {            
            p += probs[i];
        } else {
            RTYPE tRating;
            if (remainDist[i] == 1) {
                tRating = 0.;
            } else {
                INT32 tempRemainDist[STONES];
                for (int j = 0; j < STONES; j++) {
                    tempRemainDist[j] = remainDist[j];
                }
                tempRemainDist[i]--; 
                tRating = calcRating(tempRemainDist);      
            }
            rem += p * GETMINIMUM(last, tRating) + probs[i] * tRating;
            p = 0.;
            last = tRating;
            
        }
    }

    rem += p * last;
    rem += 1;

    REMMOVES_AT_REMAINDIST = rem;
    return rem;
}

void
MrBlack::calcRatingEnumerator(INT32 index, INT32 remainDist[STONES]) {
    if (index == STONES) {
        REMMOVES_AT_REMAINDIST = calcRating(remainDist);
    } else {
        for (int i = 0; i < GETMAXIMUM(SIZEX, SIZEY); i++) {
            remainDist[index] = i;
            calcRatingEnumerator(index + 1, remainDist);
        }
    }
}

void
MrBlack::flushRemMoves(INT32 index, INT32 remainDist[STONES]) {
    if (index == STONES) {
        REMMOVES_AT_REMAINDIST = 0.;
    } else {
        for (int i = 0; i < GETMAXIMUM(SIZEX, SIZEY); i++) {
            remainDist[index] = i;
            flushRemMoves(index + 1, remainDist);
        }
    }
}



void
MrBlack::initRemMoves() {
    int zeros1[STONES] = {0, 0, 0, 0, 0, 0};
    int zeros2[STONES] = {0, 0, 0, 0, 0, 0};
    flushRemMoves(0, zeros1);
    calcRatingEnumerator(0, zeros2);

    if (!staticsInited) {
        for (int i = 0; i < SIZEY; i++) {
            for (int j = 0; j < SIZEX; j++) {
                INT32 xDist = SIZEX - j - 1;
                INT32 yDist = SIZEY - i - 1;
                posDist[i * SIZEX + j] = GETMAXIMUM(xDist, yDist);
            }
        }
        staticsInited = true;
    }
}


INLINEFUNCS
INT8
MrBlack::pos2dist(INT8 pos) {
    if (pos == OFF_BOARD) {
        return 0;
    } else {
        return posDist[(INT32)pos]; 
    }
}


MrBlack::MrBlack(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, PROBTYPE _probs[STONES]) : AIPlayer(_maxDepth, hashSizeHi, hashSizeLo, _probs) {
    initRemMoves();
}


RTYPE
MrBlack::rateBoard(Board *s) {
    INT32 i;
    INT32 j;
    INT32 k;
    INT32 l;
    INT32 m;
    INT32 n;

    i = pos2dist(s->getPosRed()[0]);
    j = pos2dist(s->getPosRed()[1]);
    k = pos2dist(s->getPosRed()[2]);
    l = pos2dist(s->getPosRed()[3]);
    m = pos2dist(s->getPosRed()[4]);
    n = pos2dist(s->getPosRed()[5]);

    RTYPE bias = remMoves[i][j][k][l][m][n];

    i = pos2dist(s->getPosBlu()[0]);
    j = pos2dist(s->getPosBlu()[1]);
    k = pos2dist(s->getPosBlu()[2]);
    l = pos2dist(s->getPosBlu()[3]);
    m = pos2dist(s->getPosBlu()[4]);
    n = pos2dist(s->getPosBlu()[5]);

    bias = bias - remMoves[i][j][k][l][m][n];
    return (bias) * 30.;
}

