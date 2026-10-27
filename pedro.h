#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

class Pedro
{
private:
    struct Node
    {
        int Points;
    };

    using transition = std::pair<Node, int>;

    struct FullTransition
    {
        std::vector<transition> IncomingTransitions;
        std::vector<transition> OutcomingTransitions;
    };

    std::unordered_map<int,Node> all_nodes;
    int last_node_index = 0;
    std::unordered_map<int, FullTransition> all_transitions;
    int last_transition_index = 0;


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

public:
    void DoTransition(int index_of_transition) {
        DoTransition(all_transitions[index_of_transition]);
    }

    void AddNode(int start_points) {
        if (start_points < 0)
            throw std::invalid_argument("start_points can't be negative");
        all_nodes[last_node_index++] = {start_points};
        std::cout << "Index of new node is " << last_node_index << std::endl;
    }

    void AddTransition(std::vector<int>& indexes_of_incoming_nodes, std::vector<int>& indexes_of_outcoming_nodes) {
        FullTransition t1;
        for (int i : indexes_of_incoming_nodes)
        t1.IncomingTransitions.push_back({all_nodes[]})
    }
};
