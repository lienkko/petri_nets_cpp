#include "pedro.h"

int main(int argc, char *argv[])
{
    try
    {
        Pedro pedro;
        pedro.AddVertex(2, 1);
        pedro.AddVertex(0, 2);
        pedro.PrintVertexesInfo();
        pedro.AddTransition({{1, 2}}, {{2, 3}}, 1);
        pedro.DoTransition(1);
        pedro.PrintVertexesInfo();
        pedro.RemoveVertex(1);
        pedro.PrintVertexesInfo();
        pedro.DoTransition(1);
    }
    catch (std::invalid_argument e)
    {
        std::cout << "The program has finished with error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}