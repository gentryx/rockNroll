/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   rockNroll/shellInterface/main.cpp                                     *
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
 *   This file incorporates the command line interface to the rockNroll    *
 *   engine. It should mainly be used for automated testing.               *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/


#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>        
#include <cstdlib>
#include <sys/time.h>
#include <string>
#include <cmath>

#include <compilechain.h>

typedef std::istringstream istringstream;
typedef std::ostringstream ostringstream;

INT32 
str2int(string str) {
    istringstream conv(str);
    INT32 res;
    conv >> res;
    return res; 
}

string 
int2str(INT32 num) {
    ostringstream conv;
    conv << num;
    return conv.str();
}

void 
testBoard() {
    Board test;
    test.initTrivial();
    std::cout << ">>>>> test before all <<<<<\n";
    test.print();

    std::cout << ">>>>> all succs of test when dice==3 <<<<<\n";    
    test.initGetSucc(3);
    INT32 i = 0;
    while (test.hasNextSucc()) {
        i++;
        INT8 movedPiece;
        INT8 movedDir;
        Board *tempBoard = test.getNextSucc(&movedPiece, &movedDir);
        std::cout << "move number: " << i << "\n";
        std::cout << "moved: " << (int)movedPiece << "\n";    
        tempBoard->print();
        std::cout << "\n";
    }
    std::cout << ">>>>> this were all succs of test <<<<<\n";    

    Board *betaTest = test.move(0, SOUTH_EAST);
    std::cout << ">>>>> test after move <<<<<\n";
    test.print();
    std::cout << ">>>>> betaTest after move <<<<<\n";
    betaTest->print();

    betaTest = betaTest->move(0,0);
    std::cout << ">>>>> betaTest after 2nd move <<<<<\n";
    betaTest->print();

    betaTest = betaTest->move(0, SOUTH_EAST);
    std::cout << ">>>>> betaTest after 3rd move <<<<<\n";
    betaTest->print();
    
    betaTest = betaTest->move(4, SOUTH_EAST);
    std::cout << ">>>>> betaTest after 4th move <<<<<\n";
    betaTest->print();

    betaTest = betaTest->move(5, SOUTH);
    std::cout << ">>>>> betaTest after 5th move <<<<<\n";
    betaTest->print();

    betaTest = betaTest->move(0, 0);
    std::cout << ">>>>> betaTest after 6th move <<<<<\n";
    betaTest->print();

    betaTest = betaTest->move(5, SOUTH);
    std::cout << ">>>>> betaTest after 7th move <<<<<\n";
    betaTest->print();

    betaTest = betaTest->move(0, 0);
    std::cout << ">>>>> betaTest after 8th move <<<<<\n";
    betaTest->print();

    test.initRand();
    std::cout << ">>>>> test after randInit <<<<<\n";
    test.print();
    std::cout << ">>>>> betaTest after randInit <<<<<\n";
    betaTest->print();

    std::cout << ">>>>> betaTest's succs <<<<<\n";
    betaTest->initGetSucc();
    Board* alphaTest;
    INT32 sucNum = 0;
    std::cout << ">>> #" << sucNum++ << " <<<\n";
    while (betaTest->hasNextSucc()) {
        INT8 movedPiece;
        INT8 movedDir;
        alphaTest = betaTest->getNextSucc(&movedPiece, &movedDir);
        std::cout << ">>> #" << sucNum++ << " <<<\n";
        alphaTest->print();
    }
}

void
benchmarkMove() {
    struct timeval tBegin;
    struct timeval tEnd;
    struct timezone tz;
    gettimeofday(&tBegin,&tz);

    init_genrand(0);
    Board origin;
    const INT32 repeats = 10000000;
    INT32 realMoves = 0;
    for (INT32 i = 0; i < repeats; i++) {
        origin.initRand();
        origin.initGetSucc();
        while (origin.hasNextSucc()) {
            realMoves++;
            INT8 movedPiece;
            INT8 movedDir;
            Board *testicle = origin.getNextSucc(&movedPiece, &movedDir);
            BoardFactory::pushBoard(testicle);
        }
    }
    gettimeofday(&tEnd,&tz);
    INT32 timeSpan = (tEnd.tv_sec - tBegin.tv_sec);
    std::cout << "time taken: " << timeSpan << "\n";
    std::cout << "approx. " << (realMoves)/timeSpan << " Moves/s\n";
}


