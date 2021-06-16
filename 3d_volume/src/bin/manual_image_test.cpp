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

    norbert::Volume<std::uint16_t> image_test_connected_components(1, 4, 5);
    image_test_connected_components.at(0, 1, 2) = 1;
    image_test_connected_components.at(0, 2, 1) = 1;
    image_test_connected_components.at(0, 2, 3) = 1;
    std::cout << image_test_connected_components << std::endl;
    std::cout << image_test_connected_components.label_components() << std::endl;

    norbert::Volume<std::uint16_t> volume_test_connected_components(3, 4, 5);
    volume_test_connected_components.at(0, 1, 2) = 1;
    volume_test_connected_components.at(0, 2, 1) = 1;
    volume_test_connected_components.at(0, 2, 3) = 1;
    volume_test_connected_components.at(2, 1, 2) = 1;
    volume_test_connected_components.at(2, 2, 1) = 1;
    volume_test_connected_components.at(2, 2, 3) = 1;
    std::cout << volume_test_connected_components << std::endl;
    std::cout << volume_test_connected_components.label_components() << std::endl;

    norbert::Volume<std::uint16_t> volume_test_disconnected_components(3, 4, 5);
    volume_test_connected_components.at(0, 1, 2) = 1;
    volume_test_connected_components.at(0, 2, 1) = 1;
    volume_test_connected_components.at(0, 2, 3) = 1;
    volume_test_connected_components.at(1, 3, 2) = 1;
    volume_test_connected_components.at(2, 1, 2) = 1;
    volume_test_connected_components.at(2, 2, 1) = 1;
    volume_test_connected_components.at(2, 2, 3) = 1;
    std::cout << volume_test_connected_components << std::endl;
    std::cout << volume_test_connected_components.label_components() << std::endl;

    return EXIT_SUCCESS;
}