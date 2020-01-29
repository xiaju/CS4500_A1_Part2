//
// Created by Jiawen Liu on 1/23/20.
//

#ifndef ASSIGNMENT1_PART2_STRING_H
#define ASSIGNMENT1_PART2_STRING_H

#endif //ASSIGNMENT1_PART2_STRING_H

#pragma once
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
    size_t hash();
    bool equals(Object* object);
    String* concat(String* s);
    int compareTo(String* s);
};
#endif
