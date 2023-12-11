#pragma once
#include "Vertex.h"

// used in Dijkstra's algorithm to get the index associated with the minimum distance
struct PairIndexDistance
{
	int index;
	// distance from the source vertex to the vertex with this index
	int distance;
};

// used to create minimum priority queue - or min heap - for the Dijkstra's algorithm
struct MinComparison
{
	bool operator()(const PairIndexDistance& left, const PairIndexDistance& right)
	{
		return left.distance > right.distance;
	}
};

struct ShortestPath
{
	// names of vertices on the path
	std::vector<std::string> path;
	int length;
};

class Graph
{
public:
	// resize vertices vector and initialize it with names
	void Initialize(const std::vector<std::string>& names);

	// find the vertex with sourceName and add edge to it
	// sourceName is a const ref cause it's only used to find the needed vertex, no need to copy it here
	void AddEdge(const std::string& sourceName, const Edge& edge);

	// using Dijkstra's algorithm find shortest path between source and goal
	ShortestPath FindShortestPath(int sourceIndex, int goalIndex);

	// both strings are const refs cause they're only used to get the indexes for the method above, no need to copy them here
	ShortestPath FindShortestPath(const std::string& sourceName, const std::string& goalName);

private:
	// vertex is a const ref cause it's only used to find the needed vertex, no need to copy it here
	int FindVertexIndexByName(const std::string& vertex);

	// used in the Dijkstra's algorithm to extract the found path at the end
	std::vector<std::string> GetPathFromIndexes(const std::vector<int>& previousVertices, int goal, int source);

	//////////

	std::vector<Vertex> vertices;
};