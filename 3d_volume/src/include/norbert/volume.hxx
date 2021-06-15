#pragma once

#include <norbert/volume.hpp>

#include <map>
#include <set>


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
    std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> Volume<color_t>::get_left_up_front_neightbors_indices(std::size_t const plane, std::size_t const line, std::size_t const column) noexcept
    {
        std::vector<std::tuple<std::size_t, std::size_t, std::size_t>> neighbors;
        neighbors.reserve(7);

        for(auto && [neighbor_line, neighbor_column] : Image<color_t>::left_up_neightbor_indices(line, plane))
        {
            neighbors.push_back(
                std::make_tuple(
                    plane,
                    neighbor_line,
                    neighbor_column
                )
            );
            if(plane)
                 neighbors.push_back(
                    std::make_tuple(
                        plane - 1,
                        neighbor_line,
                        neighbor_column
                    )
                );
        }

        if(plane)
            neighbors.push_back(
                std::make_tuple(
                        plane - 1,
                        line,
                        column
                    )
            );
        
        return neighbors;
    }


    template<typename color_t>
    std::size_t Volume<color_t>::depth() const noexcept
    {
        return depth_;
    }


    template<typename color_t>
    Volume<std::size_t> Volume<color_t>::label_components() const noexcept
    {
        Volume<std::size_t> label_components_(depth_, height(), width(), 0);
        std::map<std::size_t, std::size_t> equivalence_map;
        std::size_t max_label(0);
        std::set<std::size_t> unique_neighbor_values;

        for(std::size_t plane(0); plane != depth_; ++plane)
        {
            for(std::size_t line(0); line != height(); ++line)
            {
                for(std::size_t column(0); column != width(); ++column)
                {
                    if(at(plane, line, width))
                    {
                        for(auto && [neighbor_plane, neighbor_line, neighbor_column] : Volume<color_t>::get_left_up_front_neightbors_indices(plane, line, column))
                        {
                            std::size_t label = label_components_.at(neighbor_line, neighbor_column, neighbor_plane);
                            if(label)
                                unique_neighbor_values.insert(label);
                        }
                        if(unique_neighbor_values.empty())
                        {
                            max_label++;
                            label_components_.at(plane, line, column) = max_label;
                        }
                        else
                        {
                            auto min_label = *std::min_element(std::begin(unique_neighbor_values), std::end(unique_neighbor_values));
                            label_components_.at(plane, line, column) = min_label;
                            for(auto && neightbor_value: unique_neighbor_values)
                            {
                                if(neightbor_value != min_label)
                                    equivalence_map.emplace(
                                        std::make_pair(neightbor_value, min_label)
                                    );
                            }
                        }
                        unique_neighbor_values.clear();
                    }
                }
            }
        }

        for(auto reverse_iter = std::rbegin(equivalence_map); reverse_iter != std::rend(equivalence_map); reverse_iter++)
        {
            auto && [label, original_label] = *reverse_iter;
            auto found_label_iter = equivalence_map.find(original_label);
            while (found_label_iter != std::end(equivalence_map))
            {
                original_label = *found_label_iter;
                found_label_iter = equivalence_map.find(original_label);
            }
        }

        for(std::size_t plane(0); plane != depth_; ++plane)
        {
            for(std::size_t line(0); line != height(); ++line)
            {
                for(std::size_t column(0); column != width(); ++column)
                {
                    auto equivalent_label_iter = equivalence_map.find(label_components_.at(plane, line, width));
                    if(equivalent_label_iter != std::end(equivalence_map))
                    {
                        label_components_.at(plane, line, width) = equivalent_label_iter->second;
                    }
                }
            }
        }
        return label_components_;
    }
}
