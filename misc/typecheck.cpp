/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/misc/typecheck.cpp                                         *
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
 *   This proggy checks whether the type macros defined in globals.h       *
 *   represent the correct bit sizes on this system. Shouln't be too       *
 *   important, unless you port the engine to another platform.            *
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
 *   2005-01-26-20-11-00 (by gentryx)                                      *
 *     * inited                                                            *
 *                                                                         *
 ***************************************************************************/

#include <iostream>

#include <globals.h>


bool
checkTypes() {
    INT8 testInt8 = -0x80;
    if (testInt8 != -0x80) return false;
    testInt8--; 
    if (testInt8 != 0x7F) return false;

    UINT8 testUInt8 = 0x00;
    testUInt8--;
    if (testUInt8 != 0xFF) return false;

    INT32 testInt32 = -0x80000000;
    if (testInt32 !=  -0x80000000) return false;
    testInt32--; 
    if (testInt32 !=   0x7FFFFFFF) return false;

    UINT32 testUInt32 = 0;
    testUInt32--;
    if (testUInt32 !=  0xFFFFFFFF) return false;

    return true;
}

int main() {
    if (checkTypes()) {
        std::cout << "type macros ok\n";
        return 0;
    } else {
        std::cout << "!!! type macros FAILED !!!\n";
        return 1;
    }
}
