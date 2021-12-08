#include "Graph.h"
#include <iostream>
#include <set>
#include <queue>
#include <stack>

using namespace std;

Graph::Graph()
{
	numVertices = 0;
	width = 0;
	height = 0;
}

Graph::Graph(const sf::Image& image)
{
	const sf::Uint8* arrPtr = image.getPixelsPtr(); // each pixel has r, g, b, a component

	numVertices = image.getSize().x * image.getSize().y - 1;
	width = image.getSize().x;
	height = image.getSize().y;

	// Declare and size vector of image pixels
	vector<Pixel> imagePixels;
	imagePixels.resize(image.getSize().x * image.getSize().y);

	cout << "start filling vector with image pixels" << endl;
	// Fill vector with image pixels
	for (unsigned int i = 0; i < (image.getSize().x * image.getSize().y); i++) // i is image pixel position, starts at top left goes left to right
	{
		Pixel tempPixel;
		tempPixel.index = i;
		tempPixel.yPos = i / image.getSize().x;
		tempPixel.xPos = i % image.getSize().x;
		tempPixel.red = arrPtr[i * 4];
		tempPixel.green = arrPtr[i * 4 + 1];
		tempPixel.blue = arrPtr[i * 4 + 2];
		tempPixel.alpha = arrPtr[i * 4 + 3];

		imagePixels[i] = tempPixel;
	}
	cout << "vector finished filling with all image pixels" << endl;

	cout << "start filling graph" << endl;
	// Add edges for all pixels, place in graph
	for (unsigned int i = 0; i < imagePixels.size(); i++)
	{
		vector<Pixel> neighbors;
		// If not at left of image, add left pixel to neighbors
		if (i % image.getSize().x != 0)
		{
			neighbors.push_back(imagePixels.at(i - 1));
		}
		// If not at right of image, add right pixel to neighbors
		if ((i - (image.getSize().x - 1)) % image.getSize().x != 0) // if at right of image, index will move to left of image and then perform left check
		{
			neighbors.push_back(imagePixels.at(i + 1));
		}
		// If not at top of image, add above pixel to neighbors
		if (i > image.getSize().x - 1) // not in top row
		{
			neighbors.push_back(imagePixels.at(i - image.getSize().x));
		}
		// If not at bott of image, add below pixel to neighbors
		if (i < image.getSize().x * (image.getSize().y - 1)) // above bottom row
		{
			neighbors.push_back(imagePixels.at(i + image.getSize().x));
		}

		adjList.emplace(i, neighbors);
	}
	cout << "graph filled" << endl;
}

void Graph::bfsColor(unsigned int xPos, unsigned int yPos, unsigned int threshold, vector<pair<unsigned int, unsigned int>>& toColor, sf::RenderWindow& window, sf::Event& event, bool& running) const // return vector of pairs with xPos, yPos to change color
{
	cout << "start call bfsColor" << endl;

	// bfs code referenced from Graphs lecture slide 17
	unsigned int sourceIndex = yPos * width + xPos;

	set<int> visited; // set of indexes to be colored
	queue<int> q;

	visited.insert(sourceIndex);
	q.push(sourceIndex);

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		vector<Pixel> neighbors = adjList.at(u);

		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			// doesn't visit if previously visited or color is too close to pure black
			if (visited.count(neighbors.at(i).index) == 0 &&
				neighbors.at(i).red >= threshold &&
				neighbors.at(i).green >= threshold &&
				neighbors.at(i).blue >= threshold
				)
			{
				visited.insert(neighbors.at(i).index);
				q.push(neighbors.at(i).index);
			}
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
				window.close();
				while (!q.empty())
				{
					q.pop();
				}
			}
		}
	}

	// convert set of index integers to vector of pairs xPos and yPos
	for (unsigned int index : visited)
	{
		// make pair of xPos, yPos from index visited
		unsigned int tempXPos = index % width;
		unsigned int tempYPos = index / width;

		toColor.push_back(make_pair(tempXPos, tempYPos));
	}

	cout << "finished bfsColor call" << endl;
}

