#ifndef LAB_2_CACHE_H
#define LAB_2_CACHE_H

#include "SortedSequence.h"



template <class T>
class Cache {
private:
    struct Element {
        int p_CacheTimes; // key
        T p_CacheIn; // value

        Element(): p_CacheIn(0), p_CacheTimes(0){};
        explicit Element(int CacheIn): p_CacheIn(CacheIn), p_CacheTimes(0){};

        bool operator > ( const Element &other) const{
            return this->p_CacheTimes > other.p_CacheTimes;
        }

        friend std::ostream& operator<< (std::ostream &out, Element &arr){
            return std::cout << "{ " << arr.p_CacheTimes << " : " << arr.p_CacheIn << " }   ";
        }

    };

    int p_MaxCapacity;
    int p_Capacity;
    SortedSequence<Element> myCache;
public:

    Cache(int Capacity = 0, int MaxCapacity = 0) {
        p_Capacity = Capacity;
        p_MaxCapacity = MaxCapacity;
    };

    void SetMaxCapacity(int MaxCapacity) {
        p_MaxCapacity = MaxCapacity;
    };

    int GetMaxCapacity(){
        return p_MaxCapacity;
    };

    int GetCapacity() {
        return p_Capacity;
    };

    int FindCacheIn(int CacheIn){
        for (int i = 0; i < GetCapacity(); i++){
            if (CacheIn == myCache[i].p_CacheIn)
                return i;
        }
        return -1;
    };

    bool IsContains(T CacheIn){
        if (GetCapacity() == 0)
            return false;

        for (int i = 0; i < p_Capacity; i++)
            if (myCache[i].p_CacheIn == CacheIn)
                return true;
        return false;
    };

    Element Get(int CacheTime){
        if (CacheTime > myCache[0].p_CacheTimes || CacheTime < myCache[GetCapacity() - 1].p_CacheTimes)
            return Element();

        int left = 0;
        int right = GetCapacity() - 1;

        while (left < right){
            int middle = (left + right) / 2;
            if (myCache[middle].p_CacheTimes <= CacheTime)
                right = middle;
            else
                left = middle +1;
        }

        return myCache[left];
    };

    void Add(T CacheIn){
        if (IsContains(CacheIn) == true){
            Element el;
            el.p_CacheIn = CacheIn;
            el.p_CacheTimes = myCache[FindCacheIn(CacheIn)].p_CacheTimes + 1;

            myCache.remove(FindCacheIn(CacheIn));
            myCache.add(el, p_MaxCapacity);
            return;
        }

        Element el;
        el.p_CacheTimes = 1;
        el.p_CacheIn = CacheIn;

        myCache.add(el, p_MaxCapacity);
        p_Capacity++;
    };


    void RemoveLast(){
        myCache.removeLast();
        p_Capacity--;
    };

    void Remove(int CacheIn){
        myCache.remove(FindCacheIn(CacheIn));
        p_Capacity--;
    };

    void RemoveCount(int Count) {
        myCache.removeCount(Count);
        p_Capacity--;
    };

    void PrintCache(){
        std::cout << myCache;
    };

};

#endif //LAB_2_CACHE_H
