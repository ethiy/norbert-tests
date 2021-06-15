#include <norbert/volume.hpp>

#include <cstdlib>


int main(int argc, char* argv[])
{
    norbert::Image<std::uint16_t> test(4, 5);
    test.at(1, 2) = 1;
    std::cout << test << std::endl;
    return EXIT_SUCCESS;
}