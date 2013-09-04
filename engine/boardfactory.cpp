/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/boardfactory.h                                      *
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
 *   see boardfactory.h                                                    *
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
 *   2005-01-27-12-59-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/


INT32 BoardFactory::boardStackIndex = -1;
Board *BoardFactory::boardStack[BOARDSTACKSIZE];

INLINEFUNCS 
Board*
BoardFactory::popBoard() {
    if (boardStackIndex >= 0) {
	return boardStack[boardStackIndex--];
    } else {
	return new Board();
    }
}

INLINEFUNCS 
void
BoardFactory::pushBoard(Board *b) {
    if (b != 0) {
	boardStack[++boardStackIndex] = b;
	if (boardStackIndex == BOARDSTACKSIZE) {
	    std::cout << "\nboardStackOverflow!\n";
	    exit(1);
	}	
    } else {
        //	 DEBUGOUT("Warning: Trying to give back an empty board!\n");
    }
}

