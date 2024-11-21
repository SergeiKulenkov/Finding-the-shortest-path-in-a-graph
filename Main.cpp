#include "Graph/Graph.h"
#include <iostream>
#include <chrono>

inline constexpr std::string_view CityApple = "Apple";
inline constexpr std::string_view CityOrange = "Orange";
inline constexpr std::string_view CityCarrot = "Carrot";
inline constexpr std::string_view CityAvocado = "Avocado";
inline constexpr std::string_view CityPeach = "Peach";
inline constexpr std::string_view CityPineapple = "Pineapple";
inline constexpr std::string_view CityGrape = "Grape";
inline constexpr std::string_view CityCherry = "Cherry";

struct PairSourceGoal
{
	std::string_view source;
	std::string_view goal;
};

//////////

template<Numeric T>
void SetupEdges(std::multimap<std::string_view, Edge<T>>& edges)
{
	// construct the data in place to avoid copying
	// first vertex
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityApple),
					std::forward_as_tuple(25, CityOrange));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityApple),
					std::forward_as_tuple(33.3f, CityAvocado));
	// second vertex
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityOrange),
					std::forward_as_tuple(42.3f, CityCarrot));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityOrange),
					std::forward_as_tuple(55, CityPineapple));
	// third vertex
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityCarrot),
					std::forward_as_tuple(15, CityAvocado));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityCarrot),
					std::forward_as_tuple(36, CityOrange));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityCarrot),
					std::forward_as_tuple(20, CityPeach));
	// fourth vertex
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityAvocado),
					std::forward_as_tuple(23, CityPineapple));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityAvocado),
					std::forward_as_tuple(12, CityCarrot));
	// fifth vertex
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityPeach),
					std::forward_as_tuple(68, CityPineapple));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityPeach),
					std::forward_as_tuple(58, CityOrange));
	edges.emplace(std::piecewise_construct,
					std::forward_as_tuple(CityPeach),
					std::forward_as_tuple(52, CityCherry));
	// sixth vertex
	edges.emplace(std::piecewise_construct, 
					std::forward_as_tuple(CityPineapple), 
					std::forward_as_tuple(46, CityOrange));
	edges.emplace(std::piecewise_construct, 
					std::forward_as_tuple(CityPineapple), 
					std::forward_as_tuple(27, CityApple));
	// seventh vertex
	edges.emplace(std::piecewise_construct, 
					std::forward_as_tuple(CityGrape), 
					std::forward_as_tuple(49, CityCherry));
	edges.emplace(std::piecewise_construct, 
					std::forward_as_tuple(CityGrape), 
					std::forward_as_tuple(30, CityApple));
	// eighth vertex
	edges.emplace(std::piecewise_construct, 
					std::forward_as_tuple(CityCherry), 
					std::forward_as_tuple(59.1f, CityGrape));
	edges.emplace(std::piecewise_construct, 
					std::forward_as_tuple(CityCherry), 
					std::forward_as_tuple(50, CityApple));
}

template<Numeric T>
void PrintPath(const ShortestPath<T>& shortestPath)
{
	std::string_view goal = shortestPath.path[shortestPath.path.size() - 1];
	std::cout << "The shortest path from " << shortestPath.path[0] << " to " << goal << " : ";

	for (const std::string_view vertex : shortestPath.path)
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
	for (int i = 0; i < sourcesAndGoals.size(); i++)
	{
		const auto start = std::chrono::high_resolution_clock::now();
		graph.FindShortestPath(sourcesAndGoals[i].source, sourcesAndGoals[i].goal, shortestPath);
		const auto end = std::chrono::high_resolution_clock::now();
		const std::chrono::duration<float> duration = end - start;
		std::cout << duration.count() * 1000 << "ms\n";
		if (!shortestPath.path.empty())
		{
			PrintPath(shortestPath);
		}
		else
		{
			std::cout << "There's no path from " << sourcesAndGoals[i].source << " to " << sourcesAndGoals[i].goal << '\n';
		}
	}
}

//////////

int main()
{
	//                                                0          1           2           3            4          5              6          7
	const std::vector<std::string_view> vertexNames{ CityApple, CityOrange, CityCarrot, CityAvocado, CityPeach, CityPineapple, CityGrape, CityCherry };
	const std::vector<PairSourceGoal> sourcesAndGoals{ PairSourceGoal(CityApple, CityCherry), PairSourceGoal(CityCarrot, CityGrape), PairSourceGoal(CityPineapple, CityCarrot) };
	std::multimap<std::string_view, Edge<float>> edges;
	SetupEdges(edges);
	
	Graph<float> graph(vertexNames, edges);
	SearchPaths(graph, sourcesAndGoals);

	return 0;
}