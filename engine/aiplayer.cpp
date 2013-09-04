/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/aiplayer.cpp                                        *
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
 *   see aiplayer.h                                                        *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/


#include <iostream>

#include <aiplayer.h>
#include <globals.h>


UINT32 AIPlayer::population = 0;

AIPlayer::AIPlayer(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, PROBTYPE _probs[STONES]) : Player(_probs){
    population++;
    if (population > MAXPOPULATION) {
        std::cout << "AIPlayer exceeded MAXPOPULATION!\n";
    }

    stepping = 1;
    setMaxDepth(_maxDepth);

    if (hashSizeHi > 0) {
        hashHi = new HashMap(hashSizeHi);
    } else {
        hashHi = 0;
    }
    if (hashSizeLo > 0) {
        hashLo = new HashMap(hashSizeLo);
    } else {
        hashLo = 0;
    }
}


AIPlayer::~AIPlayer() {
    population--;

    if (hashHi != 0) {
        delete hashHi;
    }
    if (hashLo != 0) {
        delete hashLo;
    } 
}


INLINEFUNCS
void
AIPlayer::setMaxDepth(INT32 _maxDepth) {
    maxDepth = _maxDepth;
}


INLINEFUNCS
ID_TYPE
AIPlayer::board2id(Board *s) {
    ID_TYPE id = 0;
    for (INT32 i = 0; i < STONES; i++) {
        id <<= 5;
        id += 31 & (UINT8)s->getPosRed()[i];
        //        std::cout << "inserting: " << (31 & (UINT8)s->getPosRed()[i]) << "\n";
        id <<= 5;
        id += 31 & (UINT8)s->getPosBlu()[i];
        //        std::cout << "inserting: " << (31 & (UINT8)s->getPosBlu()[i]) << "\n";
    }       
    return id;
}


UINT32 normalCollision = 0;

INLINEFUNCS
RTYPE
AIPlayer::_rateBoard(Board *s, INT32 remDepth) {
    //if it's a win for blu, we've just made the winning move...        
    if (s->winBlu()) {
        DEBUGOUT("_rateBoard: win...\n");
        return WIN_VAL;
    }

    //use heuristics:
    if (remDepth == 0) {
        DEBUGOUT("_rateBoard: heu...\n");
        return rateBoard(s);
    }

    //query the hash maps
    ID_TYPE id = board2id(s);
    if (hashHi != 0 || hashLo != 0) {
        if (hashLo != 0) {
            HashEntry *resLo = hashLo->search(s->getHashKey(), id);
            if (resLo != 0 && resLo->remDepth >= remDepth) {
                DEBUGOUT("_rateBoard: hashHi...\n");    
                return resLo->rating;
            }
        }        
        if (hashHi != 0) {
            HashEntry *resHi = hashHi->search(s->getHashKey(), id);
            if (resHi != 0 && resHi->remDepth >= remDepth) {
                DEBUGOUT("_rateBoard: hashLo...\n");    
                return resHi->rating;
            }
        }
    }

    //recurse deeper:
    DEBUGOUT("_rateBoard: deep...\n");    

    INT8 tPiece;
    INT8 tDir;
    RTYPE ratings[STONES];
    INT32 i;
    for (i = 0; i < STONES; i++) {
        ratings[i] = MINUS_INFTY;
    }

    Board* tBoard;
    s->initGetSucc();
    
    while (s->hasNextSucc()) {
        tBoard = s->getNextSucc(&tPiece, &tDir);	
        RTYPE tRating = _rateBoard(tBoard, remDepth - 1);
        if (tRating > ratings[(INT32)tPiece]) {
            ratings[(INT32)tPiece] = tRating;
        }
        BoardFactory::pushBoard(tBoard);
    }

    //transform ratings to expected rating
    RTYPE val = 0;
    RTYPE p = 0;
    RTYPE last = MINUS_INFTY;   
    for (i = 0; i < STONES; i++) {
        RTYPE tRating = ratings[i];
        if (tRating == MINUS_INFTY) {
            p += probs[i];
        } else {
            val += p * GETMAXIMUM(last, tRating) + probs[i] * tRating;
            p = 0;
            last = tRating;
        }
    }
    val += p * last;
    //invert because of player switching
    val = -val;

    //insert into hash maps    
    if (hashHi != 0 || hashLo != 0) {                
        HashEntry tempEntry;
        tempEntry.id = id;
        tempEntry.rating = val;
        tempEntry.stepping = stepping;
        tempEntry.remDepth = remDepth;

        if (hashHi != 0) {
            HashEntry *resHi = hashHi->search(s->getHashKey());
            if (remDepth >= resHi->remDepth || stepping > resHi->stepping) {
                hashHi->insert(s->getHashKey(), tempEntry);
                //                hashHi->insert(keyHi, id, val, stepping, remDepth, s->hashKeyRed, s->hashKeyBlu);
            } else {
                //only for debugging: from here...
//                 if (++normalCollision % 1000 == 0) {
//                     std::cout << "hashCollision # " << normalCollision << "\n";
//                 }
                //...till here.

                if (hashLo != 0) {
                    hashLo->insert(s->getHashKey(), tempEntry);
                }
            }
        } else {
            if (hashLo != 0) {
                hashLo->insert(s->getHashKey(), tempEntry);
            }
        }
    }

    return val;
}

void
printDoubleBits(INT32 bits) {
    for (INT32 i = 0; i < STONES; i++) {
        std::cout << ((bits >> (i*2)) & 3);
    }
    std::cout << " bits: " << bits << "\n";
}

void printSuccDiceLine(INT32 m, INT32 d);

INLINEFUNCS
Board*
AIPlayer::getNextMove(Board *origin, INT32 dice) {
    return getNextMove(origin, dice, maxDepth);
}


INLINEFUNCS
Board*
AIPlayer::getNextMove(Board *origin, INT32 dice, INT32 depth) {
    //set steppings to 0 in order to prevent the hashmaps from containing too much old fuzz.
    stepping++;
    if (stepping == 0) {
        if (hashHi != 0) {
            hashHi->setSteppings(0);
        }
        if (hashLo != 0) {
            hashLo->setSteppings(0);
        }
    }

    RTYPE currBestRating = MINUS_INFTY;
    Board *currBestMove = 0;    

    origin->initGetSucc(dice);
    INT8 tempPiece;
    INT8 tempDir;

    while (origin->hasNextSucc()) {
        Board *tempBoard = origin->getNextSucc(&tempPiece, &tempDir);

        RTYPE tempRating = _rateBoard(tempBoard, depth);

        if (tempRating > currBestRating) {
            BoardFactory::pushBoard(currBestMove);
            currBestMove = tempBoard;
            currBestRating = tempRating;
        } else {
            BoardFactory::pushBoard(tempBoard);
        }
    }

    return currBestMove;
}