void benchmarkDepth() {
//     RandGen::initGenRand(555);

//     INT8 posRed1[STONES] = {23,   9,  -1,  -1,  -1,  -1};
//     INT8 posBlu1[STONES] = {16,  14,  -1,  -1,  -1,  -1};
//     INT8 posRed2[STONES] = {20,   1,  -1,  -1,  -1,  -1};
//     INT8 posBlu2[STONES] = {21,   6,  -1,  -1,  -1,  -1};
//     Board *b1 = BoardFactory::popBoard();
//     Board *b2 = BoardFactory::popBoard();
//     b1->initPos(posRed1, posBlu1);
//     b2->initPos(posRed2, posBlu2);
//     std::cout << "b1.hashKey = " << b1->getHashKey() << "\n";
//     std::cout << "b2.hashKey = " << b2->getHashKey() << "\n";
//     std::cout << "b1.hashKey % (10*1024*1024) = " << (b1->getHashKey() % (10*1024*1024)) << "\n";
//     std::cout << "b2.hashKey % (10*1024*1024) = " << (b2->getHashKey() % (10*1024*1024)) << "\n";
//     BoardFactory::pushBoard(b1);
//     BoardFactory::pushBoard(b2);

    /*    for (int i = 0; i < ID_LEN; i++) {
        std::cout << "HashWords[" << i << "]\n";
        for (int j = 0; j < SIZEX*SIZEY-1; j++) {
            std::cout << "  " << Board::HashWords[i][j];
        }
        std::cout << "\n";
    }
    std::cout << "\n";*/


    for (int i = 6; i <= 7; i++) {
        std::cout << "i: " << i << "\n";
        std::cout << "  create...\n";

        Board *b1 = BoardFactory::popBoard();
        Board *b2;
        PROBTYPE probs[STONES] = {2./6., 2./6., 0./6., 2./6., 0./6., 0./6.};
        INT8 posRed[STONES] = 
            {
                SIZEX * 0 + 0,
                SIZEX * 0 + 1,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 1 + 1,
                SIZEX * 2 + 0
            };
        INT8 posBlu[STONES] = 
            {
                SIZEX * 0 + 0,
                SIZEX * 0 + 1,
                OFF_BOARD,
                OFF_BOARD,
                SIZEX * 1 + 1,
                SIZEX * 2 + 0
            };
        b1->initPos(posRed, posBlu);
        Player *m1 = new MrBlack(i, 2*1024*1024, 2*1024*1024);

        std::cout << "  get1...\n";
        b2 = m1->getNextMove(b1, 3);
        std::cout << "  get2...\n";
        b2 = m1->getNextMove(b1, 3);
        std::cout << "  ok...\n";
        BoardFactory::pushBoard(b1);
        BoardFactory::pushBoard(b2);
        delete m1;
    }
}


void testProbDrift(int modNum, int prob, int rep) {
    RandGen::initGenRand();

    PROBTYPE probs[STONES];
    int repMax = 100;
    probs[modNum] = (RTYPE)prob / (RTYPE)repMax;
    for (int j = 0; j < STONES; j++) {
        if (j != modNum) {
            probs[j] = (1. - probs[modNum]) / 5.;
        }
    }

    MrBlack *bl1a = new MrBlack(0, 0, 0);
    MrBlack *bl1b = new MrBlack(0, 0, 0);
    MrBlack *bl2a = new MrBlack(0, 0, 0, probs);
    MrBlack *bl2b = new MrBlack(0, 0, 0, probs);
    //Player *m1 = new MrMonte(1, 0, 0, 200, bl1a, bl1b);
    //Player *m1 = new MrBlack(4, 0, 0);
    Player *m1 = new FarmerBoy(4, 0, 0);
    Player *m2 = new MrMonte(1, 0, 0, 200, bl2a, bl2b, probs);

    RTYPE res1 = Referee::multiRun(m1, m2, rep, probs);
    RTYPE res2 = Referee::multiRun(m2, m1, rep, probs);
    RTYPE ressum = (double)(res1 + rep - res2) / (2. * (double)rep);
    std::cout << modNum << " " << (double)prob/(double)repMax << " " << ressum << "\n";
                
    delete m1;
    delete m2;
    delete bl1a;
    delete bl1b;
    delete bl2a;
    delete bl2b;
}


