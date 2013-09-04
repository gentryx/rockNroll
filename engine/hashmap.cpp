/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/hashmap.cpp                                         *
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
 *   see /rockNroll/engine/hashmap.h                                       *
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
 *   2005-01-27-13-26-00 (by gentryx)                                      *
 *     * introduced certification format                                   *
 *                                                                         *
 ***************************************************************************/


#include <hashmap.h>

UINT32 HashMap::population = 0;

HashMap::HashMap(UINT32 _numEntries) {
    population++;
    if (population > MAXPOPULATION) {
        std::cout << "HashMap exceeded MAXPOPULATION!\n";
    }

    numEntries = _numEntries;
    entries = new HashEntry[numEntries];
    for (UINT32 i = 0; i < numEntries; i++) {
        entries[i].remDepth = 0;
    }
}


HashMap::~HashMap() {
    population--;
    //    delete entries;    
}

// UINT32
// HashMap::hashModuloLong(UINT8 *id) {
//     UINT32 tkey = 0;    
//     for (INT32 i = 0; i < ID_LEN; i++) {
//         tkey = (tkey * 256 + (id[i] ^ randBits[i])) % numEntries;
//     }     
//     return tkey;    
// }


// INLINEFUNCS
// UINT32
// HashMap::hashModuloFast(UINT8 *id) {
//     UINT32 *idB = (UINT32 *)id;
//     UINT32 *raB = (UINT32 *)randBits;
//     UINT32 ret = ((idB[0] ^ raB[0]) + (idB[1] ^ raB[1]) + (idB[2] ^ raB[2])) % numEntries;
//     return ret;
// }


// INLINEFUNCS
// UINT32
// HashMap::hashModuloFastVariant1(UINT8 *id) {
//     UINT32 *idB = (UINT32 *)id;
//     UINT32 *raB = (UINT32 *)randBits;
//     UINT32 ret = ((idB[0] ^ raB[0]) % numEntries + (idB[1] ^ raB[1]) % numEntries + (idB[2] ^ raB[2]) % numEntries) % numEntries;
//     return ret;
// }


INLINEFUNCS 
UINT32 
HashMap::getNumEntries() {
    return numEntries;
}

INLINEFUNCS 
void 
//HashMap::insert(UINT32 key, UINT8 *id, RTYPE rating, UINT8 stepping, UINT8 remDepth, UINT32 _hashKeyRed, UINT32 _hashKeyBlu) {
HashMap::insert(UINT32 key, HashEntry entry) {

    /*    HashEntry *currEntry = &entries[key];
    for (INT32 i = 0; i < ID_LEN; i++) {
        currEntry->id[i] = id[i];       
    }
    currEntry->rating = rating;
    currEntry->stepping = stepping;
    currEntry->remDepth = 110; //remDepth;
    currEntry->hashKeyRed = _hashKeyRed;
    currEntry->hashKeyBlu = _hashKeyBlu;*/

    UINT32 realKey = key % getNumEntries();
    entries[realKey] = entry;

//     lmap[entry.id] = entry;
}


INLINEFUNCS 
HashEntry*
HashMap::search(UINT32 key) {
    UINT32 realKey = key % getNumEntries();
    return &entries[realKey];
}


    
INLINEFUNCS 
HashEntry*
HashMap::search(UINT32 key, ID_TYPE id) {
//     HashEntry *currEntry = &entries[key];

//     INT32 *idA = (INT32*)id;
//     INT32 *idB = (INT32*)currEntry->id;

//     for (INT32 i = 0; i < ID_LEN/4; i++) {
//         if (idA[i] != idB[i]) {
//             return 0;
//         }
//     }
//     return currEntry;


//     LittleMap::iterator place = lmap.find(id);
//     if (place == lmap.end()) {
//         return 0;
//     } else {
//         return &(*place).second;
//     }

    UINT32 realKey = key % getNumEntries();
    if (entries[realKey].id != id) {
        return 0;
    } else {
        return &entries[realKey];
    }
}


INLINEFUNCS 
void
HashMap::setSteppings(INT32 s) {
    for (UINT32 i = 0; i < numEntries; i++) {
//         for (LittleMap::iterator iter = entries[i].begin(); iter != entries[i].end(); iter++) {
//             (*iter).second.stepping = s;
//         }
        entries[i].stepping = s;
    }
}



