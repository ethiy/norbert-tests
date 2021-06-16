#pragma once

#include <norbert/volume.hpp>

#include <cmath>
#include <set>


namespace norbert
{
    template<typename color_t>
    Volume<color_t>::Volume(std::size_t const depth, std::size_t const height, std::size_t const width, color_t const value)
        : Image<color_t>(depth * height, width, value), height_(height), depth_(depth)
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
        // std::cout <<  << std::endl;
        return Image<color_t>::at(plane * height_ + line, column);
    }

    template<typename color_t>
    color_t Volume<color_t>::at(std::size_t const plane, std::size_t const line, std::size_t const column) const
    {
        check_plane(plane);
        return Image<color_t>::at(plane * height_ + line, column);
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


    template<typename color_t>
    std::size_t Volume<color_t>::max_number_connected_components() const noexcept
    {
        return ((depth_ + 2) * (height_ + 2) * (width() + 2)) / 27 + 1;
    }


    template<typename color_t>
    Volume<std::size_t> Volume<color_t>::label_components() const noexcept
    {
        Volume<std::size_t> label_components_(depth_, height_, width());
        auto max_components = max_number_connected_components();
        std::vector<std::size_t> rank(max_components);
        std::vector<std::size_t> parent(max_components);
        boost::disjoint_sets equivalence_map(&rank[0], &parent[0]);

        first_connectivity_pass(label_components_, equivalence_map);

        for(std::size_t plane(0); plane != depth_; ++plane)
            for(std::size_t line(0); line != height_; ++line)
                for(std::size_t column(0); column != width(); ++column)
                {
                    auto label = label_components_.at(plane, line, column);
                    if(label)
                        label_components_.at(plane, line, column) = equivalence_map.find_set(label);
                }
        return label_components_;
    }


    template<typename color_t>
    void Volume<color_t>::first_connectivity_pass(Volume<std::size_t> & label_components_, boost::disjoint_sets<std::size_t*,std::size_t*> & equivalence_map) const
    {
        std::size_t max_label(0);
        std::set<std::size_t> unique_neighbor_values;

        for(std::size_t plane(0); plane < depth_; ++plane)
            for(std::size_t line(0); line != height_; ++line)
                for(std::size_t column(0); column != width(); ++column)
                    if(at(plane, line, column))
                    {
                        for(auto && [neighbor_plane, neighbor_line, neighbor_column] : connectivity_neightbor_indices_3d(plane, line, column, height_, width()))
                        {
                            std::size_t label = label_components_.at(neighbor_plane, neighbor_line, neighbor_column);
                            if(label)
                                unique_neighbor_values.insert(label);
                        }
                        if(unique_neighbor_values.empty())
                        {
                            equivalence_map.make_set(++max_label);
                            label_components_.at(plane, line, column) = max_label;
                        }
                        else
                        {
                            auto min_label = *std::min_element(std::begin(unique_neighbor_values), std::end(unique_neighbor_values));
                            label_components_.at(plane, line, column) = min_label;
                            for(auto && neightbor_value: unique_neighbor_values)
                                equivalence_map.union_set(min_label, neightbor_value);
                        }
                        unique_neighbor_values.clear();
                    }
    }


    std::list<std::tuple<std::size_t, std::size_t, std::size_t>> connectivity_neightbor_indices_3d(std::size_t const plane, std::size_t const line, std::size_t const column, std::size_t const height, std::size_t const width) noexcept
    {
        std::list<std::tuple<std::size_t, std::size_t, std::size_t>> connectivity_neightbor_indices_;

        for(auto && [neighbor_line, neighbor_column] : connectivity_neightbor_indices_2d(line, column, height, width))
        {
            connectivity_neightbor_indices_.push_back(
                std::make_tuple(
                    plane,
                    neighbor_line,
                    neighbor_column
                )
            );
            if(plane)
                connectivity_neightbor_indices_.push_back(
                    std::make_tuple(
                        plane - 1,
                        neighbor_line,
                        neighbor_column
                    )
                );
        }

        if(plane)
            connectivity_neightbor_indices_.push_back(
                std::make_tuple(
                        plane - 1,
                        line,
                        column
                    )
            );
        
        return connectivity_neightbor_indices_;
    }
}