void
althoeferProposal(int rep) {
    RandGen::initGenRand();

    PROBTYPE probs[STONES] = {0.12 , 0.21 , 0.12 , 0.22 , 0.21 , 0.12};

    Player *m1 = new MrBlack(5, 0, 0);
    Player *m2 = new MrBlack(5, 0, 0, probs);

    RTYPE res1 = Referee::multiRun(m1, m2, rep, probs);
    RTYPE res2 = Referee::multiRun(m2, m1, rep, probs);
    RTYPE ressum = (double)(res1 + rep - res2) / (2. * (double)rep);
    std::cout << ressum << "\n";
                
    delete m1;
    delete m2;
}


void
benchmarkGetNextMove() {
    init_genrand(0);
    Board *origin = BoardFactory::popBoard();
    Player *m1 = new MrBlack(2, 1024, 0);
    Player *m2 = new MrBlack(2, 1024, 0);
    Player *subject = new MrMonte(2, 1024*1024, 0, 200, m1, m2);
//     /*
// monte search depth ++
// real	0m0.024s
// real	0m0.181s
// real	0m2.458s
// real	0m38.293s

// black search depth ++
// real	0m0.020s
// real	0m0.109s
// real	0m1.137s
// real	0m13.904s
//     */
//     MrMonte subject(0, 0, 0, 200, m1, m2);
    Board *res;
    for (INT32 i = 0; i < 1; i++) {
        origin->initTrivial();
        res=subject->getNextMove(origin, 1);
        //res->print();        
        BoardFactory::pushBoard(res);
    }

    BoardFactory::pushBoard(origin);
}


// void 
// printConstellationLine(INT32 a, INT32 ma,INT32 b, INT32 mb) {    
//     for (INT8 i = Board::ConstellationData[a][ma][b][mb][6][0]; i >= 0; i--) {
//         std::cout << "piece: " << (int)Board::ConstellationData[a][ma][b][mb][i][0] << " dir: " << (int)Board::ConstellationData[a][ma][b][mb][i][1] << "\n";
//     }
// }

// void
// printSuccDiceLine(INT32 m, INT32 d) {
//     for (INT32 i = Board::SuccDiceData[m][d][6*2]; i >= 0; i--) {
//         std::cout << "piece: " << (int)Board::SuccDiceData[m][d][i*2+0] << " dir: " << (int)Board::SuccDiceData[m][d][i*2+1] << "\n";
//     }
// }

// void 
// testSucc() {
//     std::cout << ">>>>> testing ConstellationData <<<<<\n";
//     //    printConstellationLine(0, 0, 2, 1);
//     std::cout << ">>>>> testing SuccDiceData <<<<<\n";
//     printSuccDiceLine(4019, 4);
// }

void
benchmarkRand() {
    struct timeval tBegin;
    struct timeval tEnd;
    struct timezone tz;
    gettimeofday(&tBegin,&tz);
    srand(tBegin.tv_usec);
    init_genrand(tBegin.tv_usec);
    INT32 i;
    const INT32 repeats = 0x40000000;
    
    gettimeofday(&tBegin,&tz);
    i = 0;
    for (INT32 c = 0; c < repeats; c++) {
        i += rand();
    }
    gettimeofday(&tEnd,&tz);
    std::cout << "rand()     time: " << (tEnd.tv_sec - tBegin.tv_sec) << "\n";

    gettimeofday(&tBegin,&tz);
    i = 0;
    for (INT32 c = 0; c < repeats; c++) {
        i += RandGen::genRandUInt32();
    }
    gettimeofday(&tEnd,&tz);
    std::cout << "RANDFUNC() time: " << (tEnd.tv_sec - tBegin.tv_sec) << "\n";
    
}


