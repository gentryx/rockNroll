/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/testsuites/engine.h                                        *
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
 *   This is the UnitTestSuit for the engine module. Test coverage is      *
 *   still poor - what a shame! ;-)                                        *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef QRTESTSUITE_H
#define QRTESTSUITE_H

#include <cxxtest/TestSuite.h>

//#include <headers.h>
#include <compilechain.h>

/*
no tests needed:
		compilechain.h \
		globals.h \
		headers.h \

done:
		mersenne.h \
		mersenne.cpp \
		mrblack.h \ 
		mrblack.cpp \

pending:
		aiplayer.h \
		aiplayer.cpp \
		board.h \ //almost everything, s. below
		board.cpp \
                
todo:
		boardfactory.h \
		boardfactory.cpp \
		mrmonte.h \
		mrmonte.cpp \
		farmerboy.h \
		farmerboy.cpp \
		referee.h \
		referee.cpp \
		mrrandom.h \
		mrrandom.cpp \
		player.h \
		player.cpp \
		stdinplayer.h \
		stdinplayer.cpp \
		hashmap.h \
		hashmap.cpp
*/


class MersenneTestSuite : public CxxTest::TestSuite {
 public:
    void setUp() {
    }

    void tearDown() {
    }

    void verifyProbs(PROBTYPE probs[STONES], int maxRep = 10000) {
        RandGen r(probs);
        UINT32 samples[STONES] = {0, 0, 0, 0, 0, 0};

        for (int i = 0; i < maxRep; i++) {
            samples[r.getDiceVal()]++;
        }

        for (int i = 0; i < STONES; i++) {
            TS_ASSERT_DELTA((PROBTYPE)samples[i]/(PROBTYPE)maxRep, probs[i], probs[i]/pow(maxRep, 1./3.));
        }
    }

    void testGetDiceVal() {
        PROBTYPE probs1[STONES] = {1./6., 1./6., 1./6., 1./6., 1./6., 1./6.};
        PROBTYPE probs2[STONES] = {6./6., 0./6., 0./6., 0./6., 0./6., 0./6.};
        PROBTYPE probs3[STONES] = {0./6., 6./6., 0./6., 0./6., 0./6., 0./6.};
        PROBTYPE probs4[STONES] = {0./6., 0./6., 6./6., 0./6., 0./6., 0./6.};
        PROBTYPE probs5[STONES] = {0./6., 0./6., 0./6., 6./6., 0./6., 0./6.};
        PROBTYPE probs6[STONES] = {0./6., 0./6., 0./6., 0./6., 6./6., 0./6.};
        PROBTYPE probs7[STONES] = {0./6., 0./6., 0./6., 0./6., 0./6., 6./6.};
        PROBTYPE probs8[STONES] = {1./6., 1./6., 2./6., 1./6., 0./6., 1./6.};
        PROBTYPE probs9[STONES] = {4./6., 0./6., 0./6., 1./6., 0./6., 1./6.};

        verifyProbs(probs1);
        verifyProbs(probs2);
        verifyProbs(probs3);
        verifyProbs(probs4);
        verifyProbs(probs5);
        verifyProbs(probs6);
        verifyProbs(probs7);
        verifyProbs(probs8);
        verifyProbs(probs9);
    }

    void testGenrandUInt32() {
        int sampleSize = 1024;
        int maxRep = 1024*1024;
        UINT32 samples[sampleSize];
        for (int i = 0; i < sampleSize; i++) {
            samples[i] = 0;
        }

        for (int i = 0; i < maxRep; i++) {
            samples[RandGen::genRandUInt32() % sampleSize]++;
        }

        PROBTYPE singleSample = 1. / (PROBTYPE)sampleSize;

        for (int i = 0; i < sampleSize; i++) {
            TS_ASSERT_DELTA((PROBTYPE)samples[i]/(maxRep), singleSample, singleSample / pow(maxRep, 1./6.));
        }                
    }

