#pragma once

#include <norbert/image.hpp>
#include <functional>
#include <tuple>
#include <boost/pending/disjoint_sets.hpp>


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

        std::size_t max_number_connected_components() const noexcept;
        Volume<std::size_t> label_components() const noexcept;

    private:
        std::size_t height_;
        std::size_t depth_;

        void check_plane(std::size_t const plane) const;

        void first_connectivity_pass(Volume<std::size_t> & label_components_, boost::disjoint_sets<std::size_t*,std::size_t*> & equivalence_map) const;
    };

    std::list<std::tuple<std::size_t, std::size_t, std::size_t>> connectivity_neightbor_indices_3d(std::size_t const plane, std::size_t const line, std::size_t const column, std::size_t const width, std::size_t depth) noexcept;
}

#include <norbert/volume.hxx>
