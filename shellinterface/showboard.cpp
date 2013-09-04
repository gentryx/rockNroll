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

void
showBoard(int i) {
    Board b;
    b.initNum(i, 0);
    b.print();
}

int
main(int argc, char **argv) {
    initRandWithTime();
    showBoard(str2int(argv[1]));
}
