#pragma once
#include "Vertex.h"
#include <map>
#include <queue>

//////////

// used in Dijkstra's algorithm to get the index associated with the minimum distance
template<Numeric T>
struct PairIndexDistance
{
	int index;
	// distance from the source vertex to the vertex with this index
	T length;
};

// used to create minimum priority queue - or min heap - for the Dijkstra's algorithm
template<Numeric T>
struct MinComparison
{
	bool operator()(const PairIndexDistance<T>& left, const PairIndexDistance<T>& right)
	{
		return left.length > right.length;
	}
};

template<Numeric T>
struct ShortestPath
{
	// names of vertices on the path
	std::vector<std::string_view> path;
	T length;
};

//////////

template<Numeric T>
class Graph
{
public:
	Graph() = delete;

	Graph(const std::vector<std::string_view>& vertexNames)
	{
		m_Vertices.resize(vertexNames.size());
		for (int i = 0; i < vertexNames.size(); i++)
		{
			m_Vertices[i].ChangeName(vertexNames[i]);
		}

		ResizeHelperVectors();
	}

	Graph(const std::vector<std::string_view>& vertexNames, const std::multimap<std::string_view, Edge<T>>& edges)
	{
		typedef std::multimap<std::string_view, Edge<T>>::const_iterator mapIterator;
		std::pair<mapIterator, mapIterator> range;
		std::vector<Edge<T>> edgesForCurrentVertex;

		m_Vertices.resize(vertexNames.size());
		for (int i = 0; i < vertexNames.size(); i++)
		{
			range = edges.equal_range(vertexNames[i]);
			edgesForCurrentVertex.resize(edges.count(vertexNames[i]));
			int edgeIndex = 0;
			for (mapIterator it = range.first; it != range.second; ++it, edgeIndex++)
			{
				edgesForCurrentVertex[edgeIndex] = it->second;
			}

			m_Vertices[i].ChangeName(vertexNames[i]);
			m_Vertices[i].AddEdges(edgesForCurrentVertex);
		}

		ResizeHelperVectors();
	}

	void ResizeHelperVectors()
	{
		m_PreviousVertices.resize(m_Vertices.size());
		m_DistancesToSource.resize(m_Vertices.size());
		m_VisitedVertices.resize(m_Vertices.size());
	}

	// find the vertex by sourceName and add edge to it
	void AddEdge(const std::string_view& sourceName, const Edge<T>& edge)
	{
		for (Vertex& vertex : m_Vertices)
		{
			if (vertex.GetName() == sourceName)
			{
				vertex.AddEdge(edge);
				break;
			}
		}
	}

	// using Dijkstra's algorithm find shortest path from source to goal
	void FindShortestPath(const std::string_view& sourceName, const std::string_view& goalName, ShortestPath<T>& shortestPath)
	{
		const int sourceIndex = FindVertexIndexByName(sourceName);
		const int goalIndex = FindVertexIndexByName(goalName);
		FindShortestPath(sourceIndex, goalIndex, shortestPath);
	}

	// using Dijkstra's algorithm find shortest path from source to goal
	void FindShortestPath(const int sourceIndex, const int goalIndex, ShortestPath<T>& shortestPath)
	{
		std::fill(m_PreviousVertices.begin(), m_PreviousVertices.end(), -1);
		std::fill(m_DistancesToSource.begin(), m_DistancesToSource.end(), static_cast<T>(INT_MAX));
		std::fill(m_VisitedVertices.begin(), m_VisitedVertices.end(), false);
		m_DistancesToSource[sourceIndex] = 0;
		m_VisitedVertices[sourceIndex] = true;

		// min heap - elements are sorted by an increasing distance from the source
		std::priority_queue<PairIndexDistance<T>, std::vector<PairIndexDistance<T>>, MinComparison<T>> minDistances;
		minDistances.emplace(PairIndexDistance(sourceIndex, (T)0));

		// need to calculate a path to every vertex because the shortest path to the goal may be through the last vertex
		while (!minDistances.empty())
		{
			// current element is the one with the minimum distance to the source and the first in the queue
			int currentIndex = minDistances.top().index;
			minDistances.pop();

			const std::vector<Edge<T>>& edgesOfCurrentVertex = m_Vertices[currentIndex].GetEdges();
			for (int edgeIndex = 0; edgeIndex < edgesOfCurrentVertex.size(); edgeIndex++)
			{
				const int nextVertexIndex = FindVertexIndexByName(edgesOfCurrentVertex[edgeIndex].GetDestination());
				const T distanceToNextVertexFromSource = m_DistancesToSource[currentIndex] + edgesOfCurrentVertex[edgeIndex].GetLength();

				if (!m_VisitedVertices[nextVertexIndex] && (distanceToNextVertexFromSource < m_DistancesToSource[nextVertexIndex]))
				{
					m_DistancesToSource[nextVertexIndex] = distanceToNextVertexFromSource;
					m_PreviousVertices[nextVertexIndex] = currentIndex;
					// add new found min distance for the nextVertexIndex
					minDistances.emplace(PairIndexDistance(nextVertexIndex, m_DistancesToSource[nextVertexIndex]));
				}
			}

			m_VisitedVertices[currentIndex] = true;
		}

		GetPathFromIndexes(m_PreviousVertices, sourceIndex, goalIndex, shortestPath.path);
		shortestPath.length = m_DistancesToSource[goalIndex];
	}

private:
	int FindVertexIndexByName(const std::string_view& vertexName) const
	{
		int index = 0;
		for (int i = 0; i < m_Vertices.size(); i++)
		{
			if (m_Vertices[i].GetName() == vertexName)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	// used in the Dijkstra's algorithm to extract the found path at the end
	void GetPathFromIndexes(const std::vector<int>& previousVertices, const int sourceIndex, const int goalIndex, std::vector<std::string_view>& path) const
	{
		path.clear();
		if (previousVertices[goalIndex] != -1)
		{
			int pathIndex = goalIndex;
			path.emplace_back(m_Vertices[pathIndex].GetName());

			while (pathIndex != sourceIndex)
			{
				path.emplace_back(m_Vertices[previousVertices[pathIndex]].GetName());
				pathIndex = previousVertices[pathIndex];
			}

			// originally the path is from the goal to the source, so need to reverse it
			std::reverse(path.begin(), path.end());
		}
	}

	//////////

	std::vector<Vertex<T>> m_Vertices;

	// a path of indexes from the goal to the source, accessing previousVertices[goalIndex] gives goal's previous vertex on the path
	// this way this vector can be iterated until the sourceIndex is reached, see GetPathFromIndexes() for implementation
	std::vector<int> m_PreviousVertices;

	std::vector<T> m_DistancesToSource;
	std::vector<bool> m_VisitedVertices;
};