    void testInitGenrand() {
        const int predictionLength = 20;
        UINT32 prediction[predictionLength] = 
            {
                447795748UL,
                435264311UL,
                1023979326UL,
                2504564057UL,
                1310310721UL,
                1894053011UL,
                4248179604UL,
                287918471UL,
                647567278UL,
                946803939UL,
                920912206UL,
                2578063334UL,
                1656376191UL,
                4029315096UL,
                3291893052UL,
                826506493UL,
                844116569UL,
                3119706904UL,
                2222394072UL,
                4205545611UL
            };

        RandGen::initGenRand(4711);
        for (int i = 0; i < predictionLength; i++) {
            TS_ASSERT_EQUALS(RandGen::genRandUInt32(), prediction[i]);
        }
        
    }
};


class MrBlackTestSuite : public CxxTest::TestSuite {
 private:
    MrBlack *b;
 public:
    void setUp() {
    }

    void tearDown() {
    }

    void verifyBoard(PROBTYPE probs[STONES], INT8 posRed[STONES], INT8 posBlu[STONES], RTYPE expectation) {
        Board *b = BoardFactory::popBoard();
        b->initPos(posRed, posBlu);
        MrBlack mrb(0, 0, 0, probs);
        RTYPE rating = mrb.rateBoard(b);
        TS_ASSERT_DELTA(rating, expectation, 0.00001);
        BoardFactory::pushBoard(b);
    }

    void testRemMoves() {
        RandGen::initGenRand(4711);        

        PROBTYPE probs1[STONES] = {1./6., 1./6., 1./6., 1./6., 1./6., 1./6.};
        PROBTYPE probs2[STONES] = {6./6., 0./6., 0./6., 0./6., 0./6., 0./6.};
/*         PROBTYPE probs3[STONES] = {0./6., 6./6., 0./6., 0./6., 0./6., 0./6.}; */
/*         PROBTYPE probs4[STONES] = {0./6., 0./6., 6./6., 0./6., 0./6., 0./6.}; */
/*         PROBTYPE probs5[STONES] = {0./6., 0./6., 0./6., 6./6., 0./6., 0./6.}; */
/*         PROBTYPE probs6[STONES] = {0./6., 0./6., 0./6., 0./6., 6./6., 0./6.}; */
/*         PROBTYPE probs7[STONES] = {0./6., 0./6., 0./6., 0./6., 0./6., 6./6.}; */
/*         PROBTYPE probs8[STONES] = {1./6., 1./6., 2./6., 1./6., 0./6., 1./6.}; */
/*         PROBTYPE probs9[STONES] = {4./6., 0./6., 0./6., 1./6., 0./6., 1./6.}; */


        INT8 posRed1[STONES] = 
            {
                SIZEX * 0 + 0,
                SIZEX * 0 + 1,
                SIZEX * 0 + 4,
                SIZEX * 1 + 0,
                SIZEX * 1 + 1,
                SIZEX * 2 + 0
            };
        INT8 posBlu1[STONES] = 
            {
                SIZEX * 1 + 4,
                SIZEX * 1 + 1,
                SIZEX * 1 + 2,
                SIZEX * 2 + 0,
                SIZEX * 4 + 1,
                SIZEX * 3 + 0
            };

        verifyBoard(probs2, posRed1, posBlu1, (4 - 3) * 30);

        INT8 posRed2[STONES] = 
            {
                OFF_BOARD,
                SIZEX * 3 + 3,
                OFF_BOARD,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 4 + 2
            };
        INT8 posBlu2[STONES] = 
            {
                OFF_BOARD,
                OFF_BOARD,
                OFF_BOARD,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 2 + 0
            };
        verifyBoard(probs2, posRed2, posBlu2, (1 - 4) * 30);
        verifyBoard(probs1, posRed2, posBlu2, (7./6. - 4) * 30);

        //blu dist: 1,1
        INT8 posRed3a[STONES] = 
            {
                OFF_BOARD,
                SIZEX * 3 + 3,
                OFF_BOARD,
                SIZEX * 4 + 2,
                OFF_BOARD,
                SIZEX * 4 + 3
            };
        INT8 posBlu3a[STONES] = 
            {
                OFF_BOARD,
                SIZEX * 4 + 3,
                OFF_BOARD,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 3 + 4
            };
        verifyBoard(probs1, posRed3a, posBlu3a, (7./6. - 1) * 30);

        //blu dist: 2,1
        INT8 posRed3b[STONES] = 
            {
                OFF_BOARD,
                SIZEX * 3 + 3,
                OFF_BOARD,
                SIZEX * 4 + 2,
                OFF_BOARD,
                SIZEX * 4 + 3
            };
        INT8 posBlu3b[STONES] = 
            {
                OFF_BOARD,
                SIZEX * 4 + 2,
                OFF_BOARD,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 3 + 4
            };
        verifyBoard(probs1, posRed3b, posBlu3b, 1./3. * (7./6. - 1 - 1) * 30 + 2./3. * (7./6. - 1) * 30);

    }
};
 

