#include "Vertex.h"

void Vertex::AddEdge(const Edge& edge)
{
	edges.push_back(edge);
}

void Vertex::ChangeName(std::string name)
{
	this->name = name;
}

std::string Vertex::GetName() const
{
	return name;
}

void Vertex::GetEdges(std::vector<Edge>& edges)
{
	edges = this->edges;
}