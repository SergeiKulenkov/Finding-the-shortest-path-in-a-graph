#include "Graph/Graph.h"

#define CITY_APPLE "Apple"
#define CITY_ORANGE "Orange"
#define CITY_CARROT "Carrot"
#define CITY_AVOCADO "Avocado"
#define CITY_PEACH "Peach"
#define CITY_PINEAPPLE "Pineapple"
#define CITY_GRAPE "Grape"
#define CITY_CHERRY "Cherry"

void SetupGraph(Graph& graph)
{
	Edge edge(25, CITY_ORANGE);
	// first vertex
	graph.AddEdge(CITY_APPLE, edge);
	edge.Initialize(33, CITY_AVOCADO);
	graph.AddEdge(CITY_APPLE, edge);
	// second vertex
	edge.Initialize(42, CITY_CARROT);
	graph.AddEdge(CITY_ORANGE, edge);
	edge.Initialize(55, CITY_PINEAPPLE);
	graph.AddEdge(CITY_ORANGE, edge);
	// third vertex
	edge.Initialize(15, CITY_AVOCADO);
	graph.AddEdge(CITY_CARROT, edge);
	edge.Initialize(36, CITY_ORANGE);
	graph.AddEdge(CITY_CARROT, edge);
	edge.Initialize(20, CITY_PEACH);
	graph.AddEdge(CITY_CARROT, edge);
	// fourth vertex
	edge.Initialize(23, CITY_PINEAPPLE);
	graph.AddEdge(CITY_AVOCADO, edge);
	edge.Initialize(12, CITY_CARROT);
	graph.AddEdge(CITY_AVOCADO, edge);
	// fifth vertex
	edge.Initialize(68, CITY_PINEAPPLE);
	graph.AddEdge(CITY_PEACH, edge);
	edge.Initialize(58, CITY_ORANGE);
	graph.AddEdge(CITY_PEACH, edge);
	edge.Initialize(52, CITY_CHERRY);
	graph.AddEdge(CITY_PEACH, edge);
	// sixth vertex
	edge.Initialize(46, CITY_ORANGE);
	graph.AddEdge(CITY_PINEAPPLE, edge);
	edge.Initialize(27, CITY_APPLE);
	graph.AddEdge(CITY_PINEAPPLE, edge);
	// seventh vertex
	edge.Initialize(49, CITY_CHERRY);
	graph.AddEdge(CITY_GRAPE, edge);
	edge.Initialize(30, CITY_APPLE);
	graph.AddEdge(CITY_GRAPE, edge);
	// eighth vertex
	edge.Initialize(59, CITY_GRAPE);
	graph.AddEdge(CITY_CHERRY, edge);
	edge.Initialize(50, CITY_APPLE);
	graph.AddEdge(CITY_CHERRY, edge);
}

//////////

int main()
{
	//                                           0           1            2            3             4           5               6           7
	const std::vector<std::string> vertexNames{ CITY_APPLE, CITY_ORANGE, CITY_CARROT, CITY_AVOCADO, CITY_PEACH, CITY_PINEAPPLE, CITY_GRAPE, CITY_CHERRY };
	const std::vector<std::string> sources{ CITY_APPLE, CITY_CARROT, CITY_PINEAPPLE };
	const std::vector<std::string> goals{ CITY_CHERRY, CITY_GRAPE, CITY_CARROT };

	ShortestPath shortestPath;
	Graph graph;
	graph.Initialize(vertexNames);
	SetupGraph(graph);

	for (int i = 0; i < sources.size(); i++)
	{
		shortestPath = graph.FindShortestPath(sources[i], goals[i]);
		if (!shortestPath.path.empty())
		{
			std::cout << "The shortest path from " << sources[i] << " to " << goals[i] << " : ";
			for (std::string vertex : shortestPath.path)
			{
				std::cout << vertex;
				if (vertex != goals[i])
				{
					std::cout << " => ";
				}
			}
			std::cout << "\nThe length = " << shortestPath.length << '\n';
		}
		else
		{
			std::cout << "There's no path from " << sources[i] << " to " << goals[i] << '\n';
		}
	}

	return 0;
}