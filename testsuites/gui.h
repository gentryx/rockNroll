/***************************************************************************
 *   Copyright (C) 2004,2005 by Andreas Schäfer                            *
 *   gentryx@gmx.de                                                        *
 *                                                                         *
 *                                                                         *
 *   /rockNroll/testsuites/gui.h                                           *
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
 *   This is the UnitTestSuit for the gui module. Tests coverage is quite  *
 *   good (for me).                                                        *
 *                                                                         *
 *   Notes:                                                                *
 *                                                                         *
 *   -                                                                     *
 *                                                                         *
 ***************************************************************************/

#ifndef QRTESTSUITE_H
#define QRTESTSUITE_H

#include <stack>

#include <cxxtest/TestSuite.h>

#include <qapplication.h>
#include <qsize.h>
#include <qmutex.h>
#include <qthread.h>
#include <qdatetime.h>

//abstract -> no tests:
#include <debug.h>
#include <qrdice.h>
#include <qrtestsuite.h>
#include <qrgameeventtype.h>
#include <qrplayer.h>
#include <qrplacement.h>
#include <qrplayerid.h>
#include <qrgameevent.h>
#include <globals.h>

//done:
#include <qrlogger.h>
#include <qrguidice.h> 
#include <qrguiboard.h>
#include <qrtoolbox.h> 

//pending:
#include <qrguiplayer.h>

#include <qrboard.h> //get all succs, get succ-moves (array of piece->pos combos)
#include <qraiplayer.h> //verify, that answered board is a valid successor

//todo:
#include <qrreferee.h>


/**
********************* MOCKUP OBJECTS ******************************************
 */
class MockupEventRecorder {
 private:
    QRGameEvent lastEvent;
 public:
    MockupEventRecorder() : lastEvent(0, INVALID) {};
    virtual ~MockupEventRecorder() {};

    virtual void gameEvent(QRGameEvent e);
    virtual QRGameEvent getLastEvent();
    virtual void resetEvent();
};

void 
MockupEventRecorder::gameEvent(QRGameEvent e) {
    lastEvent = e;
}

QRGameEvent 
MockupEventRecorder::getLastEvent() {
    return lastEvent;
}

void
MockupEventRecorder::resetEvent() {
    lastEvent = QRGameEvent(0, INVALID);
}

class MockupPlayer : public QRPlayer, public MockupEventRecorder {
 public:
    virtual void gameEvent(QRGameEvent e) {
        MockupEventRecorder::gameEvent(e);
    }    
};

class MockupDice : public QRDice, public MockupEventRecorder {
    int lastSelected;
 public:
    MockupDice() : QRDice(false) {};

    virtual void gameEvent(QRGameEvent e) {
        MockupEventRecorder::gameEvent(e);
    }    

    virtual void selectNumber(int i) {
        lastSelected = i;
    };     
};

class MockupReferee : public QRReferee, public MockupEventRecorder {
 public:
    MockupReferee() : QRReferee(new MockupPlayer(), new MockupPlayer(), new MockupDice(), NORMAL, RED) {}

    virtual void gameEvent(QRGameEvent e) {
        MockupEventRecorder::gameEvent(e);
    }    
};

/**
********************* TESTSUITES **********************************************
 */

class QRGUIDiceTestSuite : public CxxTest::TestSuite {
    QRGUIDice *d;
    MockupReferee *r;  
    static QApplication *app;
    static QMutex *mutex;
 public:
    void setUp() {
        int temp1 = 0;
        char **temp2 = 0;
        app = new QApplication(temp1, temp2);

        r = new MockupReferee();

        d = new QRGUIDice(0, 0, true);
        d->setGeometry(100, 100, 600, 100);
        d->setReferee(r);
        app->setMainWidget(d);
        d->show();

        mutex = new QMutex();

        TS_ASSERT_EQUALS(d->getReferee(), r);
        TS_ASSERT_EQUALS(d->getAutoMode(), true);
    }

    void tearDown() {
        delete r;
        delete d;
        delete app;
        delete mutex;
    }

