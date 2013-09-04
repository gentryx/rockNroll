#***************************************************************************
#*   Copyright (C) 2004,2005 by Andreas Schäfer                            *
#*   gentryx@gmx.de                                                        *
#*                                                                         *
#*                                                                         *
#*   rockNroll/testsuites/Makefile                                         *
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
#*   TestSuite Makefile, compiles and runs our UnitTests.                  *
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

INCPATH := $(INCPATH) -I$(BUILD_PATH) -I$(BUILD_ROOT)


TESTSUITE   = engine.h
CXXTESTS    = .engine.cpp
TEST_OBJECT = engine.o
TESTBINARY  = engine

TESTSUITE   := $(addprefix $(BUILD_PATH)/, $(TESTSUITE))
CXXTESTS    := $(addprefix $(BUILD_PATH)/, $(CXXTESTS))
TEST_OBJECT := $(addprefix $(BUILD_PATH)/, $(TEST_OBJECT))
TESTBINARY  := $(addprefix $(BUILD_PATH)/, $(TESTBINARY))


TARGETS     := $(TARGETS) $(TESTBINARY) runtests
CLEAN_FILES := $(CLEAN_FILES) $(CXXTESTS) $(TEST_OBJECT) $(TESTBINARY)

$(CXXTESTS): $(TESTSUITE)
	$(CXXCOMMAND) -o $(CXXTESTS) --error-printer $(TESTSUITE) 

$(TEST_OBJECT): $(CXXTESTS) $(ENGINE_SOURCES)
	$(CXX) $(CXXFLAGS) $(INCPATH) -o $@ $<

$(TESTBINARY): $(TEST_OBJECT)
	$(LINK) $(LFLAGS) $(LIBS) -o $@ $<

runtests: $(TESTBINARY)
	@echo running unit tests...
#	@$(TESTBINARY)

endif
