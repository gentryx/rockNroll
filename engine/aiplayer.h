/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/aiplayer.h                                          *
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
 *   AIPlayer is the central class for game tree searching. It contains    *
 *   the therefore used expect-min-max algorithm. To use it for your own   *
 *   player, you have to extend it with a heuristic (rateBoard()), which   *
 *   is used for the leaf-rating.                                          *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/


#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <hashmap.h>

class AIPlayer : public Player {
 protected:
    static UINT32 population;

    INT32 maxDepth;
    HashMap *hashHi;
    HashMap *hashLo;
    UINT8 stepping;

    INLINEFUNCS RTYPE _rateBoard(Board *s, INT32 remainingDepth);
 public:
    static INLINEFUNCS ID_TYPE board2id(Board *s);

 public:
    AIPlayer(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, PROBTYPE _probs[STONES]);
    virtual ~AIPlayer();

    INLINEFUNCS void setMaxDepth(INT32 _maxDepth);
    INLINEFUNCS Board *getNextMove(Board *s, INT32 dice);
    INLINEFUNCS Board *getNextMove(Board *s, INT32 dice, INT32 depth);
    virtual RTYPE rateBoard(Board *s) =0;

    friend class AIPlayerTestSuite;
};

#endif