    void ensureNoReaction(QRGameEventType t) {
        d->gameEvent(QRGameEvent(r, t));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);
    }

    void ensureReaction() {
        r->resetEvent();
        d->gameEvent(QRGameEvent(r, MAKEDICE));
        QRGameEvent e = r->getLastEvent();
        TS_ASSERT_EQUALS(e.getType(), MADEDICE);
        TS_ASSERT(e.getAux() >= 1 && e.getAux() <= 6);
    }

    static void executeApp() {
        mutex->lock();
        app->exec();
        mutex->unlock();
    }


    void testResize() {
        int mspan = 30;
        QTime measure;
        measure.start();
        concurrentExecute(executeApp);
        msleep(mspan);

        app->lock();
        d->resize(300, 50);
        app->unlock();
        msleep(mspan);

        app->lock();
        d->setGeometry(0, 0, 200, 500);
        app->unlock();
        msleep(mspan);

        app->lock();
        d->setGeometry(0, 412, 1200, 200);
        app->unlock();
        msleep(mspan);

        app->lock();
        d->setGeometry(0, 462, 1200, 100);
        app->unlock();

        app->quit();

        mutex->lock();
        mutex->unlock();
        //DEBUGMEDIUM("app finished..." << measure.elapsed());
    }


    void testAutoMode() {
        ensureNoReaction(SHOWBOARD);
        ensureNoReaction(MAKEPLACEMENT);
        ensureNoReaction(MAKEARBITRARYPLACEMENT);
        ensureNoReaction(MAKEMOVE);
        ensureNoReaction(PAUSED);
        ensureNoReaction(CONFIRMBACK);
        ensureNoReaction(CONFIRMFRWD);
        ensureNoReaction(MADEPLACEMENT);
        ensureNoReaction(MADEARBITRARYPLACEMENT);
        ensureNoReaction(MADEMOVE);
        ensureNoReaction(MADEDICE);
        ensureNoReaction(GIVEUP);
        ensureNoReaction(FRWD);
        ensureNoReaction(BACK);
        ensureNoReaction(FRWDCONFIRMED);
        ensureNoReaction(BACKCONFIRMED);
        ensureNoReaction(FRWDDENIED);
        ensureNoReaction(BACKDENIED);
        ensureNoReaction(PAUSE);
        ensureNoReaction(CONTINUE);

        for (int i = 0; i < 100; i++) {
        }
    }

    void testManualMode() {
        QSize ns(600, 100);
        d->resize(ns);
        TS_ASSERT_EQUALS(d->size(), ns);

        d->setAutoMode(false);

        ensureNoReaction(SHOWBOARD);
        ensureNoReaction(MAKEPLACEMENT);
        ensureNoReaction(MAKEARBITRARYPLACEMENT);
        ensureNoReaction(MAKEMOVE);
        ensureNoReaction(PAUSED);
        ensureNoReaction(CONFIRMBACK);
        ensureNoReaction(CONFIRMFRWD);
        ensureNoReaction(MADEPLACEMENT);
        ensureNoReaction(MADEARBITRARYPLACEMENT);
        ensureNoReaction(MADEMOVE);
        ensureNoReaction(MADEDICE);
        ensureNoReaction(GIVEUP);
        ensureNoReaction(FRWD);
        ensureNoReaction(BACK);
        ensureNoReaction(FRWDCONFIRMED);
        ensureNoReaction(BACKCONFIRMED);
        ensureNoReaction(FRWDDENIED);
        ensureNoReaction(BACKDENIED);
        ensureNoReaction(PAUSE);
        ensureNoReaction(CONTINUE);    

        //2) should trigger an event when a request is pending. 
        //3) again no effect after the event has been triggered
        QSize s = d->size();
        for (int i = 0; i < s.width(); i += 10) {
            for (int j = 0; j < s.height(); j += 10) {
                QPoint pos(i, j);
                QMouseEvent me(QEvent::MouseButtonRelease, pos, QEvent::LeftButton, Qt::LeftButton);

                //1) clicking shall have no effect when no dice is requested:
                r->resetEvent();
                d->mouseReleaseEvent(&me);
                TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);                                

                //2) MAKEDICE should have no effect in manual mode when no click occured
                d->gameEvent(QRGameEvent(r, MAKEDICE));
                TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);                                
                
                //3) now, after MAKEDICE has been posted and a click has been made, a MADEDICE shall be sent:
                d->mouseReleaseEvent(&me);
                QRGameEvent e = r->getLastEvent();
                TS_ASSERT_EQUALS(e.getType(), MADEDICE);
                TS_ASSERT(e.getAux() >= 0 && e.getAux() <= 5);

                //4) again, clicking shall have no effect anymore ('cause the MAKEDICE has already been satisfied)
                r->resetEvent();
                d->mouseReleaseEvent(&me);
                TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);                                
                
            }
        }

        
    }
};


