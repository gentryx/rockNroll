#***************************************************************************
#*   Copyright (C) 2004,2005 by Andreas Schäfer                            *
#*   gentryx@gmx.de                                                        *
#*                                                                         *
#*                                                                         *
#*   rockNroll/engine/Makefile                                             *
#*                                                                         *
#*                                                                         *
#*   This program is free software; you can redistribute it and/or modify  *
#*   it under the terms of the GNU General Public License as published by  *
#*   the Free Software Foundation; either version 2 of the License, or     *
#*   (at your option) any later version.                                   *
#*                                                                         *
#*   This program is distributed in the hope that it will be useful,       *
#*   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
#*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
#*   GNU General Public License for more details.                          *
#*                                                                         *
#*   You should have received a copy of the GNU General Public License     *
#*   along with this program; if not, write to the                         *
#*   Free Software Foundation, Inc.,                                       *
#*   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
#*                                                                         *
#*                                                                         *
#*   Description:                                                          *
#*                                                                         *
#*   Makefile for the rockNroll engine                                     *
#*                                                                         *
#*                                                                         *
#*   Notes:                                                                *
#*                                                                         *
#*   -                                                                     *
#*                                                                         *
#***************************************************************************/

ifeq ($(BUILD_ROOT),)
BUILD_ROOT=..
include $(BUILD_ROOT)/Makefile
else

ENGINE_SOURCES = \
		compilechain.h \
		globals.h \
		headers.h \
		mersenne.h \
		mersenne.cpp \
		board.h \
		board.cpp \
		boardfactory.h \
		boardfactory.cpp \
		aiplayer.h \
		aiplayer.cpp \
		mrblack.h \
		mrblack.cpp \
		mrmonte.h \
		mrmonte.cpp \
		farmerboy.h \
		farmerboy.cpp \
		referee.h \
		referee.cpp \
		mrrandom.h \
		mrrandom.cpp \
		player.h \
		player.cpp \
		stdinplayer.h \
		stdinplayer.cpp \
		hashmap.h \
		hashmap.cpp

ENGINE_SOURCES := $(addprefix $(BUILD_PATH)/, $(ENGINE_SOURCES))
#ENGINE_OBJECT := $(BUILD_PATH)/engine.o

INCPATH := $(INCPATH) -I$(BUILD_PATH)
#TARGETS := $(TARGETS) $(ENGINE_OBJECT)
#CLEAN_FILES := $(CLEAN_FILES) $(ENGINE_OBJECT)

# $(ENGINE_OBJECT): $(SOURCES)
# 	@echo making engine.o
# 	@pwd
# 	@echo making engine.o
# 	$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ ../engine/compilechain.h

endif
