//
// Created by Jiawen Liu on 1/23/20.
//

#ifndef ASSIGNMENT1_PART2_STRING_H
#define ASSIGNMENT1_PART2_STRING_H

#endif //ASSIGNMENT1_PART2_STRING_H

#pragma once;
#include "object.h"
#include <stdio.h>
#include <string.h>

#ifndef STRING_H
#define STRING_H

class String: public Object
{
public :
    int length;
    char* data;
public:
    String();
    String(int capacity);
    String(char* s);
    ~String();

public:
    int hashCode();
    bool equals(Object* object);
    String* concat(String* s);
    int compareTo(String* s);
};

String::String() : Object(){
    length = 0;
    data = new char[1];
    this->data[0] = '\0';
}

String::String(int length): Object() {
    length = length;
    data = new char[length+1];
}

String::String(char* s) : Object() {
    if(s == nullptr) {
        length = 0;
        data = new char[1];
        data[0] = '\0';
    } else {
        length = strlen(s);
        data = new char[length + 1];
        strcpy(data, s);
    }
}

String::~String() {
    delete [] data;
}

int String::hashCode() {
    if (length) {
        int hash = 0;
        for (int i=0; i<length; i++) {
            hash = 31* hash + int(data[i]);
        }
        return hash;
    }
    return 0;
}

bool String::equals(Object* object) {
    String* input = dynamic_cast<String*>(object);
    if (input != nullptr && input->length == length) {
        return ((int)strcmp(data, input -> data) == 0);
    }
    return false;
}

String* String::concat(String* s) {
    String* result = new String(this -> length + s -> length);
    if (s->length > 0) {
        memcpy(result->data, data, length * sizeof(char));
        memcpy(result->data + length, s->data, s -> length * sizeof(char));
        result -> data[s->length + length] = '\0';
    }
    return result;
}

// a negative number means this < s;
int String::compareTo(String* s) {
    if (s == nullptr) {return this == nullptr;}
    return strcmp(data, s -> data);
}

class StringWCount: public String {
public:
    int count;
    StringWCount(char* data, int count): String(data), count(count) {}
    StringWCount(): String(), count(0){}
    int get_count(){return count;}
};

#endif