class BoardTestSuite : public CxxTest::TestSuite {
 private:
    Board *b;

 public:
    void setUp() {
        //RandGen::initGenrand(4711);
        b = BoardFactory::popBoard();
    }

    void tearDown() {
        BoardFactory::pushBoard(b);
    }



    /*

    done:
      static UINT32 HashWords[STONES*2][SIZEX*SIZEY-1];
      static UINT32 population;

      INLINEFUNCS void initPos(INT8 posRed[STONES], INT8 posBlu[STONES]);


    pending:

    todo:
    operator=
    static INT8 SuccData[4096][20][2];
    static INT8 ConstellationData [6][3][6][3][8][2];
    static INT8 *SuccDiceData[4096][6];   
    static INT8 Positions[720][8];
    static bool staticsInited;
    static INLINEFUNCS void doEntry(INT32 w1, INT32 w2, INT32 w3, INT32 w4, INT32 move, INT32 piece, INT32 *indexer);
    static INLINEFUNCS INT32 getINibble(INT32 x, INT32 i);    
    static INLINEFUNCS void initSuccData();
    static INLINEFUNCS void initSuccDiceData();
    static INLINEFUNCS void initPositions();
    static INLINEFUNCS void initHashWords();
    static INLINEFUNCS void initStatics();
    INT8 posRed[8]; //STONES
    INT8 posBlu[8]; //STONES
    INT8 fieldRed[28]; //SIZEY * SIZEX
    INT8 fieldBlu[28]; //SIZEY * SIZEX
    INT32 movesRed;
    INT32 movesBlu;
    INT8 hashIndexRed;
    INT8 hashIndexBlu;
    UINT32 hashKey;
    bool isWinRed;
    bool isWinBlu;
    bool isWinAny;
    INT32 remainSuccNum;
    INT8 *remainSucc;
    INLINEFUNCS void cloneData(Board *ret);
    INLINEFUNCS void printDoubleBits(std::ostream &outs, INT32 bits);
    static INLINEFUNCS INT8 transposeField(INT8 f);
    Board();
    ~Board();
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
    INLINEFUNCS Board *move(INT8 piece, INT8 dir);
    INLINEFUNCS void initGetSucc();
    INLINEFUNCS void initGetSucc(INT32 dice);
    INLINEFUNCS bool hasNextSucc();
    INLINEFUNCS Board *getNextSucc(INT8 *movedPiece, INT8 *movedDir);    
     */

    void testHashWords() {
        RandGen::initGenRand(4711);
        UINT32 HashWords[2*STONES][SIZEX*SIZEY-1];
        //std::ifstream randFile("/home/gentryx/temp.raw");
        for (INT32 i = 0; i < 2*STONES; i++) {
            for (INT32 j = 0; j < SIZEX*SIZEY-1; j++) {
                /*                UINT32 val = 0;
                UINT8 buf;
                buf = randFile.get();
                val = 256 * val + buf;
                buf = randFile.get();
                val = 256 * val + buf;
                buf = randFile.get();
                val = 256 * val + buf;
                buf = randFile.get();
                val = 256 * val + buf;            
                HashWords[i][j] = val;*/
                HashWords[i][j] = RandGen::genRandUInt32();
            }
        }    

        for (INT32 i = 0; i < 2*STONES; i++) {
            for (INT32 j = 0; j < SIZEX*SIZEY-1; j++) {
                TS_ASSERT_EQUALS(Board::HashWords[i][j], HashWords[i][j]);
            }
        }
    }

