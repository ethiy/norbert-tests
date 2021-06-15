#pragma once

#include <norbert/image.hpp>

namespace norbert
{
    template<typename color_t>
    class Volume : public Image<color_t>
    {
    public:
        Volume() = delete;
        Volume(std::size_t const depth, std::size_t const height, std::size_t const width, color_t const value = 0);
        Volume(std::size_t const depth, std::size_t const height, std::size_t const width, std::vector<color_t> const& values);
        Volume(Volume const& other) = default;
        Volume(Volume && other) = default;
        ~Volume();

        Volume & operator =(Volume const& other) = default;
        Volume & operator =(Volume && other) = default;

        color_t & at(std::size_t const plane, std::size_t const line, std::size_t const column);
        color_t at(std::size_t const plane, std::size_t const line, std::size_t const column) const;

        using Image<color_t>::height;
        using Image<color_t>::width;
        std::size_t depth() const noexcept;

    private:
        std::size_t depth_;

        void check_plane(std::size_t const plane) const;
    };
}

#include <norbert/volume.hxx>
