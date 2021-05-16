#pragma once


class Edge {

public:
    int start;
    int end;
    int weight;
    bool directed;

    Edge();
    ~Edge();
};
