#include "main.h"
#include <algorithm>

struct triple {
    int a[3];

    operator int() const {
        return a[2];
    }

    const bool operator!=(const triple &t) {
        return a[0] != t.a[0] || a[1] != t.a[1];
    }

    const bool operator<(const triple &t) {
        return   a[0]  < t.a[0] || 
                (a[0] == t.a[0] && (a[1]  < t.a[1] || 
                                   (a[1] == t.a[1] && a[2] < t.a[2])));
    }
};

string T;
vector<vector<int>> P;
vector<int> sa, Llcp, Rlcp, lineBreaks;

void build_P(const string &txt) {

    const int n = txt.size();
    P.resize(1);
    P[0].assign(txt.begin(), txt.end());

    for (int l = 1, k = 0; l < n; l <<= 1, k++) {
        vector<triple> triples(txt.size());

        for (int i = 0; i < n; ++i)
            triples[i] = {P[k][i], i + l < n ? P[k][i + l] : -1, i};

        sort(triples.begin(), triples.end());

        P.push_back(vector<int>(n));
        vector<int> &Pk = *(P.end() - 1);

        Pk[triples[0]] = 0;

        for (int i = 1, order = 0; i < n; ++i) {
            if (triples[i - 1] != triples[i]) [[likely]]
                order++;
            
            Pk[triples[i]] = order;
        }
    }
}

void build_sa(const vector<int> &p) {
    for (unsigned i = 0; i < p.size(); ++i)
        sa[p[i]] = i;
}

int lcp(int i, int j) {

    const int n = P[0].size();
    
    if (i == j)
        return n - i;

    int lcp = 0;
    for (int k = P.size() - 1, l; k >= 0 && i < n && j < n; k--) {
        l = 1 << k;

        if (P[k][i] == P[k][j]) [[unlikely]] {
            lcp += l;
            i += l;
            j += l;
        }
    }

    return lcp;
}

void fill_RL_lcp_aux(const string &txt, int l, int r) {
    if (r - l <= 1) [[unlikely]]
        return;
    
    int h = (l + r) / 2;

    Llcp[h] = lcp(sa[l], sa[h]);
    Rlcp[h] = lcp(sa[h], sa[r]);

    fill_RL_lcp_aux(txt, l, h);
    fill_RL_lcp_aux(txt, h, r);
}

void fill_RL_lcp(const string& txt) {
    fill_RL_lcp_aux(txt, 0, txt.size() - 1);
}

int lex_cmp(int &lcp, const string &s1, const string &s2) {
    
    const int m = min(s1.size(), s2.size());

    for (lcp = 0; lcp < m; ++lcp)
        if (s1[lcp] != s2[lcp])
            return s1[lcp] - s2[lcp];
    
    return (int)s1.size() - (int)s2.size();
}

template<bool succ>
int find(const string& txt, const string &pat) {
    const int m = pat.size(), n = txt.size();
    int H, L, R, h, l = 0, r = n - 1, lcp_h;

    int cmp_first = lex_cmp(L, pat, txt.substr(sa[0]));
    int cmp_last  = lex_cmp(R, pat, txt.substr(sa[n - 1]));

    if (cmp_first <= 0 - !succ) [[unlikely]]
        return 0 - !succ;

    if (cmp_last > 0 - !succ) [[unlikely]]
        return n - !succ;

    while (r - l > 1) {
        h = (l + r) / 2;

        if (L >= R) [[likely]]
            if (L <= Llcp[h]) {
                lex_cmp(lcp_h, pat.substr(L), txt.substr(sa[h] + L));
                H = L + lcp_h;
            }
            else
                H = Llcp[h];
        else
            if (R <= Rlcp[h]) {
                lex_cmp(lcp_h, pat.substr(R), txt.substr(sa[h] + R));
                H = R + lcp_h;
            }
            else
                H = Rlcp[h];
        
        if (    ( succ &&  (H == m || pat[H] <= txt[sa[h] + H]))
            ||  (!succ && !(H == m || pat[H]  > txt[sa[h] + H])))
            r = h, R = H;
        else
            l = h, L = H;
    }

    return succ ? r : l;
}

#include <fstream>
void save_file(const string &fileName) {

    ofstream wf(fileName, ios::out | ios::binary);
    int s = P[0].size();

    wf.write((char*)&s, sizeof(s));
    wf.write((char*)&sa[0], s * sizeof(sa[0]));
    wf.write((char*)&Llcp[0], s * sizeof(Llcp[0]));
    wf.write((char*)&Rlcp[0], s * sizeof(Rlcp[0]));
    wf.write((char*)&P[0][0], s * sizeof(P[0][0]));
    wf.write((char*)&lineBreaks[0], lineBreaks.size() * sizeof(lineBreaks[0]));
    wf.close();
}

int read_file(const string &fileName) {

    ifstream rf(fileName, ios::in | ios::binary);
    if (!rf.is_open()) {
        return 1;
    }
    int s;

    rf.read((char*)&s, sizeof(s));

    sa.resize(s);
    Llcp.resize(s);
    Rlcp.resize(s);
    P.assign(1, vector<int>(s));

    rf.read((char*)&sa[0], s * sizeof(sa[0]));
    rf.read((char*)&Llcp[0], s * sizeof(Llcp[0]));
    rf.read((char*)&Rlcp[0], s * sizeof(Rlcp[0]));
    rf.read((char*)&P[0][0], s * sizeof(P[0][0]));

    lineBreaks.clear();
    do {
        lineBreaks.push_back(0);
        rf.read((char*)&lineBreaks[lineBreaks.size() - 1], sizeof(lineBreaks[0]));
    } while(lineBreaks[lineBreaks.size() - 1] != s);

    rf.close();
    return 0;
}

void index(const string& txt, const string &fileName) {

    lineBreaks.assign(1, -1);
    for (unsigned i = 0; i < txt.size(); ++i)
        if (txt[i] == '\n') [[unlikely]]
            lineBreaks.push_back(i);
    lineBreaks.push_back(txt.size());

    sa.resize(txt.size());
    Llcp.resize(txt.size());
    Rlcp.resize(txt.size());

    build_P(txt);
    build_sa(*(P.end() - 1));
    fill_RL_lcp(txt);

    save_file(fileName);
}

int build_search(const string &fileName) {
    int rd = read_file(fileName);
    if (rd == 1) {
        return 1;
    }
    T.assign(P[0].begin(), P[0].end());
    return 0;
}

#include <iostream>
template<bool count>
vector<string> search(const vector<string> &pats) {
    vector<int> occ;

    for (auto pat : pats) {
        int L = find< true>(T, pat);
        int R = find<false>(T, pat);

        if (L <= R)
            occ.insert(occ.end(), sa.begin() + L, sa.begin() + R + 1);
    }

    if (count)
        return vector<string>(1, to_string(occ.size()));
    
    vector<int> lines;
    for (auto c : occ)
        lines.push_back(lower_bound(lineBreaks.begin(), lineBreaks.end(), c) - lineBreaks.begin());

    sort(lines.begin(), lines.end());
    lines.erase( unique( lines.begin(), lines.end() ), lines.end() );

    vector<string> ans;
    for (auto l : lines)
        ans.push_back(T.substr(lineBreaks[l - 1] + 1, lineBreaks[l] - lineBreaks[l - 1] - 1));

    return ans;
}

vector<string> search(bool count, const vector<string> &pats) {
    return count ? search< true>(pats)
                 : search<false>(pats);
}
