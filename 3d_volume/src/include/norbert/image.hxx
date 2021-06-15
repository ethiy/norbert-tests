#pragma once

#include <norbert/image.hpp>

#include <algorithm>
#include <stdexcept>


namespace norbert
{
    template<typename color_t>
    Image<color_t>::Image(std::size_t const height, std::size_t const width, color_t const value)
        : height_(height), width_(width), values_(height * width, value)
    {}

    template<typename color_t>
    Image<color_t>::Image(std::size_t const height, std::size_t const width, std::vector<color_t> const& values)
        : Image<color_t>(height, width)
    {
        std::move(
            std::begin(values),
            std::end(values),
            std::begin(values_)
        );
    }

    template<typename color_t>
    Image<color_t>::~Image() {}


    template<typename color_t>
    color_t & Image<color_t>::at(std::size_t const line, std::size_t const column)
    {
        check_line(line);
        check_column(column);
        return values_.at(line * width_ + column);
    }

    template<typename color_t>
    color_t Image<color_t>::at(std::size_t const line, std::size_t const column) const
    {
        check_line(line);
        check_column(column);
        return values_.at(line * width_ + column);
    }

    template<typename color_t>
    void Image<color_t>::check_line(std::size_t const line) const
    {
        if(line >= height_)
            throw std::out_of_range("Line index out of range.");
    }

    template<typename color_t>
    void Image<color_t>::check_column(std::size_t const column) const
    {
        if(column >= width_)
            throw std::out_of_range("Column index out of range.");
    }


    template<typename color_t>
    std::size_t Image<color_t>::height() const noexcept
    {
        return height_;
    }
    template<typename color_t>
    std::size_t Image<color_t>::width() const noexcept
    {
        return width_;
    }


    template<typename color_t>
    std::ostream & operator <<(std::ostream & out, Image<color_t> const& image)
    {
        for(std::size_t line(0); line != image.height(); ++line)
        {
            out << image.at(line, 0);
            for(std::size_t column(1); column != image.width(); ++column)
                out << " " << image.at(line, column);
            out << std::endl;
        }
        return out;
    }
}
