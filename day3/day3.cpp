#include <algorithm>    // std::set_intersection, std::sort
#include <climits>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <istream>
#include <string>

typedef std::pair<int, int> coord_t;

void add_all_range_coordinates(std::vector<coord_t> &points, int x_start, int x_end, int y_start, int y_end)
{
    for (int x = x_start; x <= x_end; x++)
    {
        for (int y = y_start; y <= y_end; y++)
        {
            points.push_back(coord_t (x, y));
        }
    }
}

std::vector<coord_t> get_global_points(std::vector<std::string> &wire)
{
    std::vector<coord_t> global_points;

    int curr_x = 0;
    int curr_y = 0;
    for (std::vector<std::string>::iterator it = wire.begin(); it != wire.end(); ++it)
    {
        std::string tmp_point = *it;
        std::string tmp_dir = tmp_point.substr(0, 1);
        int tmp_mag = atoi(tmp_point.substr(1).c_str());

        if (tmp_dir == "R")
        {
            add_all_range_coordinates(global_points, curr_x, curr_x + tmp_mag, curr_y, curr_y);
            curr_x += tmp_mag;
        }
        else if (tmp_dir == "L")
        {
            add_all_range_coordinates(global_points, curr_x - tmp_mag, curr_x, curr_y, curr_y);
            curr_x -= tmp_mag;
        }
        else if (tmp_dir == "U")
        {
            add_all_range_coordinates(global_points, curr_x, curr_x, curr_y, curr_y - tmp_mag);
            curr_y += tmp_mag;
        }
        else if (tmp_dir == "D")
        {
            add_all_range_coordinates(global_points, curr_x, curr_x, curr_y - tmp_mag, curr_y);
            curr_y -= tmp_mag;
        }
    }
    return global_points;
}

int get_steps(std::vector<std::string> &wire, coord_t intersect_point)
{
    int steps = 0;
    int curr_x = 0;
    int curr_y = 0;
    for (std::vector<std::string>::iterator it = wire.begin(); it != wire.end(); ++it)
    {
        std::string tmp_point = *it;
        std::string tmp_dir = tmp_point.substr(0, 1);
        int tmp_mag = atoi(tmp_point.substr(1).c_str());

        if (tmp_dir == "R")
        {
            for (int i = 1; i <= tmp_mag; i++)
            {
                steps++;
                if (curr_x + i == intersect_point.first && curr_y == intersect_point.second)
                {
                    return steps;
                }
            }
            curr_x += tmp_mag;
        }
        else if (tmp_dir == "L")
        {
            for (int i = 1; i <= tmp_mag; i++)
            {
                steps++;
                if (curr_x - i == intersect_point.first && curr_y == intersect_point.second)
                {
                    return steps;
                }
            }
            curr_x -= tmp_mag;
        }
        else if (tmp_dir == "U")
        {
            for (int i = 1; i <= tmp_mag; i++)
            {
                steps++;
                if (curr_x == intersect_point.first && curr_y + i == intersect_point.second)
                {
                    curr_y += tmp_mag;
                    return steps;
                }
            }
            curr_y += tmp_mag;
        }
        else if (tmp_dir == "D")
        {
            for (int i = 1; i <= tmp_mag; i++)
            {
                steps++;
                if (curr_x == intersect_point.first && curr_y - i == intersect_point.second)
                {
                    curr_y -= tmp_mag;
                    return steps;
                }
            }
            curr_y -= tmp_mag;
        }
    }
    return steps;
}
std::vector<std::string> split_string(const std::string &s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

std::vector<coord_t> get_intersection_coords(std::vector<coord_t> v1, std::vector<coord_t> v2)
{

    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());

    std::vector<coord_t> intersect;

    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                  std::inserter(intersect,intersect.begin()));
    return intersect;
}

int main()
{
    std::ifstream infile("input.txt");

    std::vector<std::string> wire1;
    std::vector<std::string> wire2;

    std::string line;
    int wire_idx = 0;
    while (infile >> line)
    {
        const std::string tmp = line;
        if (wire_idx == 0)
        {
            wire1 = split_string(tmp, ',');
        }
        else if (wire_idx == 1)
        {
            wire2 = split_string(tmp, ',');
        }
        wire_idx ++;
    }

    int min_steps = INT_MAX;

    std::vector<coord_t> intersect = get_intersection_coords(get_global_points(wire1), get_global_points(wire2));
    for (std::vector<coord_t>::iterator it = intersect.begin(); it != intersect.end(); ++it)
    {
        int steps = get_steps(wire1, *it) + get_steps(wire2, *it);
        if (steps < min_steps)
        {
            min_steps = steps;
        }
    }
    std::cout << "Min steps: " << min_steps << std::endl;
    return 0;
}

