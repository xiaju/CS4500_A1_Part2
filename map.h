//
// Created by Jiawen Liu on 1/24/20.
//

#ifndef PART2_Map_H
#define PART2_Map_H

#endif //PART2_Map_H

#pragma once
#include "object.h"
#include "node.h"

class Map : public Object {
public:
    LinkedList** buckets_;
    int capacity;
    int size;

    /**
     * Default constructor that constructs an empty Map with
     * the default initial capacity 16
    */
    Map() {
      this->create_ll(16);
      this->size = 0;
    }

    /**
     * Destructor that delete Map object
     */
    ~Map() {
      for (size_t i = 0; i < this->capacity; i++) {
        LinkedList* existing_list = this->buckets_[i];
        Node* cur = existing_list->get_next();
        while (cur != NULL) {
          existing_list->remove(cur->key_);
          delete cur;
          cur = existing_list->get_next();
        }
        delete this->buckets_[i];
      }
      delete this->buckets_;
    }

public:
    /**
     * Returns the number of key-value pairs in this map.
     */
    int get_size() {
      return this->size;
    }

    /**
     * Returns the capacity of the map.
     */
    int get_capacity() {
      return this->capacity;
    }

    /**
     * increase or decrease the capacity of the map
     */
    void resize() {}

    /**
     * Put the given key value pair into the map
     * If the key is already associated with a value, the new value should overwrite the previous one
     * @return  val
     */
    Object* put(Object* key, Object* val) {
      int bucket = this->get_bucket(key);
      LinkedList* existing_list = this->buckets_[bucket];
      Node* node_w_same_key = existing_list->get_node(key);
      if (node_w_same_key == NULL) {
        Node* new_node = new Node(key, val);
        existing_list->insert(new_node);
        this->size++;
        this->rehash();
      } else {
        node_w_same_key->set_value(val);
      }
      return val;
    }


    /**
     * Returns the value of which the specified key is mapped to, or nullptr if this map does not contain the given key
     * @param key   the key whose associated value is to be returned
     * @return  the value mapped to the given key, or nullptr if the key is not found
     */
    Object* get(Object* key) {
      int bucket = this->get_bucket(key);
      LinkedList* existing_list = this->buckets_[bucket];
      Node* node_w_same_key = existing_list->get_node(key);
      if (node_w_same_key != NULL) {
        return node_w_same_key->value_;
      } else {
        return NULL;
      }
    }


    /**
     * Returns true if this map contains the given key
     * @param key   The key whose presence in this map is to be tested
     * @return  true if this map contains a mapping for the specified key, otherwise false
     */
    bool contains_key(Object* key) {
      int bucket = this->get_bucket(key);
      LinkedList* existing_list = this->buckets_[bucket];
      if (existing_list == NULL) {
        return false;
      } else {
        return existing_list->get_node(key) != NULL;
      }
    }


    /**
     * Removes the mapping for the specified key from this map if present.
     * @param key
     * @return   value associated with the key, or nullptr if the key is not found
     */
    Object* remove(Object* key) {
      int bucket = this->get_bucket(key);
      LinkedList* existing_list = this->buckets_[bucket];
      Node* removed_node = existing_list->remove(key);
      if (removed_node == NULL) {
        return NULL;
      } else {
        this->size--;
        return removed_node->value_;
      }
    }


    /**
     * @return  a list of the keys contained in this map
     */
    Object** key_set() {
      Object** key_set = new Object*[this->size];
      int key_set_ind = 0;

      for (int i = 0; i < this->get_capacity(); i++) {
        LinkedList* existing_list = this->buckets_[i];
        existing_list->reset_cur();
        Node* cur = existing_list->get_next();
        while (cur != NULL) {
          key_set[key_set_ind] = cur->key_;
          key_set_ind++;
          cur = existing_list->get_next();
        }
      }
      return key_set;
    }


    //TODO code duplication
    /**
     * @return  a list of values contained in this map
     */
    Object** values() {
      Object** values = new Object*[this->size];
      int values_ind = 0;

      for (int i = 0; i < this->get_capacity(); i++) {
        LinkedList* existing_list = this->buckets_[i];
        existing_list->reset_cur();
        Node* cur = existing_list->get_next();
        while (cur != NULL) {
          values[values_ind] = cur->value_;
          cur = existing_list->get_next();
          values_ind++;
        }
      }
      return values;
      
    }

    size_t hash() {
      //TODO: hash
    }

    bool equals(Object* object) {
      Map* other = dynamic_cast<Map*>(object);
      if (other == NULL || other->get_size() != this->get_size()) {
        return false;
      }

      for (int i = 0; i < this->get_capacity(); i++) {
        LinkedList* existing_list = this->buckets_[i];
        existing_list->reset_cur();
        Node* cur = existing_list->get_next();
        while (cur != NULL) {
          if (other->get(cur->key_) != cur->value_) {
            return false;
          }
          cur = existing_list->get_next();
        }
      } 

      return true;
    }

    // helper methods
    int get_bucket(Object* o) {
      size_t h = o->hash();
      return h % this->get_capacity();
    }

    // TODO verify that this is working!
    void rehash() {
      if ((float)this->get_size() / this->get_capacity() < .75) {
        return ;
      }

      int size = this->get_size();

      Object** keys = this->key_set();
      Object** values = this->values();

      this->create_ll(this->get_capacity() * 2);
      this->size = 0;

      for (int i = 0; i < size; i++) {
        this->put(keys[i], values[i]);
      }

      delete keys;
      delete values;
    }

    void create_ll(int capacity) {
      this->capacity = capacity;
      this->buckets_ = new LinkedList*[this->capacity];
      
      for (int i = 0; i < capacity; i++) {
        this->buckets_[i] = new LinkedList();
      }
    }
};
