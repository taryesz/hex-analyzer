// this function will delete an array
template <typename ArrayType>
void free_array(ArrayType** array, const int size) {
    if (array != nullptr) {
        for (int i = 0; i < size; i++) delete [] array[i];
        delete [] array;
    }
}

// this function will create an array, and, if necessary, fill it with data
template <typename ArrayType>
ArrayType** create_array(const int size, bool initiate = false, int data = UNDEFINED) {

    auto** array = new ArrayType*[size];
    for (int i = 0; i < size; ++i) {
        array[i] = new ArrayType[size];
        if (initiate) {
            for (int j = 0; j < size; ++j) {
                array[i][j] = data;
            }
        }
    }

    return array;

}

// this function will reset an array, i.e. set its cells to some specified datum
template <typename ArrayType>
void reset_array(ArrayType** array, const int size, int value, int connect_x = UNDEFINED, int connect_y = UNDEFINED) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != connect_x && j != connect_y) array[i][j] = value;
        }
    }
}

template <typename ArrayType>
ArrayType** copy_array(ArrayType** array, const int size) {
    ArrayType** new_array = create_array<ArrayType>(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            new_array[i][j] = array[i][j];
        }
    }
    return new_array;
}

template <typename ArrayType>
void print_array(ArrayType** array, const int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
//            if (typeid(ArrayType) == typeid(bool())) {
                if (array[i][j]) printf("* ");
                else printf(". ");
//            }
//            else printf("%c ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}