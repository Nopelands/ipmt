#include "main.h"
#include <iostream>
#include <fstream>

//settings

int search_buffer_bytes = 1;
int lookahead_buffer_bytes = 1;
int search_buffer_size = 1 << (8*search_buffer_bytes);
int lookahead_buffer_size = 1 << (8*lookahead_buffer_bytes);

//end settings

vector<char> intToBytes(unsigned input_int, int size) {
    vector<char> arrayOfByte(size);
    for (int i = 0; i < size; i++)
        arrayOfByte[size - 1  - i] = (input_int >> (i * 8));
    return arrayOfByte;
}

unsigned bytesToInt(unsigned char *input_char, int size) {
    unsigned result = 0;
    for (int i = 0; i < size; ++i) {
        result <<= 8;
        result |= input_char[i];
    }
    return result;
}

pair<int, int> max_prefix_match_bm_so(const string &search, const string &lookahead) {
    int last_position = 0;
    int position;
    for (unsigned i = 1; i < lookahead.size(); i++) {
        string pat = lookahead.substr(0, i);
        if (i <= 6) {
            buildShiftOr(pat);
            position = ShiftOr(search, pat);
        } else {
            buildBoyer(pat);
            position = BoyerMoore(search, pat);
        }
        if (position == -1) {
            return make_pair(last_position, i - 1);
        }
        last_position = position;
    }
    return make_pair(last_position, lookahead.size() - 1);
}

void zip77(const string &file_name) {
    ifstream input_file (file_name);
    if (input_file.is_open()) {
        ofstream output_file(file_name + ".lz77", ios::binary);
        string search_buffer(search_buffer_size, ' ');
        char *temp_buffer = new char[lookahead_buffer_size + 1];
        memset(temp_buffer, 0, lookahead_buffer_size + 1);
        input_file.read(temp_buffer, lookahead_buffer_size);
        string lookahead_buffer(temp_buffer);
        int actual_la_buffer_size = lookahead_buffer.size();
        while (actual_la_buffer_size > 0) {
            pair<int, int> aux = max_prefix_match_bm_so(search_buffer, lookahead_buffer);
            int position = aux.first;
            int length= aux.second;
            char* character = &lookahead_buffer[length];
            output_file.write(intToBytes(position, search_buffer_bytes).data(), search_buffer_bytes);
            output_file.write(intToBytes(length, lookahead_buffer_bytes).data(), lookahead_buffer_bytes);
            output_file.write(character, 1);
            search_buffer = search_buffer.substr(length + 1) + lookahead_buffer.substr(0, length + 1);
            char* aux_buffer = new char [length+2];
            memset(aux_buffer, 0, length + 2);
            input_file.read(aux_buffer, length + 1);
            string aux_string(aux_buffer);
            lookahead_buffer = lookahead_buffer.substr(length + 1) + aux_string;
            actual_la_buffer_size = lookahead_buffer.size();
            delete[] aux_buffer;
        }
        output_file.close();
        input_file.close();
    } else{ cout << "file not found" << endl;}
}

void unzip77(const string &fileName) {
    ifstream input_file (fileName, ios::binary);
    string new_name = fileName.substr(0, fileName.size() - 5);
    if (input_file.is_open()) {
        ofstream output_file(new_name + ".unlz77");
        string search_buffer(search_buffer_size, ' ');
        char *temp_buffer = new char[search_buffer_bytes + 1];
        while (true) {
            input_file.read(temp_buffer, search_buffer_bytes);
            if (input_file.eof()) {
                break;
            }
            int position = *(unsigned char*)temp_buffer;
            input_file.read(temp_buffer, lookahead_buffer_bytes);
            int length = *(unsigned char*)temp_buffer;
            input_file.read(temp_buffer, 1);
            char* character = &temp_buffer[0];
            string prefix = search_buffer.substr(position, length);
            output_file.write(prefix.data(), prefix.size());
            output_file.write(character, 1);
            search_buffer = search_buffer.substr(length+1) + prefix + character;
        }
        input_file.close();
        output_file.close();
    } else {
        cout << "file not found" << endl;
    }
}