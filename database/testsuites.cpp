/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "testsuites.h"

static RecFileSuite suite_RecFileSuite;

static CxxTest::List Tests_RecFileSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RecFileSuite( "testsuites.h", 8, "RecFileSuite", suite_RecFileSuite, Tests_RecFileSuite );

static class TestDescription_RecFileSuite_testPushWriteSize : public CxxTest::RealTestDescription {
public:
 TestDescription_RecFileSuite_testPushWriteSize() : CxxTest::RealTestDescription( Tests_RecFileSuite, suiteDescription_RecFileSuite, 36, "testPushWriteSize" ) {}
 void runTest() { suite_RecFileSuite.testPushWriteSize(); }
} testDescription_RecFileSuite_testPushWriteSize;

static class TestDescription_RecFileSuite_testFileCreation : public CxxTest::RealTestDescription {
public:
 TestDescription_RecFileSuite_testFileCreation() : CxxTest::RealTestDescription( Tests_RecFileSuite, suiteDescription_RecFileSuite, 87, "testFileCreation" ) {}
 void runTest() { suite_RecFileSuite.testFileCreation(); }
} testDescription_RecFileSuite_testFileCreation;

static class TestDescription_RecFileSuite_testBasic : public CxxTest::RealTestDescription {
public:
 TestDescription_RecFileSuite_testBasic() : CxxTest::RealTestDescription( Tests_RecFileSuite, suiteDescription_RecFileSuite, 118, "testBasic" ) {}
 void runTest() { suite_RecFileSuite.testBasic(); }
} testDescription_RecFileSuite_testBasic;

static class TestDescription_RecFileSuite_testReal : public CxxTest::RealTestDescription {
public:
 TestDescription_RecFileSuite_testReal() : CxxTest::RealTestDescription( Tests_RecFileSuite, suiteDescription_RecFileSuite, 150, "testReal" ) {}
 void runTest() { suite_RecFileSuite.testReal(); }
} testDescription_RecFileSuite_testReal;

static BoardTestSuite suite_BoardTestSuite;

static CxxTest::List Tests_BoardTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BoardTestSuite( "testsuites.h", 196, "BoardTestSuite", suite_BoardTestSuite, Tests_BoardTestSuite );

static class TestDescription_BoardTestSuite_testInit : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testInit() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 204, "testInit" ) {}
 void runTest() { suite_BoardTestSuite.testInit(); }
} testDescription_BoardTestSuite_testInit;

static class TestDescription_BoardTestSuite_testInitNum : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testInitNum() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 212, "testInitNum" ) {}
 void runTest() { suite_BoardTestSuite.testInitNum(); }
} testDescription_BoardTestSuite_testInitNum;

static class TestDescription_BoardTestSuite_testBasic : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardTestSuite_testBasic() : CxxTest::RealTestDescription( Tests_BoardTestSuite, suiteDescription_BoardTestSuite, 236, "testBasic" ) {}
 void runTest() { suite_BoardTestSuite.testBasic(); }
} testDescription_BoardTestSuite_testBasic;

static BoardRecTestSuite suite_BoardRecTestSuite;

static CxxTest::List Tests_BoardRecTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_BoardRecTestSuite( "testsuites.h", 288, "BoardRecTestSuite", suite_BoardRecTestSuite, Tests_BoardRecTestSuite );

static class TestDescription_BoardRecTestSuite_testBasic : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testBasic() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 303, "testBasic" ) {}
 void runTest() { suite_BoardRecTestSuite.testBasic(); }
} testDescription_BoardRecTestSuite_testBasic;

static class TestDescription_BoardRecTestSuite_testMultiInsertUnique : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testMultiInsertUnique() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 333, "testMultiInsertUnique" ) {}
 void runTest() { suite_BoardRecTestSuite.testMultiInsertUnique(); }
} testDescription_BoardRecTestSuite_testMultiInsertUnique;

static class TestDescription_BoardRecTestSuite_testMultiInsertWithCollisions : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testMultiInsertWithCollisions() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 402, "testMultiInsertWithCollisions" ) {}
 void runTest() { suite_BoardRecTestSuite.testMultiInsertWithCollisions(); }
} testDescription_BoardRecTestSuite_testMultiInsertWithCollisions;

static class TestDescription_BoardRecTestSuite_testBigBadInsert : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testBigBadInsert() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 482, "testBigBadInsert" ) {}
 void runTest() { suite_BoardRecTestSuite.testBigBadInsert(); }
} testDescription_BoardRecTestSuite_testBigBadInsert;

static class TestDescription_BoardRecTestSuite_testInsertRatings : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testInsertRatings() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 593, "testInsertRatings" ) {}
 void runTest() { suite_BoardRecTestSuite.testInsertRatings(); }
} testDescription_BoardRecTestSuite_testInsertRatings;

static class TestDescription_BoardRecTestSuite_testBigInsertPerformance : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testBigInsertPerformance() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 665, "testBigInsertPerformance" ) {}
 void runTest() { suite_BoardRecTestSuite.testBigInsertPerformance(); }
} testDescription_BoardRecTestSuite_testBigInsertPerformance;

static class TestDescription_BoardRecTestSuite_testSmallInsertPerformance : public CxxTest::RealTestDescription {
public:
 TestDescription_BoardRecTestSuite_testSmallInsertPerformance() : CxxTest::RealTestDescription( Tests_BoardRecTestSuite, suiteDescription_BoardRecTestSuite, 670, "testSmallInsertPerformance" ) {}
 void runTest() { suite_BoardRecTestSuite.testSmallInsertPerformance(); }
} testDescription_BoardRecTestSuite_testSmallInsertPerformance;

static EmptyTestSuite suite_EmptyTestSuite;

static CxxTest::List Tests_EmptyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_EmptyTestSuite( "testsuites.h", 677, "EmptyTestSuite", suite_EmptyTestSuite, Tests_EmptyTestSuite );

static class TestDescription_EmptyTestSuite_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_EmptyTestSuite_testAddition() : CxxTest::RealTestDescription( Tests_EmptyTestSuite, suiteDescription_EmptyTestSuite, 685, "testAddition" ) {}
 void runTest() { suite_EmptyTestSuite.testAddition(); }
} testDescription_EmptyTestSuite_testAddition;

#include <cxxtest/Root.cpp>
