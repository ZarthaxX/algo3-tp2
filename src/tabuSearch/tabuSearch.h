#pragma once

#include <iostream>
#include <vector>
#include <deque>

#include "../types.h"

namespace TabuSearch{

    class Solution{
        public:
            Solution(Coloring initialColoring);
            void change(Node node,Color color);
            void swap(Node node1,Node node2);
            Color colorOfNode(Node node);
            bool operator==(const Solution& s) const;
            bool operator!=(const Solution& s) const;
            friend ostream& operator<<(ostream& os, const Solution& s);
        private:
            Coloring _colorsByNodes;
    };

    class Modificator{
        public:
            Modificator(){};
            void applyToSolution(Solution& solution){};
            void reverseOnSolution(Solution& solution){};
            friend bool operator==(Modificator const& lhs, Modificator const& rhs) {return lhs.equal_to(rhs);}
        protected:
            virtual bool equal_to(Modificator const& other) const {return false;};
    };

    class Change : public Modificator{
        public:
            Change(Node node,Color oldColor,Color newColor);
            void applyToSolution(Solution& solution);
            void reverseOnSolution(Solution& solution);
        private:
            Node _node;
            Color _oldColor;
            Color _newColor;
        protected:
            bool equal_to(Modificator const& other) const {
            if (Change const* p = dynamic_cast<Change const*>(&other)) {return *this == *p;}
            else {return false;}
            }
    };

    class Swap : public Modificator{
        public:
            Swap(Node node1,Node node2);
            void applyToSolution(Solution& solution);
            void reverseOnSolution(Solution& solution);
            bool operator==(const Swap& s) const;
            bool operator!=(const Swap& s) const;
            friend ostream& operator<<(ostream& os, const Swap& s);
        private:
            Node _node1;
            Node _node2;
        protected:
            bool equal_to(Modificator const& other) const {
            if (Swap const* p = dynamic_cast<Swap const*>(&other)) {return *this == *p;}
            else {return false;}
            }
    };
 
    template<class T>
    class Memory{
        public:
            Memory(int size);
            bool contains(const T& e) const;
            void add(const T& e);
        private:
            deque<T const*> _elems;
            int _size;
    };
    
    template<class T>
    Memory<T>::Memory(int size){
        _size = size;
    }
    
    template<class T>
    bool Memory<T>::contains(const T& e) const{
        return find_if(_elems.begin(),_elems.end(), [e](T const * elem){return *elem == e;}) != _elems.end();
    }

    template<class T>
    void Memory<T>::add(const T& e){
        if(_elems.size() == _size){
            _elems.pop_front();
        }
        _elems.push_back(&e);
    }

    Coloring tabuSearch(Graph& G, Graph& H);

}
