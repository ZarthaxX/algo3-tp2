#include <iostream>
#include <vector>
#include <algorithm>

#include "tabuSearch.h"
#include "../heuristicasGolosas/expansivo/expansivo.h"

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

    bool Solution::modificationIsValid(Modificator* modificator,Graph& G){
        //Modificator - affected nodes vector<nodos> 
        //Aplicame
        //Revisa que sea validos los nodos afectados
        //revertime
        //devolve el and de paso 3
        
        vector<Node> affectedNodes = modificator->affectedNodes();
        modificator->applyToSolution(*this);

        bool isValid = true;

        for(Node node : affectedNodes){
            for(Node adyNode : G.adyacents(node)){
                if(colorOfNode(adyNode) == colorOfNode(node)){
                    isValid = false;
                }
            }
        }
        modificator->reverseOnSolution(*this);

        return isValid;
    }

    bool Solution::operator!=(const Solution& s) const{
        return !(*this==s);
    }

    const Coloring& Solution::getColoring() const {
        return _colorsByNodes;
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

    vector<Node> Change::affectedNodes(){
        return vector<Node>(1,_node);
    };

    bool Change::operator==(const Change& s) const{
        return _node == s._node && _oldColor == s._oldColor && _newColor == s._newColor;
            
    }
    bool Change::operator!=(const Change& s) const{
        return !(*this==s);
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

    vector<Node> Swap::affectedNodes(){
        return {_node1,_node2};
    };

    ostream& operator<<(ostream& os, const Swap& s)
    {
        os << s._node1 << " <-> " << s._node2;
        return os;
    }
    
    // Memory

/*
busquedaTabu(. . .)
salida: s solucion factible
s
∗ ← s
inicializar la lista tabu T
inicializar la funcion de aspiracion A
mientras no se verifique criterio de parada hacer
definir V
∗
elegir s
0 ∈ V
∗ tal que f (s
0
) < f (¯s) ∀s¯ ∈ V
∗
actualizar la funcion de aspiracion A
actualizar la lista tabu T
si f (s
0
) < f (s
∗
) hacer
s
∗ ← s
0
fin si
s ← s
0
fin mientras
retornar s
    */


    int calculateImpact(Graph& graph, Solution& solution){

        int n = graph.getNodeCount();

        Score score = 0;

        for(int i = 0; i < n; i++){
            for(int j = i+1; j < n; j++){
                if( graph.isAdyacent(i,j) &&
                    solution.colorOfNode(i) == solution.colorOfNode(j)){
                        score++;
                }
            }
        }

        return score;
    }

    Coloring tabuSearch(Graph& G, Graph& H, int memorySize, int neighbourhoodPercentage){
        
        int n = G.getNodeCount();

        Coloring initialColoring = Expansivo::expansivo(G,H);

        Solution solution(initialColoring);

        Memory<Solution> tabuMemory(memorySize);
        
        int iterations = 0;
        int LIMIT = 1000;

        while(iterations < LIMIT){
            
            vector<Modificator*>neighbourhood;
            //Change Neighbourhood
            for(Node node = 0;node < n;node++){
                for(Color color = 0;color < n;color++){
                    neighbourhood.push_back(new Change(node,solution.colorOfNode(node),color));
                }
            }
            //Swap Neighbourhood
            vector<Swap> allSwaps;
            for(Node node1 = 0;node1 < n;node1++){
                for(Node node2 = node1+1;node2 < n;node2++){
                    neighbourhood.push_back(new Swap(node1,node2));
                }
            }

            random_shuffle(neighbourhood.begin(),neighbourhood.end());
            
            int percentage = (int)(neighbourhood.size()*((float)neighbourhoodPercentage/100.0));

            int bestImpact = -1;
            int bestIndex = -1;

            for(int i = 0;i < percentage;i++){
                Modificator * modificator = neighbourhood[i];

                if(solution.modificationIsValid(modificator, G)){
                    modificator->applyToSolution(solution);

                    if(tabuMemory.contains(solution))
                        continue;

                    int impact = calculateImpact(H,solution);

                    if(impact > bestImpact){
                        bestImpact = impact;
                        bestIndex = i;
                    }

                    modificator->reverseOnSolution(solution);
                }
            }

            int currentImpact = calculateImpact(H,solution);

            //aca podriamos agregar la funcion de aspiracion para permitir peores soluciones
            if(currentImpact < bestImpact){
                neighbourhood[bestIndex]->applyToSolution(solution);
                tabuMemory.add(solution);
            }

            iterations++;
        }

        return solution.getColoring();
    }
/*
            //Change Neighbourhood
            vector<Change> allChanges;
            for(Node node = 0;node < n;node++){
                for(Color color = 0;color < n;color++){
                    allChanges.push_back(Change(node,solution.colorOfNode(node),color));
                }
            }
            random_shuffle(allChanges.begin(),allChanges.end());

            //Swap Neighbourhood
            vector<Swap> allSwaps;
            for(Node node1 = 0;node1 < n;node1++){
                for(Node node2 = node1+1;node2 < n;node2++){
                    allSwaps.push_back(Swap(node1,node2));
                }
            }
            random_shuffle(allSwaps.begin(),allSwaps.end());

            vector<Modificator*>x;

            for(int i = 0;i < (int)(allChanges.size()*((float)neighbourhoodPercentage/100.0));i++){
                x.push_back(&allChanges[i]);
            }
            for(int i = 0;i < (int)(allSwaps.size()*((float)neighbourhoodPercentage/100.0));i++){
                x.push_back(&allSwaps[i]);
            }
            */
}