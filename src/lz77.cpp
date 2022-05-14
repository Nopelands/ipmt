#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

//settings

int search_buffer_bytes = 1;
int lookahead_buffer_bytes = 1;
int search_buffer_size = 1 << (8*search_buffer_bytes);
int lookahead_buffer_size = 1 << (8*lookahead_buffer_bytes);

//end settings

char* intToBytes(int input_int, int size) {
    vector<unsigned char> arrayOfByte(size);
    for (int i = 0; i < size; i++)
        arrayOfByte[size - 1  - i] = (input_int >> (i * 8));
    char* result = reinterpret_cast<char*>(arrayOfByte.data());
    return result;
}

pair<int, int> max_prefix_match(const string &search, const string &lookahead) {
    return std::make_pair(0, 0);
}

void zip(const string &file_name) {
    ifstream input_file (file_name);
    ofstream output_file(file_name + ".lz77", ios::binary);
    if (input_file.is_open()) {
        string search_buffer(search_buffer_size, ' ');
        char *temp_buffer = new char[lookahead_buffer_size];
        input_file.read(temp_buffer, lookahead_buffer_size);
        string lookahead_buffer(temp_buffer);
        int actual_la_buffer_size = lookahead_buffer.size();
        while (actual_la_buffer_size > 0) {
            pair<int, int> aux = max_prefix_match(search_buffer, lookahead_buffer);
            int p = aux.first;
            int l = aux.second;
            char* c = &lookahead_buffer[l];
            output_file.write(intToBytes(p, search_buffer_bytes), search_buffer_bytes);
            output_file.write(intToBytes(l, lookahead_buffer_bytes), lookahead_buffer_bytes);
            output_file.write(c, sizeof(c));
            search_buffer = search_buffer.substr(l + 1, search_buffer.size()) + lookahead_buffer.substr(0, l + 1);
            char* aux_buffer = new char [l+1];
            input_file.read(aux_buffer, l + 1);
            string aux_string(aux_buffer);
            lookahead_buffer = lookahead_buffer.substr(l + 1, lookahead_buffer.size()) + aux_string;
            actual_la_buffer_size = lookahead_buffer.size();
        }
        input_file.close();
        output_file.close();
    } else{ cout << "file not found";}
}