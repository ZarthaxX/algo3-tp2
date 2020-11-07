

# Algoritmos golosos

- secuencial:
    ```
    ordenar nodos a recorrer de mayor a menor grado segun grafo 1

    por cada nodo en la lista ordenada:

        si se puede pintar igual que un vecino a el en el grafo 2:

            elegir el color que se repita mas en los vecinos del nodo en el segundo grafo que sea valido

        sino:

            elegir el color que mas fue utilizado hasta ahora que sea valido, o utilizar uno nuevo en caso contrario
    ```

- expansivo:
    ```
    mientras haya nodos sin pintar:

        seleccionar nodo con mayor cantidad de vecinos sin pintar y que no haya sido pintado del grafo 2

        correr un bfs en el grafo 2 desde este que pinte a todos los nodos que pueda con un color nuevo sin generar conflictos en el grafo 1
    ```

# Tabu Search: