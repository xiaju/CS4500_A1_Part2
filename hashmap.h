//
// Created by Jiawen Liu on 1/24/20.
//

#ifndef PART2_HASHMAP_H
#define PART2_HASHMAP_H

#endif //PART2_HASHMAP_H

#pragma once;
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
    int capacity();

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
    bool contains_key(Object* key);


    /**
     * Removes the mapping for the specified key from this map if present.
     * @param key   key whose mapping is to be removed from the map
     * @return  the previous value associated with key, or null if there was no mapping for key.
     */
    Object* remove(Object* key);


    /**
     * @return  a list of the keys contained in this map
     */
    Object** key_set();


    /**
     * @return  a list of values contained in this map
     */
    Object** values();

    size_t hash();

    bool equals(Object* object);
};