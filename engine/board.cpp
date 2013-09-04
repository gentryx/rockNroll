/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/board.cpp                                           *
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
 *   see board.h                                                           *
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
 *   2005-01-27-12-39-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/


#include <iostream>
#include <iterator>
#include <stack>
#include <algorithm>        
#include <cstdlib>
#include <algorithm>
#include <fstream>

#include <board.h>
#include <boardfactory.h>

//STATIC DATA:
INT8 Board::SuccData[4096][20][2];
INT8 Board::ConstellationData [6][3][6][3][8][2];
INT8 *Board::SuccDiceData[4096][6];
INT8 Board::Positions[720][8];
UINT32 Board::HashWords[2 * STONES][SIZEX*SIZEY-1];
bool Board::staticsInited = false;
UINT32 Board::population = 0;


//STATIC FUNCTIONS:
INLINEFUNCS
void
Board::initStatics() {
    //std::cout << "Board::initStatics()\n";

    initSuccData();
    initSuccDiceData();
    initPositions();
    initHashWords();

    staticsInited = true;
}


INLINEFUNCS 
void 
Board::initHashWords() {
    //std::cout << "Board::initHashWords() " << ID_LEN << "\n";
    for (INT32 i = 0; i < 2*STONES; i++) {
        for (INT32 j = 0; j < SIZEX*SIZEY-1; j++) {
            HashWords[i][j] = RandGen::genRandUInt32();
        }
    }
    /*    std::ifstream randFile("/home/gentryx/temp.raw");
    for (INT32 i = 0; i < 2*STONES; i++) {
        //        std::cout << i << ":\n";
        for (INT32 j = 0; j < SIZEX*SIZEY-1; j++) {
            UINT32 val = 0;
            UINT8 buf;
            buf = randFile.get();
            val = 256 * val + buf;
            buf = randFile.get();
            val = 256 * val + buf;
            buf = randFile.get();
            val = 256 * val + buf;
            buf = randFile.get();
            val = 256 * val + buf;
            
            HashWords[i][j] = val;
            //            std::cout << " " << HashWords[i][j];
        }
        //        std::cout << "\n";
        }    */
}


INLINEFUNCS 
void
Board::initSuccData() {
    for (INT32 i = 0; i < 4096; i++) {
	INT32 sIndex = 0;
	for (INT32 j = 0; j < STONES; j++) {
	    INT32 mType = (i >> (2*j)) & 3;
	    switch (mType) {
		case 0:
		    SuccData[i][sIndex][0] = j;
		    SuccData[i][sIndex][1] = SOUTH;
		    sIndex++;
		    SuccData[i][sIndex][0] = j;
		    SuccData[i][sIndex][1] = EAST;
		    sIndex++;
		    SuccData[i][sIndex][0] = j;
		    SuccData[i][sIndex][1] = SOUTH_EAST;
		    sIndex++;
		    break;
		case 1:
		    SuccData[i][sIndex][0] = j;
		    SuccData[i][sIndex][1] = SOUTH;
		    sIndex++;
		    break;
		case 2:
		    SuccData[i][sIndex][0] = j;
		    SuccData[i][sIndex][1] = EAST;
		    sIndex++;
		    break;
		case 3:		
		    break;
		default:
		    std::cout << "initSuccData error\n";
		    exit(1);
		    break;
	    }
	}
	SuccData[i][18][0] = sIndex-1;
    }
}


INLINEFUNCS
void
Board::doEntry(INT32 w1, INT32 w2, INT32 w3, INT32 w4, INT32 move, INT32 piece, INT32 *conIndex) {
    switch (move) {
	case 0:
	    //all moves possible:
	    ConstellationData[w1][w2][w3][w4][*conIndex][0] = piece;
	    ConstellationData[w1][w2][w3][w4][*conIndex][1] = SOUTH;
	    (*conIndex)++;
	    ConstellationData[w1][w2][w3][w4][*conIndex][0] = piece;
	    ConstellationData[w1][w2][w3][w4][*conIndex][1] = EAST;
	    (*conIndex)++;
	    ConstellationData[w1][w2][w3][w4][*conIndex][0] = piece;
	    ConstellationData[w1][w2][w3][w4][*conIndex][1] = SOUTH_EAST;
	    (*conIndex)++;
	    break;
	case 1:
	    //on the right border - SOUTH only:
	    ConstellationData[w1][w2][w3][w4][*conIndex][0] = piece;
	    ConstellationData[w1][w2][w3][w4][*conIndex][1] = SOUTH;
	    (*conIndex)++;
	    break;
	case 2:
	    //on the lower border - EAST only:
	    ConstellationData[w1][w2][w3][w4][*conIndex][0] = piece;
	    ConstellationData[w1][w2][w3][w4][*conIndex][1] = EAST;
	    (*conIndex)++;
	    break;
    }
}


