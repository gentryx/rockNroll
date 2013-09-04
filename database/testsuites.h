#ifndef QRTESTSUITE_H
#define QRTESTSUITE_H

#include <cxxtest/TestSuite.h>
#include <compileChain.h>


class RecFileSuite : public CxxTest::TestSuite {
 public:
#define TEST_REC_SIZE 8192

    unsigned randChunkShortLength;
    unsigned randChunkLongLength;
    UINT8 *randChunkShort;
    UINT8 *randChunkLong;

    void setUp() {
        randChunkLongLength = TEST_REC_SIZE;
        randChunkLong = new UINT8[randChunkLongLength];
        for (unsigned i = 0; i < randChunkLongLength; i++) {
            randChunkLong[i] = genrand_int32() % 256;
        }

        randChunkShortLength = 30;
        randChunkShort = new UINT8[randChunkShortLength];
        for (unsigned i = 0; i < randChunkShortLength; i++) {
            randChunkShort[i] = genrand_int32() % 256;
        }
    }

    void tearDown() {
        delete randChunkLong;
        delete randChunkShort;
    }

    void testPushWriteSize() {
        char *fileName = "foo.boo3";
        const int dataLen1 = 831;
        const int dataLen2 = 121;
        const int recSize = 1024;
        UINT8 data1[dataLen1];
        UINT8 data2[dataLen2];
        std::fill(data1, data1 + dataLen1, 47);
        std::fill(data2, data2 + dataLen2, 11);

        std::ifstream ifile1(fileName);
        TS_ASSERT(!ifile1);

        RecFile *recFile;

        recFile = new RecFile(fileName, recSize);
        UINT64 filePos = recFile->push(data1, dataLen1);
        delete recFile;

        std::ifstream ifile2(fileName);
        TS_ASSERT(ifile2);
        UINT8 buf[recSize];
        std::fill(buf, buf+recSize, 0);
        ifile2.read((char*)buf, recSize);
        for (int i = 0; i < dataLen1; i++) {
            TS_ASSERT_EQUALS(buf[i], data1[i]);
        }
        for (int i = dataLen1; i < recSize; i++) {
            TS_ASSERT_EQUALS(buf[i], 0);
        }
        ifile2.seekg(0, std::ios_base::end);
        TS_ASSERT_EQUALS((int)ifile2.tellg(), recSize);
        ifile2.close();

        recFile = new RecFile(fileName, recSize);
        recFile->write(filePos, data2, dataLen2);
        delete recFile;

        std::ifstream ifile3(fileName);
        TS_ASSERT(ifile3);
        std::fill(buf, buf+recSize, 0);
        ifile3.read((char*)buf, recSize);
        for (int i = 0; i < dataLen2; i++) {
            TS_ASSERT_EQUALS(buf[i], data2[i]);
        }
        for (int i = dataLen2; i < recSize; i++) {
            TS_ASSERT_EQUALS(buf[i], 0);
        }
        ifile3.close();        
    }

    void testFileCreation() {
        char *fileName = "foo.boo2";
        const int dataLen = 131;
        UINT8 data[dataLen];
        UINT8 comp[dataLen];

        for (int i = 0; i < dataLen; i++) {
            data[i] = genrand_int32() % 256;
        }
        int filePos;

        std::ifstream ifile1(fileName);
        TS_ASSERT(!ifile1);

        RecFile *recFile;
        recFile = new RecFile(fileName, 1024);
        filePos = recFile->push(data, dataLen);
        delete recFile;

        std::ifstream ifile2(fileName);
        TS_ASSERT(ifile2);

        recFile = new RecFile(fileName, 1024);
        recFile->read(filePos, comp, dataLen);
        delete recFile;

        for (int i = 0; i < dataLen; i++) {
            TS_ASSERT_EQUALS(comp[i], data[i]);
        }        
    }

