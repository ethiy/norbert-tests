#include <norbert/algorithms.hpp>

#include <cmath>


namespace norbert
{
    std::tuple<double, double, double> polar2cartesian(double const length, double const angle, double const altitude)
    {
        return std::make_tuple(
            length * std::cos(angle),
            length * std::sin(angle),
            altitude
        );
    }
    std::tuple<double, double, double> cartesian2polar(double const x, double const y, double const z)
    {
        return std::make_tuple(
            std::hypot(x, y, z),
            std::atan2(y, x),
            z
        );
    }
}