INLINEFUNCS
INT32 
Board::getINibble(INT32 x, INT32 i) {
    return ((x >> (i*2)) & 3);
}


INLINEFUNCS
void 
Board::initSuccDiceData() {
    //1) ConstellationData 
    for (INT32 a = 0; a < 6; a++) {
	for (INT32 ma = 0; ma < 3; ma++) {
	    for (INT32 b = 0; b < 6; b++) {
		for (INT32 mb = 0; mb < 3; mb++) {
		    INT32 conIndex = 0;
		    doEntry(a, ma, b, mb, ma, a, &conIndex);
		    if (b <= a) {
			//if b <= a then consider this as a single piece move. therefore do nothing
		    } else {
			doEntry(a, ma, b, mb, mb, b, &conIndex);
		    }
		    ConstellationData[a][ma][b][mb][6][0] = conIndex-1;
		}	
	    }
	}	
    }
    

    //2) SuccDiceData
    //do not run until 4095, cause this would imply that there were no stones left...
    for (INT32 i = 0; i < 4096-1; i++) {
	for (INT32 j = 0; j < 6; j++) {
	    if  (getINibble(i, j) == 3) {
		//we have the choice, if piece j is killed
		INT32 scanDown = j;
		INT32 scanUp = j;
		while ((scanDown >= 0) && (getINibble(i, scanDown) == 3)) {
		    scanDown--;
		}
		while ((scanUp < STONES) && (getINibble(i, scanUp) == 3)) {
		    scanUp++;
		}

		if (scanDown < 0) {
		    //if scanDown exceeded its limits, scanUp must have found sth. - unless no stones are on the board, what must not occur.
		    SuccDiceData[i][j] = ConstellationData[scanUp][getINibble(i, scanUp)][0][0][0];
		} else {
		    if (scanUp >= STONES) {
			SuccDiceData[i][j] = ConstellationData[scanDown][getINibble(i, scanDown)][0][0][0];			
		    } else {
			SuccDiceData[i][j] = ConstellationData[scanDown][getINibble(i, scanDown)][scanUp][getINibble(i, scanUp)][0];			
		    }
		}

	    } else {
		SuccDiceData[i][j] = ConstellationData[j][getINibble(i, j)][0][0][0];
	    }
	}
    }
}


INLINEFUNCS
void
Board::initPositions() {
#include <initpos.cpp>
}


//NON-STATIC FUNCTIONS


Board::Board() {
    population++;
    if (population > MAXPOPULATION) {
        std::cout << "Board exceeded MAXPOPULATION!\n";
    }

    if (!staticsInited) {
        initStatics();
    }

    initTrivial();
}


Board::~Board() {
    population--;
}


bool 
Board::operator==(Board& other) {
    for (int i = 0; i < STONES; i++) {
        if ((posRed[i] != other.posRed[i]) || (posBlu[i] != other.posBlu[i])) {            
            std::cout << "uneq. pos\n";
            return false;
        }
    }

    for (int i = 0; i < SIZEX*SIZEY; i++) {
        if ((fieldRed[i] != other.fieldRed[i]) || (fieldBlu[i] != other.fieldBlu[i])) {
            std::cout << "uneq. field\n";
            return false;
        }
    }

    if (movesRed != other.movesRed) {
        std::cout << "uneq. movesRed\n";
        return false;
    }

    if (movesBlu != other.movesBlu) {
        std::cout << "uneq. movesBlu\n";
        return false;
    }

    if (hashKeyRed != other.hashKeyRed) {
        std::cout << "uneq. hashKeyRed\n";
        std::cout << "  this: " << hashKeyRed << "\n";
        std::cout << "  othr: " << other.hashKeyRed << "\n";
        return false;
    }

    if (hashKeyBlu != other.hashKeyBlu) {
        std::cout << "uneq. hashKeyBlu\n";
        std::cout << "  this: " << hashKeyBlu << "\n";
        std::cout << "  othr: " << other.hashKeyBlu << "\n";
        return false;
    }

    if (isWinRed != other.isWinRed) {
        std::cout << "uneq. isWinRed\n";
        return false;
    }

    if (isWinBlu != other.isWinBlu) {
        std::cout << "uneq. isWinBlu\n";
        return false;
    }

    if (isWinAny != other.isWinAny) {
        std::cout << "uneq. isWinAny\n";
        return false;
    }

    return true;
}


