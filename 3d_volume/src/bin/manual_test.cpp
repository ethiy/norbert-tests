#include <norbert/volume.hpp>

#include <cstdlib>


int main(int argc, char* argv[])
{
    norbert::Image<bool> zero(4, 5);
    std::cout << zero << std::endl;
    return EXIT_SUCCESS;
}