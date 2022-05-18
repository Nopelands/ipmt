#ifndef IPMT_MAIN_H
#define IPMT_MAIN_H

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

#define AB_SIZE 256

// index and search
extern void index(const string& txt, const string &fileName);
extern void build_search(const string &fileName);
extern vector<string> search(bool count, const vector<string> &pat);
extern void zip77(const string &file_name);
extern void unzip77(const string &fileName);
extern void buildBoyer(const string &pat);
extern int BoyerMoore(const string &txt, const string &pat);
extern void buildShiftOr(const string &pat);
extern int ShiftOr(const string &txt, const string &pat);

#endif //IPMT_MAIN_H
