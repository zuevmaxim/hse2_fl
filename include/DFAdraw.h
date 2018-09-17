#ifndef _GRAPH_DRAW_H_
#define _GRAPH_DRAW_H_

#include "minDFA.h"

class DFAdraw {
private:
    const minDFA& dfa;
public:
    DFAdraw(const minDFA& dfa);
    void draw(const char* s);
};

#endif
