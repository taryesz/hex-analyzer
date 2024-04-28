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