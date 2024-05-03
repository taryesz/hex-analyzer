#include "node.h"

node::node() {
    this->content = empty_hex_symbol;
    this->position_x = UNDEFINED;
    this->position_y = UNDEFINED;
    this->next = nullptr;
}

void node::set_content(int value) {
    content = value;
}

void node::set_position_x(int value) {
    position_x = value;
}

void node::set_position_y(int value) {
    position_y = value;
}

void node::set_next(node* value) {
    next = value;
}

[[nodiscard]] int node::get_content() const {
    return content;
}

[[nodiscard]] int node::get_position_x() const {
    return position_x;
}

[[nodiscard]] int node::get_position_y() const {
    return position_y;
}

[[nodiscard]] node* node::get_next() const {
    return next;
}
