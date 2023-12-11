#pragma once
#include <iostream>
#include <string>

class Edge
{
public:
	Edge();

	// destination is passed by value cause we set it to the local variable
	Edge(int weight, std::string destination);

	// sets the weight and destination; destination is passed by value cause we set it to the local variable
	void Initialize(int weight, std::string destination);

	int GetDistance() const;

	// returns destination - name of the connected vertex
	std::string GetDestination() const;

private:
	int distance;

	// name of the connected vertex
	std::string destination;
};