INLINEFUNCS 
INT8*
Board::getPosRed() {
    return posRed;
}


INLINEFUNCS 
INT8*
Board::getPosBlu() {
    return posBlu;
}


INLINEFUNCS 
UINT32 
Board::getHashKey() {
    return hashKeyRed;
}

INT32 getFlag(int pos, int stone) {
    INT32 flag = 0;
    switch (pos) {
    case OFF_BOARD:
        flag = 3;            
        break;
    case 1*SIZEX-1:
    case 2*SIZEX-1:
    case 3*SIZEX-1:
    case 4*SIZEX-1:
        flag = 1;
        break;
    case SIZEX*SIZEY-5:
    case SIZEX*SIZEY-4:
    case SIZEX*SIZEY-3:
    case SIZEX*SIZEY-2:
        flag = 2;
        break;
    default:
	    break;
    }
//     std::cout << "getFlag(" << pos << ", " << stone << ") = " << flag << "\n";
    return flag << (2*stone);
}

bool allKilled(INT8 pos[STONES]) {
    bool allKill = 1;
    for (int i = 0; i < STONES; i++) {
        if (pos[i] != OFF_BOARD) {
            allKill = 0;
            break;
        } 
    }
    return allKill;
}

bool oneOnGoal(INT8 pos[STONES]) {
    bool goal = 0;
    for (int i = 0; i < STONES; i++) {
        if (pos[i] == GOAL) {
            goal = 1;
            break;
        } 
    }
    return goal;    
}


INLINEFUNCS 
void 
Board::initPos(INT8 _posRed[STONES], INT8 _posBlu[STONES]) {
    //std::cout << "Board::initPos()\n";
    int i;
    //init pos
    for (i = 0; i < STONES; i++) {
        posRed[i] = _posRed[i];
        posBlu[i] = _posBlu[i];
    }

    //clear field
    for (i = 0; i < SIZEY * SIZEX; i++) {
	fieldRed[i] = fieldBlu[i] = OFF_BOARD;
    }

    //copy pos. to field
    for (i = 0; i < STONES; i++) {
        if (posRed[i] != OFF_BOARD) {
            fieldRed[(INT32)posRed[i]] = i;
        }
        if (posBlu[i] != OFF_BOARD) {
            fieldBlu[(INT32)posBlu[i]] = i;
        }
    }

    //init misc.
    movesRed = movesBlu = 0;
    for (i = 0; i < STONES; i++) {
        movesRed |= getFlag(posRed[i], i);
        movesBlu |= getFlag(posBlu[i], i);
    }

    isWinRed = isWinBlu = 0;
    if (allKilled(posRed) || oneOnGoal(posBlu)) isWinBlu = 1;
    if (allKilled(posBlu) || oneOnGoal(posRed)) isWinRed = 1;    

    isWinAny = isWinRed | isWinBlu;
    
    //init hash
    hashKeyRed = 0;
    hashKeyBlu = 0;
    for (i = 0; i < STONES; i++) {
        if (posRed[i] != OFF_BOARD) {
            hashKeyRed ^= HashWords[0      + i][posRed[i]];
            hashKeyBlu ^= HashWords[STONES + i][posRed[i]];
        }
        if (posBlu[i] != OFF_BOARD) {
            hashKeyRed ^= HashWords[STONES + i][posBlu[i]];
            hashKeyBlu ^= HashWords[0      + i][posBlu[i]];
        }
    }

//     print();
}


