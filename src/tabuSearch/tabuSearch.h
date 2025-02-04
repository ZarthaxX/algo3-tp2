#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <memory>

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <chrono>
#include <set>

#include "../types.h"

using namespace std;
using namespace chrono;
//high_resolution_clock::time_point now = high_resolution_clock::now();
//#define TIME duration_cast<duration<double>>(high_resolution_clock::now() - now).count()
#define NOW high_resolution_clock::now()
#define TIMEOUT 40000 //10 ms timeout
#define TIMEOUT2 900000
#define Now() chrono::high_resolution_clock::now()
static struct Stopwatch {
	chrono::high_resolution_clock::time_point c_time, c_timeout;
	void setTimeout(int us) { c_timeout = c_time + chrono::microseconds(us); }
	void Start() { c_time = Now();}
	inline bool Timeout() { return Now() > c_timeout; }
	long long EllapsedMicroseconds() { return chrono::duration_cast<chrono::microseconds>(Now() - c_time).count(); }
	long long EllapsedMilliseconds() { return chrono::duration_cast<chrono::milliseconds>(Now() - c_time).count(); }
} stopwatch;//} Stopwatch


namespace TabuSearch{

    class Modificator;

    class Solution{
        public:
            Solution(Coloring initialColoring);
            bool modificationIsValid(unique_ptr<Modificator>& modificator,Graph& G);
            void change(Node node,Color color);
            void swap(Node node1,Node node2);
            Color colorOfNode(Node node);
            bool operator==(const Solution& s) const;
            bool operator!=(const Solution& s) const;
            const Coloring& getColoring() const;
            friend ostream& operator<<(ostream& os, const Solution& s);
        private:
            Coloring _colorsByNodes;
    };

    class Modificator{
        public:
            Modificator(){};
            virtual void applyToSolution(Solution& solution){};
            virtual void reverseOnSolution(Solution& solution){};
            virtual vector<Node> affectedNodes() {return {-1};};
            friend bool operator==(Modificator const& lhs, Modificator const& rhs) {return lhs.equal_to(rhs);}
        protected:
            virtual bool equal_to(Modificator const& other) const {return 0;};
    };

    class Change : public Modificator{
        public:
            Change(Node node,Color oldColor,Color newColor);
            void applyToSolution(Solution& solution);
            void reverseOnSolution(Solution& solution);
            vector<Node> affectedNodes();
            bool operator==(const Change& s) const;
            bool operator!=(const Change& s) const;
        protected:
            bool equal_to(Modificator const& other) const {
            Change const* p = dynamic_cast<Change const*>(&other);
            if (p != NULL) {return *this == *p;}
            else {return false;}
            }
        private:
            Node _node;
            Color _oldColor;
            Color _newColor;
    };

    class Swap : public Modificator{
        public:
            Swap(Node node1,Node node2);
            void applyToSolution(Solution& solution);
            void reverseOnSolution(Solution& solution);
            vector<Node> affectedNodes();
            bool operator==(const Swap& s) const;
            bool operator!=(const Swap& s) const;
            friend ostream& operator<<(ostream& os, const Swap& s);
        protected:
            bool equal_to(Modificator const& other) const {
            Swap const* p = dynamic_cast<Swap const*>(&other);
            if (p != NULL) {return *this == *p;}
            else {return false;}
            }
        private:
            Node _node1;
            Node _node2;
    };

    class MemorySolution{
        public: 
            MemorySolution(int size);
            bool contains(const Solution& e) const;
            void add(const Solution& e);
        private:
            deque<Solution> _elems;
            int _size;
    };

    class MemoryModificators{
        public: 
            explicit MemoryModificators(int size);
            MemoryModificators(const MemoryModificators&) = delete;
            MemoryModificators& operator=(const MemoryModificators&) = delete;
            ~MemoryModificators() = default;
            bool contains(const unique_ptr<Modificator>& e) const;
            void add(unique_ptr<Modificator>& e);
        private:
            deque<unique_ptr<Modificator>> _elems;
            int _size;
    };


    /*
    
    Memory::Memory(int size){
        _size = size;
    }
    
    bool Memory::contains(const T& e) const{
        bool found = false;
        for (auto it = _elems.begin(); it != _elems.end(); ++it)
		    found = found || (e == *it);
        return found;
    }

    template<class T>
    bool Memory<T>::contains(const T* e) const{
        bool found = false;
        for (auto it = _elems.begin(); it != _elems.end(); ++it)
		    found = found || (*e == **it);
        return found;
    }

    template<class T>
    void Memory<T>::print_type_of_position(int index){
        cout << typeid(*_elems[index]).name() << endl;
    };

    template<class T>
    void Memory<T>::add(const T& e){
        if(_elems.size() == _size){
            _elems.pop_front();
        }
        _elems.push_back(&e);
    }

    template<class T>
    void Memory<T>::add(const T * e){
        if(_elems.size() == _size){
            _elems.pop_front();
        }
        _elems.push_back(e);
    }


    


    class MemoryModificators{
        public:
            Memory(int size);
            bool contains(const Modificator* e) const;
            void add(const Solution& e);
            void print_type_of_position(int index);
        private:
            deque<Solution> _elems;
            int _size;
    };

    */
 
    Coloring tabuSearch(Graph& G, Graph& H, int memorySize, int neighbourhoodPercentage, bool memoryOfSolutions, int max_iterations, string golosoInicial, long long& tiempo_mejor_solucion);

}
