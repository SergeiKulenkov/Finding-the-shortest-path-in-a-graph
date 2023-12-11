#include "Edge.h"

Edge::Edge() : distance(0), destination("")
{
}

Edge::Edge(int weight, std::string destination)
{
	this->distance = weight;
	this->destination = destination;
}

void Edge::Initialize(int weight, std::string destination)
{
	this->distance = weight;
	this->destination = destination;
}

int Edge::GetDistance() const
{
	return distance;
}

std::string Edge::GetDestination() const
{
	return destination;
}