void
testPlayer() {
    Board *alphaBoard = new Board();
    alphaBoard->initRand();
    std::cout << ">>>>> Starting <<<<<\n";

    StdInPlayer buzz;
    MrRandom aldrin(0, 0, 0);
    while (!alphaBoard->winAny()) {
        Board *tempBoard = buzz.getNextMove(alphaBoard, 4);
        BoardFactory::pushBoard(alphaBoard);
        alphaBoard = tempBoard;

        tempBoard = aldrin.getNextMove(alphaBoard, 4);
        BoardFactory::pushBoard(alphaBoard);
        alphaBoard = tempBoard;	
    }
}

void testReferee() {
    Referee panther;
    RTYPE res;

    /*    res = panther.multiRun(new MrBlack(5, 0, 1000000),
                           new MrBlack(5, 0, 1000000),
                           2);*/
    Player *m1 = new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    Player *m2 = new MrBlack(6, 1024*1024, 0);

    Board *b = BoardFactory::popBoard();
    b->initNum(405, 405);

    res = panther.multiRun(m1, m2, 1, b);
    std::cout << "res: " << res << "\n";
      

    /*    for (INT32 i = 0; i < 100/stepsize; i++) {
        total += stepsize;

        res = panther.multiRun(new MrBlack(0),
                               new MrMonte(0, 200, new MrBlack(0), new MrBlack(0)),                               
                               stepsize);
        val00 += res;

        res = panther.multiRun(new MrMonte(0, 200, new MrBlack(0), new MrBlack(0)),                               
                               new MrBlack(0),
                               stepsize);
        val11 += res;
    
        res = panther.multiRun(new MrBlack(0),
                               new MrMonte(2, 200, new MrBlack(0), new MrBlack(0)),                               
                               stepsize);
        val22 += res;

        res = panther.multiRun(new MrMonte(2, 200, new MrBlack(0), new MrBlack(0)),                               
                               new MrBlack(0),
                               stepsize);
        val33 += res;
        
        std::cout << "multiRun: MrBlack(0)                              vs. MrMonte(0, 200, MrBlack(0), MrBlack(0)) " << (val00/total) << "\n";
        std::cout << "multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(0)                              " << (val11/total) << "\n";
        std::cout << "multiRun: MrBlack(0)                              vs. MrMonte(2, 200, MrBlack(0), MrBlack(0)) " << (val22/total) << "\n";
        std::cout << "multiRun: MrMonte(2, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(0)                              " << (val33/total) << "\n";
    
        std::cout << "total: " << total << "\n\n";
    }
    */

    /*
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrMonte(0, 200, MrBlack(0), MrBlack(0))  0.5423
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrMonte(1, 200, MrBlack(0), MrBlack(0))  0.511
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(5)                               0.5373
total: 10000

multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrMonte(0, 200, MrBlack(0), MrBlack(0))  0.5388
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrMonte(1, 200, MrBlack(0), MrBlack(0))  0.5083
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(5)                               0.5355
total: 10000

multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrMonte(0, 200, MrBlack(0), MrBlack(0))  0.5395
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrMonte(1, 200, MrBlack(0), MrBlack(0))  0.5138
multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(5)                               0.544
total: 10000

multiRun: MrBlack(1) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.462635
multiRun: MrBlack(2) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.479734
multiRun: MrBlack(3) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.494617
multiRun: MrBlack(4) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.525966
multiRun: MrBlack(5) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.546865
total: 3158

multiRun: MrBlack(1) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.448128
multiRun: MrBlack(2) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.477594
multiRun: MrBlack(3) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.514426
multiRun: MrBlack(4) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.524555
multiRun: MrBlack(5) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.558625
total: 3258

multiRun: MrBlack(1) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.475223
multiRun: MrBlack(2) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.481994
multiRun: MrBlack(3) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.504463
multiRun: MrBlack(4) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.528163
multiRun: MrBlack(5) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.533703
total: 3249

multiRun: MrBlack(1) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.449598
multiRun: MrBlack(2) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.473098
multiRun: MrBlack(3) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.489796
multiRun: MrBlack(4) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.528448
multiRun: MrBlack(5) vs. MrMonte(0, 2, MrBlack(0), MrBlack(0)) 0.551948
total: 3234


multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(6)                               0.499642
total: 1397

multiRun: MrMonte(0, 200, MrBlack(0), MrBlack(0)) vs. MrBlack(6)                               0.521837
total: 1328


    */


    //  //ca. 5min
    //  res = panther.multiRun(new MrMonte(0, 20), new MrMonte(0, 20), 10);
    //  std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(0, 20) " << res << "\n";
  
    //   //ca. 15min
    //   res = panther.multiRun(new MrMonte(0, 20), new MrMonte(1, 20), 10);
    //   std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(1, 20) " << res << "\n";

    //   //ca. 30min
    //   res = panther.multiRun(new MrMonte(0, 20), new MrMonte(2, 20), 10);
    //   std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(2, 20) " << res << "\n";

    //     //ca. 1h
    //     res = panther.multiRun(new MrMonte(0, 20), new MrMonte(2, 20), 1000);
    //     std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(2, 20) " << res << "\n";
    //     //ca. 1h
    //     res = panther.multiRun(new MrMonte(0, 20), new MrMonte(2, 20), 1000);
    //     std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(2, 20) " << res << "\n";
    //     //ca. 1h
    //     res = panther.multiRun(new MrMonte(0, 20), new MrMonte(2, 20), 1000);
    //     std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(2, 20) " << res << "\n";
    //     //ca. 1h
    //     res = panther.multiRun(new MrMonte(0, 20), new MrMonte(2, 20), 1000);
    //     std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(2, 20) " << res << "\n";
    //     //ca. 1h
    //     res = panther.multiRun(new MrMonte(0, 20), new MrMonte(2, 20), 1000);
    //     std::cout << "multiRun: MrMonte(0, 20) vs. MrMonte(2, 20) " << res << "\n";

    //     //ca. 30min
    //     res = panther.multiRun(new MrMonte(1, 200), new MrMonte(0, 200), 1000);
    //     std::cout << "multiRun: MrMonte(1, 200) vs. MrMonte(0, 200) " << res << "\n";

    //     //ca. 1h
    //     res = panther.multiRun(new MrMonte(2, 200), new MrMonte(0, 200), 1000);
    //     std::cout << "multiRun: MrMonte(2, 200) vs. MrMonte(0, 200) " << res << "\n";
}