QApplication *QRGUIDiceTestSuite::app;
QMutex *QRGUIDiceTestSuite::mutex;

class QRBoardTestSuite : public CxxTest::TestSuite {
    QRBoard *b;
 public:    

    void setUp() {
        b = new QRBoard();
    }

    void tearDown() {
        delete b;
    }


    void testStdConstructor() {
        TS_ASSERT_EQUALS(b->getPos(RED, 0), SIZEX * 0 + 0);
        TS_ASSERT_EQUALS(b->getPos(RED, 1), SIZEX * 0 + 1);
        TS_ASSERT_EQUALS(b->getPos(RED, 2), SIZEX * 0 + 2);
        TS_ASSERT_EQUALS(b->getPos(RED, 3), SIZEX * 1 + 0);
        TS_ASSERT_EQUALS(b->getPos(RED, 4), SIZEX * 1 + 1);
        TS_ASSERT_EQUALS(b->getPos(RED, 5), SIZEX * 2 + 0);

        TS_ASSERT_EQUALS(b->getPos(BLU, 0), SIZEX * 5 - 1);
        TS_ASSERT_EQUALS(b->getPos(BLU, 1), SIZEX * 5 - 2);
        TS_ASSERT_EQUALS(b->getPos(BLU, 2), SIZEX * 5 - 3);
        TS_ASSERT_EQUALS(b->getPos(BLU, 3), SIZEX * 4 - 1);
        TS_ASSERT_EQUALS(b->getPos(BLU, 4), SIZEX * 4 - 2);
        TS_ASSERT_EQUALS(b->getPos(BLU, 5), SIZEX * 3 - 1);

        TS_ASSERT_EQUALS(b->getDiceVal(), 0);
        TS_ASSERT_EQUALS(b->getActivePlayer(), RED);
    }


    void testEqOp() {
        QRBoard t1;
        QRBoard t2;
        TS_ASSERT(t1 == t2);
        TS_ASSERT(!(t1 != t2));
        t1.setPos(RED, 0, playerGoal(RED));
        TS_ASSERT(!(t1 == t2));
        TS_ASSERT(t1 != t2);
    }

    void testGetSetPosInt() {
        int njuPos = 4711;
        b->setPos(RED, 0, njuPos);
        TS_ASSERT_EQUALS(b->getPos(RED, 0), njuPos);        
    }

    void testGetSetPosQRPos() {
        QRPos temp(STONES);
        for (unsigned i = 0; i < temp.size(); i++) {
            temp[i] = rand();
        }

        b->setPos(BLU, temp);
        TS_ASSERT_EQUALS(b->getPos(BLU), temp);
    }

    void testGetSetDiceVal() {
        int njuDice = 56;
        b->setDiceVal(njuDice);
        TS_ASSERT_EQUALS(b->getDiceVal(), njuDice);        
    }

    void testGoals() {
        TS_ASSERT_EQUALS(playerGoal(RED), SIZEX*SIZEY-1);
        TS_ASSERT_EQUALS(playerGoal(BLU), 0);
    }

    void testWinPos() {
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(!b->win(BLU));

        b->setPos(RED, 3, playerGoal(RED));
        TS_ASSERT(b->win(RED));
        TS_ASSERT(!b->win(BLU));

        b->setPos(RED, 3, 3);
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(!b->win(BLU));
        
        b->setPos(BLU, 5, playerGoal(BLU));
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(b->win(BLU));

        b->setPos(BLU, 5, 3);
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(!b->win(BLU));       
    }        

    void testWinKillRed() {
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(!b->win(BLU));
        for (int i = 0; i < STONES; i++) {
            b->setPos(RED, i, OFF_BOARD);
        }
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(b->win(BLU));
    }

