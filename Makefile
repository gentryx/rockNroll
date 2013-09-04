#***************************************************************************
#*   Copyright (C) 2004,2005 by Andreas Schäfer                            *
#*   gentryx@gmx.de                                                        *
#*                                                                         *
#*                                                                         *
#*   rockNroll/Makefile                                                    *
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
#*   The main Makefile for the rockNroll project                           *
#*                                                                         *
#*                                                                         *
#*   Notes:                                                                *
#*                                                                         *
#*   -                                                                     *
#*                                                                         *
#***************************************************************************/

####### Compiler, tools and options

ifeq ($(BUILD_ROOT),)
BUILD_ROOT = .
endif

#CC       = gcc
CXX      = g++
#LEX      = flex
#YACC     = yacc
#CFLAGS   = -pipe -Wall -W -O2 -march=athlon-xp -pipe -DQT_THREAD_SUPPORT -DQT_NO_DEBUG
CXXFLAGS = -c -pipe -Wall -W          -O2 -march=athlon-xp -pipe -fkeep-inline-functions -DQT_THREAD_SUPPORT -DQT_NO_DEBUG -DQT_CLEAN_NAMESPACE
#CXXFLAGS =   -pipe -Wall -W -Winline -O2 -march=athlon-xp -pipe -fkeep-inline-functions -DQT_THREAD_SUPPORT -DQT_NO_DEBUG -DQT_CLEAN_NAMESPACE 
#LEXFLAGS = 
#YACCFLAGS= -d
INCPATH  = -I/usr/qt/3/mkspecs/linux-g++ -I$(QTDIR)/include
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS)
#LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -L/usr/X11R6/lib -lqt -lXext -lX11 -lm
#AR       = ar cqs
#RANLIB   = 
#MOC      = $(QTDIR)/bin/moc
#UIC      = $(QTDIR)/bin/uic
#QMAKE    = qmake
#TAR      = tar -cf
#GZIP     = gzip -9f
#COPY     = cp -f
#COPY_FILE= $(COPY)
#COPY_DIR = $(COPY) -r
#INSTALL_FILE= $(COPY_FILE)
#INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
#SYMLINK  = ln -sf
#DEL_DIR  = rmdir
#MOVE     = mv -f
#CHK_DIR_EXISTS= test -d
#MKDIR    = mkdir -p
CXXCOMMAND = $(BUILD_ROOT)/cxxtest/cxxtestgen.pl


SUBDIRS  := engine

#.cpp.o:

#CXXCOMPILE = $(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

#CXXFLAGS := $(CXXFLAGS) -pg
#LFLAGS   := $(LFLAGS)   -pg

first: all

BUILD_PATH = $(BUILD_ROOT)/engine
include $(BUILD_ROOT)/engine/Makefile
BUILD_PATH = $(BUILD_ROOT)/testsuites
include $(BUILD_ROOT)/testsuites/Makefile
BUILD_PATH = $(BUILD_ROOT)/shellinterface
include $(BUILD_ROOT)/shellinterface/Makefile

all: $(TARGETS)

clean:
	@$(foreach file,$(CLEAN_FILES), echo $(DEL_FILE) $(file) ; $(DEL_FILE) $(file) ; )

#rockNroll:
#	@$(foreach file,$(SUBDIRS), echo Making Subdirectory $(file); $(include $(file)/Makefile))

####### Output directory

#OBJECTS_DIR = .obj/

####### Files

#HEADERS = qrreferee.h \
# 		qrplayer.h \
# 		qrboard.h \
