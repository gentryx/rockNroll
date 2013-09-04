/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/hashmap.h                                           *
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
 *   The HashMap prevents the multiple calculation of Boards during the    *
 *   game tree search.                                                     *
 *                                                                         *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef HASHMAP_H
#define HASHMAP_H

#include <globals.h>
#include <board.h>

//#define ID_LEN 8
#define ID_TYPE UINT64

struct HashEntry {
    //    UINT8 id[ID_LEN];
    ID_TYPE id;
    RTYPE rating;
    INT8 stepping;
    INT8 remDepth;        
};

class HashMap {
 private:
    static UINT32 population;

    HashEntry *entries;
    UINT32 numEntries;
 public:
    HashMap(UINT32 _numEntries);
    ~HashMap();

    INLINEFUNCS UINT32 getNumEntries();
    //    INLINEFUNCS void insert(UINT32 key, UINT8 *id, RTYPE rating, UINT8 stepping, UINT8 remDepth, UINT32 _hashKeyRed, UINT32 _hashKeyBlu);
    INLINEFUNCS void insert(UINT32 key, HashEntry entry);
    INLINEFUNCS HashEntry *search(UINT32 key);
    INLINEFUNCS HashEntry *search(UINT32 key, ID_TYPE id);
    INLINEFUNCS void setSteppings(INT32 s);
};

#endif
