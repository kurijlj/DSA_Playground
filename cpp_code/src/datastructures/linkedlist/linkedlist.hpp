/* ==========================================================================
 * linkedlist.hpp - A header only implementation of a linked list.
 *
 *  Copyright (C) 2023 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * ========================================================================== */


/* ==========================================================================
 *
 * 2023-12-02 Ljubomir Kurij <ljubomir_kurij@protonmail.com>
 *
 * * linkedlist.hpp: created.
 *
 * ========================================================================== */


#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP


/* ==========================================================================
 * Headers include section
 * ========================================================================== */

/* Standard Library headers */
#include <iostream>
#include <string>


/* ==========================================================================
 * Abstract Data Types Definition Section
 * ========================================================================== */
class LinkedList {
private:
    /* Inner classes */
    class Node {
    private:
        /* data */
        int data_;
        Node *next_;

    public:
        Node(int data) : data_(data), next_(nullptr) {};
        ~Node() {};
        void print(void);
        std::string string();
        void data(int data);
        int data(void);
        void next(Node *next);
        Node *next(void);
    };

private:
    /* data */
    LinkedList::Node *head_;
    LinkedList::Node *tail_;
    int size_;

public:
    LinkedList();
    ~LinkedList();
    void print(void);
    std::string string(void);
    void append(int data);
    void prepend(int data);
    void insert(int data, int index);
    Node *remove(int index);
    Node *get(int index);
    int size(void);
    void set(int data, int index);
    Node *pop_back(void);
    Node *pop_front(void);
    void reverse(void);
};


/* ==========================================================================
 * Methods Definitions Section
 * ========================================================================== */
void LinkedList::Node::print(void) {
    std::cout << this->string() << std::endl;
}

std::string LinkedList::Node::string(void) {
    std::string str = "Node(" + std::to_string(this->data()) + ")";
    return str;
}

void LinkedList::Node::data(int data) {
    this->data_ = data;
}

int LinkedList::Node::data(void) {
    return this->data_;
}

void LinkedList::Node::next(Node *next) {
    this->next_ = next;
}

LinkedList::Node *LinkedList::Node::next(void) {
    return this->next_;
}

LinkedList::LinkedList() {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
}

LinkedList::~LinkedList() {
    LinkedList::Node *current = this->head_;
    LinkedList::Node *next = nullptr;
    while (current != nullptr) {
        next = current->next();
        delete current;
        current = next;
    }
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
}

void LinkedList::print(void) {
    std::cout << this->string() << std::endl;
}

std::string LinkedList::string(void) {
    std::string str = "LinkedList(";
    LinkedList::Node *current = this->head_;
    while (current != nullptr) {
        str += std::to_string(current->data());
        current = current->next();
        if (current != nullptr) {
            str += ", ";
        }
    }
    str += ")";

    return str;
}

void LinkedList::append(int data) {
    LinkedList::Node *node = new LinkedList::Node(data);
    if (this->head_ == nullptr) {
        this->head_ = node;
        this->tail_ = node;
    } else {
        this->tail_->next(node);
        this->tail_ = node;
    }
    this->size_++;
}

void LinkedList::prepend(int data) {
    LinkedList::Node *node = new LinkedList::Node(data);
    if (this->head_ == nullptr) {
        this->head_ = node;
        this->tail_ = node;
    } else {
        node->next(this->head_);
        this->head_ = node;
    }
    this->size_++;
}

void LinkedList::insert(int index, int data) {
    if (index < 0 || index > this->size_) {
        throw std::out_of_range("Index out of range");
    }

    if (index == 0) {
        this->prepend(data);
    } else if (index == this->size_) {
        this->append(data);
    } else {
        LinkedList::Node *node = new LinkedList::Node(data);
        LinkedList::Node *prev = this->get(index - 1);
        node->next(prev->next());
        prev->next(node);
        this->size_++;
    }
}

LinkedList::Node *LinkedList::remove(int index) {
    if (index < 0 || index >= this->size_) {
        throw std::out_of_range("Index out of range");
    }

    LinkedList::Node *node = nullptr;
    if (index == 0) {
        node = this->pop_front();
    } else if (index == this->size_ - 1) {
        node = this->pop_back();
    } else if (this->head_ == this->tail_) {
        node = this->head_;
        this->head_ = nullptr;
        this->tail_ = nullptr;
        this->size_--;
    } else {
        LinkedList::Node *prev = this->get(index - 1);
        node = prev->next();
        prev->next(node->next());
        this->size_--;
    }

    return node;
}

LinkedList::Node *LinkedList::get(int index) {
    if (index < 0 || index >= this->size_) {
        throw std::out_of_range("Index out of range");
    }

    LinkedList::Node *current = this->head_;
    for (int i = 0; i < index; i++) {
        current = current->next();
    }

    return current;
}

int LinkedList::size(void) {
    return this->size_;
}

void LinkedList::set(int index, int data) {
    if (index < 0 || index >= this->size_) {
        throw std::out_of_range("Index out of range");
    }

    LinkedList::Node *node = this->get(index);
    node->data(data);
}

LinkedList::Node *LinkedList::pop_back(void) {
    LinkedList::Node *node = this->tail_;
    if (this->head_ == this->tail_) {
        this->head_ = nullptr;
        this->tail_ = nullptr;
    } else {
        LinkedList::Node *prev = this->get(this->size_ - 2);
        prev->next(nullptr);
        this->tail_ = prev;
    }
    this->size_--;
    return node;
}

LinkedList::Node *LinkedList::pop_front(void) {
    LinkedList::Node *node = this->head_;
    if (this->head_ == this->tail_) {
        this->head_ = nullptr;
        this->tail_ = nullptr;
    } else {
        this->head_ = this->head_->next();
    }
    this->size_--;
    return node;
}

void LinkedList::reverse(void) {
    LinkedList::Node *prev = nullptr;
    LinkedList::Node *current = this->head_;
    LinkedList::Node *next = nullptr;
    while (current != nullptr) {
        next = current->next();
        current->next(prev);
        prev = current;
        current = next;
    }
    this->tail_ = this->head_;
    this->head_ = prev;
}

#endif  /* LINKEDLIST_HPP */