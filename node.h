#include "define.h"

class node {
private:

    int content;
    int position_x;
    int position_y;
    node* next;

public:

    node();

    void set_content(int value);

    void set_position_x(int value);

    void set_position_y(int value);

    void set_next(node* value);

    [[nodiscard]] int get_content() const;

    [[nodiscard]] int get_position_x() const;

    [[nodiscard]] int get_position_y() const;

    [[nodiscard]] node* get_next() const;

};
