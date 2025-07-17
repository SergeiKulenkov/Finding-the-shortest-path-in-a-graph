#include "Graph/Graph.h"
#include "Utilities/json.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

using json = nlohmann::json;

//////////

struct PairSourceGoal
{
	std::string_view source;
	std::string_view goal;
};

//////////

template<Numeric T>
void SetupData(std::unordered_multimap<std::string_view, Edge<T>>& edges, std::vector<std::string>& vertexNames)
{
	std::ifstream data;
	data.open("Data/graph.json");
	if (data.is_open())
	{
		json objects;
		data >> objects;
		data.close();
		vertexNames.reserve(objects.size());

		// first fill the names, they are needed to initialize string_view parameters
		for (const auto& [key, vertex] : objects.items())
		{
			vertexNames.emplace_back(vertex.at("name"));
		}

		uint8_t index = 0;
		for (const auto& [key, vertex] : objects.items())
		{
			for (const auto& [key, edge] : vertex.at("neighbours").items())
			{
				edges.emplace(std::piecewise_construct, std::forward_as_tuple(vertexNames[index]),
														std::forward_as_tuple(static_cast<float>(edge.at("distance")), vertexNames[edge.at("destinationId")]));
			}
			index++;
		}
	}
}

template<Numeric T>
void PrintPath(const ShortestPath<T>& shortestPath)
{
	const std::string_view goal = shortestPath.path[shortestPath.path.size() - 1];
	std::cout << "The shortest path from " << shortestPath.path[0] << " to " << goal << " : ";

	for (const std::string_view& vertex : shortestPath.path)
	{
		std::cout << vertex;
		if (vertex != goal)
		{
			std::cout << " => ";
		}
	}
	std::cout << "\nDistance = " << shortestPath.length << '\n';
}

template<Numeric T>
void SearchPaths(Graph<T>& graph, const std::vector<PairSourceGoal>& sourcesAndGoals)
{
	ShortestPath<T> shortestPath;
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> duration = std::chrono::milliseconds(0);

	for (auto current = sourcesAndGoals.cbegin(); current != sourcesAndGoals.cend(); ++current)
	{
		start = std::chrono::high_resolution_clock::now();
		graph.FindShortestPath((*current).source, (*current).goal, shortestPath);

		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		std::cout << duration.count() * 1000 << "ms\n";

		if (!shortestPath.path.empty())
		{
			PrintPath(shortestPath);
		}
		else
		{
			std::cout << "There's no path from " << (*current).source << " to " << (*current).goal << '\n';
		}
		std::cout << std::endl;
	}
}

//////////

int main()
{
	std::vector<std::string> vertexNames;
	std::unordered_multimap<std::string_view, Edge<float>> edges;

	SetupData(edges, vertexNames);
	Graph<float> graph(vertexNames, edges);

	const std::vector<PairSourceGoal> sourcesAndGoals{ {vertexNames[0], vertexNames[7]},
														{vertexNames[2], vertexNames[6]},
														{vertexNames[5], vertexNames[2]} };
	SearchPaths(graph, sourcesAndGoals);

	return 0;
}