    void testPopulation() {
        UINT32 pop = Board::population;
        Board *t4 = new Board();
        TS_ASSERT_EQUALS(Board::population, pop+1);
        Board *t5 = new Board();
        TS_ASSERT_EQUALS(Board::population, pop+2);
        delete t4;
        TS_ASSERT_EQUALS(Board::population, pop+1);
        delete t5;
        TS_ASSERT_EQUALS(Board::population, pop+0);
        t4 = new Board();
        t5 = new Board();
        Board *t6 = new Board();
        TS_ASSERT_EQUALS(Board::population, pop+3);
        delete t6;
        delete t5;
        delete t4;
        TS_ASSERT_EQUALS(Board::population, pop+0);
    }

    void easyMove(Board **mover, INT8 piece, INT8 dir, bool even) {
        Board *buffer = (*mover)->move(piece, dir);
        BoardFactory::pushBoard(*mover);
        *mover = buffer;
        //        (*mover)->print();

        Board *comp = BoardFactory::popBoard();
        if (even) { 
            comp->initPos((*mover)->getPosRed(), (*mover)->getPosBlu());
        } else {
            comp->initPos((*mover)->getPosRed(), (*mover)->getPosBlu());
        }

        bool res = (**mover == *comp);
        TS_ASSERT(res);
        delete comp;
    }


    void testMove1() {
        Board *mover = BoardFactory::popBoard();
        mover->initTrivial();
        //mover->print();
        easyMove(&mover, 0, 1*SIZEX+1, false);
        easyMove(&mover, 2, 0*SIZEX+1, true);
        easyMove(&mover, 0, 1*SIZEX+1, false);
        easyMove(&mover, 2, 0*SIZEX+1, true);
        easyMove(&mover, 0, 1*SIZEX+1, false);
        easyMove(&mover, 2, 1*SIZEX+0, true);
        easyMove(&mover, 0, 1*SIZEX+0, false);
        easyMove(&mover, 2, 1*SIZEX+0, true);      
        BoardFactory::pushBoard(mover);
    }

    void testMove2() {
        Board *mover = BoardFactory::popBoard();
        mover->initTrivial();
        Board *temp = mover->move(0, 1);
        BoardFactory::pushBoard(mover);
        mover = temp;

        Board *mirrored = BoardFactory::popBoard();
        mirrored->initPos(mover->getPosBlu(), mover->getPosRed());
        TS_ASSERT_DIFFERS(mover->getHashKey(), mirrored->getHashKey());        

        BoardFactory::pushBoard(mover);        
    }

    void compArray(INT8 *pos1, INT8 *pos2, int length) {
        for (int i = 0; i < length; i++) {
            TS_ASSERT_EQUALS(pos1[i], pos2[i]);
        }
    }

    void testInitPos1() {

        INT8 posRed[STONES] = 
            {
                SIZEX * 0 + 0,
                SIZEX * 0 + 1,
                SIZEX * 0 + 4,
                SIZEX * 1 + 0,
                SIZEX * 1 + 1,
                SIZEX * 2 + 0
            };
        INT8 posBlu[STONES] = 
            {
                SIZEX * 1 + 4,
                SIZEX * 1 + 1,
                SIZEX * 1 + 2,
                SIZEX * 2 + 0,
                SIZEX * 4 + 1,
                SIZEX * 3 + 0
            };

        INT8 fieldRed[SIZEX*SIZEY] = 
            {
                0,         1,         OFF_BOARD, OFF_BOARD, 2,
                3,         4,         OFF_BOARD, OFF_BOARD, OFF_BOARD, 
                5,         OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, 
                OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, 
                OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD
            };
        
        INT8 fieldBlu[SIZEX*SIZEY] = 
            {
                OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD,
                OFF_BOARD, 1,         2,         OFF_BOARD, 0,
                3,         OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, 
                5,         OFF_BOARD, OFF_BOARD, OFF_BOARD, OFF_BOARD, 
                OFF_BOARD, 4,         OFF_BOARD, OFF_BOARD, OFF_BOARD
            };

        b->initPos(posRed, posBlu);
        //b->print();    
   
        compArray(posRed, b->getPosRed(), STONES);
        compArray(posBlu, b->getPosBlu(), STONES);
        compArray(fieldRed, b->fieldRed, SIZEX*SIZEY);
        compArray(fieldBlu, b->fieldBlu, SIZEX*SIZEY);

        TS_ASSERT_EQUALS(b->movesRed, 1 << (2*2));
        TS_ASSERT_EQUALS(b->movesBlu, (1 << (2*4+1)) + (1 << (2*0)));

        UINT32 hashKeyRed = 0;
        UINT32 hashKeyBlu = 0;
        for (int i = 0; i < STONES; i++) {
            hashKeyRed ^= Board::HashWords[0      + i][b->getPosRed()[i]] ^ Board::HashWords[STONES + i][b->getPosBlu()[i]];
            hashKeyBlu ^= Board::HashWords[STONES + i][b->getPosRed()[i]] ^ Board::HashWords[0      + i][b->getPosBlu()[i]];
        }
        TS_ASSERT_EQUALS(b->getHashKey(), hashKeyRed);
        TS_ASSERT_EQUALS(b->hashKeyRed, hashKeyRed);
        TS_ASSERT_EQUALS(b->hashKeyBlu, hashKeyBlu);

        TS_ASSERT_EQUALS(b->winRed(), false);
        TS_ASSERT_EQUALS(b->winBlu(), false);
        TS_ASSERT_EQUALS(b->winAny(), false);

        b->initGetSucc();
        TS_ASSERT_EQUALS(b->remainSuccNum, 16-1);
        TS_ASSERT_EQUALS(b->remainSucc, Board::SuccData[b->movesRed][0]);
    }
};


