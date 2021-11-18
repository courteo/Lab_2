#ifndef CACHE_H
#define CACHE_H


#include "SortedSequence.h"
#include "string"


template <class T>
class Cache {
private:
    struct Person {
        std::string p_Name = "";
        std::string p_Job = " ";
        T p_Salary;

        Person(): p_Job(""), p_Name(""), p_Salary(T(0)){};
        explicit  Person(std::string Name, std::string Job, T salary): p_Job(Job), p_Name(Name), p_Salary(salary){};
        Person(const Person &arr): p_Job(arr.p_Job), p_Name(arr.p_Name), p_Salary(arr.p_Salary){};

        bool operator == (const Person &other) const {
            return  this->p_Job == other.p_Job && this->p_Name == other.p_Name && this->p_Salary == other.p_Salary;
        }

        friend std::ostream& operator<< (std::ostream &out, Person &arr) {
            return std::cout << "--Name: " << arr.p_Name << "; Job: " << arr.p_Job << "; Salary: " << arr.p_Salary << ";-- ";
        }
    };

    struct Element {
        int p_CacheTimes; // key
        Person p_InCache; // value

        Element(): p_InCache(Person()), p_CacheTimes(0){};
        explicit Element(Person InCache): p_InCache(InCache), p_CacheTimes(0){};

        bool operator > ( const Element &other) const {
            return this->p_CacheTimes > other.p_CacheTimes;
        }

        friend std::ostream& operator<< (std::ostream &out, Element &arr){
            return std::cout << "{ " << arr.p_CacheTimes << " : " << arr.p_InCache << " }   ";
        }

    };

    int p_MaxCapacity; // max capacity of cache
    int p_Capacity; // current capacity of cache
    SortedSequence<Element> myCache; // our Dictionary
public:

    Cache(int Capacity = 0, int MaxCapacity = 0) {
        p_Capacity = Capacity;
        p_MaxCapacity = MaxCapacity;
    };


    int GetMaxCapacity(){
        return p_MaxCapacity;
    };

    int GetCapacity() {
        return p_Capacity;
    };

    Person PersonInput(){
        std::string name;
        std::string job;
        T salary;
        std::cin >> name >> job >> salary;
        Person p(name, job, salary);
        return p;
    }

    int FindInCache(Person InCache) { // find index by value of Dictionary
        for (int i = 0; i < GetCapacity(); i++){
            if (InCache == myCache[i].p_InCache)
                return i;
        }
        return -1;
    };

    bool IsContain(Person InCache){ // check on contain in cache
        if (GetCapacity() == 0)
            return false;

        for (int i = 0; i < p_Capacity; i++)
            if (myCache[i].p_InCache == InCache)
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

    void Add(Person InCache){
        if (IsContain(InCache) == true){ // check on contain
            Element el;
            el.p_InCache = InCache;
            el.p_CacheTimes = myCache[FindInCache(InCache)].p_CacheTimes + 1; // increase number of requests

            myCache.remove(FindInCache(InCache));
            myCache.add(el, p_MaxCapacity);
            return;
        }

        Element el;
        el.p_CacheTimes = 1;
        el.p_InCache = InCache;

        myCache.add(el, p_MaxCapacity);
        p_Capacity++;
    };

    void ChangeMaxCapacity(int MaxCapacity){
        if (MaxCapacity < GetCapacity()){
            RemoveCount( GetCapacity()- MaxCapacity);
        }

        p_MaxCapacity = MaxCapacity;
    }


    void RemoveLast(){
        myCache.removeLast();
        p_Capacity--;
    };

    void Remove(Person InCache){
        myCache.remove(FindInCache(InCache));
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


#endif // CACHE_H
