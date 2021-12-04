#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <stack>
#include <set>
#include <map>
#include "Image.h"
using namespace std;

struct Edge
{
	Image::Pixel src;
	Image::Pixel dest;
	// ints are the red, blue, or green values
	Edge(Image::Pixel _src, Image::Pixel _dest) { src = _src; dest = _dest; }

	/*
	int src, dest;
	Edge(int _src, int _dest) {src = _src; dest = _dest;}
	 */
};

class Graph
{
public:
	int numVertices;
	//vector<vector<Image::Pixel>> adjList;  // adjacency list
	map <Image::Pixel, vector<Image::Pixel>> adjList; // revised adjacency list

	//Graph(const vector<Edge>& edges, int vertices)
	//{
	//	numVertices = vertices;

	//	adjList.resize(vertices);

	//	for (auto& edge : edges) {
	//		adjList[edge.src].push_back(edge.dest); // doesn't work b/c adjList[] using vectors expects int, but edge.src is Pixel
	//	}
	//}

	Graph(const vector<Edge>& edges, int vertices)
	{
		numVertices = vertices;
		map <Image::Pixel, vector<Image::Pixel>> adjList;

		for (auto& edge : edges)
		{
			//adjList[edge.src].push_back(edge.dest);
		}
	}

	bool dfs(Image::Pixel src, Image::Pixel dest);
};

//bool Graph::dfs(Image::Pixel src, Image::Pixel dest) // deleted const Graph& graph from parameter list b/c don't need to pass in graph, member function
//{
//	set<Image::Pixel> visited;
//	stack<Image::Pixel> stk;
//	stk.push(src);
//
//	while (!stk.empty())
//	{
//		Image::Pixel u = stk.top();
//		stk.pop();
//		vector<Image::Pixel> neighbors = adjList[u];
//		for (auto v : neighbors)
//		{
//			if (visited.count(v) == 0)
//			{
//				visited.insert(v);
//				stk.push(v);
//			}
//		}
//	}
//	return false;
//}