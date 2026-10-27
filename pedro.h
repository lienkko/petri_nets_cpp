#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

class Pedro
{
private:
    using index = size_t;
    using way = std::pair<size_t, int>; // index of vertex, points to go

    struct Transition
    {
        std::vector<way> IncomingWays;
        std::vector<way> OutcomingWays;
    };

    std::map<index, int> all_vertexes; // index, points
    std::map<index, Transition> all_transitions;

    void DoTransition(Transition &transition, index index_of_transition)
    {
        // Take points from Incoming Vertexes
        for (way &w : transition.IncomingWays)
        {
            if (all_vertexes[w.first] - w.second < 0)
                throw std::invalid_argument("Not enough points for this transition");
            else
                all_vertexes[w.first] -= w.second;
        }

        // Give points to Outcoming Vertexes
        for (way &w : transition.OutcomingWays)
        {
            all_vertexes[w.first] += w.second;
        }
        std::cout << "Transition t" << std::to_string(index_of_transition) << " was completed successfully" << std::endl;
    }

public:
    void DoTransition(index index_of_transition)
    {
        if (all_transitions.find(index_of_transition) == all_transitions.end())
            throw std::invalid_argument("Transition t" + std::to_string(index_of_transition) + " doesn't exist");
        DoTransition(all_transitions[index_of_transition], index_of_transition);
    }

    void AddVertex(int start_points, index vertex_index)
    {
        if (start_points < 0)
            throw std::invalid_argument("Start_points can't be negative");
        if (all_vertexes.find(vertex_index) != all_vertexes.end())
            throw std::invalid_argument("Vertex with index " + std::to_string(vertex_index) + " already exists");
        all_vertexes[vertex_index] = {start_points};
        std::cout << "Created new vertex - v" << vertex_index << std::endl;
    }

    void AddTransition(std::vector<way> &&incoming_ways, std::vector<way> &&outcoming_ways, index transition_index)
    {
        if (all_transitions.find(transition_index) != all_transitions.end())
            throw std::invalid_argument("Transition with index " + std::to_string(transition_index) + " already exists");
        all_transitions[transition_index] = {incoming_ways, outcoming_ways};
        std::cout << "Created new transition - t" << transition_index << std::endl;
    }

    void AddTransition(std::vector<way> &incoming_ways, std::vector<way> &outcoming_ways, index transition_index)
    {
        AddTransition(std::move(std::vector<way>(incoming_ways)), std::move(std::vector<way>(incoming_ways)), transition_index);
    }

    // void AddTransition(way &incoming_way, std::vector<way> &outcoming_ways, index transition_index)
    // {
    //     AddTransition({incoming_way}, outcoming_ways, transition_index);
    // }
    // void AddTransition(std::vector<way> &incoming_ways, way &outcoming_way, index transition_index)
    // {
    //     AddTransition(incoming_ways, {outcoming_way}, transition_index);
    // }
    // void AddTransition(way &incoming_way, way &outcoming_way, index transition_index)
    // {
    //     AddTransition({incoming_way}, {outcoming_way}, transition_index);
    // }

    void RemoveVertex(index vertex_index)
    {
        if (all_vertexes.find(vertex_index) == all_vertexes.end())
            throw std::invalid_argument("Vertex v" + std::to_string(vertex_index) + " doesn't exist");
        all_vertexes.erase(vertex_index);
        std::cout << "Vertex v" << vertex_index << " was removed" << std::endl;
        for (const std::pair<index, Transition> &w : all_transitions)
        {
            auto it = std::find_if(w.second.IncomingWays.begin(), w.second.IncomingWays.end(), [vertex_index](const auto &item)
                                   { return item.first == vertex_index; });

            if (it != w.second.IncomingWays.end())
            {
                all_transitions.erase(w.first);
                std::cout << "Transition t" << w.first << " was removed" << std::endl;
            }
        }
    }

    void RemoveTransition(index transition_index)
    {
        all_transitions.erase(transition_index);
    }

    void PrintVertexesInfo() const noexcept
    {
        for (const std::pair<index, int> &vertex_pair : all_vertexes)
            std::cout << "V" << vertex_pair.first << ": " << vertex_pair.second << " points" << std::endl;
    }
};
