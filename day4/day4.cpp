#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int char_to_int(char c)
{
    return c - '0';
}

std::vector<int> get_digit_vec(std::string num_str)
{
    std::vector<int> digit_vec;
    for (int digits = 0; digits < num_str.size(); ++digits)
    {
        digit_vec.push_back(char_to_int(num_str.at(digits)));
    }
    return digit_vec;
}

bool adjacency_found(std::vector<int> digits)
{
    bool found = false;
    int i = 0;
    while (i < digits.size())
    {
        int seq = 0;
        for (int j = i; j < digits.size(); ++j)
        {
            if (digits[j] == digits[i])
            {
                seq++;
            }
        }
        i += seq;
        if (seq == 2)
        {
            found = true;
            break;
        }
    }
    return found;
}

bool is_valid_password(std::string num_str)
{
    if (num_str.size() != 6)
    {
        return false;
    }

    std::vector<int> digit_vec = get_digit_vec(num_str);

    if (!adjacency_found(digit_vec))
    {
        return false;
    }

    bool valid_password = true;

    for (int i = 1; i < digit_vec.size(); ++i)
    {
        if (digit_vec[i] < digit_vec[i-1])
        {
            valid_password = false;
            break;
        }
    }
    return valid_password;
}

int main(int argc, char** argv)
{
    int start = std::stoi(argv[1]);
    int end = std::stoi(argv[2]);
    int valid_counter = 0;
    for (int p = start; p <= end; ++p)
    {
        std::string num_str = std::to_string(p);
        if (is_valid_password(num_str))
        {
            valid_counter++;
            std::cout << "Found valid password : " << num_str << std::endl;
        }
    }
    std::cout << "Number of valid password : " << valid_counter << "\n";
    return 0;
}
