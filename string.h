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
    int length_;
    char* str_;

    String() {
      this->length_ = 0;
      this->str_ = new char('\0');
    }
    String(int capacity) {
      this->length_ = capacity;
      this->str_ = new char[capacity];
      this->str_[capacity - 1] = '\0';
    }
    String(char* s) {
      this->length_ = strlen(s);
      this->str_ = new char[this->length_];
      strcpy(this->str_, s);
      this->length_ = strlen(s);
    }

    ~String() {
      delete this->str_;
    }

    size_t hash() {
      int hash = 7;
      char* s = this->str_;
      for (size_t i = 0; i < strlen(s); i++) {
        hash = hash * 31 + s[i];
      }
      return hash; 
    }

    bool equals(Object* object) {
      String* other = dynamic_cast<String*>(object);

      if (object == NULL) {
        return false;
      } else {
        return strcmp(this->str_, other->str_) == 0;
      }
    }

    String* concat(String* s) {
      size_t otherSize = strlen(s->str_);
      size_t thisSize = strlen(this->str_);
      char* c = s->str_;
      char *newstr = new char[otherSize + thisSize + 1];
      memcpy(newstr, this->str_, thisSize);
      memcpy(&newstr[thisSize], c, otherSize);
      newstr[otherSize + thisSize] = '\0';
      String* ret = new String(newstr);
      delete newstr;
      return ret;
    }

    int compareTo(String* s) {
      int cmp = strcmp(this->str_, s->str_);
      return cmp;
    }
};
#endif
