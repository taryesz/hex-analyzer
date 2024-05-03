#include "node.h"


class stack {
private:

    node* head;
    node* tail;

public:

    stack();

    void push(int content, int position_x, int position_y);

    void clear();

    [[nodiscard]] node* pop();

    [[nodiscard]] node* get_head() const;

    [[nodiscard]] int count();

};