    void testWinKillBlu() {
        TS_ASSERT(!b->win(RED));
        TS_ASSERT(!b->win(BLU));
        for (int i = 0; i < STONES; i++) {
            b->setPos(BLU, i, OFF_BOARD);
        }
        TS_ASSERT(b->win(RED));
        TS_ASSERT(!b->win(BLU));
    }

};


class QRGameEventTestSuite : public CxxTest::TestSuite {
    MockupPlayer *p;
    QRBoard *b;
 public:
    void setUp() {
        p = new MockupPlayer();
        b = new QRBoard();
        b->setPos(RED, 3, 1*SIZEX + 1);
    }

    void tearDown() {
        delete p;
        delete b;
    }

    void testConstAndGetter() {        
        int newAux = 4711;
        QRGameEventType newType = MAKEDICE;

        QRGameEvent subject(p, newType, *b, newAux);

        TS_ASSERT_EQUALS(subject.getSender(), p);
        TS_ASSERT_EQUALS(subject.getType(), newType);
        TS_ASSERT(subject.getBoard() == *b);
        TS_ASSERT_EQUALS(subject.getAux(), newAux);
    }
};


class QRLoggerTestSuite : public CxxTest::TestSuite {
    QRLogger *l;
    QRBoard b0;
    QRBoard b1;
    QRBoard b2;

 public:
    void setUp() {
        l = new QRLogger();        
        b0 = b1 = b2 = QRBoard();
        b1.setPos(RED, 0, 4);
        b2.setPos(RED, 2, 16);
        TS_ASSERT(b0 != b2);
        TS_ASSERT(b1 != b2);
        TS_ASSERT(b1 != b0);
    }

    void tearDown() {
        delete l;
    }


    void testSetReferee() {
        MockupReferee r;
        TS_ASSERT(l->getReferee() == 0);
        l->setReferee(&r);
        TS_ASSERT(l->getReferee() == &r);        
        l->setReferee(0);
        TS_ASSERT(l->getReferee() == 0);
    }

    void testDirectLogging() {
        l->insertBoard(b0);
        TS_ASSERT(*l->currentBoard() == b0);
        l->insertBoard(b1);
        TS_ASSERT(*l->currentBoard() == b1);
        l->insertBoard(b2);
        TS_ASSERT(*l->currentBoard() == b2);

        TS_ASSERT(*l->prevBoard() == b1);
        TS_ASSERT(*l->nextBoard() == b2);
        TS_ASSERT(*l->prevBoard() == b1);
        TS_ASSERT(*l->prevBoard() == b0);
        TS_ASSERT( l->prevBoard() ==  0);
        TS_ASSERT( l->prevBoard() ==  0);
        TS_ASSERT( l->prevBoard() ==  0);
        TS_ASSERT(*l->nextBoard() == b0);
        TS_ASSERT(*l->nextBoard() == b1);
        
        l->insertBoard(b1);
        TS_ASSERT(*l->currentBoard() == b1);
        TS_ASSERT(*l->prevBoard() == b1);
        
        TS_ASSERT(*l->nextBoard() == b1);
        TS_ASSERT( l->nextBoard() == 0);
        TS_ASSERT( l->nextBoard() == 0);
        TS_ASSERT( l->nextBoard() == 0);
        
        l->insertBoard(b2);
        l->insertBoard(b2);
        
        TS_ASSERT(*l->prevBoard() == b2);
        TS_ASSERT(*l->prevBoard() == b1);
        TS_ASSERT(*l->prevBoard() == b1);
        TS_ASSERT(*l->prevBoard() == b0);
        TS_ASSERT( l->prevBoard() == 0);
        
        l->insertBoard(b1);
        TS_ASSERT(*l->currentBoard() == b1);
        TS_ASSERT( l->nextBoard() == 0);
        TS_ASSERT(*l->prevBoard() == b1);
        TS_ASSERT( l->prevBoard() == 0);       
    }

