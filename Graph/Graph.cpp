#include "Graph.h"
#include <queue>

void Graph::Initialize(const std::vector<std::string>& names)
{
	vertices.resize(names.size());
	for (int i = 0; i < names.size(); i++)
	{
		vertices[i].ChangeName(names[i]);
	}
}

void Graph::AddEdge(const std::string& sourceName, const Edge& edge)
{
	for (Vertex& vertex : vertices)
	{
		if (vertex.GetName() == sourceName)
		{
			vertex.AddEdge(edge);
			break;
		}
	}
}

int Graph::FindVertexIndexByName(const std::string& vertex)
{
	int index = 0;
	for (int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].GetName() == vertex)
		{
			index = i;
			break;
		}
	}

	return index;
}

std::vector<std::string> Graph::GetPathFromIndexes(const std::vector<int>& previousVertices, int goal, int source)
{
	int pathIndex = goal;
	std::vector<std::string> path;
	path.push_back(vertices[pathIndex].GetName());

	while (pathIndex != source)
	{
		path.push_back(vertices[previousVertices[pathIndex]].GetName());
		pathIndex = previousVertices[pathIndex];
	}

	// originally the path is from the goal to the source, so need to reverse it
	std::reverse(path.begin(), path.end());
	return path;
}

ShortestPath Graph::FindShortestPath(const std::string& sourceName, const std::string& goalName)
{
	int sourceIndex = FindVertexIndexByName(sourceName);
	int goalIndex = FindVertexIndexByName(goalName);
	return FindShortestPath(sourceIndex, goalIndex);
}

ShortestPath Graph::FindShortestPath(int sourceIndex, int goalIndex)
{
	// a path of indexes from the goal to the source, accessing previousVertices[goalIndex] gives goal's previous vertex on the path
	// this way this vector can be iterated until the sourceIndex is reached, see GetPathFromIndexes() for implementation
	std::vector<int> previousVertices(vertices.size(), -1);

	std::vector<int> distancesToSource(vertices.size(), INT_MAX);
	std::vector<bool> visitedVertices(vertices.size(), false);
	distancesToSource[sourceIndex] = 0;
	visitedVertices[sourceIndex] = true;

	// min heap - elements are sorted in an increasing order by distance from the source
	std::priority_queue<PairIndexDistance, std::vector<PairIndexDistance>, MinComparison> minDistances;
	minDistances.push({ sourceIndex, 0 });

	int currentIndex = 0;
	int nextVertexIndex = 0;
	int distanceToNextVertexFromSource = 0;
	std::vector<Edge> edgesOfCurrentVertex;

	// need to calculate a path to every vertex because the shortest path to the goal may be through the last vertex
	while (!minDistances.empty())
	{
		// current element is the one with the minimum distance to the source and it is the first in the queue
		currentIndex = minDistances.top().index;
		minDistances.pop();

		vertices[currentIndex].GetEdges(edgesOfCurrentVertex);
		for (int edgeIndex = 0; edgeIndex < edgesOfCurrentVertex.size(); edgeIndex++)
		{
			nextVertexIndex = FindVertexIndexByName(edgesOfCurrentVertex.at(edgeIndex).GetDestination());
			distanceToNextVertexFromSource = distancesToSource[currentIndex] + edgesOfCurrentVertex.at(edgeIndex).GetDistance();

			if (!visitedVertices[nextVertexIndex] && (distanceToNextVertexFromSource < distancesToSource[nextVertexIndex]))
			{
				distancesToSource[nextVertexIndex] = distanceToNextVertexFromSource;
				previousVertices[nextVertexIndex] = currentIndex;
				// add new found min distance for the nextVertexIndex
				minDistances.push({ nextVertexIndex, distancesToSource[nextVertexIndex] });
			}
		}

		visitedVertices[currentIndex] = true;
	}

	std::vector<std::string> path = GetPathFromIndexes(previousVertices, goalIndex, sourceIndex);
	return { path, distancesToSource[goalIndex] };
}