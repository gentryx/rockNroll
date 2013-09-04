#***************************************************************************
#*   Copyright (C) 2004,2005 by Andreas Schäfer                            *
#*   gentryx@gmx.de                                                        *
#*                                                                         *
#*                                                                         *
#*   rockNroll/shellInterface/Makefile                                     *
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
#*   Makefile for the shellInterface                                       *
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

MAIN_SRC = main.cpp
MAIN_OBJ = main.o
MAIN_EXE = rockNroll

SHOWBOARD_SRC = showboard.cpp
SHOWBOARD_OBJ = showboard.o
SHOWBOARD_EXE = showboard

TOURNAMENT_SRC = tournament.cpp
TOURNAMENT_OBJ = tournament.o
TOURNAMENT_EXE = tournament

MAIN_SRC := $(addprefix $(BUILD_PATH)/, $(MAIN_SRC))
MAIN_OBJ := $(addprefix $(BUILD_PATH)/, $(MAIN_OBJ))
MAIN_EXE := $(addprefix $(BUILD_PATH)/, $(MAIN_EXE))

SHOWBOARD_SRC := $(addprefix $(BUILD_PATH)/, $(SHOWBOARD_SRC))
SHOWBOARD_OBJ := $(addprefix $(BUILD_PATH)/, $(SHOWBOARD_OBJ))
SHOWBOARD_EXE := $(addprefix $(BUILD_PATH)/, $(SHOWBOARD_EXE))

TOURNAMENT_SRC := $(addprefix $(BUILD_PATH)/, $(TOURNAMENT_SRC))
TOURNAMENT_OBJ := $(addprefix $(BUILD_PATH)/, $(TOURNAMENT_OBJ))
TOURNAMENT_EXE := $(addprefix $(BUILD_PATH)/, $(TOURNAMENT_EXE))

TARGETS := $(TARGETS) $(MAIN_EXE) $(SHOWBOARD_EXE) $(TOURNAMENT_EXE)
CLEAN_FILES := $(CLEAN_FILES) $(MAIN_OBJ) $(MAIN_EXE) $(SHOWBOARD_OBJ) $(SHOWBOARD_EXE) $(TOURNAMENT_OBJ) $(TOURNAMENT_EXE)
INCPATH := $(INCPATH) -I$(BUILD_PATH) -I$(BUILD_ROOT)


$(MAIN_OBJ): $(MAIN_SRC) $(ENGINE_SOURCES)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ $<

$(MAIN_EXE): $(MAIN_OBJ)
	$(LINK) $(LFLAGS) $(LIBS) -o $@ $<

$(SHOWBOARD_OBJ): $(SHOWBOARD_SRC) $(ENGINE_SOURCES)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ $<

$(SHOWBOARD_EXE): $(SHOWBOARD_OBJ)
	$(LINK) $(LFLAGS) $(LIBS) -o $@ $<

$(TOURNAMENT_OBJ): $(TOURNAMENT_SRC) $(ENGINE_SOURCES)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ $<

$(TOURNAMENT_EXE): $(TOURNAMENT_OBJ)
	$(LINK) $(LFLAGS) $(LIBS) -o $@ $<

endif
