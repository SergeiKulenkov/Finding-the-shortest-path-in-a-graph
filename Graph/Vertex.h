#pragma once
#include <vector>
#include "Edge.h"

class Vertex
{
public:
	void AddEdge(const Edge& edge);

	// name is passed by value cause we set it to the local variable
	void ChangeName(std::string name);

	std::string GetName() const;

	// edges is a reference cause it's used as a return value
	void GetEdges(std::vector<Edge>& edges);

private:
	std::string name;
	std::vector<Edge> edges;
};