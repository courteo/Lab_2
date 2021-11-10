#ifndef ARRAYSEQUENCE_H
#define ARRAYSEQUENCE_H

#include "dynamic_array.h"
#include <iostream>

template<class T>
class ArraySequence{
private:
    Dynamic_array<T> dynArr;
public:
//    class IndexOutOfRange();
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    ArraySequence<T> &operator = (const ArraySequence<T> &arraySequence) {

        dynArr = arraySequence.dynArr;
        return *this;
    }

    ArraySequence<T> &operator = (ArraySequence<T> *arraySequence) {
        dynArr = arraySequence->dynArr;
        return *this;
    }

    int get_len(){
        return dynArr.get_len();
    }

    ArraySequence() {
        dynArr = Dynamic_array<T>();
    }

    explicit ArraySequence(int size){
        dynArr = Dynamic_array<T>(size);

    }

    explicit ArraySequence(int count, T* items) {
        dynArr = Dynamic_array<T>(items, count);
    }

    ArraySequence(const ArraySequence<T> &array) {
        dynArr = array.dynArr;
    }

    //explicit ArraySequence(Sequence<T> &sequence) {
    //    for (int i = 0; i < sequence.get_len(); i++) {
    //        append(sequence[i]);
    //    }
    //}

    explicit ArraySequence(const Dynamic_array<T> &array) {
        dynArr = array;
    }

    T get_first() {
        if (dynArr.get_len() == 0) throw IndexOutOfRange(get_len(), get_len());
        return dynArr.get_first();
    }

    T get_last() {
        if (dynArr.get_len() == 0) throw IndexOutOfRange(get_len(), get_len());
        return dynArr.get_last();
    }

    T get_i(int index) {
        if (index < 0 || index >= dynArr.get_len())
            throw IndexOutOfRange(get_len(), index);
        return dynArr.get_i(index);
    }

    T &operator[](int index) {
        if (index < 0 || index >= get_len())
            throw IndexOutOfRange(get_len(), index);
        return dynArr[index];
    }

    void set_i(int index,T item) {
        if (index < 0 || index >= dynArr.get_len()) throw IndexOutOfRange(get_len(), index);
        dynArr.set_i(index, item);
    }

