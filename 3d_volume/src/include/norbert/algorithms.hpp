#pragma once

#include <tuple>

namespace norbert
{
    std::tuple<double, double, double> polar2cartesian(double const length, double const angle, double const altitude);
    std::tuple<double, double, double> cartesian2polar(double const x, double const y, double const z);
}