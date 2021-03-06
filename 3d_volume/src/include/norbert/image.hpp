#pragma once

#include <vector>
#include <iostream>
#include <utility>
#include <list>


namespace norbert
{
    template<typename color_t>
    class Image
    {
    public:
        Image() = delete;
        Image(std::size_t const height, std::size_t const width, color_t const value = 0);
        Image(std::size_t const height, std::size_t const width, std::vector<color_t> const& values);
        Image(Image const& other) = default;
        Image(Image && other) = default;
        ~Image();

        Image & operator =(Image const& other) = default;
        Image & operator =(Image && other) = default;

        color_t & at(std::size_t const line, std::size_t const column);
        color_t at(std::size_t const line, std::size_t const column) const;

        std::size_t height() const noexcept;
        std::size_t width() const noexcept;

    protected:
        void check_line(std::size_t const line) const;
        void check_column(std::size_t const column) const;

    private:
        std::size_t height_;
        std::size_t width_;
        std::vector<color_t> values_;
    };

    std::list<std::pair<std::size_t, std::size_t>> connectivity_neightbor_indices_2d(std::size_t const line, std::size_t const column, std::size_t const height, std::size_t const width, bool const is_3d = true) noexcept;

    template<typename color_t>
    std::ostream & operator <<(std::ostream & out, Image<color_t> const& image);
}

#include <norbert/image.hxx>