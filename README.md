### Algorithm for finding the shortest path in a graph also known as Dijkstra's algorithm

# This implementation features:
* separate Edge, Vertex and Graph classes where Graph contains a vector of type Vertex, and Vertex containt a vector of type Edge
* string names for vertices which looks nicer in the output and makes the code a bit more interesting (usually similar algorithms use numbers for vertices)
* the algorithm returns a struct which contains a path - vector of strings - and a distance from a given source vertex to a given goal vertex
* some utility methods to reinitialize a graph, initialize edges in different ways, access private fields and other
* easy to edit test variables and test loop