void Graph::dfsColor(unsigned int xPos, unsigned int yPos, unsigned int threshold, vector<pair<unsigned int, unsigned int>>& toColor) const
{
	cout << "start call dfsColor" << endl;

	// dfs code referenced from Graphs lecture slide 17
	unsigned int sourceIndex = yPos * width + xPos;

	set<int> visited; // set of indexes to be colored
	stack<int> s;

	visited.insert(sourceIndex);
	s.push(sourceIndex);

	while (!s.empty())
	{
		unsigned int u = s.top();
		s.pop();

		vector<Pixel> neighbors = adjList.at(u);

		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			// doesn't visit if previously visited or color is too close to pure black
			if (visited.count(neighbors.at(i).index) == 0 &&
				neighbors.at(i).red >= threshold &&
				neighbors.at(i).green >= threshold &&
				neighbors.at(i).blue >= threshold
				)
			{
				visited.insert(neighbors.at(i).index);
				s.push(neighbors.at(i).index);
			}
		}
	}

	// convert set of index integers to vector of pairs xPos and yPos
	for (int index : visited)
	{
		// make pair of xPos, yPos from index visited
		unsigned int tempXPos = index % width;
		unsigned int tempYPos = index / width;

		toColor.push_back(make_pair(tempXPos, tempYPos));
	}

	cout << "finished dfsColor call" << endl;
}

void Graph::bfsColorRealTime(unsigned int xPos, unsigned int yPos, unsigned int threshold, sf::Image& image, sf::Texture texture, sf::Sprite sprite, sf::RenderWindow& window, sf::Event& event, const sf::Color& color, bool& running) const
{
	cout << "start call real time bfsColor" << endl;

	// bfs code referenced from Graphs lecture slide 17
	unsigned int sourceIndex = yPos * width + xPos;

	set<int> visited; // set of indexes to be colored
	queue<int> q;

	// visit and color start pixel
	visited.insert(sourceIndex);
	q.push(sourceIndex);
	unsigned int tempXPos = sourceIndex % width;
	unsigned int tempYPos = sourceIndex / width;
	image.setPixel(tempXPos, tempYPos, color);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	// visit and color start pixel

	window.clear();
	window.draw(sprite);
	window.display();

	while (!q.empty())
	{
		int u = q.front();
		q.pop();

		vector<Pixel> neighbors = adjList.at(u);

		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			// doesn't visit if previously visited or color is too close to pure black
			if (visited.count(neighbors.at(i).index) == 0 &&
				neighbors.at(i).red >= threshold &&
				neighbors.at(i).green >= threshold &&
				neighbors.at(i).blue >= threshold
				)
			{
				visited.insert(neighbors.at(i).index);
				q.push(neighbors.at(i).index);

				// color the pixel
				unsigned int tempXPos = neighbors.at(i).index % width;
				unsigned int tempYPos = neighbors.at(i).index / width;
				image.setPixel(tempXPos, tempYPos, color);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						running = false;
						window.close();
						while (!q.empty())
						{
							q.pop();
						}
					}
				}

				window.clear();
				window.draw(sprite);
				window.display();
			}
		}
	}
}

void Graph::dfsColorRealTime(unsigned int xPos, unsigned int yPos, unsigned int threshold, sf::Image& image, sf::Texture texture, sf::Sprite sprite, sf::RenderWindow& window, sf::Event& event, const sf::Color& color, bool& running) const
{
	cout << "start call real time dfsColor" << endl;

	// dfs code referenced from Graphs lecture slide 17
	unsigned int sourceIndex = yPos * width + xPos;

	set<int> visited; // set of indexes to be colored
	stack<int> s;

	// visit and color start pixel
	visited.insert(sourceIndex);
	s.push(sourceIndex);
	unsigned int tempXPos = sourceIndex % width;
	unsigned int tempYPos = sourceIndex / width;
	image.setPixel(tempXPos, tempYPos, color);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	window.clear();
	window.draw(sprite);
	window.display();

	while (!s.empty())
	{
		int u = s.top();
		s.pop();

		vector<Pixel> neighbors = adjList.at(u);

		for (unsigned int i = 0; i < neighbors.size(); i++)
		{
			// doesn't visit if previously visited or color is too close to pure black
			if (visited.count(neighbors.at(i).index) == 0 &&
				neighbors.at(i).red >= threshold &&
				neighbors.at(i).green >= threshold &&
				neighbors.at(i).blue >= threshold
				)
			{
				visited.insert(neighbors.at(i).index);
				s.push(neighbors.at(i).index);


				// color the pixel
				tempXPos = neighbors.at(i).index % width;
				tempYPos = neighbors.at(i).index / width;
				image.setPixel(tempXPos, tempYPos, color);
				texture.loadFromImage(image);
				sprite.setTexture(texture);
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
					{
						running = false;
						window.close();
						while (!s.empty())
						{
							s.pop();
						}
						i = neighbors.size();
					}
				}

				window.clear();
				window.draw(sprite);
				window.display();
			}
		}
	}
}