    void testBasic() {
        RecFile recFile("foo.boo1", TEST_REC_SIZE); 

        UINT8 chunk1[TEST_REC_SIZE];
        for (int i = 0; i < TEST_REC_SIZE/2; i++) {
            chunk1[2*i+0] = i % 256;
            chunk1[2*i+1] = i / 256;
        }

        UINT64 pos1 = recFile.push(chunk1, TEST_REC_SIZE);
        UINT64 pos2 = recFile.push(randChunkShort, randChunkShortLength);
        UINT64 pos3 = recFile.push(randChunkLong,  randChunkLongLength);

        UINT8 comp[TEST_REC_SIZE];

        recFile.read(pos1, comp, TEST_REC_SIZE);
        for (int i = 0; i < TEST_REC_SIZE/2; i++) {
            TS_ASSERT_EQUALS(i % 256, comp[2*i+0]);
            TS_ASSERT_EQUALS(i / 256, comp[2*i+1]);
        }
        
        recFile.read(pos2, comp, randChunkShortLength);
        for (unsigned i = 0; i < randChunkShortLength; i++) {
            TS_ASSERT_EQUALS(randChunkShort[i], comp[i]);
        }

        recFile.read(pos3, comp, randChunkLongLength);
        for (unsigned i = 0; i < randChunkLongLength; i++) {
            TS_ASSERT_EQUALS(randChunkLong[i], comp[i]);
        }
    }

    void testReal() {
        unsigned realRecLength = 1024;
        std::vector<UINT8*> chunks(4711);
        std::vector<unsigned> originals(chunks.size());
        std::vector<UINT64> positions(chunks.size());
        std::vector<unsigned> lengths(chunks.size());

        for (unsigned i = 0; i < chunks.size(); i++) {
            unsigned s = genrand_int32() % realRecLength;
            chunks[i] = new UINT8[s];

            for (unsigned j = 0; j < s; j++) {
                chunks[i][j] = genrand_int32() % 256;
            }

            originals[i] = i;
            lengths[i] = s;
        }

        RecFile recFile("foo.boo4", realRecLength); 
        for (unsigned i = 0; i < chunks.size(); i++) {
            positions[i] = recFile.push(chunks[i], lengths[i]);
        }

        for (unsigned i = genrand_int32() % 10000; i > 0; i--) {
            next_permutation(originals.begin(), originals.end());
        }

        UINT8 fromFile[TEST_REC_SIZE];
        for (unsigned i = 0; i < chunks.size(); i++) {  
            unsigned originalIndex = originals[i];
            UINT8 *original = chunks[originalIndex];
            recFile.read(positions[originalIndex], fromFile, lengths[originalIndex]);
            
            for (unsigned j = 0; j < lengths[originalIndex]; j++) {
                TS_ASSERT_EQUALS(original[j], fromFile[j]);
            }
        }

        for (unsigned i = 0; i < chunks.size(); i++) {
            delete chunks[i];
        }

    }
};

class BoardTestSuite : public CxxTest::TestSuite {
 public:
    void setUp() {
    }

    void tearDown() {
    }

