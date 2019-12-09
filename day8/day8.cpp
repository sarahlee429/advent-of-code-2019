#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

int char_to_int(char c)
{
    return c - '0';
}

int main()
{
    size_t col = 25;
    size_t row = 6;
    size_t pixels_per_layer = row * col;

    std::ifstream infile("input.txt");
    std::string line;
    std::vector<std::vector<int> > layers;
    std::vector<int> layer;
    std::vector<int> least_zeros;
    int min_zero_count = INT_MAX;

    while (infile >> line)
    {
        for (size_t i = 0; i < line.size(); ++i)
        {
            layer.push_back(char_to_int(line[i]));
            if (layer.size() == pixels_per_layer)
            {
                int count = std::count(layer.begin(), layer.end(), 0);
                if (count < min_zero_count)
                {
                    min_zero_count = count;
                    least_zeros = layer;
                }
                layers.push_back(layer);
                layer.clear();
            }
        }
    }
    int one_count = std::count(least_zeros.begin(), least_zeros.end(), 1);
    int two_count = std::count(least_zeros.begin(), least_zeros.end(), 2);
    std::cout << "Part One : " << one_count * two_count << std::endl;
    std::cout << "Part Two : " << std::endl;

    //25 by 6 vector
    std::vector<int> visible_layer;
    for (int i = 0; i < pixels_per_layer; i++)
    {
        int pixel_value = 1;
        for (auto it = layers.begin(); it != layers.end(); ++it)
        {
            pixel_value = it->at(i);
            if (pixel_value != 2)
            {
                break;
            }
        }
        visible_layer.push_back(pixel_value);
    }

    for (size_t r = 0; r < row; ++r)
    {
        std::string row_buff;
        for (size_t c = 0; c < col; c++)
        {
            if (visible_layer[(r * col) + c] == 0)
            {
                row_buff.append(" ");
            }
            else
            {
                row_buff.append("x");
            }
        }
        std::cout << row_buff << "\n";
    }
    return 0;
}
