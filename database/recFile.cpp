#include <fstream>

class RecFile {
    std::fstream *file;
    int recLength;
    UINT64 numRecords;

    inline 
    void 
    checkIndex(const UINT64& index) {
        if (index >= numRecords) {
            fail("index out of bounds. is: "+int2str(index)+" should be: 0.."+int2str(numRecords));
        }
    }

    inline 
    void 
    seek(const UINT64& index) {
        file->seekp(index*recLength);
    }

    inline 
    void 
    writeHere(const UINT8* data, const int& length) {
        file->write((char*)data, length);
        if (length < recLength) {
            int remainder = recLength - length;
            UINT8 tmp[remainder];
            std::fill(tmp, tmp+remainder, 0);
            file->write((char*)tmp, remainder);            
        }
    }

    inline   
    void
    readHere(const UINT8* data, const int& length) {
        file->read((char*)data, length);
    }

public:

    inline
    RecFile(char *name, const int& rLength) {        
        file = new std::fstream(name);
        if (!*file) {
            delete file;
            std::ofstream fileCreater(name);
            if (!fileCreater) fail("could not create file \"", name, "\""); 

            file = new std::fstream(name);            
            if (!*file) fail("could not open created file \"", name, "\""); 
        }

        recLength = rLength;

        file->seekp(0, std::ios_base::end);
        numRecords = file->tellp() / recLength;
    }

    ~RecFile() {
        file->close();
        delete file;
    }

    inline
    int 
    size() {
        return numRecords;
    }

    inline
    void 
    write(const UINT64 index, const UINT8* data, const int& length) {
        checkIndex(index);
        seek(index);
        writeHere(data, length);
    }

    inline
    void
    read(const UINT64 index, const UINT8* data, const int& length) {
        checkIndex(index);
        seek(index);
        readHere(data, length);
    }


    inline
    int
    getRecLength() {
        return recLength;
    }

    inline
    UINT64
    push(const UINT8* data, const int& length) {
        seek(numRecords);
        writeHere(data, length);
        return numRecords++;
    }
};
