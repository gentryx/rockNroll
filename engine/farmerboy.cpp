/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/farmerboy.cpp                                       *
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
 *   see /rockNroll/engine/farmerboy.h                                     *
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
 *   2005-01-27-14-38-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/

#include <farmerboy.h>

FarmerBoy::FarmerBoy(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, PROBTYPE _probs[STONES]) : AIPlayer(_maxDepth, hashSizeHi, hashSizeLo, _probs) {
    fieldRatings = rawFieldRatings + 1;
    setField(-1, 0, 0);

    setField(0, 0, 0);  
    setField(1, 0, 1);
    setField(2, 0, 1);
    setField(3, 0, 1);
    setField(4, 0, 1);

    setField(0, 1, 1);  
    setField(1, 1, 2);
    setField(2, 1, 2);
    setField(3, 1, 2);
    setField(4, 1, 2);

    setField(0, 2, 1);  
    setField(1, 2, 2);
    setField(2, 2, 4);
    setField(3, 2, 4);
    setField(4, 2, 5);

    setField(0, 3, 1);  
    setField(1, 3, 2);
    setField(2, 3, 4);
    setField(3, 3, 8);
    setField(4, 3, 10);

    setField(0, 4, 1);  
    setField(1, 4, 2);
    setField(2, 4, 5);
    setField(3, 4, 10);
    setField(4, 4, 32);
}


void
FarmerBoy::setField(int x, int y, RTYPE rating) {
    fieldRatings[x + SIZEX * y] = rating;
}


RTYPE
FarmerBoy::rateBoard(Board *s) {
    INT8 *posRed = s->getPosRed();
    INT8 *posBlu = s->getPosBlu();
    RTYPE numRed = 0.;
    RTYPE numBlu = 0.;
    INT32 sumRed = 0.;
    INT32 sumBlu = 0.;
    for (int i = 0; i < STONES; i++) {
        sumRed += fieldRatings[posRed[i]];
        sumBlu += fieldRatings[posBlu[i]];
        numBlu += ((s->movesBlu >> 2*i & 3) != 3);
        numRed += ((s->movesRed >> 2*i & 3) != 3);
    }

    RTYPE rating = sumBlu / ((RTYPE)numBlu) - sumRed / ((RTYPE)numRed);
    return rating;
}
