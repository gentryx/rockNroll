#include <cstdarg>
#include <sstream>
#include <string>

#define MAXIMUM(a, b) (a > b? a : b)
#define MINIMUM(a, b) (a < b? a : b)
#define UINT8 unsigned char
#define INT8 char
#define UINT32 unsigned
#define UINT64 unsigned long long
#define puts(s) std::cout << s << "\n"

#define STONES 6
#define SIZEX 5
#define SIZEY 5
#define OFF_BOARD 256
#define BOARD_SIZE 16
#define Vector std::vector

typedef std::string String;
int str2int(String str) {
    std::istringstream conv(str);
    int res;
    conv >> res;
    return res;
}

String int2str(int num) {
    std::ostringstream conv;
    conv << num;
    return conv.str();
}

void
fail(String message1, String message2="", String message3="") {
    std::cout << "FAILED BECAUSE OF ERROR: " << message1 << message2 << message3 << "\n";
    exit(1);
}

    

