//lang::CwC 
#pragma once
#include "object.h"
#include <stdlib.h>

class Node : public Object {
  public:
    Object* key_;
    Object* value_;
    //TODO should this be private?
    Node* next;

    Node(Object* key_, Object* value_) {
      this->key_ = key_;
      this->value_ = value_;
      this->next = NULL;
    }

    ~Node() {
      
    }

    Node* remove(Object* o) {
      if (this->next == NULL) {
        return NULL;
      } else if (this->next->key_->equals(o)) {
        Node* tmp = this->next;
        this->next = this->next->next;
        return tmp;
      } else {
        return this->next->remove(o);
      }
    }


    // TODO This reveals private fields sorta
    Node* get_node(Object* key) {
      if (this->key_->equals(key)) {
        return this;
      } else if (this->next != NULL) {
        return this->next->get_node(key);
      } else {
        return NULL;
      }
    }

    // TODO potential memory leak
    Object* set_value(Object* o) {
      this->value_ = o;
    }
};

class LinkedList : public Object {
  public:
    Node* cur_;
    Node* head_;

    LinkedList() {

    }

    virtual ~LinkedList() {

    }

    Node* insert(Node* n) {
      n->next = head_;
      this->head_ = n;
      return n;
    }

    Node* remove(Object* o) {
      if (this->head_ == NULL) {
        return NULL;
      } else if (this->head_->key_->equals(o)) {
        Node* tmp = this->head_;
        this->head_ = this->head_->next;
        return tmp;
      } else {
        return this->head_->remove(o);
      }
    }

    Node* get_node(Object* key) {
      if (this->head_ != NULL) {
        this->head_->get_node(key);
      } else {
        return NULL;
      }
    }

    void reset_cur() {
      this->cur_ = this->head_;
    }

    Node* get_next() {
      if (this->cur_ == NULL) {
        return NULL;
      } else {
        Node* tmp = this->cur_;
        this->cur_ = this->cur_->next;
        return tmp;
      }
    }
};
