#pragma once
#include <vector>
#include "Edge.h"

//////////

template<Numeric T>
class Vertex
{
public:
	Vertex() : m_Name("") { }

	Vertex(const std::string_view& name) : m_Name(name) { }

	Vertex(const std::string_view& name, const Edge<T>& edge) : m_Name(name)
	{
		m_Edges.emplace_back(edge);
	}

	void AddEdge(const Edge<T>& edge) { m_Edges.emplace_back(edge); }

	// using std::move so edges shouldn't be const
	void AddEdges(std::vector<Edge<T>>& edges) { m_Edges = std::move(edges); }

	void ChangeName(const std::string_view& newName) { m_Name = newName; }

	std::string_view GetName() const { return m_Name; }

	const std::vector<Edge<T>>& GetEdges() const { return m_Edges; }

private:
	std::string_view m_Name;

	std::vector<Edge<T>> m_Edges;
};