    void testGameEvents() {
        MockupReferee r;
        l->setReferee(&r);
        l->gameEvent(QRGameEvent(&r, SHOWBOARD, b0, 0));
        l->gameEvent(QRGameEvent(&r, SHOWBOARD, b1, 0));
        l->gameEvent(QRGameEvent(&r, SHOWBOARD, b2, 0));
        l->gameEvent(QRGameEvent(&r, SHOWBOARD, b1, 0));
        TS_ASSERT(*l->currentBoard() == b1);
        TS_ASSERT(*l->prevBoard() == b2);
        TS_ASSERT(*l->prevBoard() == b1);
        TS_ASSERT(*l->prevBoard() == b0);
        l->gameEvent(QRGameEvent(&r, SHOWBOARD, b0, 0));
        TS_ASSERT(*l->currentBoard() == b0);
        TS_ASSERT( l->nextBoard() == 0);
        TS_ASSERT(*l->prevBoard() == b0);
        TS_ASSERT(*l->prevBoard() == b0);
        TS_ASSERT( l->prevBoard() == 0);                     
    }


};

#define NUMSTAMPS 4

class QRToolboxTestSuite : public CxxTest::TestSuite {
    QRBoard *subject1;
    QRBoard *subject2;
 public:
    static uint timeStamps1[NUMSTAMPS];
    static uint timeStamps2[NUMSTAMPS];
    
    static QMutex mutex1;
    static QMutex mutex2;


    static void recorder(uint *stamps, int num) {
        for (int i = 0; i < num; i++) {
            msleep(50);
            //DEBUGMEDIUM("ping");
            QTime temp = QTime::currentTime();
            stamps[i] = (temp.minute() * 60 + temp.second()) * 1000 + temp.msec();
        }
    }

    static void recorder1() {        
        mutex1.lock();
        recorder(timeStamps1, NUMSTAMPS);
        mutex1.unlock();
    }

    static void recorder2() {
        mutex2.lock();
        recorder(timeStamps2, NUMSTAMPS);
        mutex2.unlock();
    }

    void setUp() {
        subject1 = new QRBoard();
        subject2 = new QRBoard();
        subject1->setPos(RED, 3, SIZEX * 0 + 4);
        subject2->setPos(BLU, 2, SIZEX * 2 + 2);
    }

    void tearDown() {
        delete subject1;
        delete subject2;
    }


    void testIsIn() {
        TS_ASSERT( isIn(QPoint(10, 10), QRect(0, 0, 20, 20)));
        TS_ASSERT(!isIn(QPoint(10, 10), QRect(20, 20, 20, 20)));
        TS_ASSERT(!isIn(QPoint(30, 50), QRect(20, 20, 100, 20)));
        TS_ASSERT( isIn(QPoint(30, 30), QRect(20, 20, 100, 20)));
    }

    void testMSleep() {
        QTime t;
        t.start();
        msleep(100);
        int elapsed = t.elapsed();
        TS_ASSERT_DELTA(100, elapsed, 5);
    }

    void testConcurrentExecute() {
        concurrentExecute(&recorder1);
        msleep(250);
        concurrentExecute(&recorder2);

        //wait for the two threads
        mutex1.lock();
        mutex1.unlock();
        mutex2.lock();
        mutex2.unlock();
    }

    void testTransposeField() {
        TS_ASSERT_EQUALS(SIZEX * 0 + 0, transposeField(SIZEX * 4 + 4));
        TS_ASSERT_EQUALS(SIZEX * 1 + 0, transposeField(SIZEX * 3 + 4));
        TS_ASSERT_EQUALS(SIZEX * 0 + 1, transposeField(SIZEX * 4 + 3));
        TS_ASSERT_EQUALS(SIZEX * 2 + 2, transposeField(SIZEX * 2 + 2));
    }

    void testQRSignalRecorder() {
        QRSignalRecorder s;
        QPoint p1(4711, 42);
        QPoint p2(24, 1231);

        s.setPoint(p1);
        TS_ASSERT_EQUALS(s.getPoint(), p1);
        TS_ASSERT_EQUALS(s.x(), p1.x());
        TS_ASSERT_EQUALS(s.y(), p1.y());
        s.selected(p2);
        TS_ASSERT_EQUALS(s.getPoint(), p2);        
    }

    void testPushPopBoard() {
        Board *raw1;
        Board *raw2;

        raw1 = popBoard(*subject1);
        raw2 = popBoard(*subject2);
        QRBoard ret1 = pushBoard(raw1);
        QRBoard ret2 = pushBoard(raw2);
        
        TS_ASSERT_EQUALS(ret1, *subject1);
        TS_ASSERT_EQUALS(ret2, *subject2);
    }

};

