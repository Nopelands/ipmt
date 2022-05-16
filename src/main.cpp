#include "main.h"
#include <fstream>

void help() {

    printf("\
Usage: ipmt mode [options] (pattern)* file\n\
*pattern is only used for search mode\n\
\n\
index: Create index file for subsequent search.\n\
Example: ipmt index text.txt\n\
\n\
search: Use index file to search for pattern.\n\
Example: ipmt search text index.txt\n\
\n\
zip: Compress file.\n\
Example: ipmt zip text.txt\n\
\n\
unzip: Decompress file.\n\
Example: ipmt unzip text.lz77\n\
\n\
Pattern selection and interpretation:\n\
  -a, --algorithm       force usage of selected algorithm. Options:\n\
                            lz,  lz77\n\
                            hu,  huffman\n\
                            de,  deflate (default)\n\
  -p, --pattern         use pattern file instead of pattern string\n\
\n\
Miscellaneous:\n\
  -h, --help            display this help text and exit\n\
\n\
Output control:\n\
  -c, --count           print only a count of pattern occurrences\n\
\n\
Report bugs to: /dev/null\n\
pmt home page: https://github.com/Nopelands/ipmt\n");

}

void usage() {
    printf("Usage: ipmt mode [options] (pattern)* file\nTry 'ipmt --help' for more information.\n");
}

void alg_warning() {
    printf("Unknown algorithm\nTry 'ipmt --help' for more information.\n");
}

void size_warning(const string &pat) {
    printf("Pattern %s is ignored due to its size.\nPlease, keep pattern size less than %d characters.\n", pat.c_str(), maxBinarySize + 1);
}

int main(const int argc, const char *argv[]) {
    if (argc <= 1) {
        usage();
        return 1;
    }
    string func = argv[1];
    if (func == "-h" or func == "--help") {
        help();
        return 0;
    } else if (func != "index" and func != "search" and func != "zip" and func != "unzip") {
        usage();
        return 1;
    }
    bool pat_arg = false;
    bool count = false;
    bool file_found = false;
    bool pat_found = false;
    string pattern = "";
    string algorithm = "";
    string file = "";
    for (int i = 2; i < argc; ++i) {
        string flag = argv[i];
        if (flag == "-p" or flag == "--pattern") {
            pat_arg = true;
        } else if (flag == "-c" or flag == "--count") {
            count = true;
        } else if (flag == "-h" or flag == "--help") {
            help();
            return 0;
        } else if (flag == "-a" or flag == "--algorithm") {
            algorithm = argv[i + 1];
            i++;
        } else {
            if (strcmp(argv[1], "search") == 0 and !pat_found) {
                pattern = argv[i];
                pat_found = true;
            } else {
                if (!file_found) {
                    file_found = true;
                    file = argv[i];
                } else {
                    usage();
                    return 1;
                }
            }
        }
    }
    if (file == "") {
        usage();
        return 1;
    }
    if (func == "index") {
        string fileName = file;

        ifstream rf(fileName);
        std::string txt((std::istreambuf_iterator<char>(rf)),
                         std::istreambuf_iterator<char>());
        rf.close();

        fileName = fileName.substr(0, fileName.find_last_of('.')) + ".idx";

        index(txt, fileName);
    }
    else if (func == "search") {
        bool patternFile = pat_arg;

        vector<string> pats;
        if (patternFile) {
            ifstream pat_file(pattern);

            for (string s; getline(pat_file, s);)
                if (s.size())
                    pats.push_back(s);
            pat_file.close();
        }
        else
            pats.assign(1, pattern);

        string fileName = file;
        if (fileName.substr(fileName.find_last_of('.')) != ".idx") {
            printf("%s isn't an idx index file\n", fileName.data());
            return 1;
        }
        build_search(fileName);

        for (auto l : search(count, pats))
            printf("%s\n", l.c_str());
    }
    else if (func == "zip") {
        string fileName = file;
        if (algorithm == "") {
            zip77(fileName);
        } else if (algorithm == "lz") {
            zip77(fileName);
        } else {
            alg_warning();
            return 1;
        }
    }
    else if (func == "unzip") {
        string fileName = file;
            if (algorithm == "") {
                if (fileName.substr(fileName.find_last_of('.')) != ".lz77") {
                    printf("%s isn't an lz77 compressed file\n", fileName.data());
                    return 1;
                }
                unzip77(fileName);
            } else if (algorithm == "lz") {
                if (fileName.substr(fileName.find_last_of('.')) != ".lz77") {
                    printf("%s isn't an lz77 compressed file\n", fileName.data());
                    return 1;
                }
                unzip77(fileName);
            } else {
                alg_warning();
                return 1;
            }
        }
    else
        return 1;

    return 0;
}
