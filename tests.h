#ifndef TESTS_H
#define TESTS_H


#include "pedro.h"



inline void net_test1() {
    Pedro pedro;
    pedro.AddVertex(1, 1);
    pedro.AddVertex(2, 0);
    pedro.AddVertex(3, 0);
    pedro.AddVertex(4, 0);
    pedro.AddTransition({{1, 1}}, {{1, 1}, {2,1}}, 1);
    pedro.AddTransition({{1, 1}}, {{3, 1}}, 2);
    pedro.AddTransition({{2, 1}, {3, 1}}, {{3, 1}, {4, 1}}, 3);

    for (int i = 0; i<4; i++) {
        pedro.DoTransition(1);
    }
    pedro.DoTransition(2);
    for (int i = 0; i<4; i++) {
        pedro.DoTransition(3);
    }
    pedro.PrintVertexesInfo();
}

inline void print_transitions_test1() {
    Pedro pedro;
    pedro.AddVertex(1, 1);
    pedro.AddVertex(2, 0);
    pedro.AddVertex(3, 0);
    pedro.AddVertex(4, 0);
    pedro.AddTransition({{1, 1}}, {{1, 1}, {2,1}}, 1);
    pedro.AddTransition({{1, 1}}, {{3, 1}}, 2);
    pedro.AddTransition({{2, 1}, {3, 1}}, {{3, 1}, {4, 1}}, 3);

    pedro.PrintTransitions();
}


inline void run_tests() {
    // net_test1();
    print_transitions_test1();
}

#endif /* TESTS_H */