void
testHashMaps() {

    Referee panther;
    RTYPE res;

    init_genrand(0);
    MrBlack* t1 = new MrBlack(5, 0, 0);
    MrBlack* t2 = new MrBlack(7, 0, 0);
    res = panther.multiRun(t1,
                           t2,
                           1);      
    std::cout << "res: " << res << "\n";
}

// void
// testMrBlack() {
//     MrBlack tester(0, 0, 0);
//     std::cout << "000000: " << tester.remMoves[0][0][0][0][0][0] << "\n";
//     std::cout << "100000: " << tester.remMoves[1][0][0][0][0][0] << "\n";
//     std::cout << "000200: " << tester.remMoves[0][0][0][2][0][0] << "\n";
//     std::cout << "111111: " << tester.remMoves[1][1][1][1][1][1] << "\n";
//     std::cout << "222222: " << tester.remMoves[2][2][2][2][2][2] << "\n";
//     std::cout << "100001: " << tester.remMoves[1][0][0][0][0][1] << "\n";
//     std::cout << "200001: " << tester.remMoves[2][0][0][0][0][1] << "\n";
//     std::cout << "200002: " << tester.remMoves[2][0][0][0][0][2] << "\n";
//     std::cout << "333333: " << tester.remMoves[3][3][3][3][3][3] << "\n";
//     std::cout << "444444: " << tester.remMoves[4][4][4][4][4][4] << "\n";
// }

