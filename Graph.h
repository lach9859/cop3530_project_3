#pragma once
#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <stack>
#include <set>
#include "Image.h"
using namespace std;

struct Edge
{
    Image::Pixel src;
    Image::Pixel dest;
    // ints are the rec, blue, or green values
    Edge( Image::Pixel _src, Image::Pixel _dest) {src = _src; dest = _dest;}

    /*
    int src, dest;
    Edge(int _src, int _dest) {src = _src; dest = _dest;}
     */

class Graph
{
public:
    int numVertices;
    vector<vector<Image::Pixel>> adjList;  // adjacency list


    Graph(const vector<Edge>& edges, int vertices)
    {
        numVertices = vertices;

        adjList.resize(vertices);

        for (auto &edge : edges) {
            adjList[edge.src].push_back(edge.dest);
        }
    }

    bool dfs(const Graph& graph, Image::Pixel src, Image::Pixel dest);
};

bool Graph::dfs(const Graph& graph, Image::Pixel src, Image::Pixel dest)
{
    set<Image::Pixel> visited;
    stack<Image::Pixel> stk;
    stk.push(src);

    while (!stk.empty())
    {
        Image::Pixel u = stk.top();
        stk.pop();
        vector<Image::Pixel> neighbors = graph.adjList[u];
        for (auto v: neighbors)
        {
            if (visited.count(v) == 0)
            {
                visited.insert(v);
                stk.push(v);
            }
        }
    }
    return false;
}