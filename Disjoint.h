#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include<tuple>
using namespace std;

class Disjoint
{
private:

    int* parent;
    int* rank;

public:

    Disjoint(int n);

    ~Disjoint();

    int find(int u);

    void unionSets(int u, int v);
};