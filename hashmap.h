//
// Created by Jiawen Liu on 1/24/20.
//

#ifndef PART2_HASHMAP_H
#define PART2_HASHMAP_H

#endif //PART2_HASHMAP_H

#pragma once;
#include <cstring>
#include "object.h"
#include "hashnode.h"

class Hashmap : public Object {

private:
    Hashnode** table;
    int size;
    int capacity;


public:
    /**
     * Default constructor that constructs an empty HashMap with
     * the default initial capacity 16
    */
    Hashmap();

    /**
     * Destructor that delete Hashmap object
     */
    ~Hashmap();

public:
    /**
     * Returns the number of key-value (Hashnode) mappings in this map.
     */
    int get_size();

    /**
     * Returns the capacity of key-value (Hashnode) mappings in this map.
     */
    int get_cap();

    /**
     * return index for hashcode of key
     * @param key       the key that used to be hashed and get location of an object that needs to be stored
     * @return index    index of the inner array
     */
    int index_for(Object* key);

    /**
     * resize of inner array when size hits its threshold(capacity)
     */
    void resize();


    /**
     * Associates the specified value with the specified key in this map.
     * If the map previously contained a mapping for the key, the old value is replaced.
     * @param key   key with which the specified value is to be associated
     * @param val   value to be associated with the specified key
     * @return  the previous value associated with key, or null if there was no mapping for key.
     */
    Object* put(Object* key, Object* val);


    /**
     * Returns the value to which the specified key is mapped, or null if this map contains no mapping for the key.
     * @param key   the key whose associated value is to be returned
     * @return  the value to which the specified key is mapped, or null if this map contains no mapping for the key
     */
    Object* get(Object* key);


    /**
     * Returns true if this map contains a mapping for the specified key.
     * @param key   The key whose presence in this map is to be tested
     * @return  true if this map contains a mapping for the specified key, otherwise false
     */
    bool containsKey(Object* key);


    /**
     * Removes the mapping for the specified key from this map if present.
     * @param key   key whose mapping is to be removed from the map
     * @return  the previous value associated with key, or null if there was no mapping for key.
     */
    Object* remove(Object* key);


    /**
     * @return  a list of the keys contained in this map
     */
    Object** keys();


    /**
     * @return  a list of values contained in this map
     */
    Object** values();

};
Hashmap:: Hashmap() : Object(){
    table = new Hashnode* [16];
    size = 0;
    capacity = 16;
    for(int i = size; i < capacity; i++){
        table[i] = nullptr;
    }
}

Hashmap:: ~Hashmap() {
    delete[] table;
}

int Hashmap:: get_size(){
    return size;
}

int Hashmap:: get_cap(){
    return capacity;
}

int Hashmap:: index_for(Object* key) {
    if(key) {
        return key->hashCode() & (capacity - 1);
    }
}

void Hashmap:: resize() {
    capacity *= 2;
    Hashnode** newTable = new Hashnode* [capacity];
    for(int i = 0; i < size; i++){
        Hashnode* needAdd = new Hashnode(table[i]);
        while(table[i] != NULL) {
            int index = index_for(needAdd->_key);
            while(newTable[index] != NULL) {
                newTable[index] = newTable[index]->next;
            }
            newTable[index] = needAdd;
            table[i] = table[i]->next;
        }
    }
    delete [] table;
    table = newTable;
}

Object* Hashmap:: put(Object* key, Object* val) {

    if(size == capacity) {
        resize();
    }

    int index = index_for(key);

    Hashnode* node = new Hashnode(key, val);

    Hashnode* cur = table[index];

    if(cur == NULL) {
        table[index] = node;
        size++;
    }
    else {
        while(cur->next != NULL) {
            if(cur->_key->equals(key)){
                cur->_value = val;
                return cur->_value;
            }
            cur = cur->next;
        }

        if(cur->_key->equals(key)) {
            cur->_value = val;
        } else {
            cur->next = node;
            size++;
        }
    }
    return NULL;
}


Object* Hashmap:: get(Object* key){
    int index = index_for(key);

    Hashnode* cur = table[index];

    while(cur != NULL){
        if(cur->_key->equals(key)){
            return cur->_value;
        }
        cur = cur->next;
    }
    return NULL;
}

bool Hashmap:: containsKey(Object* key){
    int index = index_for(key);

    Hashnode* cur = table[index];

    while(cur != NULL){
        if(cur->_key->equals(key)){
            return true;
        }
        cur = cur->next;
    }
    return false;
}

Object* Hashmap:: remove(Object* key) {
    int index = index_for(key);
    Hashnode* cur = table[index];
    Hashnode* pre = NULL;

    while(cur != NULL){
        if(cur->_key->equals(key)){
            if(pre != NULL){
                pre->next = cur->next;
            } else {
                table[index] = cur->next;
            }
            size--;
            return cur->_value;
        }
        else{
            pre = cur;
            cur = cur->next;
        }
    }
    return NULL;
}

Object** Hashmap:: keys(){
    Object** result = new Object*[size];
    int key_size = 0;
    for(int i = 0; i < capacity; i++){
        Hashnode* cur = table[i];
        while(cur != NULL){
            result[key_size] = cur->_key;
            cur = cur->next;
            key_size++;
        }
    }
    return result;
}

Object** Hashmap:: values() {
    Object** result = new Object*[size];
    int key_size = 0;
    for(int i = 0; i < capacity; i++){
        Hashnode* cur = table[i];
        while(cur != NULL){
            result[key_size] = cur->_value;
            cur = cur->next;
            key_size++;
        }
    }
    return result;
}