    void testInit() {
        UINT8 comp[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
        Board foo(comp);
        for (int i = 0; i < BOARD_SIZE; i++) {
            TS_ASSERT_EQUALS(foo.data[i], comp[i]);
        }
    }

    void testInitNum() {
        //fixme: "inline const &" boardRec etc.
        Board foo(431, 648);
        INT8 pos[2*STONES] = {
            0 + 1*SIZEX,
            2 + 0*SIZEX,
            0 + 2*SIZEX,
            1 + 1*SIZEX,
            1 + 0*SIZEX,
            0 + 0*SIZEX,

            0 + 2*SIZEX,
            2 + 0*SIZEX,
            0 + 0*SIZEX,
            1 + 0*SIZEX,
            0 + 1*SIZEX,
            1 + 1*SIZEX
        };

        for (int i = 0; i < 2*STONES; i++) {
            TS_ASSERT_EQUALS((int)foo.data[i], (int)pos[i]);
        }
    }

    void testBasic() {
        Board f;        
        UINT32 rating = ((4*256+7)*256+1)*256+1;
        f.setRating(rating);        
        f.setRed(0,  3);
        f.setRed(1,  7);
        f.setRed(2, 11);
        f.setRed(3, 13);
        f.setRed(4, 17);
        f.setRed(5, 23);
        f.setBlu(0, 29);
        f.setBlu(1, 31);
        f.setBlu(2, 37);
        f.setBlu(3, 43);
        f.setBlu(4, 53);
        f.setBlu(5, 61);
        TS_ASSERT_EQUALS(f.getRed(0),  3);
        TS_ASSERT_EQUALS(f.getRed(1),  7);
        TS_ASSERT_EQUALS(f.getRed(2), 11);
        TS_ASSERT_EQUALS(f.getRed(3), 13);
        TS_ASSERT_EQUALS(f.getRed(4), 17);
        TS_ASSERT_EQUALS(f.getRed(5), 23);
        TS_ASSERT_EQUALS(f.getBlu(0), 29);
        TS_ASSERT_EQUALS(f.getBlu(1), 31);
        TS_ASSERT_EQUALS(f.getBlu(2), 37);
        TS_ASSERT_EQUALS(f.getBlu(3), 43);
        TS_ASSERT_EQUALS(f.getBlu(4), 53);
        TS_ASSERT_EQUALS(f.getBlu(5), 61);
        TS_ASSERT_EQUALS(f.getRating(), rating);

        UINT8 data[16] = {3, 7, 11, 13, 17, 23, 29, 31, 37, 43, 53, 61, 1, 1, 7, 4};
        for (int i = 0; i < 16; i++) {
            TS_ASSERT_EQUALS(f.data[i], data[i]);        
        }

        Board g;
        g = f;
        f.setRating(32);
        TS_ASSERT_EQUALS(f.getRating(), 32);        
        TS_ASSERT_EQUALS(g.getRating(), rating);        
    }
};

char *strCopy(char *str) {
    int length = 0;
    while (str[length++]);
    
    char *newStr = new char[length];
    std::copy(str, str+length, newStr);
    return newStr;
}

class BoardRecTestSuite : public CxxTest::TestSuite {
    int recLength;
    char *fileName;
 public:
    void setUp() {
        fileName = strCopy("foo.boo5");
        recLength = 1024;
        std::ofstream truncFile(fileName);
        truncFile.close();
    }

    void tearDown() {
        delete fileName;
    }

    void testBasic() {
        /*set up*/
        RecFile *recFile = new RecFile(fileName, recLength);
        Board b(0, 0);
        BoardRec iglu(recFile, b);
        std::vector<Board>insertBoards(1);
        insertBoards[0] = b;
        std::vector<Board>newBoards;
        std::vector<BoardRec> overflowRecords;
        UINT8 compBuf[recLength];
        for (int i = 0; i < recLength; i++) {
            compBuf[i] = 0;
        }
        for (int i = 0; i < BOARD_SIZE; i++) {
            compBuf[i] = b.data[i];
        }

        /*testcode*/
        iglu.insertSorted(insertBoards, &newBoards, &overflowRecords);
        TS_ASSERT_EQUALS(newBoards.size(), 1);
        TS_ASSERT_EQUALS(newBoards[0], Board(0, 0));
        TS_ASSERT_EQUALS(overflowRecords.size(), 0);

        delete recFile; //flush file
        std::ifstream compFile(fileName);
        for (int i = 0; i < recLength; i++) {
            TS_ASSERT_EQUALS((UINT8)compFile.get(), compBuf[i]);            
        }
    }

