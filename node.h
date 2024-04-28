#include "define.h"


class node {
private:

    int content;
    int position_x;
    int position_y;
    node* next;

public:

    node() {
        this->content = empty_hex_symbol;
        this->position_x = UNDEFINED;
        this->position_y = UNDEFINED;
        this->next = nullptr;
    }

    int get_content() const {
        return content;
    }

    void set_content(int value) {
        content = value;
    }

    int get_position_x() const {
        return position_x;
    }

    void set_position_x(int value) {
        position_x = value;
    }

    int get_position_y() const {
        return position_y;
    }

    void set_position_y(int value) {
        position_y = value;
    }

    node* get_next() const {
        return next;
    }

    void set_next(node* value) {
        next = value;
    }

};
