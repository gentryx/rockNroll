/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/board.h                                             *
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
 *   Board represents a situation during the game. It holds the places,    *
 *   where each stone is located as well as it provides methods to         *
 *   generate all successing boards.                                       *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/

/**
 *
 * 1) Red plays from bottom/left to upper/right
 * 2) Board is mapped to the ints:
 *    
 *  (SIZEY-1 * LINE_OFFSET + 0) (SIZEY-1 * LINE_OFFSET + 1) ... (SIZEY-1 * LINE_OFFSET + SIZEX-1)
 *  ...
 *  (1 * LINE_OFFSET + 0) (1 * LINE_OFFSET + 1) ... (1 * LINE_OFFSET + SIZEX-1)
 *  (0 * LINE_OFFSET + 0) (0 * LINE_OFFSET + 1) ... (0 * LINE_OFFSET + SIZEX-1)
 *  
 * x) fix random_shuffle
 * 
 * x) todo: check for memory leaks!
 * x) todo: change MAXX & MAXY into DIMX & DIMY
 * x) todo: don't use RED_STONES & BLU_STONES but only STONES
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>

#include <globals.h>


class Board {        
 protected:
    /*******************************STATIC************************************/
    static UINT32 population;
    //listet für movesRed \in [0..4095] alle 1..18 möglichen moves (piece, dir) auf.
    static INT8 SuccData[4096][20][2];
    //in jeder Stellung sind für ein fixiertes Würfelergebnis max. 2*3 züge möglich (2 pieces, je 3 moves, für jeden move 2 INT8). 
    //nehme aber anstelle von [6][2] lieber [8][2] um zählerdaten mit reinzuquetschen.
    //fixiert man die pieces und moves so ist das eine constellation. davon gibt's offenbar max. 6*3*6*3 (eigentlich weniger) = 364;
    static INT8 ConstellationData [6][3][6][3][8][2];
    static INT8 *SuccDiceData[4096][6];   
    //alle 720 moeglichkeiten startstellungen je spieler
    static INT8 Positions[720][8];
    //für alle 12 bytes der id und alle ihre 24 möglichen zustände je ein zufalls-int32 wert (für's xor-hashing)
 public:
    static UINT32 HashWords[STONES*2][SIZEX*SIZEY-1];
 private:
    static bool staticsInited;

    static INLINEFUNCS void doEntry(INT32 w1, INT32 w2, INT32 w3, INT32 w4, INT32 move, INT32 piece, INT32 *indexer);
    static INLINEFUNCS INT32 getINibble(INT32 x, INT32 i);    
    static INLINEFUNCS void initSuccData();
    static INLINEFUNCS void initSuccDiceData();
    static INLINEFUNCS void initPositions();
    static INLINEFUNCS void initHashWords();
    static INLINEFUNCS void initStatics();

    /******************************NON-STATIC*********************************/
    INT8 posRed[8]; //STONES
    INT8 posBlu[8]; //STONES
    INT8 fieldRed[28]; //SIZEY * SIZEX
    INT8 fieldBlu[28]; //SIZEY * SIZEX
    //bit nr. "piece*2 + 0" ist true gdw. piece am rechten rand
    //bit nr. "piece*2 + 1" ist true gdw. piece am unteren rand
    INT32 movesRed;
    INT32 movesBlu;
    //we need two hashKeys to keep the updating of hashKeys easy while catering for the board flipping after each move.
    //for hashKeyRed we use:            HashWords[0..STONES-1]        for red and HashWords[STONES..2*STONES-1] for blu.
    //for hashKeyBlu we turn it around: HashWords[STONES..2*STONES-1] for red and HashWords[0..STONES-1]        for blu.
    UINT32 hashKeyRed;
    UINT32 hashKeyBlu;
    bool isWinRed;
    bool isWinBlu;
    bool isWinAny;
    //used for initGetSucc(), hasNextSucc() and getNextSucc() :
    INT32 remainSuccNum;
    INT8 *remainSucc;

    INLINEFUNCS void cloneData(Board *ret);
    INLINEFUNCS void printDoubleBits(std::ostream &outs, INT32 bits);


 public:
    /*******************************STATIC************************************/
    static INLINEFUNCS INT8 transposeField(INT8 f);

    /******************************NON-STATIC*********************************/
    Board();
    ~Board();

    bool operator==(Board& other);

    INLINEFUNCS void initPos(INT8 posRed[STONES], INT8 posBlu[STONES]);
    INLINEFUNCS void initNum(INT32 red, INT32 blu);
    INLINEFUNCS void initTrivial();
    INLINEFUNCS void initRand();

    INLINEFUNCS bool winRed();
    INLINEFUNCS bool winBlu();
    INLINEFUNCS bool winAny();

    INLINEFUNCS INT8 *getPosRed();
    INLINEFUNCS INT8 *getPosBlu();
    INLINEFUNCS UINT32 getHashKey();

    INLINEFUNCS void print(std::ostream &outstream = std::cout);

    //return a clone of the current instance with the corresponding piece moved
    INLINEFUNCS Board *move(INT8 piece, INT8 dir);

    //return all successing boards one by one
    INLINEFUNCS void initGetSucc();
    INLINEFUNCS void initGetSucc(INT32 dice);
    INLINEFUNCS bool hasNextSucc();
    INLINEFUNCS Board *getNextSucc(INT8 *movedPiece, INT8 *movedDir);    

    //only for testing:
    friend class BoardTestSuite;
    friend class AIPlayer;
    friend class FarmerBoy;
};

#endif
