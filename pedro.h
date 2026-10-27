#include <iostream>
#include <utility>
#include <vector>
class Pedro
{
    struct Node
    {
        int Points;
    };
    using transition = std::pair<Node, int>;
    struct FullTransition
    {
        int number;
        std::vector<transition> IncomingTransitions;
        std::vector<transition> OutomingTransitions;
    };

    void DoTransition(FullTransition transition)
    {
    }
};
