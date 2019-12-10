#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>

typedef enum
{
    ADD = 1,
    MULT = 2,
    INPUT = 3,
    OUTPUT = 4,
    JUMPIFT = 5,
    JUMPIFF = 6,
    LT = 7,
    EQ = 8,
    BASE = 9,
    HALT = 99
} OptCode;

typedef enum
{
    POS = 0,
    IMMED = 1,
    REL = 2
} ParamCode;

static long long r_base = 0;
static std::map<long long, long long> extended;

long long get(std::vector<long long> &input, long long index)
{
    long long ret = 0;
    if (index >= input.size())
    {
        if (extended.find(index) != extended.end())
        {
            ret = extended[index];
        }
    }
    else
    {
        ret = input[index];
    }
    return ret;
}

void set(std::vector<long long> &input, long long index, long long value)
{
    if (index >= input.size())
    {
        extended[index] = value;
    }
    else
    {
        input[index] = value;
    }
}

long long get_param_value(std::vector<long long> &input, int param_mode, long long index)
{
    long long ret = 0;
    size_t len = input.size();

    if (param_mode == POS)
    {
        ret = get(input, get(input, index));
    }
    else if (param_mode == IMMED)
    {
        ret = get(input, index);
    }
    else
    {
        long long offset_idx = (get(input, index) + r_base);
        ret = get(input, offset_idx);
    }
    return ret;
}

void process_opt_code(std::vector<long long> &input)
{
    long long i = 0;
    size_t len = input.size();
    while (true)
    {
        long long int_code = input[i];
        int opt = int_code % 100;
        int param_arg1 = (int_code / 100) %  10;
        int param_arg2 = (int_code / 1000) %  10;
        int param_arg3 = (int_code / 10000) %  10;

        long long arg1_value = get_param_value(input, param_arg1, i + 1);
        long long arg2_value = get_param_value(input, param_arg2, i + 2);

        long long user_input;
        long long write_idx;

        switch (opt)
        {
        case ADD:
            write_idx = (param_arg3 == REL) ? get(input, i + 3) + r_base : get(input, i + 3);
            set(input, write_idx, arg1_value + arg2_value);
            i += 4;
            break;
        case MULT: // code to be executed if n = 2;
            write_idx = (param_arg3 == REL) ? get(input, i + 3) + r_base : get(input, i + 3);
            set(input, write_idx, arg1_value * arg2_value);
            i += 4;
            break;
        case INPUT:
            std::cout << "Enter Input Number : ";
            std::cin >> user_input;
            write_idx = (param_arg1 == REL) ? get(input, i + 1) + r_base : get(input, i + 1);
            set(input, write_idx, user_input);
            i += 2;
            break;
        case OUTPUT:
            std::cout << "Output : " << arg1_value << std::endl;
            i += 2;
            break;
        case JUMPIFT:
            i = arg1_value != 0 ? arg2_value : i + 3;
            break;
        case JUMPIFF:
            i = arg1_value == 0 ? arg2_value : i + 3;
            break;
        case LT:
            write_idx = (param_arg3 == REL) ? get(input, i + 3) + r_base : get(input, i + 3);
            set(input, write_idx, arg1_value < arg2_value);
            i += 4;
            break;
        case EQ:
            write_idx = (param_arg3 == REL) ? get(input, i + 3) + r_base : get(input, i + 3);
            set(input, write_idx, arg1_value == arg2_value);
            i += 4;
            break;
        case HALT:
            return;
        case BASE:
            r_base += arg1_value;
            i += 2;
            break;
        default:
            std::cout << "invalid opt code : " << opt << std::endl;
            return; // code to be executed if n doesn't match any cases
        }
    }
}

int main()
{
    std::ifstream infile("input.txt");
    std::vector<long long> int_codes;
    std::string line;

    while (infile >> line)
    {
        std::stringstream ss(line);
        for (long long i; ss >> i;) {
            int_codes.push_back(i);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }
    }
    process_opt_code(int_codes);
}
