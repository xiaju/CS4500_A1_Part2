#include "string.h"
#include "object.h"
#include <iostream>
#include <stdlib.h>

#ifndef PART2_LIST_H
#define PART2_LIST_H

#endif //PART2_LIST_H

class StrList : public Object
{
public :
    int length;
    int capacity;
    String* entries = nullptr;
public:
    StrList() {
        length = 0;
        capacity = 8;
        entries = new String[capacity];
    }
    ~StrList() {
        delete [] entries;
    }
public:
    virtual void add(size_t i, String* e);
    virtual void add_all(size_t i, StrList* c);
    virtual void push_back(String* e);
    bool equals(Object* o);
    void resize();
    void clear();
    size_t index_of(Object* o);
    String* remove(size_t i);
    String* get(size_t index);
    size_t hash();
    String* set(size_t i, String* e);
    size_t size();
};

void StrList::resize() {
    String* newEntries = new String[length * 2];
    memcpy(newEntries, entries, length * sizeof(String));
    entries = newEntries;
    capacity *= 2;
}

void StrList::push_back(String* e) {
    if (length < capacity) {
        entries[length] = *e;
        length += 1;
    } else {
        resize();
        push_back(e);
    }
}

void StrList::add(size_t i, String* e) {
    if (i > length || i < 0) {throw "index out of bound";}
    if (length < capacity) {
        memmove(entries + i + 1, entries + i, (length - i) * sizeof(String));
        entries[i] = *e;
        length += 1;
    } else {
        resize();
        add(i, e);
    }
}

void StrList::add_all(size_t i, StrList *c) {
    if (i > length || i < 0) {throw "index out of bound";}
    if (c == nullptr || c -> length == 0) {return;}
    if (c->length + length < capacity) {
        memmove(entries + i + c->length, entries + i, (length - i) * sizeof(String));
        memcpy(entries + i, c -> entries, c->length * sizeof(String));
        length += c -> length;
    } else {
        resize();
        add_all(i, c);
    }
}

void StrList::clear() {
    delete [] entries;
    entries = new String[8];
    length = 0;
    capacity = 8;
}

bool StrList::equals(Object *o) {
    StrList* input = dynamic_cast<StrList*>(o);
    if (input == nullptr || input -> length != length) {return false;}
    for(int i=0; i<length; i++) {
        if (!(entries[i]).equals(&(input -> entries[i]))) {return false;}
    }
    return true;
}

String*  StrList::get(size_t index) {
    if (index >= length || index < 0) {throw "index out of bound";}
    return &entries[index];
}

size_t StrList::hash() {
    size_t hash = 0;
    for(int i=0; i<length; i++) {
        hash += entries[i].hashCode();
        hash *= 31;
    }
    return hash;
}

size_t StrList::index_of(Object* o) {
    for (int i=0; i<length; i++) {
        if (entries[i].equals(o)) {
            return i;
        }
    }
    return -1;
}

String* StrList::remove(size_t i) {
    if (i >= length || i < 0) {throw "index out of bound";}
    String* result = entries + i;
    for (int j = i + i; j < length; j++) {
        entries[i - 1] = entries[i];
    }
    delete &entries[length--];
    return result;
}

String* StrList::set(size_t i, String* e) {
    if (i >= length || i < 0) {throw "index out of bound";}
    entries[i] = *e;
    return e;
}

size_t StrList::size() {
    return length;
}


class SortedStrList : public StrList {
public:
    SortedStrList() : StrList(){}
    ~SortedStrList(){}
public:
    void add(size_t i, String* e);
    void add_all(size_t i, StrList* c);
    void push_back(String* e);
    void sorted_add(String* e);
    void sort();
    StringWCount* count_occurrence();
    int num_of_unique_string();
};

int string_cmp(const void* a, const void* b) {
    return strcmp(((String*) a) -> data, ((String*) b) -> data);
}

void SortedStrList::sort() {
    qsort(entries, length, sizeof(String), &string_cmp);
}

void SortedStrList::sorted_add(String *e) {
    if (length < capacity) {
        int idx = 0;
        while (idx < length && entries[idx].compareTo(e) < 0) {idx ++;}
        StrList::add(idx, e);
    } else {
        resize();
        sorted_add(e);
    }
}

void SortedStrList::add(size_t i, String* e) {
    if (i > length || i < 0) {throw "index out of bound";}
    sorted_add(e);
}

void SortedStrList::push_back(String* e) {
    sorted_add(e);
}

void SortedStrList::add_all(size_t i, StrList* c) {
    if (i > length || i < 0) {throw "index out of bound";}
    if (c->length + length <  capacity) {
        memmove(entries + i + c->length, entries + i, (length - i) * sizeof(String));
        memcpy(entries + i, c -> entries, c->length * sizeof(String));
        length += c -> length;
        sort();
    } else {
        resize();
        add_all(i, c);
    }
}

//get the number of unique strings in the list
int SortedStrList::num_of_unique_string() {
    int result = 0, idx = 0;
    String* prev = nullptr;
    while(idx < length) {
        if (! entries[idx].equals(prev)) {
            prev = &entries[idx];
            result ++;
        }
        idx ++;
    }
    return result;
}

//get the number of occurrence for each unique string in the list
StringWCount *SortedStrList::count_occurrence() {
    if (length < 1) {return nullptr;}
    int idx = 0, count = 1, next = 0;
    String* prev = nullptr;
    StringWCount* result = new StringWCount[num_of_unique_string()];
    while(idx < length) {
        if (entries[idx].equals(prev)) {
            count ++;
        } else {
            if (prev != nullptr) {
                StringWCount *temp = new StringWCount(prev->data, count);
                result[next++] = *temp;
            }
            prev = &entries[idx];
            count = 1;
        }
        idx ++;
    }
    StringWCount *temp = new StringWCount(prev->data, count);
    result[next++] = *temp;
    return result;
}

