/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/mersenne.h                                           *
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
 *   The famous Mersenne Twister delivers fast and reliable pseudo random  *
 *   numbers. It's written by Takuji Nishimura and Makoto Matsumoto. See   *
 *   /rockNroll/engine/mersenne.cpp for details.                           *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef MERSENNE_H
#define MERSENNE_H

class RandGen {
 public:
    RandGen(PROBTYPE _probs[STONES] = 0);
    virtual ~RandGen();

    UINT32 getDiceVal();

    static void initGenRand(UINT32 seed = 0);
    static UINT32 genRandUInt32();

 protected:
    static UINT32 population;

    PROBTYPE probs[STONES];
    UINT32 sumProbs[STONES - 1];
    
};

#endif
