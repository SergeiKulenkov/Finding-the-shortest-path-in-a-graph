#pragma once
#include <string_view>
#include <assert.h>

template<typename T>
concept Numeric = (std::is_integral_v<T> || std::is_arithmetic_v<T>) && !std::is_same_v<T, bool>;

template<Numeric T>
class Edge
{
public:
	Edge() : m_Length(0), m_Destination("") { }

	Edge(const T length, const std::string_view& destination) : m_Length(length), m_Destination(destination)
	{
		assert((length > (T)0), "Length should be > 0.");
	}

	T GetLength() const { return m_Length; }

	std::string_view GetDestination() const { return m_Destination; }

private:
	T m_Length;

	// name of the connected vertex
	std::string_view m_Destination;
};