class MockupAIPlayer : public AIPlayer {
 public:
    MockupAIPlayer(INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo, PROBTYPE _probs[STONES] = 0) : AIPlayer(_maxDepth, hashSizeHi, hashSizeLo, _probs) {}

    RTYPE rateBoard(Board *s) {
        return s->getPosRed()[0];
    }
};

class AIPlayerTestSuite : public CxxTest::TestSuite {
    /*
      testsuite status:

      done:
      INLINEFUNCS RTYPE _rateBoard(Board *s, INT32 remainingDepth);
      virtual RTYPE rateBoard(Board *s) =0;

      pending:
      INLINEFUNCS void board2id(Board *s, UINT8 id[]);


      todo:
      AIPlayer(PROBTYPE _probs[STONES], INT32 _maxDepth, INT32 hashSizeHi, INT32 hashSizeLo);
      virtual ~AIPlayer();
      INLINEFUNCS void setMaxDepth(INT32 _maxDepth);
      INLINEFUNCS Board *getNextMove(Board *s, INT32 dice);
      INLINEFUNCS Board *getNextMove(Board *s, INT32 dice, INT32 depth);
    */


 private:
    AIPlayer *a1;
    AIPlayer *a2;
    AIPlayer *a3;

 public:
    void setUp() {
        PROBTYPE probs1[STONES] = {1./6., 1./6., 1./6., 1./6., 1./6., 1./6.};
        PROBTYPE probs2[STONES] = {1./6., 0./6., 4./6., 1./6., 0./6., 0./6.};
        PROBTYPE probs3[STONES] = {4./6., 0./6., 0./6., 0./6., 2./6., 0./6.};
        a1 = new MockupAIPlayer(0, 0, 0, probs1);
        a2 = new MockupAIPlayer(0, 0, 0, probs2);
        a3 = new MockupAIPlayer(0, 0, 0, probs3);
    }

    void tearDown() {
        delete a1;
        delete a2;
        delete a3;
    }

    void testBoard2ID() {
        Board *b = BoardFactory::popBoard();
        b->initTrivial();
        Board *t = b->move(0, SIZEX + 1);
        BoardFactory::pushBoard(b);
        b = t;
        ID_TYPE id = AIPlayer::board2id(b);
        
        for (int i = STONES-1; i >= 0; i--) {
            UINT8 fieldID;
            UINT8 fieldBO;

            fieldID = id & 31;
            id >>= 5;
            fieldBO = b->getPosBlu()[i] & 31;
            //            std::cout << "fieldID: " << (int)fieldID << "\n";
            //            std::cout << "fieldBO: " << (int)fieldBO << "\n";
            TS_ASSERT_EQUALS(fieldID, fieldBO);

            fieldID = id & 31;
            id >>= 5;
            fieldBO = b->getPosRed()[i] & 31;
            //std::cout << "fieldID: " << (int)fieldID << "\n";
            //            std::cout << "fieldBO: " << (int)fieldBO << "\n";
            TS_ASSERT_EQUALS(fieldID, fieldBO);
        }

        BoardFactory::pushBoard(b);
    }

