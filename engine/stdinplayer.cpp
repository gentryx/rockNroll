/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/stdinplayer.cpp                                     *
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
 *   see /rockNroll/engine/stdinplayer.h                                   *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/


#include <iostream>

#include <stdinplayer.h>

StdInPlayer::StdInPlayer(PROBTYPE _probs[STONES]) : Player(_probs) {
}


Board*
StdInPlayer::getNextMove(Board *s, INT32 dice) {
    std::cout << "\nDice: " << dice << "\nYou are here:\n";
    s->print();
    INT32 stone;
    std::cout << "Enter Piece: ";
    std::cin >> stone;
    INT32 dir;
    std::cout << "Enter Direction: ";
    std::cin >> dir;

    return s->move(stone, dir);
}
