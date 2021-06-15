#pragma once

#include <norbert/volume.hpp>


namespace norbert
{
    template<typename color_t>
    Volume<color_t>::Volume(std::size_t const depth, std::size_t const height, std::size_t const width, color_t const value)
        : Image<color_t>(depth * height, width, value)
    {}

    template<typename color_t>
    Volume<color_t>::Volume(std::size_t const depth, std::size_t const height, std::size_t const width, std::vector<color_t> const& values)
        : Image<color_t>(depth * height, width, values), depth_(depth)
    {}

    template<typename color_t>
    Volume<color_t>::~Volume() {}


    template<typename color_t>
    color_t & Volume<color_t>::at(std::size_t const plane, std::size_t const line, std::size_t const column)
    {
        check_plane(plane);
        return Image<color_t>::at(plane * height() + line, column);
    }

    template<typename color_t>
    color_t Volume<color_t>::at(std::size_t const plane, std::size_t const line, std::size_t const column) const
    {
        check_plane(plane);
        return Image<color_t>::at(plane * height() + line, column);
    }

    template<typename color_t>
    void Volume<color_t>::check_plane(std::size_t const plane) const
    {
        if(plane >= depth_)
            throw std::out_of_range("Plane index out of range.");
    }


    template<typename color_t>
    std::size_t Volume<color_t>::depth() const noexcept
    {
        return depth_;
    }
}
