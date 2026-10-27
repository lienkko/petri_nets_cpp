#include "pedro.h"
#include "tests.h"

int main(int argc, char *argv[])
{
    try
    {
        run_tests();
    }
    catch (std::invalid_argument e)
    {
        std::cout << "The program has finished with error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}