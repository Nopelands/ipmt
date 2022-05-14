#include "main.h"
#include <fstream>

int main(const int argc, const char *argv[]) {

    if (argc < 3)
        return 1;
    
    string func = argv[1];
    if (func == "index") {
        string fileName = argv[2];

        ifstream rf(fileName);
        std::string txt((std::istreambuf_iterator<char>(rf)),
                         std::istreambuf_iterator<char>());
        rf.close();

        fileName = fileName.substr(0, fileName.find_last_of('.')) + ".idx";

        index(txt, fileName);
    }
    else if (func == "search") {
        bool patternFile = false, count = false;
        int c = 2;

        while (    string(argv[c]) == "-c" || string(argv[c]) == "--count"
                || string(argv[c]) == "-p" || string(argv[c]) == "--patternfile") {
            
            if (string(argv[c]) == "-c" || string(argv[c]) == "--count")
                count = true;
            else
                patternFile = true;

            c++;
        }

        vector<string> pats;
        if (patternFile) {
            ifstream file(argv[c]);

            for (string s; getline(file, s);)
                if (s.size())
                    pats.push_back(s);

            file.close();
        }
        else
            pats.assign(1, argv[c]);

        string fileName = argv[c + 1];
        build_search(fileName);

        for (auto l : search(count, pats))
            printf("%s\n", l.c_str());
    }
    else if (func == "zip") {
        string fileName = argv[argc - 1];
        zip(fileName);
    }
    else if (func == "unzip") {
        string fileName = argv[argc - 1];
        unzip(fileName);
    }
    else
        return 1;

    return 0;
}
