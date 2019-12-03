#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

int process_opt_code(std::vector<int> &input)
{
    for (int i = 0; i < input.size(); i+=4)
    {
        int opt = input[i];
        int param1_idx = input[i+1];
        int param2_idx = input[i+2];
        int dest_idx = input[i+3];

        if (opt == 1)
        {
            input[dest_idx] = input[param1_idx] + input[param2_idx];
        }
        else if (opt == 2)
        {
            input[dest_idx] = input[param1_idx] * input[param2_idx];
        }
        else if (opt == 99)
        {
            break;
        }
        else
        {
            std::cout << "unknown opt code" << std::endl;
        }
    }
    return input[0];
}

int main()
{
    std::ifstream infile("input.txt");

    std::vector<int> int_codes;
    std::string line;
    while (infile >> line)
    {
        std::stringstream ss(line);
        std::cout << "line : " << line << std::endl;
        for (int i; ss >> i;) {
            int_codes.push_back(i);
            std::cout << "pushing : " << i << std::endl;
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }
    }
    //int_codes[1] = 12;
    //int_codes[2] = 2;
    int final_noun = -1;
    int final_verb = -1;
    for (int noun = 0; noun <= 99; noun++)
    {
        for (int verb = 0; verb <= 99; verb++)
        {
            std::vector<int> copy_int_codes = int_codes;
            copy_int_codes[1] = noun;
            copy_int_codes[2] = verb;

            if (process_opt_code(copy_int_codes) == 19690720)
            {
                final_noun = noun;
                final_verb = verb;
                break;
            }
        }
    }

    if (final_noun != -1 && final_verb != -1)
    {
        int noun_verb_sum = 100 * final_noun + final_verb;
        std::cout << "Answer is : " << noun_verb_sum << std::endl;
    }
    else
    {
        std::cout << "No solution of noun and verb found" << std::endl;
    }
    return 0;
}