    void testMultiInsertUnique() {
        /*set up*/
        int boardNum = 63;
        Vector<Board> testBoards;
        for (int i = 0; i < boardNum;) {
            Board b(genrand_int32() % 720, genrand_int32() % 720);

            if (!(std::count(testBoards.begin(), testBoards.end(), b))) {
                testBoards.push_back(b);
                i++;
            }
        }
        RecFile *recFile = new RecFile(fileName, recLength);
        BoardRec iglu(recFile, Board::getMin(testBoards));

        int remainingBoards = boardNum;
        Vector<int> chargeSizes;
        while (remainingBoards) {
            int i = genrand_int32() % 10;
            i = MINIMUM(i, remainingBoards);
            chargeSizes.push_back(i);
            remainingBoards -= i;
        }

        /*testcode*/
        unsigned start = 0;
        for(unsigned i = 0; i < chargeSizes.size(); i++) {
            int chargeSize = chargeSizes[i];
            Vector<Board> njuBoards;
            Vector<BoardRec> overflowRecords;
            Vector<Board> insertBoards(testBoards.begin() + start, testBoards.begin() + start + chargeSize);
            std::sort(insertBoards.begin(), insertBoards.end());
            iglu.insertSorted(insertBoards, &njuBoards, &overflowRecords);
            
            TS_ASSERT_EQUALS(overflowRecords.size(), 0);
            TS_ASSERT_EQUALS(njuBoards.size(), chargeSize);

            start += chargeSize;
        }

        delete recFile;

        std::sort(testBoards.begin(), testBoards.end());
        std::ifstream compFile(fileName);
        UINT8 compBuf[recLength];
        for (int i = 0; i < recLength; i++) {
            compBuf[i] = 0;
        }
        compFile.read((char*)compBuf, recLength);

        for (int i = 0; i < boardNum*BOARD_SIZE; i++) {
            UINT8 orig = testBoards[i / BOARD_SIZE].data[i % BOARD_SIZE];
            TS_ASSERT_EQUALS(compBuf[i], orig);
        }
        for (int i = boardNum*BOARD_SIZE; i < recLength; i++) {
            TS_ASSERT_EQUALS(compBuf[i], 0);
        }
    }

    Vector<Board> getCharge(Vector<Board> boards, int start, int length) {
        Vector<Board> raw(boards.begin() + start, boards.begin() + start + length);
        std::sort(raw.begin(), raw.end());

        Vector<Board> ret;
        std::unique_copy(raw.begin(), raw.end(), back_inserter(ret));

        return ret;
    }

    void testMultiInsertWithCollisions() {
        /*set up*/
        int boardNum = 60;
        int doublettes = 10;
        int uniques = boardNum - doublettes;
        Vector<Board> testBoards;
        for (int i = 0; i < uniques;) {
            Board b(genrand_int32() % 720, genrand_int32() % 720);

            if (!(std::count(testBoards.begin(), testBoards.end(), b))) {
                testBoards.push_back(b);
                i++;
            }
        }
        Vector<Board> mixer;
        for (int i = 0; i < 20; i++) {
            mixer.push_back(testBoards[i]);
        }
        for (int i = 0; i < doublettes; i++) {
            int randIndex = genrand_int32() % 10;
            mixer.push_back(testBoards[randIndex]);
            mixer.push_back(testBoards[20+i]);
        }
        for (int i = 0; i < boardNum-20-2*doublettes; i++) {
            mixer.push_back(testBoards[30+i]);
        }
        testBoards = mixer;
        TS_ASSERT_EQUALS(testBoards.size(), boardNum);

        RecFile *recFile = new RecFile(fileName, recLength);
        BoardRec iglu(recFile, Board::getMin(testBoards));

        int remainingBoards = boardNum;
        Vector<int> chargeSizes;
        while (remainingBoards) {
            int i = genrand_int32() % 10;
            i = MINIMUM(i, remainingBoards);
            chargeSizes.push_back(i);
            remainingBoards -= i;
        }

        /*testcode*/
        unsigned start = 0;
        for(unsigned i = 0; i < chargeSizes.size(); i++) {
            int chargeSize = chargeSizes[i];
            Vector<Board> njuBoards;
            Vector<BoardRec> overflowRecords;
            Vector<Board> insertBoards = getCharge(testBoards, start, chargeSize);

            iglu.insertSorted(insertBoards, &njuBoards, &overflowRecords);
            njuBoards = Vector<Board>(0);

            TS_ASSERT_EQUALS(overflowRecords.size(), 0);

            start += chargeSize;
        }
        TS_ASSERT_EQUALS(iglu.getSize(), uniques);

        delete recFile;

        Vector<Board> testBoardsFiltered;
        std::sort(testBoards.begin(), testBoards.end());
        std::unique_copy(testBoards.begin(), testBoards.end(), back_inserter(testBoardsFiltered));
        TS_ASSERT_EQUALS(testBoardsFiltered.size(), uniques);
        std::ifstream compFile(fileName);
        UINT8 compBuf[recLength];
        for (int i = 0; i < recLength; i++) {
            compBuf[i] = 0;
        }
        compFile.read((char*)compBuf, recLength);

        for (unsigned i = 0; i < testBoardsFiltered.size()*BOARD_SIZE; i++) {
            UINT8 orig = testBoardsFiltered[i / BOARD_SIZE].data[i % BOARD_SIZE];
            TS_ASSERT_EQUALS(compBuf[i], orig);
        }
        for (int i = testBoardsFiltered.size()*BOARD_SIZE; i < recLength; i++) {
            TS_ASSERT_EQUALS(compBuf[i], 0);
        }
    }

