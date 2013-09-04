#include <iostream>
#include <vector>
#include <time.h>

#include <compileChain.h>

#define FILE_INDEX unsigned long long
#define KEY_LENGTH 12
#define PAYLOAD_LENGTH 20
#define MAX_LEAF_ENTRIES 256
#define LEAF_BYTE_LENGTH 8192

// class Key {
// };

// class PayLoad {
    
// };

// int max(int a, int b) {
//     return (a < b ? a : b);
// }

// class Node {
// public:
//     Key min;
//     virtual bool isLeaf() =0;
//     virtual Payload search(Key k) =0;
//     virtual Node *insert(Key k, Payload p) =0;
// };

// // class InnerNode : public Node<Key, Payload> {
// // public:
// //     Node *left;
// //     Node *right;
// //     bool isLeaf() { return false; }
// // };

// class LeafNode : public Node {
// public:
//     FILE_INDEX i;
//     int length;

//     Key key;
//     Payload payload;

//     bool isLeaf() { return true; }

//     Payload search(Key k) {
//         if (k == key) {
//             return payload;
//         } else {
//             return Payload(0);
//         }
//     }

//     Node *insert(Key k, Payload p) {
//         key = k;
//         payload = p;
//         return this;
//     }
// };


/*
  1024 61

 */

int
main() {
    int factor=4;
    RecFile foo("foo.boo", factor*1024);
    UINT8 chunk[factor*1024];

    UINT64 t1 = time(NULL);
//     for (int i = 0; i < 1024*1024/factor; i++) {
//         foo.push(chunk, factor*1024);
//     }
    UINT64 t2 = time(NULL);
    puts("time: " << (t2-t1));


//     puts(foo.size());

//     LeafNode *f = new LeafNode();
//     f->insert(4, 65);

//     Node<int, int> *g = f;
//     if (typeid(*g) == typeid(InnerNode<int, int>)) {
//         std::cout << "<<<bar>>>\n";
//     }
//     std::cout << typeid(*f).name() << "\n";
//     std::cout << typeid(*g).name() << "\n";
    std::cout << "foo\n";
}

// #define STONETYPE unsigned char
// #define FILESIZE ((unsigned long long)1*1024*1024*32)
// #define BUFFERSIZE 1024*1024
// #define POSTYPE unsigned long long

// POSTYPE randPos() {
//     POSTYPE r = genrand_int32();
//     r <<= 32;
//     r += genrand_int32();
//     r = r % FILESIZE;
//     return r;
// }

// void
// putTime() {
//     std::cout << time(NULL) << "\n";
// }

// int
// main() {
// //     std::fstream foo("test.raw", std::ios_base::in | std::ios_base::out | std::ios_base::binary);
//     std::fstream foo("/home/gentryx/test.raw", std::ios_base::in);
//     char buffer[BUFFERSIZE];
//     for (int i = 0; i < BUFFERSIZE; i++) {
//         buffer[i] = 0;
//     }

//     foo.seekp(0);

//     for (int i = 0; i < 1*1024; i++) {
//         foo.write(buffer, BUFFERSIZE);
//         if ((i % (100)) == 0) {
//             std::cout << "foo " << i << "\n";
//         }
//     }

//     init_genrand(time(NULL));

//     int sum = 0;
    
//     int seeks = 1024*1024*10;
//     std::vector<POSTYPE> positions(seeks);

//     putTime();
//     for (int i = 0; i < seeks; i++) {
//         positions[i] = randPos();
//     }

//     putTime();
//     std::sort(positions.begin(), positions.end());

//     putTime();
//     char res[8192];
//     for (int i = 0; i < seeks/10; i++) {
//         char c[8192];
//         foo.seekp(positions[i]*32);
//         foo.read(c, 8192);
        
//         for (int j = 0; j < 32; j++) {
//             res[j] += c[j];
//         }
//     }
//     std::cout << "sum: " << sum << "\n";
//     putTime();

//     foo.close();
// }
