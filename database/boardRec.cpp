class BoardRec {
private:
    static std::vector<std::pair<UINT8*, int> > buffers;

    RecFile *file;
    int size;
    int recLength;
    int maxElements;
    UINT64 filePos;
    Board minBoard;

    inline
    void
    allocateBuffer(const int& i, const int& bufSize) {
        if (buffers[i].second < bufSize) {
            if (buffers[i].first) delete buffers[i].first;
            buffers[i].first = new UINT8[bufSize];
            buffers[i].second = bufSize;
        }
    }

    inline
    int
    merge(UINT8 *sourceOld, const int& sourceOldSize, std::vector<Board> sourceNew, UINT8 *target, std::vector<Board> *newBoards) {
        /*************************************************************/
        // some "closures" 
#define COMMON_PUSH \
        mergedNum++; \
        std::copy(beg, beg + BOARD_SIZE, indexMerge); \
        indexMerge += BOARD_SIZE
        // copy new board to target
#define PUSH_SOURCE_OLD \
        beg = sourceOld + indexOld; \
        indexOld += BOARD_SIZE; \
        COMMON_PUSH
        // copy new board to taget 
#define PUSH_SOURCE_NEW \
        beg = sourceNew[indexNew].data; \
        indexNew++; \
        COMMON_PUSH
        // copy new board to taget and newBoards
#define PUSH_SOURCE_NEW_AND_COPY_NEW_BOARD \
        beg = sourceNew[indexNew].data; \
        newBoards->push_back(sourceNew[indexNew]); \
        indexNew++; \
        COMMON_PUSH
        /*************************************************************/
        
        int mergedNum = 0;
        int indexOld = 0;
        UINT8 *beg;
        UINT32 indexNew = 0;
        UINT8 *indexMerge = target;

        //merge
        while ((indexOld < sourceOldSize) && (indexNew < sourceNew.size())) {
            switch (sourceNew[indexNew].compareWith(sourceOld + indexOld)) {
            case -1: //...copy sourceNew
                PUSH_SOURCE_NEW_AND_COPY_NEW_BOARD;   
                break;
            case 0: //both are equal: 
                indexOld += BOARD_SIZE; //discard sourceOld because of its outdatedRating 
                PUSH_SOURCE_NEW;                                         
                break;
            case 1://copy sourceOld
                PUSH_SOURCE_OLD;                    
                break;
            }
        }

        //append remainder (only one of the loops will run)
        for (; indexOld < sourceOldSize; ) {
            PUSH_SOURCE_OLD;
        }
        for (; indexNew < sourceNew.size(); ) {
            PUSH_SOURCE_NEW_AND_COPY_NEW_BOARD;
        }

        return mergedNum;

        /*************************************************************/
#undef PUSH_SOURCE1
#undef PUSH_SOURCE2
#undef COMMON_PUSH 
        /*************************************************************/
    }

    inline
    void
    initFile(RecFile* _file) {
        file = _file;
        recLength = file->getRecLength();
        maxElements = recLength / BOARD_SIZE;
    }


public:

    inline
    BoardRec(RecFile* _file, const UINT64& _filePos) {
        initFile(_file);

        filePos = _filePos;
        Vector<Board> tmpBoards = readBoards();
        size = tmpBoards.size();
        if (size==0) {
            fail("empty boardRec found in file. minBoard would be undefined!");
        }
        minBoard = Board::getMin(tmpBoards);
    }

    inline 
    BoardRec(RecFile* _file, UINT8* data, int boardNum) {
        initFile(_file);
        
        filePos = file->push(data, boardNum * BOARD_SIZE);
        minBoard = Board(data + 0);
        size = boardNum;
        if (size == 0) {
            fail("BoardRec with 0 boards created from data (exiting, since I'm almost sure this is is fatal ;-)");
        }
    }

    inline 
    BoardRec(RecFile* _file, const Board& _minBoard) {
        initFile(_file);

        allocateBuffer(0, recLength);
        UINT8 *buffer = buffers[0].first;
        for (int i = 0; i < recLength; i++) {
            buffer[i] = 0;
        }

        filePos = file->push(buffer, recLength);
        minBoard = _minBoard;
        size = 0;
    }

    // return the number of boards stored
    inline
    int    
    getSize() const {
        return size;
    }

    inline
    Board*
    const
    getMinBoard() {
        return &minBoard;
    }

    inline
    UINT64
    getFilePos() const {
        return filePos;
    }

    inline
    Vector<Board>
    readBoards() {
        Vector<Board> ret;
        allocateBuffer(0, recLength);
        UINT8 *buf = buffers[0].first;
        file->read(filePos, buf, recLength);
        UINT8 zd[BOARD_SIZE] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        Board zeroBoard(zd);
        for (int i = 0; i < recLength; i+=BOARD_SIZE) {
            Board tmpBoard(buf + i);
            if (tmpBoard == zeroBoard) break;
            ret.push_back(tmpBoard);
        }
        return ret;
    }

    /*merges current boards with insertBoards. insertBoards has to be sorted and free of dublettes*/
    inline
    void
    insertSorted(const std::vector<Board>& insertBoards, std::vector<Board> *newBoards, std::vector<BoardRec> *overflowRecords) {
        int thisByteSize = size * BOARD_SIZE;
        allocateBuffer(0, thisByteSize);
        allocateBuffer(1, thisByteSize + insertBoards.size() * BOARD_SIZE);
        UINT8 *dataThis  = buffers[0].first;
        UINT8 *dataMerge = buffers[1].first;

        file->read(filePos, dataThis, thisByteSize);
        int mergedNum = merge(dataThis, thisByteSize, insertBoards, dataMerge, newBoards);
       
        int boardRecNum = 1 + mergedNum / maxElements;
        std::vector<int> startIndexes(boardRecNum+1, 0);
        for (unsigned i = 0; i < startIndexes.size(); i++) {
            startIndexes[i] = mergedNum * i / boardRecNum;
        }

//         int maxSize = size + insertBoards.size();

        size = (startIndexes[1] - startIndexes[0]);
        int byteSize = size * BOARD_SIZE;
        file->write(filePos, dataMerge, byteSize);        

        for (int i = 1; i < boardRecNum; i++) {
            int boardNum = startIndexes[i+1] - startIndexes[i];
            UINT8 *dataStart = dataMerge + startIndexes[i] * BOARD_SIZE;
//             puts("insert -------- 4.1 ----------");
//             puts("boardRecNum: " << boardRecNum);
//             puts("startIndexes[" << i+0 << "] = " << startIndexes[i+0]);
//             puts("startIndexes[" << i+1 << "] = " << startIndexes[i+1]);

//             puts("");
//             puts("boardNum:    " << boardNum);
//             puts("startIndex:  " << startIndexes[i]);
//             puts("maxSize:     " << maxSize);
            BoardRec nju(file, dataStart, boardNum);            
//             puts("insert -------- 4.2 ----------");        
            overflowRecords->push_back(nju);
        }
    }
};

std::vector<std::pair<UINT8*, int> > BoardRec::buffers(2);