    void testBigBadInsert() {
        /*setup*/
        int boardNum = 10000;
        Vector<Board> testBoards;
        for (int i = 0; i < boardNum; i++) {
            Board b(genrand_int32() % 100, genrand_int32() % 100);
            testBoards.push_back(b);
        }

        Vector<int> chargeSizes;
        int remBoards = boardNum;
        while (remBoards) {
            int rand = genrand_int32() % 20;
            int cs = MINIMUM(remBoards, rand);
            chargeSizes.push_back(cs);
            remBoards -= cs;
        }

        /*testcode*/
        RecFile *recFile = new RecFile(fileName, recLength);
        BoardRec iglu(recFile, Board::getMin(testBoards));

        int start = 0;
        Vector<Board> njuBoards;
        Vector<BoardRec> overflowRecords;
        for (unsigned i = 0; i < chargeSizes.size(); i++) {
            int chargeSize = chargeSizes[i];
            Vector<Board> charge = getCharge(testBoards, start, chargeSize);

            iglu.insertSorted(charge, &njuBoards, &overflowRecords);

            start += chargeSize;
        }

        delete recFile;

        
        
        /*simulate boardRec*/
        Board b(3, 45);
        Vector<Board> fakeRec;
        start = 0;
        for (unsigned i = 0; i < chargeSizes.size(); i++) {
            int chargeSize = chargeSizes[i];
            Vector<Board> charge = getCharge(testBoards, start, chargeSize);
            

            Vector<Board> tmp = fakeRec;
            for (unsigned j = 0; j < charge.size(); j++) {
                tmp.push_back(charge[j]);
            }
            std::sort(tmp.begin(), tmp.end());
            Vector<Board> merged;
            std::unique_copy(tmp.begin(), tmp.end(), back_inserter(merged));

            int newRecs = 1 + merged.size() / (recLength / BOARD_SIZE);
            int newLength = merged.size() / newRecs;
            Vector<Board> newFakeRec(merged.begin(), merged.begin() + newLength);
            fakeRec = newFakeRec;

            start += chargeSize;
        }
        TS_ASSERT_EQUALS(fakeRec.size(), iglu.getSize());

        /*compare*/
        recFile = new RecFile(fileName, recLength);
        BoardRec comp(recFile, iglu.getFilePos());
        Vector<Board> compRec = comp.readBoards();
        TS_ASSERT_EQUALS(comp.getSize(), fakeRec.size());
        TS_ASSERT_EQUALS(compRec.size(), fakeRec.size());
        for (unsigned i = 0; i < fakeRec.size(); i++) {
            TS_ASSERT_EQUALS(compRec[i], fakeRec[i]);
        }

        Vector<Board> originals;
        Vector<Board> raw = testBoards;
        std::sort(raw.begin(), raw.end());
        std::unique_copy(raw.begin(), raw.end(), back_inserter(originals));
        Vector<Board> fromFile = compRec;
        for (unsigned i = 0; i < overflowRecords.size(); i++) {
            BoardRec tempRec(recFile, overflowRecords[i].getFilePos());
            Vector<Board> tempBoards = tempRec.readBoards();
            for (unsigned j = 0; j < tempBoards.size(); j++) {
                fromFile.push_back(tempBoards[j]);
            }
            
            Vector<Board> tmp;
            std::sort(fromFile.begin(), fromFile.end());
            std::unique_copy(fromFile.begin(), fromFile.end(), back_inserter(tmp));
            fromFile = tmp;
        }

        for (int i = 0; i < boardNum; i++) {
            int numO = std::count(originals.begin(), originals.end(), testBoards[i]);
            TS_ASSERT_EQUALS(numO, 1);
        }

        for (unsigned i = 0; i < fromFile.size(); i++) {
            int numF = std::count(testBoards.begin(), testBoards.end(), fromFile[i]);
            TS_ASSERT(numF >= 1);
        }

        TS_ASSERT_EQUALS(fromFile.size(), originals.size());
        for (unsigned i = 0; i < fromFile.size(); i++) {
            TS_ASSERT_EQUALS(fromFile[i], originals[i]);
        }

        delete recFile;
    }