uint QRToolboxTestSuite::timeStamps1[NUMSTAMPS];
uint QRToolboxTestSuite::timeStamps2[NUMSTAMPS];
QMutex QRToolboxTestSuite::mutex1;
QMutex QRToolboxTestSuite::mutex2;


class QRGUIBoardTestSuite : public CxxTest::TestSuite {
    QRGUIBoard *b;
    MockupReferee *r;  
    QRSignalRecorder *signalRecorder;
    static QApplication *app;
    static QMutex *mutex;

 public:
    void setUp() {
        int temp1 = 0;
        char **temp2 = 0;
        signalRecorder = new QRSignalRecorder();

        app = new QApplication(temp1, temp2);

        r = new MockupReferee();


        b = new QRGUIBoard(0, 0);
        b->setGeometry(100, 100, 600, 600);
        b->setReferee(r);
        app->setMainWidget(b);
        b->show();

        mutex = new QMutex();

        TS_ASSERT_EQUALS(b->getReferee(), r);
    }

    void tearDown() {
        delete signalRecorder;
        delete r;
        delete b;
        delete app;
        delete mutex;
    }

    static void executeApp() {
        mutex->lock();
        app->exec();
        mutex->unlock();
    }

    

    void testResize() {
        int mspan = 100;
        QTime measure;
        measure.start();
        concurrentExecute(executeApp);
        msleep(mspan);

        QRPointList p;        
        p.append(QPoint(0,1));
        p.append(QPoint(1,1));
        p.append(QPoint(2,1));
        b->enableFields(p);

        for (int i = 0; i < 30; i++) {
            app->lock();
            b->resize(b->width() - 2, b->height());
            app->unlock();
            msleep(2);
        }

        app->lock();
        b->setGeometry(0, 412, 1200, 200);
        app->unlock();
        msleep(mspan);

        app->lock();
        b->setGeometry(0, 462, 1200, 100);
        app->unlock();

        app->quit();

        mutex->lock();
        mutex->unlock();
        //DEBUGMEDIUM("app finished..." << measure.elapsed());
    }


    void testClick() {
        int unmodX = 4711;
        int unmodY = 666;
        signalRecorder->selected(QPoint(unmodX, unmodY));
        TS_ASSERT_EQUALS(signalRecorder->x(), unmodX);
        TS_ASSERT_EQUALS(signalRecorder->y(), unmodY);
        QObject::connect(b, SIGNAL(selected(QPoint)), signalRecorder, SLOT(selected(QPoint)));


        int sx = 250;
        int sy = 450;
        b->setGeometry(100, 100, sx, sy);

        for (int x = 0; x < sx; x += 10) {
            for (int y = 0; y < sy; y += 10) {
                QPoint pos(x, y);
                QMouseEvent me(QEvent::MouseButtonRelease, pos, QEvent::LeftButton, Qt::LeftButton);
                b->mouseReleaseEvent(&me);
                TS_ASSERT_EQUALS(signalRecorder->x(), unmodX);
                TS_ASSERT_EQUALS(signalRecorder->y(), unmodY);
            }
        }
        
        QRPointList l;
        QMouseEvent me(QEvent::MouseButtonRelease, QPoint(0, 0), QEvent::LeftButton, Qt::LeftButton);

        l = QRPointList();
        l.append(QPoint(0, 1));
        l.append(QPoint(1, 1));
        l.append(QPoint(2, 1));
        b->enableFields(l);
        me = QMouseEvent(QEvent::MouseButtonRelease, QPoint(sx*1/10, sy*3/10), QEvent::LeftButton, Qt::LeftButton);
        b->mouseReleaseEvent(&me);
        TS_ASSERT_EQUALS(signalRecorder->x(), 0);

        l = QRPointList();
        l.append(QPoint(0, 1));
        l.append(QPoint(1, 1));
        l.append(QPoint(2, 1));
        b->enableFields(l);
        me = QMouseEvent(QEvent::MouseButtonRelease, QPoint(sx*3/10, sy*3/10), QEvent::LeftButton, Qt::LeftButton);
        b->mouseReleaseEvent(&me);
        TS_ASSERT_EQUALS(signalRecorder->x(), 1);

        l = QRPointList();
        l.append(QPoint(0, 1));
        l.append(QPoint(1, 1));
        l.append(QPoint(2, 1));
        b->enableFields(l);
        me = QMouseEvent(QEvent::MouseButtonRelease, QPoint(sx*5/10, sy*3/10), QEvent::LeftButton, Qt::LeftButton);
        b->mouseReleaseEvent(&me);
        TS_ASSERT_EQUALS(signalRecorder->x(), 2);

        signalRecorder->selected(QPoint(unmodX, unmodY));

        for (int x = 0; x < sx; x += 10) {
            for (int y = 0; y < sy; y += 10) {
                QPoint pos(x, y);
                QMouseEvent me(QEvent::MouseButtonRelease, pos, QEvent::LeftButton, Qt::LeftButton);
                b->mouseReleaseEvent(&me);
                TS_ASSERT_EQUALS(signalRecorder->x(), unmodX);
                TS_ASSERT_EQUALS(signalRecorder->y(), unmodY);
            }
        }        
    }
};


