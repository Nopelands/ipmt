#include "main.h"

uint64_t SO[AB_SIZE];
void buildShiftOr(const string &pat) {

    memset(SO, -1, AB_SIZE * sizeof(uint64_t));

    uint64_t j = 1;
    for (uint8_t c : pat)
        SO[c] &= ~j, j <<= 1;
}

int ShiftOr(const string &txt, const string &pat) {

    const uint64_t lim = 1ULL << (pat.size() - 1);

    uint64_t state = -1;
    for (unsigned i = 0; i < txt.size(); i++) {
        state = (state << 1) | SO[(uint8_t)txt[i]];

        if (!(state & lim)) [[unlikely]]
            return i - pat.size() + 1;
    }
    return -1;
}
