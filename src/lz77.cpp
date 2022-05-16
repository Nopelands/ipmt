#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

//settings

int search_buffer_bytes = 258;
int lookahead_buffer_bytes = 258;
int search_buffer_size = 1 << (8*search_buffer_bytes);
int lookahead_buffer_size = 1 << (8*lookahead_buffer_bytes);

//end settings

vector<char> intToBytes(unsigned input_int, int size) {
    vector<char> arrayOfByte(size);
    for (int i = 0; i < size; i++)
        arrayOfByte[size - 1  - i] = (input_int >> (i * 8));
    return arrayOfByte;
}

pair<int, int> max_prefix_match(const string &search, const string &lookahead) {
    int n = search.size();
    int m = lookahead.size() - 1;
    int p = 0;
    int l = 0;
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (i + j < n and j < m and lookahead[j] == search[i + j]) {
            j++;
        }
        if (j > l) {
            l = j;
            p = i;
        }
    }
    return std::make_pair(p,l);
}

void zip77(const string &file_name) {
    ifstream input_file (file_name);
    ofstream output_file(file_name + ".lz77", ios::binary);
    if (input_file.is_open()) {
        string search_buffer(search_buffer_size, ' ');
        char *temp_buffer = new char[lookahead_buffer_size + 1];
        memset(temp_buffer, 0, lookahead_buffer_size + 1);
        input_file.read(temp_buffer, lookahead_buffer_size);
        string lookahead_buffer(temp_buffer);
        int actual_la_buffer_size = lookahead_buffer.size();
        while (actual_la_buffer_size > 0) {
            pair<int, int> aux = max_prefix_match(search_buffer, lookahead_buffer);
            int p = aux.first;
            int l = aux.second;
            char* c = &lookahead_buffer[l];
            output_file.write(&intToBytes(p, search_buffer_bytes)[0], search_buffer_bytes);
            output_file.write(&intToBytes(l, lookahead_buffer_bytes)[0], lookahead_buffer_bytes);
            output_file.write(c, 1);
            search_buffer = search_buffer.substr(l + 1) + lookahead_buffer.substr(0, l + 1);
            char* aux_buffer = new char [l+2];
            memset(aux_buffer, 0, l + 2);
            input_file.read(aux_buffer, l + 1);
            string aux_string(aux_buffer);
            lookahead_buffer = lookahead_buffer.substr(l + 1) + aux_string;
            actual_la_buffer_size = lookahead_buffer.size();
            delete[] aux_buffer;
        }
        input_file.close();
        output_file.close();
    } else{ cout << "file not found";}
}

void unzip77(const string &fileName) {
    ifstream input_file (fileName, ios::binary);
    string new_name = fileName.substr(0, fileName.size() - 5);
    ofstream output_file(new_name + ".unlz77");
    if (input_file.is_open()) {
        string search_buffer(search_buffer_size, ' ');
        char *temp_buffer = new char[search_buffer_bytes + 1];
        while (true) {
            input_file.read(temp_buffer, search_buffer_bytes);
            if (input_file.eof()) {
                break;
            }
            int p = *(unsigned char*)temp_buffer;
            input_file.read(temp_buffer, lookahead_buffer_bytes);
            int l = *(unsigned char*)temp_buffer;
            input_file.read(temp_buffer, 1);
            char* c = &temp_buffer[0];
            string prefix = search_buffer.substr(p, l);
            output_file.write(prefix.data(), prefix.size());
            output_file.write(c, 1);
            search_buffer = search_buffer.substr(l+1) + prefix + c;
        }
        input_file.close();
        output_file.close();
    }
}