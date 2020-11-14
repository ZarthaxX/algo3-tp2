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
    };
 
    template<class T>
    class Memory{
        public:
            Memory(int size);
            bool contains(const T& e) const;
            void add(const T& e);
        private:
            deque<T> _elems;
            int _size;
    };
    
    template<class T>
    Memory<T>::Memory(int size){
        _size = size;
    }
    
    template<class T>
    bool Memory<T>::contains(const T& e) const{
        return find(_elems.begin(),_elems.end(), e) != _elems.end();
    }

    template<class T>
    void Memory<T>::add(const T& e){
        if(_elems.size() == _size){
            _elems.pop_front();
        }
        _elems.push_back(e);
    }

    Coloring tabuSearch(Graph& G, Graph& H);

}
