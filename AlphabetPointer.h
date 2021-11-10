#ifndef LAB_2_ALPHABETPOINTER_H
#define LAB_2_ALPHABETPOINTER_H
#include "arraysequence.h"
#include "string"

class AlphabetPointer {
private:
    struct Couple {
        std::string p_word;
        int p_number;

        Couple(): p_word(""), p_number(0);
        explicit Couple(std::string word, int number): p_word(word), p_number(number);


    };

    int p_NumberOfPages;
    int p_SizeOfPage;
    ArraySequence<Couple> Alphabet;
public:

    AlphabetPointer(int SizeOfPage = 0, int NumberOfPages = 0){
        p_SizeOfPage = SizeOfPage;
        p_NumberOfPages = NumberOfPages;
    }


    int GetNumberOfPages(){
        return p_NumberOfPages;
    }

    int GetSizeOfPage(){
        return p_SizeOfPage;
    }

    void SetSizeOfPage(int NewSize){
        if (NewSize / 2< Alphabet.operator[](0).p_word.size())
            return;
        int tempNumber = 0;
        int Size = 0;
        int start = 0;
        int end = 0;

        for (int i = 0; Alphabet.get_len(); i++){
            int NSize = NewSize;

            if (tempNumber == 0)
                Nsize = NewSize / 2;

            if (tempNumber % 10 == 9)
                NSize = 3 * NewSize / 4;


            if (Alphabet.operator[](i).p_word.size()  + Size + tempNumber - 1 <= NSize){
                if (Size == 0)
                    start = i;

                Size += Alphabet.operator[](i).p_word.size();
            }
            else {
                end = i - 1;

                tempNumber++;
                SetNumber(start, end, tempNumber);

                Size = 0;
                start = 0;
                end = 0;

            }
        }
        p_SizeOfPage = NewSize;
        p_NumberOfPages = tempNumber;
    }


    void SetNumber(int left, int right, int number){
        for (int i = left; i <= right; i++)
            Alphabet.operator[](i).p_number = number;
    }

    void InputArray(){

    }
};


#endif //LAB_2_ALPHABETPOINTER_H
