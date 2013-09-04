
/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/engine/threadwrapper.cpp                                   *
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
 *   see threadwrapper.h                                                   *
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
 *   2005-01-26-20-27-00 (by gentryx)                                      *
 *     * inited                                                            *
 *                                                                         *
 ***************************************************************************/

#include <threadwrapper.h>

#include <qthread.h>
#include <qptrlist.h>
#include <qmutex.h>

class VanillaExec;
typedef QPtrList<VanillaExec> QRThreadList;

QRThreadList runningThreads;
QRThreadList finishedThreads;
QMutex mutex;


class VanillaExec : public QThread {
private:
    void (*func)();
public:
    VanillaExec(void (*_func)());
    void setFunc(void (*_func)());
    virtual void run();

    static void msleep(uint msec);
};

void
VanillaExec::msleep(uint msec) {
    QThread::msleep(msec);
}

VanillaExec::VanillaExec(void (*_func)()) {
    setFunc(_func);
}


void
VanillaExec::setFunc(void (*_func)()) {
    func = _func;
}


void 
VanillaExec::run() {
    mutex.lock();
    runningThreads.append(this);
    mutex.unlock();

    func();

    mutex.lock();
    runningThreads.remove(this);
    finishedThreads.append(this);
    mutex.unlock();
}

void 
concurrentExecute(void (*func)()) {
    mutex.lock();
       VanillaExec *njuThread = finishedThreads.current();
    if (njuThread != 0) {
        finishedThreads.remove(njuThread);
        njuThread->setFunc(func);
    } else {
        njuThread = new VanillaExec(func);
    }
    mutex.unlock();

    njuThread->start();
}

void
msleep(uint msec) {
    VanillaExec::msleep(msec);
}


