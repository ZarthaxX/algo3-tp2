#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <memory>

#include "../types.h"

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
 
    Coloring tabuSearch(Graph& G, Graph& H, int memorySize, int neighbourhoodPercentage, bool memoryOfSolutions);

}
