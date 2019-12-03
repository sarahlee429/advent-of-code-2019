#include <cmath>
#include <fstream>
#include <iostream>

int64_t get_fuel(uint64_t fuel)
{
    int64_t sum_fuel = 0;
    while (true)
    {
        int64_t tmp_fuel = std::floor(fuel / 3) - 2;
        if (tmp_fuel <= 0)
        {
            break;
        }
        else
        {
            sum_fuel += tmp_fuel;
            fuel = tmp_fuel;
        }
    }

    return sum_fuel;
}

int main()
{
    std::ifstream infile("input.txt");
    int64_t input_mass;
    int64_t fuel_sum = 0;
    while (infile >> input_mass)
    {
        fuel_sum += get_fuel(input_mass);
    }
    std::cout << "Final Fuel Mass : " << fuel_sum << std::endl;
}

