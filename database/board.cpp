class Board {
    static UINT8 Positions[720][6];
    static bool staticsInited;

public:
    UINT8 data[16];

    inline Board() {
    }

    inline Board(UINT8 *_data) {
        std::copy(_data, _data+BOARD_SIZE, data);
    }

    inline Board(int posRed, int posBlu, UINT32 rating=0) {
        if (!staticsInited) {
#include <../engine/initpos.cpp>
            staticsInited = true;
        }

        std::copy(Positions[posRed], Positions[posRed] + STONES, data);
        std::copy(Positions[posBlu], Positions[posBlu] + STONES, data + STONES);
        ((UINT32*)data)[3] = rating;
    }
    
    inline INT8 compareWith(const Board& otherBoard) const {
        return compareWith(otherBoard.data);
    }

    inline INT8 compareWith(const UINT8 *otherBoardData) const {
        UINT32 *dataThis  = (UINT32*)data;
        UINT32 *dataOthr = (UINT32*)otherBoardData;
        for (int i = 0; i < 3; i++) {
            if (dataThis[i] < dataOthr[i]) return -1;
            if (dataThis[i] > dataOthr[i]) return  1;
        }
        return 0;
    }

    inline void setRating(const UINT32& rating) {
        ((UINT32*)data)[3] = rating;
    }

    inline UINT32 getRating() const {
        return ((UINT32*)data)[3];
    }

    inline void setRed(const int& stone, const UINT8& pos) {
        data[0+stone] = pos;
    }

    inline void setBlu(const int& stone, const UINT8& pos) {
        data[6+stone] = pos;
    }

    inline UINT8 getRed(const int& stone) const {
        return data[0+stone];
    }

    inline UINT8 getBlu(const int& stone) const {
        return data[6+stone];
    }

    inline void print() const {
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout.width(4);
            std::cout << (int)data[i];
        }
        std::cout << "\n";
    }

    static
    Board 
    getMin(const Vector<Board>& boards); 
};

inline bool operator==(const Board& board1, const Board& board2) {
    return board1.compareWith(board2) ==  0;
}

inline bool operator<(const Board& board1, const Board& board2) {
    return board1.compareWith(board2) == -1;
}

inline bool operator>(const Board& board1, const Board& board2) {
    return board1.compareWith(board2) ==  1;
}

Board 
Board::getMin(const Vector<Board>& boards) {
    Board min = boards[0];
    for (unsigned i = 1; i < boards.size(); i++) {
        Board n = boards[i];
        if (n < min) min = n;
    }
    return min;
}


UINT8 Board::Positions[720][6];
bool Board::staticsInited = false;
