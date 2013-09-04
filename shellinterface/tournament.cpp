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
initRandWithTime() {
    struct timeval tBegin;
    struct timezone tz;
    gettimeofday(&tBegin,&tz);
    srand(tBegin.tv_usec);
    init_genrand(tBegin.tv_usec);
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
        return new MrBlack(4, 1024*1024*2, 1024*1024*2);
    case 12:
        return new FarmerBoy(0, 0, 0);
    case 13:
        return new FarmerBoy(1, 0, 0);
    case 14:
        return new FarmerBoy(2, 0, 0);
    case 15:
        return new FarmerBoy(3, 0, 0);
    case 16:
        return new FarmerBoy(4, 1024*1024*2, 1024*1024*2);
    case 17:
        return new MrMonte(1, 0, 0, 20, new FarmerBoy(1, 0, 0), new FarmerBoy(1, 0, 0));
    case 18:
        return new MrMonte(2, 0, 0, 20, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0));
    case 19:
        return new MrMonte(2, 0, 0, 40, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0));
    case 20:
        return new MrMonte(0, 0, 0, 20, 
                           new MrMonte(0, 0, 0, 10, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0)), 
                           new MrMonte(0, 0, 0, 10, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0))
                           );
    case 21:
        return new MrMonte(0, 0, 0,  50, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0));
    case 22:
        return new MrMonte(0, 0, 0, 100, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0));
    case 23:
        return new MrMonte(0, 0, 0, 150, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0));
    case 24:
        return new MrMonte(0, 0, 0, 200, new FarmerBoy(0, 0, 0), new FarmerBoy(0, 0, 0));
    default:
        std::cout << "bad player selected!";
        exit(1);
    }
}

void
q3arena(int p1, int p2, int rep) {
    Player *m1 = int2player(p1);
    Player *m2 = int2player(p2);
    Board *board = BoardFactory::popBoard();

    int bestBoards[] = {405, 431, 92, 83, 87, 167, 227, 63, 40, 65, 16, 407, 57, 395, 81, 116};
    int boardNum = 16;

    for (int i = 0; i < boardNum; i++) {
        for (int j = 0; j < boardNum; j++) {
            board->initNum(bestBoards[i], bestBoards[j]);
            int gamesWonByM1 = Referee::multiRun(m1, m2, rep, board);

            std::cout << "startPosM1: " << bestBoards[i] << "\n";
            std::cout << "startPosM2: " << bestBoards[j] << "\n";
            std::cout << "playerM1: " << p1 << "\n";
            std::cout << "playerM2: " << p2 << "\n";
            std::cout << "repeats: " << rep << "\n";
            std::cout << "gamesWonByM1: " << gamesWonByM1 << "\n";
            std::cout << "\n";
        }
    }

    delete m1;
    delete m2;
    BoardFactory::pushBoard(board);
}

int
main(INT32 argc, char **argv) {
    initRandWithTime();
    q3arena(str2int(argv[1]), str2int(argv[2]), str2int(argv[3]));
}
