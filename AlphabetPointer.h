#ifndef LAB_2_ALPHABETPOINTER_H
#define LAB_2_ALPHABETPOINTER_H
#include "arraysequence.h"
#include "string"

class AlphabetPointer {
private:
    struct Couple {
        std::string p_word;
        ArraySequence<int> p_PageBorders; // begging and ending of page for all words in this page
        int p_number; // current number of page
        int p_line; // number line in page (SizeOfPage /)
        Couple(): p_word(""), p_number(0), p_PageBorders(ArraySequence<int>()), p_line(0){};
        explicit Couple(std::string word, int number, ArraySequence<int> pageBorders = ArraySequence<int>(), int line = 0):
                        p_word(word), p_number(number), p_PageBorders(pageBorders), p_line(line){};


    };

    int p_NumberOfPages;
    int p_SizeOfPage;
    ArraySequence<Couple> Alphabet;
public:

    AlphabetPointer(int SizeOfPage = 0, int NumberOfPages = 0){
        p_SizeOfPage = SizeOfPage;
        p_NumberOfPages = NumberOfPages;
        Alphabet = new ArraySequence<Couple>;
    }

    int GetAlphabet(){
        for (int i = 0; i <Alphabet.get_len(); i++){
            if (i >0)
            if (Alphabet.operator[](i).p_number != Alphabet.operator[](i - 1).p_number)
                std::cout << '\n';
            std::cout << "{ " << Alphabet.operator[](i).p_word << ", Number of Page: " << Alphabet.operator[](i).p_number
                      << ", Beginning: " << Alphabet.operator[](i).p_PageBorders.get_i(0) << ", Ending: "
                      <<Alphabet.operator[](i).p_PageBorders.get_i(1)  <<", Line: " << Alphabet.operator[](i).p_line <<"} ";
        }
    }


    int GetNumberOfPages(){
        return p_NumberOfPages;
    }

    int GetSizeOfPage(){
        return p_SizeOfPage;
    }

    void SetSizeOfPage(int NewSize){
        if (NewSize / 2 < Alphabet.operator[](0).p_word.size())
            return;

        p_SizeOfPage = NewSize;

        int tempNumber = 0;
        int tempCount = 1;
        int Size = 0;
        int start = -1;
        int end = 0;
        for (int i = 0; i <Alphabet.get_len(); i++){
            int NSize = NewSize;
            if (tempNumber == 0) // set size of current page by rule of first page
                NSize = NewSize / 2;

            if (tempNumber % 10 == 9) // set size of current page by rule of ech tenth page
                NSize = 3 * NewSize / 4;


            if (Alphabet.operator[](i).p_word.size()  + Size + tempCount - 1 <= NSize){ // check on possibility adding word to page
                if (Size == 0)
                    start = i;

                Size += Alphabet.operator[](i).p_word.size();
                tempCount++;
            }
            else { // set number of pages to interval
                end = i - 1;

                tempNumber++;
                SetNumber(start, end, tempNumber);
                tempCount = 1;

                start = i;
                Size = Alphabet.operator[](i).p_word.size();
                tempCount++;

            }
        }

        if (start > -1) { // check on adding last word to page
            end = Alphabet.get_len() - 1;

            tempNumber++;
            SetNumber(start, end, tempNumber);
        }

        p_NumberOfPages = tempNumber;
    }


    void SetNumber(int left, int right, int number){ // set number of page to interval in Alphabet
        int MaxLine = GetSizeOfPage() / 5; // Max size of one Line in Page
        if (MaxLine == 0)
            MaxLine = 1;

        int CurrentLine = 0;

        for (int i = left; i <= right; i++){
            int array[] = {left, right};

            CurrentLine++;
            if (CurrentLine >= MaxLine)
                CurrentLine = 1;

            Couple couple(Alphabet.operator[](i).p_word, number,
                          ArraySequence<int>(2,array), CurrentLine);
            Alphabet.set_i(i, couple);
        }
    }

    void InputArray(){
        std::string Stream;


        std::getline(std::cin, Stream);

        std::string tempWord;
        for (int i = 0; i < Stream.size(); i++){
            if (Stream[i] != ' '){ // creating word
                tempWord += Stream[i];
            }
            else { // adding word
                Couple couple(tempWord, 0);
                Alphabet.append(couple);
                tempWord = "";
            }
        }
        if (tempWord.size() > 0){ // check on adding last word
            Couple couple(tempWord, 0);
            Alphabet.append(couple);
            tempWord = "";
        }
    }
};


#endif //LAB_2_ALPHABETPOINTER_H