    void testInsertRatings() {
        /*setup*/
        int boardNum = 50;
        Vector<Board> testBoards;
        for (int i = 0; i < boardNum; i++) {
            Board b(i, i, 47);
            testBoards.push_back(b);
        }
        std::sort(testBoards.begin(), testBoards.end());

        /*testcode & compare*/
        RecFile *recFile = new RecFile(fileName, recLength);
        BoardRec iglu(recFile, Board::getMin(testBoards));
        Vector<Board> newBoards;
        Vector<BoardRec> overflowRecords;
        iglu.insertSorted(testBoards, &newBoards, &overflowRecords);
        TS_ASSERT_EQUALS(newBoards.size(), testBoards.size());
        TS_ASSERT_EQUALS(overflowRecords.size(), 0);
        
        Vector<Board> comp = iglu.readBoards();
        TS_ASSERT_EQUALS(comp.size(), testBoards.size());        
        for (unsigned i = 0; i < comp.size(); i++) {
            TS_ASSERT_EQUALS(comp[i].getRating(), 47);
        }

        for (unsigned i = 0; i < testBoards.size(); i++) {
            testBoards[i].setRating(11);
        }
        iglu.insertSorted(testBoards, &newBoards, &overflowRecords);
        TS_ASSERT_EQUALS(newBoards.size(), testBoards.size());
        TS_ASSERT_EQUALS(overflowRecords.size(), 0);

        comp = iglu.readBoards();
        TS_ASSERT_EQUALS(comp.size(), testBoards.size());        
        for (unsigned i = 0; i < comp.size(); i++) {
            TS_ASSERT_EQUALS(comp[i].getRating(), 11);
        }

        delete recFile;
    }

    void insert(int repeats, int blockSize, char *tFileName) {
        RecFile *recFile = new RecFile(tFileName, recLength);
        BoardRec iglu(recFile, Board(0, 0));
        Vector<BoardRec> boardRecs;     
        boardRecs.push_back(iglu);
        UINT64 t1 = time(NULL);

        Vector<Board> insertBoardsRaw(blockSize);       

        for (int i = 0; i < repeats; i++) {
            for (unsigned j = 0; j < insertBoardsRaw.size(); j++) {
                insertBoardsRaw[j] = Board(genrand_int32() % 720, genrand_int32() % 720, genrand_int32());
            }
            std::sort(insertBoardsRaw.begin(), insertBoardsRaw.end());
            Vector<Board> insertBoards;
            std::unique_copy(insertBoardsRaw.begin(), insertBoardsRaw.end(), back_inserter(insertBoards));
            Vector<Board> newBoards;

            BoardRec randRec = boardRecs[genrand_int32() % boardRecs.size()];
            randRec.insertSorted(insertBoards, &newBoards, &boardRecs);

            puts("randRecSize: " << randRec.getSize());
            //            puts("insertBoards.size: " << insertBoards.size() << " newBoards.size: " << newBoards.size() << " boardRecs: " << boardRecs.size());
        }
        UINT64 t2 = time(NULL);
        puts("boardRecs:  " << boardRecs.size());
        puts("insertTime: " << t2-t1);

        delete recFile;
    }

    void testBigInsertPerformance() {
        puts("big");
        insert(2, 5000000, fileName);
    }

    void testSmallInsertPerformance() {
        puts("small");
        insert(1000000, 10, "sizeer.foo");
    }

};

class EmptyTestSuite : public CxxTest::TestSuite {
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
