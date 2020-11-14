#include <iostream>
#include <vector>

#include "tabuSearch.h"

using namespace std;

namespace TabuSearch{

    //Solution
    
    Solution::Solution(Coloring initialColoring){
        _colorsByNodes = initialColoring;
    }

    void Solution::change(Node node,Color color){
        _colorsByNodes[node] = color;
    }

    void Solution::swap(Node node1,Node node2){
        Color temp_color = _colorsByNodes[node1];
        _colorsByNodes[node1] = _colorsByNodes[node2];
        _colorsByNodes[node2] = temp_color;
    }

    Color Solution::colorOfNode(Node node){
        return _colorsByNodes[node];
    }
    
    bool Solution::operator==(const Solution& s) const{
        vector<Color>biyection(s._colorsByNodes.size(),-1);

        for(int i=0;i<biyection.size();i++){
            Color equivalence = biyection[_colorsByNodes[i]];
            if(equivalence != -1 && s._colorsByNodes[i]!=equivalence){
                return false;
            }else if(equivalence == -1){
                biyection[_colorsByNodes[i]] = s._colorsByNodes[i];
            }
        }

        return true;
    }

    bool Solution::operator!=(const Solution& s) const{
        return !(*this==s);
    }

    ostream& operator<<(ostream& os, const Solution& s)
    {
        for(Color c : s._colorsByNodes)
            os << c << " ";
        return os;
    }
    // Change

    Change::Change(Node node,Color oldColor,Color newColor){
        _node = node;
        _oldColor = oldColor;
        _newColor = newColor;
    }

    void Change::applyToSolution(Solution& solution){
        solution.change(_node,_newColor);
    }

    void Change::reverseOnSolution(Solution& solution){
        solution.change(_node,_oldColor);
    }
    
    // Swap
    
    Swap::Swap(Node node1,Node node2){
        _node1 = node1;
        _node2 = node2;
    }

    bool Swap::operator==(const Swap& s) const{
        return 
            (_node1 == s._node1 && _node2 == s._node2) ||
            (_node1 == s._node2 && _node2 == s._node1);
    }

    bool Swap::operator!=(const Swap& s) const{
        return !(*this==s);
    }

    void Swap::applyToSolution(Solution& solution){
        solution.swap(_node1,_node2);
    }

    void Swap::reverseOnSolution(Solution& solution){
        solution.swap(_node1,_node2);
    }

    ostream& operator<<(ostream& os, const Swap& s)
    {
        os << s._node1 << " <-> " << s._node2;
        return os;
    }
    
    // Memory

    Coloring tabuSearch(Graph& G, Graph& H){
        
        return Coloring(G.getNodeCount(),-1);
    }

}