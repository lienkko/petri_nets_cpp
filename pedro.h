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
        std::vector<transition> OutcomingTransitions;
    };

    void DoTransition(FullTransition ftransition)
    {
        // Take points from Incoming Nodes
        for (transition& t : ftransition.IncomingTransitions) {
            if (t.first.Points - t.second < 0)
                throw std::invalid_argument("Not enough points for this transition");
            else
                t.first.Points -= t.second;
        }

        // Give points to Outcoming Nodes
        for (transition& t : ftransition.OutcomingTransitions) {
            t.first.Points += t.second;
        }

    }
};
