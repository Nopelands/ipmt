#ifndef IPMT_MAIN_H
#define IPMT_MAIN_H

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define AB_SIZE 256


class main {

};

#if defined(__GNUC__)
__extension__ typedef __int128_t int128_t;
constexpr int maxBinarySize = 128;
#else
constexpr int maxBinarySize = 64;
#endif

#endif //IPMT_MAIN_H
