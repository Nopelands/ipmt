#include "main.h"
#include <iostream>
#include <fstream>
#include <string>

//settings

search_buffer_bytes = 1;
lookahead_buffer_bytes = 1;
search_buffer_size = 1 << (8*sbufbytes);
lookahead_buffer_size = 1 << (8*labufbytes);

//end settings

vector<unsigned char> intToBytes(int input_int, int size) {
    vector<unsigned char> arrayOfByte(size);
    for (int i = 0; i < size; i++)
        arrayOfByte[size - 1  - i] = (paramInt >> (i * 8));
    return arrayOfByte;
}

pair<int> max_prefix_match(const string &search, const string &lookahead) {
    return std::make_pair(0, 0);
}

void zip(const string &file_name) {
    ifstream input_file (file_name);
    ofstream output_file(file_name + ".lz77", ios::binary);
    if (input_file.is_open()) {
        string search_buffer(search_buffer_size, ' ');
        string lookahead_buffer = input_file.read(lookahead_buffer_size);
        int actual_la_buffer_size = lookahead_buffer.size();
        while (actual_la_buffer_size > 0) {
            pair<int> aux = max_prefix_match(search_buffer, lookahead_buffer);
            int p = aux[0];
            int l = aux[1];
            char c = lookahead_buffer[l];
            output_file.write(intToBytes(p, search_buffer_bytes));
            output_file.write(intToBytes(l, lookahead_buffer_bytes));
            output_file.write(c);
            search_buffer = search_buffer.substr(l + 1, search_buffer.size()) + lookahead_buffer.substr(0, l + 1);
            lookahead_buffer = lookahead_buffer.substr(l + 1, lookahead_buffer.size()) + input_file.read(l + 1);
            actual_la_buffer_size = lookahead_buffer.size();
        }
        input_file.close();
        output_file.close();
    } else{ cout << "file not found"}
}