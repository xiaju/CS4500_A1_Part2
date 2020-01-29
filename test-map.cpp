#include <iostream>
#include <string.h>
#include "map.h"
#include "string.h"


void FAIL() {   exit(1);    }
void OK(const char* m) { std:: cout << "All test cases in test " << m << " are passed" << std:: endl;}
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }


/**
 * test cases for put() and get_size() methods
 * put an object(in this case we used string) will increase the size of Map
 */

void test1() {
    Map* h1 = new Map();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    t_true(h1->get_size() == 1);
    h1->put(key_2, val_2);
    t_true(h1->get_size() == 2);
    OK("1");
}

/**
 * test cases for put() and get_size() method when using the same key
 *  the map's size remains the same, the previous value should be overwritten
 */
void test2() {
    Map* h1 = new Map();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    t_true(h1->get_size() == 1);
    h1->put(key_1, val_2);
    t_true(h1->get_size() == 1);
    t_false(val_1 -> equals(h1->get(key_1)));
    OK("2");
}

/**
 * test cases for get() methods
 * comparing value extracting from Map with input value
 */
void test3() {
    Map* h1 = new Map();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    t_true(h1->get(key_1)->equals(val_1));
    t_true(h1->get(key_2)->equals(val_2));
    OK("3");
}

/**
 * get() returns nullptr if there's no mapping for the given key in the map
 */
void test4() {
    Map* h1 = new Map();
    t_true(h1 -> get(new String("1")) == nullptr);
    OK("3");
}


/**
 * test cases for remove() method
 * remove returns the value mapped to the given key if the key exists in the map
 * remove returns nullptr if the key does not exist
 */

void test5() {
    Map* h1 = new Map();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    t_true(h1->remove(key_1)->equals(val_1));
    t_false(h1->remove(key_2)->equals(val_1));
    t_true(h1->remove(key_1) == nullptr);
    OK("5");
}

/**
 * test cases for contains_key() method
 * contains_key returns true/false if the key exist/not exist in the map
 */
void test6() {
    Map* h1 = new Map();
    String * key_1 = new String("Hello");
    String * val_1 = new String("1");
    String * key_2 = new String("World");
    String * val_2 = new String("2");
    String * key_3 = new String("NEU");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    t_true(h1->contains_key(key_1));
    t_true(h1->contains_key(key_2));
    t_false(h1->contains_key(key_3));
    OK("6");
}


/**
 * test cases for key_set() function
 * testing on key_set() function which should return all keys in the Map
 */
void test7() {
    Map* h1 = new Map();
    String * key_1 = new String("A");
    String * val_1 = new String("1");
    String * key_2 = new String("B");
    String * val_2 = new String("2");
    String * key_3 = new String("C");
    String * val_3 = new String("3");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    h1->put(key_3, val_3);
    Object** keys_array;
    keys_array =  h1->key_set();
    t_true(key_1 -> equals(keys_array[0]));
    t_true(key_2 -> equals(keys_array[1]));
    t_true(key_3 -> equals(keys_array[2]));
    OK("8");
}


/**
 * test cases for values() function
 * testing on keys() function that return all values that exist in the Map
 */
void test8() {
    Map* h1 = new Map();
    String * key_1 = new String("A");
    String * val_1 = new String("1");
    String * key_2 = new String("B");
    String * val_2 = new String("2");
    String * key_3 = new String("C");
    String * val_3 = new String("3");
    h1->put(key_1, val_1);
    h1->put(key_2, val_2);
    h1->put(key_3, val_3);
    Object** values_array = h1->values();
    Object** keys_array = h1->key_set();
    t_true(val_1 -> equals(keys_array[0]));
    t_true(val_2 -> equals(keys_array[1]));
    t_true(val_3 -> equals(keys_array[2]));
    OK("9");
}





int main() {
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    return 0;
}