QApplication *QRGUIBoardTestSuite::app;
QMutex *QRGUIBoardTestSuite::mutex;


class QRAIPlayerTestSuite : public CxxTest::TestSuite {    
    MockupReferee *r;
    QRAIPlayer *p;
 public:
    void setUp() {
        p = new QRAIPlayer();
        r = new MockupReferee();
        p->setReferee(r);
    }

    void tearDown() {
        delete p;
        delete r;
    }

    void testNoReaction() {
        p->gameEvent(QRGameEvent(r, SHOWBOARD));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, MAKEARBITRARYPLACEMENT));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, MAKEDICE));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, PAUSED));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, CONFIRMBACK));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, CONFIRMFRWD));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, MADEPLACEMENT));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, MADEARBITRARYPLACEMENT));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, MADEMOVE));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, MADEDICE));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, GIVEUP));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, FRWD));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, BACK));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, FRWDCONFIRMED));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, BACKCONFIRMED));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, FRWDDENIED));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, BACKDENIED));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, PAUSE));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
        p->gameEvent(QRGameEvent(r, CONTINUE));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);    
    }

    void testPlacement() {
        int bestRedPos[STONES] = 
        {
            SIZEX * 1 + 0,
            SIZEX * 1 + 0,
            SIZEX * 1 + 0,
            SIZEX * 1 + 0,
            SIZEX * 1 + 0,
            SIZEX * 1 + 0
        };
        QRBoard queryBoard;
        QRBoard tempBoard;

        queryBoard.setActivePlayer(RED);
        p->gameEvent(QRGameEvent(r, MAKEPLACEMENT, queryBoard));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), MADEPLACEMENT);    
        tempBoard = r->getLastEvent().getBoard();
        for (int i = 0; i < STONES; i++) {
            TS_ASSERT_EQUALS(tempBoard.getPos(RED, i), bestRedPos[i]);
        }

        queryBoard.setActivePlayer(BLU);
        p->gameEvent(QRGameEvent(r, MAKEPLACEMENT, queryBoard));
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), MADEPLACEMENT);    
        tempBoard = r->getLastEvent().getBoard();
        for (int i = 0; i < STONES; i++) {
            TS_ASSERT_EQUALS(tempBoard.getPos(BLU, i), transposeField(bestRedPos[i]));
        }
    }

    void testMakeMove() {
        QRBoard initBoard;

        TS_ASSERT_EQUALS(r->getLastEvent().getType(), INVALID);     
        p->gameEvent(QRGameEvent(r, MAKEMOVE, initBoard));
        msleep(500); 
        TS_ASSERT_EQUALS(r->getLastEvent().getType(), MADEMOVE);     
    }
};


class QRGUIPlayerTestSuite : public CxxTest::TestSuite {
 public:
    void setUp() {
    }

    void tearDown() {
    }

    void testAddition() {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};


class QREmptyTestSuite : public CxxTest::TestSuite {
 public:
    void setUp() {
    }

    void tearDown() {
    }

    void testAddition() {
        TS_ASSERT( 1 + 1 > 1 );
        TS_ASSERT_EQUALS( 1 + 1, 2 );
    }
};



#endif