void
initRandWithTime() {
    struct timeval tBegin;
    struct timezone tz;
    gettimeofday(&tBegin,&tz);
    srand(tBegin.tv_usec);
    init_genrand(tBegin.tv_usec);
}

void
clash(INT32 boardRed, INT32 reps) {
    initRandWithTime();

    Referee panther;
    Player *m1 = new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    Player *m2 = new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));

    for (INT32 boardBlu = 0; boardBlu < 720; boardBlu++) {
        Board *b = BoardFactory::popBoard();
        b->initNum(boardRed, boardBlu);
        INT32 res = panther.multiRun(m1, m2, reps, b);
        BoardFactory::pushBoard(b);
        
        std::cout << "#\n";
        std::cout << "# MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0))\n";
        std::cout << "# vs.\n";
        std::cout << "# MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0))\n";
        std::cout << "#\n";
        std::cout << "# boardRed boardBlu repeats result\n";
        std::cout << boardRed << " " << boardBlu << " " << reps << " " << res << "\n";
        std::cout << "#\n";
    }
}

void
smash(INT32 depth1, INT32 depth2, INT32 reps) {
    initRandWithTime();

    Referee panther;
    Player *m1 = new MrBlack(depth1, 1024*1024-1, 1024*1024-1);
    Player *m2 = new MrBlack(depth2, 1024*1024-1, 1024*1024-1);

    INT32 res = panther.multiRun(m1, m2, reps);
        std::cout << "#\n";
        std::cout << "# MrBlack(depth1, 1024*1024-1, 1024*1024-1);\n";
        std::cout << "# vs.\n";
        std::cout << "# MrBlack(depth2, 1024*1024-1, 1024*1024-1);\n";
        std::cout << "#\n";
        std::cout << "# depth1 depth2 repeats result\n";
        std::cout << depth1 << " " << depth2 << " " << reps << " " << res << "\n";
        std::cout << "#\n";
    
}


void
thrash(INT32 depth, INT32 reps) {
    initRandWithTime();

    Referee panther;

    Player *m1 = new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    Player *m2 = new MrMonte(0, 0, 0, 200, new MrBlack(depth, 1024*4, 1024*4), new MrBlack(depth, 1024*4, 1024*4));
    INT32 res = panther.multiRun(m1, m2, reps);

    std::cout << "#\n";
    std::cout << "# MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));\n";
    std::cout << "# vs.\n";
    std::cout << "# MrMonte(0, 0, 0, 200, MrBlack(depth, 1024*1024-1, 1024*1024-1), MrBlack(depth, 1024*1024-1, 1024*1024-1));\n";
    std::cout << "#\n";
    std::cout << "# depth repeats result\n";
    std::cout << depth << " " << reps << " " << res << "\n";
    std::cout << "#\n";   
}

void 
clobber(INT32 hashParam) {
    INT32 hashSize = (int)(0.1+exp(log(sqrt(sqrt(2)))*hashParam));
    init_genrand(0);
    Board *origin = BoardFactory::popBoard();
    MrBlack subject(6, hashSize, 0);

    struct timeval tBegin;
    struct timeval tEnd;
    struct timezone tz;
    gettimeofday(&tBegin,&tz);

    for (INT32 i = 0; i < 1; i++) {
        origin->initTrivial();
        Board *res=subject.getNextMove(origin, 1);
        BoardFactory::pushBoard(res);
    }

    gettimeofday(&tEnd,&tz);
    float timeSpan = (tEnd.tv_sec*1000+tEnd.tv_usec/1000 - tBegin.tv_sec*1000-tBegin.tv_usec/1000);
    timeSpan /= 1000;
    std::cout << hashSize << " " << timeSpan << "\n";
}