    void testMockupAIPlayer() {
        INT8 posRed[STONES] = 
            {
                SIZEX * 1 + 4,
                SIZEX * 0 + 1,
                SIZEX * 0 + 2,
                SIZEX * 2 + 0,
                SIZEX * 4 + 1,
                SIZEX * 3 + 0
            };
        INT8 posBlu[STONES] = 
            {
                SIZEX * 2 + 2,
                SIZEX * 0 + 1,
                SIZEX * 0 + 4,
                SIZEX * 1 + 0,
                SIZEX * 1 + 1,
                SIZEX * 2 + 0
            };

        Board *b = BoardFactory::popBoard();
        b->initPos(posRed, posBlu);

        TS_ASSERT_DELTA(b->getPosRed()[0],    SIZEX * 1 + 4,                                     0.00001);

        TS_ASSERT_DELTA(a1->rateBoard(b),     SIZEX * 1 + 4,                                     0.00001);
        TS_ASSERT_DELTA(a1->_rateBoard(b, 0), SIZEX * 1 + 4,                                     0.00001);
        TS_ASSERT_DELTA(a1->_rateBoard(b, 1), -(SIZEX * 2 + 2),                                  0.00001);
        TS_ASSERT_DELTA(a1->_rateBoard(b, 2), 1./6. * (SIZEX * 2 + 4) + 5./6. * (SIZEX * 1 + 4), 0.00001);

        TS_ASSERT_DELTA(a2->rateBoard(b),     SIZEX * 1 + 4,                                     0.00001);
        TS_ASSERT_DELTA(a2->_rateBoard(b, 0), SIZEX * 1 + 4,                                     0.00001);
        TS_ASSERT_DELTA(a2->_rateBoard(b, 1), -(SIZEX * 2 + 2),                                  0.00001);
        TS_ASSERT_DELTA(a2->_rateBoard(b, 2), 1./6. * (SIZEX * 2 + 4) + 5./6. * (SIZEX * 1 + 4), 0.00001);
        
        TS_ASSERT_DELTA(a3->rateBoard(b),     SIZEX * 1 + 4,                                     0.00001);
        TS_ASSERT_DELTA(a3->_rateBoard(b, 0), SIZEX * 1 + 4,                                     0.00001);
        TS_ASSERT_DELTA(a3->_rateBoard(b, 1), -(SIZEX * 2 + 2),                                  0.00001);
        TS_ASSERT_DELTA(a3->_rateBoard(b, 2), 4./6. * (SIZEX * 2 + 4) + 2./6. * (SIZEX * 1 + 4), 0.00001);

        BoardFactory::pushBoard(b);
    }
};


class FarmerBoyTestSuite : public CxxTest::TestSuite {
 private:
    AIPlayer *f;

 public:
    void setUp() {
        f = new FarmerBoy(1, 0, 0);
    }

    void tearDown() {
        delete f;
    }

    void testRating() {
        INT8 posRed1[STONES] = 
            {
                SIZEX * 0 + 0,
                OFF_BOARD,
                SIZEX * 4 + 1,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 2 + 0
            };
        INT8 posBlu1[STONES] = 
            {
                SIZEX * 1 + 4,
                SIZEX * 1 + 1,
                SIZEX * 1 + 2,
                SIZEX * 2 + 0,
                SIZEX * 4 + 1,
                SIZEX * 3 + 0
            };

        Board *s = BoardFactory::popBoard();
        s->initPos(posRed1, posBlu1);

        RTYPE rating = f->rateBoard(s);
        TS_ASSERT_DELTA(rating, 2./3., 0.0001);

        BoardFactory::pushBoard(s);
    }
};


class EmptyTestSuite : public CxxTest::TestSuite {
 public:
    void setUp() {
    }

    void tearDown() {
    }

    void testAddition() {
        TS_ASSERT( 1 + 1 > 1 ); 
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};


#endif
