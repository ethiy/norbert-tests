#include <norbert/volume.hpp>

#include <cstdlib>


int main(int argc, char* argv[])
{
    norbert::Image<std::uint16_t> test_image(4, 5);
    test_image.at(1, 2) = 1;
    std::cout << test_image << std::endl;

    norbert::Volume<std::uint16_t> test_volume(3, 4, 5);
    test_volume.at(0, 1, 2) = 1;
    std::cout << test_volume << std::endl;
    return EXIT_SUCCESS;
}