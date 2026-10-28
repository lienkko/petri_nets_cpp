#ifndef PEDRO_H
#define PEDRO_H

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <math.h>


class Pedro
{
private:
    const std::string print_r_arrow = "-->";
    const std::string print_line = "--";
    const std::string print_corner = "+"; 
    const std::string print_border = "|";

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
        // Validation Test
        for (way &w : transition.IncomingWays)
        {
            if (all_vertexes[w.first] - w.second < 0)
                throw std::invalid_argument("Not enough points for this transition");
        }

        // Take points from Incoming Vertexes
        for (way &w : transition.IncomingWays)
        {
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

    // Add elements
    void AddVertex(index vertex_index, int start_points)
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


    // Remove Elements
    void RemoveVertex(index vertex_index)
    {
        if (all_vertexes.find(vertex_index) == all_vertexes.end())
            throw std::invalid_argument("Vertex v" + std::to_string(vertex_index) + " doesn't exist");

        // Removing vertex
        all_vertexes.erase(vertex_index);
        std::cout << "Vertex v" << vertex_index << " was removed" << std::endl;

        // Removing transitions that contain removed vertex
        // This is implemented to avoid transitions errors after the deletion of vertices 
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
        if (all_transitions.find(transition_index) == all_transitions.end())
            throw std::invalid_argument("Transition t" + std::to_string(transition_index) + " doesn't exist");
        all_transitions.erase(transition_index);
    }



    // Print Info About Net
    void PrintVertexesInfo() const noexcept
    {
        for (const std::pair<index, int> &vertex_pair : all_vertexes)
            std::cout << "v" << vertex_pair.first << ": " << vertex_pair.second << " points" << std::endl;
    }
    
    void PrintTransitions() const noexcept
    {
        std::cout << "Transitions info:" << std::endl;
        for (const std::pair<index,Transition>& trans: all_transitions) {
            std::cout << "Transition t" << trans.first << ":" << std::endl;
            const std::vector<way>& inc_ways = trans.second.IncomingWays;
            const std::vector<way>& outc_ways = trans.second.OutcomingWays;
            std::string ways_strings[inc_ways.size()+ outc_ways.size()];
            for (int i = 0; i<inc_ways.size(); i++)
            {
                std::string way_string = "v" + std::to_string(inc_ways[i].first) + print_line + std::to_string(inc_ways[i].second) + print_line + print_corner;
                ways_strings[i] = way_string;
            }
            for (int i = 0; i<outc_ways.size(); i++)
            {
                std::string way_string = print_corner + print_line + std::to_string(inc_ways[i].second) + print_line +  "v" + std::to_string(inc_ways[i].first) ;
                ways_strings[inc_ways.size()+i] = way_string;
            }
            int count_of_strokes = std::max(inc_ways.size(), outc_ways.size());
            bool is_inc_ways_bigger = inc_ways.size() > outc_ways.size();
            size_t top_blanks = std::abs(inc_ways.size() - outc_ways.size());
            for (int i = 0; i < count_of_strokes; i++) {

            }
        }

    }
    
};


#endif  /* PEDRO_H*/