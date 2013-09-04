/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/referee.h                                           *
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
 *   see engine/referee.h                                                  *
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
 *   2005-01-27-13-15-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/

#include <referee.h>


INLINEFUNCS
INT32
Referee::multiRun(Player *red, Player *blu, INT32 num,           PROBTYPE _probs[STONES]) {
    INT32 redWin = 0;
    Board *s = BoardFactory::popBoard();
    RandGen randGen(_probs);

    for (INT32 i = 0; i < num; i++) {
        s->initRand();
        if (run(&randGen, red, blu, s)) {
            redWin++;
        }
    }

    BoardFactory::pushBoard(s);
    return redWin;
}


INLINEFUNCS
INT32
Referee::multiRun(Player *red, Player *blu, INT32 num, Board *s, PROBTYPE _probs[STONES]) {
    INT32 redWin = 0;
    RandGen randGen(_probs);

    for (INT32 i = 0; i < num; i++) {
        if (run(&randGen, red, blu, s)) {
            redWin++;
        }
    }

    return redWin;
}


INLINEFUNCS
bool
Referee::run(RandGen *randGen, Player *red, Player *blu, Board *s) {
    Player *players[2];
    players[0] = red;
    players[1] = blu;

    INT32 activePlayer = 0;

    Board *board1 = s;
    Board *board2;

#ifdef DEBUG
    board1->print();
#endif

    while (!board1->winAny()) {
        INT32 dice = randGen->getDiceVal();

        board2 = players[activePlayer]->getNextMove(board1, dice);

        if (board1 != s) {
            BoardFactory::pushBoard(board1);
        }

        board1 = board2;
	
        if (activePlayer == 0) {
            activePlayer = 1;
        } else {
            activePlayer = 0;
        }
    }    
    BoardFactory::pushBoard(board1);
    
    return activePlayer == 1;
}