INLINEFUNCS 
void 
Board::initNum(INT32 redNum, INT32 bluNum) {
    //check for random init.
    if (redNum == -1) {
        redNum = RandGen::genRandUInt32() % 720;
        //init turn symmetric, if  both are random
        if (bluNum == -1) bluNum = redNum;
    } else {
        if (bluNum == -1) bluNum = RandGen::genRandUInt32() % 720;
    }

    initPos(Positions[redNum], Positions[bluNum]);
}


INLINEFUNCS
void
Board::initTrivial() {
    initNum(0, 0);
}


INLINEFUNCS
void 
Board::initRand() {
    initNum(-1, -1);
}


INLINEFUNCS 
bool
Board::winRed() {
    return isWinRed;
}


INLINEFUNCS 
bool
Board::winBlu() {
    return isWinBlu;
}


INLINEFUNCS 
bool
Board::winAny() {
    return isWinAny;
}


INLINEFUNCS
void
Board::printDoubleBits(std::ostream &outs, INT32 bits) {
    for (INT32 i = 0; i < STONES; i++) {
	outs << ((bits >> (i*2)) & 3);
    }
}


void
Board::print(std::ostream &outs) {
    INT32 i;

    outs << "posRed: ";
    for (i = 0; i < STONES; i++) {
	if (posRed[i] == OFF_BOARD) {
	    outs << "  .";
	} else {
	    outs.width(3);
	    outs << (INT32)posRed[i];
	}
    }
    outs << "\n";

    outs << "posBlu: ";
    
    for (i = 0; i < STONES; i++) {
	if (posBlu[i] == OFF_BOARD) {
	    outs << "  .";
	} else {
	    outs.width(3);
	    outs << (INT32)posBlu[i];
	}
    }
    outs << "\n";

    outs << "fieldRed:\n";
    for(i = 0; i < SIZEY; i++) {
	outs << i << " [";
	for(INT32 j = 0; j < SIZEX; j++) {
	    if (fieldRed[i * SIZEX + j] == OFF_BOARD) {
		outs << " .";
	    } else {
		outs << " " << (INT32)fieldRed[i * SIZEX + j];
	    }
	}
	outs << "]\n";
    }

    outs << "fieldBlu:\n";
    for(i = 0; i < SIZEY; i++) {
	outs << i << " [";
	for(INT32 j = 0; j < SIZEX; j++) {
	    if (fieldBlu[i * SIZEX + j] == OFF_BOARD) {
		outs << " .";
	    } else {
		outs << " " << (INT32)fieldBlu[i * SIZEX + j];
	    }
	}
	outs << "]\n";
    }
    outs << "movesRed: ";
    printDoubleBits(outs, movesRed);
    outs << "\n";
    outs << "movesBlu: ";
    printDoubleBits(outs, movesBlu);
    outs << "\n";
    outs << "winRed: " << (winRed()? "1" : "") << "\n";
    outs << "winBlu: " << (winBlu()? "1" : "") << "\n";
    outs << "winAny: " << (winAny()? "1" : "") << "\n";
    outs << '\n';
}


INLINEFUNCS
void
Board::cloneData(Board *ret) {
    INT32 i;
    //clone pos
    INT32 *sr = (INT32*)posRed;
    INT32 *sb = (INT32*)posBlu;
    INT32 *tr = (INT32*)ret->posRed;
    INT32 *tb = (INT32*)ret->posBlu;
    for (i = 0; i < 2; i++) {
	*tr++ = *sb++;
	*tb++ = *sr++;       
    }

    //clone field
    sr = (INT32*)fieldRed;
    sb = (INT32*)fieldBlu;
    tr = (INT32*)ret->fieldRed;
    tb = (INT32*)ret->fieldBlu;
    for (i = 0; i < 7; i++) {
	*tr++ = *sb++;
	*tb++ = *sr++;       
    }
    
    //clone moves
    ret->movesRed = movesBlu;
    ret->movesBlu = movesRed;

    //init win conditions
    ret->isWinRed = 0;
    ret->isWinBlu = 0;
    ret->isWinAny = 0;

    //copy swapped hashPointers & key
    ret->hashKeyRed = hashKeyBlu;
    ret->hashKeyBlu = hashKeyRed;
}


