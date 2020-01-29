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

    Node* insert(Node* n) {
      this->next = n;
      return n;
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