void
dash() {
    initRandWithTime();
    Referee panther;
    RTYPE res;

    Player *m1 = new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    Player *m2 = new MrBlack(6, 1024*1024, 0);
    //ayer *m2 = new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    Player *m3 = new MrMonte(0, 0, 0, 200, new MrBlack(1, 1024*4, 0), new MrBlack(1, 1024*4, 0));

    Board *b = BoardFactory::popBoard();
    b->initNum(405, 405);

    res = panther.multiRun(m1, m2, 10, b);
    std::cout << "res m1 vs. m2: " << res << "\n";
    res = panther.multiRun(m2, m1, 10, b);
    std::cout << "res m2 vs. m1: " << res << "\n";
    res = panther.multiRun(m1, m3, 10, b);
    std::cout << "res m1 vs. m3: " << res << "\n";
    res = panther.multiRun(m3, m1, 10, b);
    std::cout << "res m3 vs. m1: " << res << "\n";
    res = panther.multiRun(m2, m3, 10, b);
    std::cout << "res m2 vs. m3: " << res << "\n";
    res = panther.multiRun(m3, m2, 10, b);
    std::cout << "res m3 vs. m2: " << res << "\n";

}


Player *int2player(int p) {
    switch (p) {
    case  0:
        return new MrRandom(0, 0, 0);
    case  1:
        return new MrMonte(0, 0, 0,  50, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    case  2:
        return new MrMonte(0, 0, 0, 100, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    case  3:
        return new MrMonte(0, 0, 0, 150, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    case  4:
        return new MrMonte(0, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    case  5:
        return new MrMonte(1, 0, 0, 200, new MrBlack(0, 0, 0), new MrBlack(0, 0, 0));
    case  6:
        return new MrMonte(0, 0, 0, 200, new MrBlack(1, 0, 0), new MrBlack(1, 0, 0));
    case  7:
        return new MrBlack(0, 0, 0);
    case  8:
        return new MrBlack(1, 0, 0);
    case  9:
        return new MrBlack(2, 0, 0);
    case 10:
        return new MrBlack(3, 0, 0);
    case 11:
        return new MrBlack(4, 0, 0);
    case 12:
        return new FarmerBoy(0, 0, 0);
    case 13:
        return new FarmerBoy(1, 0, 0);
    case 14:
        return new FarmerBoy(2, 0, 0);
    case 15:
        return new FarmerBoy(3, 0, 0);
    case 16:
        return new FarmerBoy(4, 0, 0);
    default:
        std::cout << "bad player selected!";
        exit(1);
    }
}

void
q3arena(int p1, int p2, int rep) {
    Player *m1 = int2player(p1);
    Player *m2 = int2player(p2);

    RTYPE res1 = Referee::multiRun(m1, m2, rep);
    RTYPE res2 = Referee::multiRun(m2, m1, rep);
    RTYPE ressum = (double)(res1 + rep - res2) / (2. * (double)rep);
    std::cout << p1 << " " << p2 << " " << ressum << "\n";
    
    delete m1;
    delete m2;
}

void
showcase(int i) {
    Board b;
    b.initNum(i, 0);
    b.print();
}

int
main(INT32 argc, char **argv) {
    initRandWithTime();
    //testUnitHashMap();
    //testBoard();
    //benchmarkMove();
    //benchmarkDepth();
    //testProbDrift(str2int(argv[1]), str2int(argv[2]), str2int(argv[3]));
    //althoeferProposal(str2int(argv[1]));
    //testSucc();
    //benchmarkRand();
    //testPlayer();
    //testMrBlack();
    //testReferee();
    //testHashMaps();
    //benchmarkGetNextMove();
    //clash(str2int(argv[1]), str2int(argv[2]));
    //smash(str2int(argv[1]), str2int(argv[2]), str2int(argv[3]));
    //thrash(str2int(argv[1]), str2int(argv[2]));
    //clobber(str2int(argv[1]));
    //dash();
    showcase(str2int(argv[1]));
    //    q3arena(str2int(argv[1]), str2int(argv[2]), str2int(argv[3]));
//     Board *test = BoardFactory::popBoard();
//     test->initNum(405, 338);
//     test->print();

}