INLINEFUNCS
INT8 
Board::transposeField(INT8 f) {
    return SIZEX*SIZEY - 1 - f;
}


/**
 * 1) get new board from factory
 * 2) clone this board to new one, flip red & blu
 * 3) change blu data
 */
INLINEFUNCS 
Board* 
Board::move(INT8 piece, INT8 dir) {

    Board *ret = BoardFactory::popBoard();

    //todo: do the clone after win-checking?
    cloneData(ret);

    //update posBlu
    INT8 oldField = ret->posBlu[(INT32)piece];
    INT8 njuField = ret->posBlu[(INT32)piece] += dir;

    if (njuField == GOAL) {
	//update win*
	ret->isWinBlu = 1;
	ret->isWinAny = 1;
	return ret;
    }

    //update the hashKeys 1/3
    //has to be done AFTER win-checking to prevent access from goal-field (only 24 fields in hashWords, #25 would be futile)
    ret->hashKeyRed ^= Board::HashWords[piece + STONES][oldField] ^ Board::HashWords[piece + STONES][njuField];
    ret->hashKeyBlu ^= Board::HashWords[piece + 0     ][oldField] ^ Board::HashWords[piece + 0     ][njuField];

    //update movesBlu
    switch (njuField) {
	case 1*SIZEX-1:
	case 2*SIZEX-1:
	case 3*SIZEX-1:
	case 4*SIZEX-1:
	    ret->movesBlu |= (1 << (2*piece));
	    break;
	case SIZEX*SIZEY-5:
	case SIZEX*SIZEY-4:
	case SIZEX*SIZEY-3:
	case SIZEX*SIZEY-2:
	    ret->movesBlu |= (2 << (2*piece));
	    break;
	default:
	    break;
    }


    //update fieldBlu
    ret->fieldBlu[(INT32)oldField] = OFF_BOARD;
    //check for killed blu ones
    INT8 killedPiece = ret->fieldBlu[(INT32)njuField];
    if (killedPiece != OFF_BOARD) {
        //update the hashKeys 2/3 
        //just remove it!
        ret->hashKeyRed ^= HashWords[killedPiece + STONES][njuField];
        ret->hashKeyBlu ^= HashWords[killedPiece + 0     ][njuField];

	ret->posBlu[(INT32)killedPiece] = OFF_BOARD;
        ret->movesBlu |= 3 << (2*killedPiece);
    }

    ret->fieldBlu[(INT32)njuField] = piece;

    INT8 transPos = transposeField(njuField);
    killedPiece = ret->fieldRed[(INT32)transPos];
    if (killedPiece != OFF_BOARD) {	
        //update the hashKeys 3/3 
        //just remove it!
        ret->hashKeyRed ^= HashWords[killedPiece + 0     ][transPos];
        ret->hashKeyBlu ^= HashWords[killedPiece + STONES][transPos];

	ret->posRed[(INT32)killedPiece] = OFF_BOARD;
	ret->movesRed |= 3 << (2*killedPiece);

	if ((ret->movesRed) == 4095) {
	    //all killed...
	    //update win*
	    ret->isWinBlu = 1;
	    ret->isWinAny = 1;
	    return ret;
	}
	//update fieldBlu
	ret->fieldRed[(INT32)transPos] = OFF_BOARD;	
    }

    return ret;
}


INLINEFUNCS 
void
Board::initGetSucc() {
    remainSuccNum = SuccData[movesRed][18][0];
    remainSucc    = SuccData[movesRed][0];
}


INLINEFUNCS 
void 
Board::initGetSucc(INT32 dice) {
    remainSuccNum = SuccDiceData[movesRed][dice][12];
    remainSucc    = SuccDiceData[movesRed][dice];
}


INLINEFUNCS
Board*
Board::getNextSucc(INT8 *movedPiece, INT8 *movedDir) {
    INT8 piece = remainSucc[remainSuccNum*2 + 0];
    INT8 dir   = remainSucc[remainSuccNum*2 + 1];

    remainSuccNum--;
    *movedPiece = piece;
    *movedDir = dir;
    return move(piece, dir);
}


INLINEFUNCS 
bool
Board::hasNextSucc() {    
    return remainSuccNum >= 0;
}
