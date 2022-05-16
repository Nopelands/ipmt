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

// index and search
extern void index(const string& txt, const string &fileName);
extern void build_search(const string &fileName);
extern vector<string> search(bool count, const vector<string> &pat);
extern void zip77(const string &file_name);
extern void unzip77(const string &fileName);

#endif //IPMT_MAIN_H