    ArraySequence<T> *getSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= dynArr.get_len())
            throw IndexOutOfRange(get_len(), startIndex);
        if (endIndex < 0 || endIndex > dynArr.get_len())
            throw IndexOutOfRange(get_len(), endIndex);

        auto *newArr = new ArraySequence<T>;
        for (int i = startIndex; i <= endIndex; i += 1) {

            newArr->append(dynArr.get_i(i));
        }
        return newArr;
    }

    ArraySequence<T>* clone(){
        return new ArraySequence<T>(*this);
    }

    ArraySequence<T>* empty(){
        return new ArraySequence<T>();
    }

    void append(T item){
        dynArr.resize(dynArr.get_len() + 1);
        dynArr.set_i(get_len() - 1, item);
    }


    void prepend(T item){

        dynArr.resize(dynArr.get_len() + 1);
        for (int i = dynArr.get_len() - 1; i > 0; i--) {
            dynArr.set_i(i, dynArr.get_i(i - 1));
        }
        dynArr.set_i(0, item);
    }

    void clear(){
        dynArr.resize(0);
    }

    //void remove(int from) {
    //    if (from < 0 || from >= dynArr.get_len()) throw IndexOutOfRange(get_len(), from);
    //    dynArr.resize(from);
    //}

    void remove(int from, int to) {
        if (from < 0 || from >= dynArr.get_len()) throw IndexOutOfRange(get_len(), from);
        if (to < 0 || to >= dynArr.get_len()) throw IndexOutOfRange(get_len(), to);

        if (from >= to) return;

        for (int i = 0; i + to < dynArr.get_len(); i++) {
            dynArr.set_i(i + from, dynArr.get_i(i + to));
        }
        dynArr.resize(dynArr.get_len() - to + from);
    }

    void insert(T item, int index){
        if (index < 0 || index >= dynArr.get_len()) throw IndexOutOfRange(get_len(), index);
        dynArr.resize(dynArr.get_len()+ 1);
        for (int i = dynArr.get_len() - 2; i >= index; i--) {
            dynArr.set_i(i + 1, dynArr.get_i(i));
        }
        //std::cout << dynArr[0] << " " << dynArr[1] << std::endl;
        dynArr.set_i(index, item);
        //std::cout << dynArr[0] << " " << dynArr[1] << std::endl;
    }

    ArraySequence<T> *concat(ArraySequence<T>* sequence) {
        auto *newArr = new ArraySequence<T>;
        newArr->dynArr = this->dynArr;


        int start = dynArr.get_len();
        newArr->dynArr.resize(start + sequence->get_len());
        for (int i = 0; i < sequence->get_len(); i++) {
            newArr->set_i(i +start, sequence->get_i(i));
        }
        this->dynArr = newArr->dynArr;
        return  this;
    }

     int where(T item) {
        for (int i = 0; i < dynArr.get_len(); i++){
            //if (dynArr.get_i(i) == item) {
                return i;
            //}
        }
        return -1;
    }

    ArraySequence<ArraySequence<T>*> *split(int index) {
        if (index < 0 || index >= get_len())
            throw IndexOutOfRange();

        auto *NewArr1 = new ArraySequence<T>;
        auto *NewArr2 = new ArraySequence<T>;
        auto *NewArr = new ArraySequence<ArraySequence<T>*>;
        for (int i = 0; i < index; i++){
            NewArr1->append(dynArr.get_i(i));
        }

        for (int i = index + 1; i < dynArr.get_len(); i++){
            NewArr2->append(dynArr.get_i(i));
        }
        NewArr->append(NewArr1);
        NewArr->append(NewArr2);
        return NewArr;
    }

    ArraySequence<Dynamic_array<T>*>* zip(ArraySequence<T> dar){
        if (dar.get_len() <= 0) throw IndexOutOfRange(dar.get_len(), 0);

        auto *NewArr = new ArraySequence<Dynamic_array<T>*>;
        int min;
        if (this->dynArr.get_len() < dar.dynArr.get_len()){

            min = this->dynArr.get_len();
        }
        else {

            min = dar.dynArr.get_len();
        }

        for (int i = 0; i < min; i++){

            auto *tuple = new Dynamic_array<T>(2);
            tuple->set_i(0, get_i(i));
            tuple->set_i(1, dar.get_i(i));
            NewArr->append(tuple);
        }
//        for (int i = 0; i < NewArr->get_len(); i++){
//            std::cout << '{';
//            for (int j = 0; j < NewArr->get_i(i)->get_len(); j++){
//                std::cout << NewArr->get_i(i)->get_i(j) << ", ";
//            }
//            std::cout << "\b\b}, ";
//        }
//        std::cout << "\b\b\n";
        return NewArr;
    }

    T pop(int index) {
        if (index < 0 || index >= dynArr.get_len())
            throw IndexOutOfRange(dynArr.get_len(), index);

        T item = dynArr[index];
        for (int i = index; i < dynArr.get_len() - 1; i++) {
            set_i(i, dynArr.get_i(i+1));
        }
        dynArr.resize(dynArr.get_len() - 1);
        return item;
    }

    bool operator == (ArraySequence<T>& arr1){
        if (get_len() != arr1.get_len())
            return false;

        for (int i = 0; i < arr1.get_len(); i++){
            if (arr1[i] != operator[](i)){
                return false;
            }
        }
        return true;
    }

};

template<class T>
std::ostream& operator<< (std::ostream &out, ArraySequence<T> &arr){
    for (int i = 0; i < arr.get_len(); i++){
        std::cout << arr[i] << " ";
    }
    return std::cout << std::endl;
}



#endif // ARRAYSEQUENCE_H
