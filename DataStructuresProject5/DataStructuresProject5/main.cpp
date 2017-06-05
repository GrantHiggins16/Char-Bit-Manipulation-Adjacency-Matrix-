//
//  main.cpp
//  DataStructuresProject5
//
//  Created by Grant Higgins on 4/19/17.
//  Copyright © 2017 Grant Higgins. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace::std;

class BitMatrixGraph
{
protected:
    unsigned char** bitAdjacencyMatrix;//adjacency matrix
    int n;//number of nodes in the graph
public:
    BitMatrixGraph();//default constructor
    BitMatrixGraph(int numNodes);//non-default constructor
    BitMatrixGraph(const BitMatrixGraph& otherGraph);//copy constructor
    void operator=(const BitMatrixGraph& otherGraph);//assignment operator
    friend ostream& operator<<(ostream& s, const BitMatrixGraph& otherGraph);//ostream operator
    void addEdge(int u, int v);//adds edge to graph
    bool isAnEdge(int u, int v);//returns true if edge exists btwn nodes
    void printBits();//prints the bit adjacency matrix
    virtual ~BitMatrixGraph();//destructor
    int** breadthFirstSearch();//return parent array of graph using breadth first search
    int** depthFirstSearch();//return parent array of graph using depth first search
    
};

int** breadthFirstSearch()
{
    int** b;
    return b;
}

int** depthFirstSearch()
{
    int** b;
    return b;
}

BitMatrixGraph::BitMatrixGraph()
{
    n = 0;//no nodes in graph
    bitAdjacencyMatrix = NULL;//bit adjacency matrix points to nothing
}

BitMatrixGraph::BitMatrixGraph(int numNodes)
{
    n = numNodes;
    int size;
    if (n % 8 == 0)
    {
        size = n / 8;
    }
    else
    {
        size = (int) (n / 8) + 1;
    }
    bitAdjacencyMatrix = new unsigned char* [n];
    for (int i = 0; i < n; i++)
    {
        bitAdjacencyMatrix[i] = new unsigned char [size];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < size; j++)
        {
            bitAdjacencyMatrix[i][j] = 0x00 << 8;
        }
}

BitMatrixGraph::BitMatrixGraph(const BitMatrixGraph& otherGraph)
{
    char temp;
    n = otherGraph.n;
    int size;
    if (n % 8 == 0)
    {
        size = n / 8;
    }
    else
    {
        size = (int) (n / 8) + 1;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < size; j++)
        {
            temp = otherGraph.bitAdjacencyMatrix[i][j];
            bitAdjacencyMatrix[i][j] = temp;
        }
}

void BitMatrixGraph::operator=(const BitMatrixGraph &otherGraph)
{
    char temp;
    n = otherGraph.n;
    int size;
    if (n % 8 == 0)
    {
        size = n / 8;
    }
    else
    {
        size = (int) (n / 8) + 1;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < size; j++)
        {
            temp = otherGraph.bitAdjacencyMatrix[i][j];
            bitAdjacencyMatrix[i][j] = temp;
        }
}

ostream& operator<<(ostream& s, const BitMatrixGraph& otherGraph)
{
    return s;
}

void BitMatrixGraph::addEdge(int u, int v)
{
    //index containing correct char is int value of v/8
    int indexToModify = (int) (v / 8);
    char toChange = bitAdjacencyMatrix[u][indexToModify];
    //bit to change in char
    int bitToModify = 8 - (v % 8) - 1;
    toChange |= 0x01 << (bitToModify);
    bitAdjacencyMatrix[u][indexToModify] = toChange;
    //make other edge as well
    int indexToModify2 = (int) (u / 8);
    char toChange2 = bitAdjacencyMatrix[v][indexToModify2];
    int bitToModify2 = 8 - (u % 8) - 1;
    toChange2 |= 0x01 << (bitToModify2);
    bitAdjacencyMatrix[v][indexToModify2] = toChange2;
}

bool BitMatrixGraph::isAnEdge(int u, int v)
{
    int indexToCheck = (int) (v/8);
    char toCheck = bitAdjacencyMatrix[u][indexToCheck];
    int bitToCheck = v % 8;
    if (toCheck & (0x01 << bitToCheck))
        return true;
    else
        return false;
}

void BitMatrixGraph::printBits()
{
    int size;
    if (n % 8 == 0)
    {
        size = n / 8;
    }
    else
    {
        size = (int) (n / 8) + 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < size && j < n; j++)
        {
            for (int k = 0; k < 8; k++)
            {
                if (bitAdjacencyMatrix[i][j] & (0x01 << (7-k)))
                    cout << 1;
                else
                    cout << 0;
            }
            cout << " ";
        }
        cout << endl;
    }
}

BitMatrixGraph::~BitMatrixGraph()
{
    //only need to delete bit adjacency matrix
    delete [] bitAdjacencyMatrix;
}

int main()
{
    int size;
    int node1;
    int node2;
    cin >> size;
    BitMatrixGraph bmg0 = BitMatrixGraph(size);
    while (!cin.eof())
    {
        cin >> node1 >> node2;
        bmg0.addEdge(node1, node2);
        bmg0.printBits();
        if (bmg0.isAnEdge(4, 3))
        {
            cout << "good job";
        }
    }
    //print bmg
    cout << bmg0;
    //displaying the copy constructor and assignment operator
    BitMatrixGraph bmg1 = BitMatrixGraph(bmg0);
    BitMatrixGraph bmg2 = BitMatrixGraph(size);
    bmg2 = bmg0;
}
