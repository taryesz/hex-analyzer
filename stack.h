#include "node.h"


class stack {
private:

    node* head;
    node* tail;

public:

    stack() {
        head = nullptr;
        tail = nullptr;
    }

    [[nodiscard]] node* get_head() const {
        return head;
    }

    void push(int content, int position_x, int position_y) {

        auto* hex = new node();

        hex->set_content(content);
        hex->set_position_x(position_x);
        hex->set_position_y(position_y);

        // if the stack is empty ...
        if (head == nullptr) {

            // set both head & tail as the same node
            head = hex;
            tail = hex;

        }

        // if the stack is not empty ...
        else {

            // connect a new node to the first node in the stack
            hex->set_next(this->head);

            // update the head
            this->head = hex;

        }

    }

    node* pop() {

        // if the head of the stack doesn't exist, return null
        if (this->head == nullptr) return nullptr;

        // if the head exists, get it
        node* popped = this->head;

        // if there was only one element on the stack and the program has popped it, set to null both head and tail
        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
        }

            // if there were more than one element on the stack, scoot the whole stack by one 'to the left'
        else this->head = this->head->get_next();

        // reset the popped's connection
        popped->set_next(nullptr);

        // return the popped symbol
        return popped;

    }

    void clear() {

        // get the head of the stack
        node* current = this->head;

        // while there are elements on the stack
        while (current != nullptr) {

            // get the next symbol from the stack
            node* next = current->get_next();

            // delete the currently parsed symbol
            delete current;

            // update the currently parsed symbol with the next element
            current = next;

        }

        // after deleting all elements from the stack, make sure the key nodes are set to null
        head = nullptr;
        tail = nullptr;

    }

    int count() {

        node* iterator = this->head;
        int counter = 0;

        // while there are elements on the stack
        while (iterator != nullptr) {

            ++counter;

            // get the next symbol from the stack
            iterator = iterator->get_next();

        }

        // print the new line char for the sake of aesthetic look of the output
        return counter;

    }

};
