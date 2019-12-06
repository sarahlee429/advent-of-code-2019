#include <fstream>
#include <iostream>
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
    HALT = 99
} OptCode;

typedef enum
{
    POS = 0,
    IMMED = 1
} ParamCode;

int get_param_value(std::vector<int> &input, int param_mode, int index)
{
    int ret = 0;
    size_t len = input.size();

    if (param_mode == POS)
    {
        ret = input[input[index % len] % len];
    }
    else
    {
        ret = input[index % len];
    }
    return ret;
}

void process_opt_code(std::vector<int> &input)
{
    for (int i = 0; i < input.size();)
    {
        int int_code = input[i];
        int opt = int_code % 100;
        int param_arg1 = (int_code / 100) %  10;
        int param_arg2 = (int_code / 1000) %  10;

        int arg1_value = get_param_value(input, param_arg1, i + 1);
        int arg2_value = get_param_value(input, param_arg2, i + 2);
        int user_input;

        switch (opt)
        {
        case ADD:
            input[input[i + 3]] = arg1_value + arg2_value;
            i += 4;
            break;
        case MULT: // code to be executed if n = 2;
            input[input[i + 3]] = arg1_value * arg2_value;
            i += 4;
            break;
        case INPUT:
            std::cout << "Enter Input Number : ";
            std::cin >> user_input;
            input[input[i + 1]] = user_input;
            i += 2;
            break;
        case OUTPUT:
            std::cout << "Output : " << input[input[i + 1]] << std::endl;
            i += 2;
            break;
        case JUMPIFT:
            i = arg1_value != 0 ? arg2_value : i + 3;
            break;
        case JUMPIFF:
            i = arg1_value == 0 ? arg2_value : i + 3;
            break;
        case LT:
            input[input[i + 3]] = arg1_value < arg2_value;
            i += 4;
            break;
        case EQ:
            input[input[i + 3]] = arg1_value == arg2_value;
            i += 4;
            break;
        case HALT:
            return;
        default:
            std::cout << "invalid opt code : " << opt << std::endl;
            return; // code to be executed if n doesn't match any cases
        }
    }
}

int main()
{
    std::ifstream infile("input.txt");
    std::vector<int> int_codes;
    std::string line;

    while (infile >> line)
    {
        std::stringstream ss(line);
        for (int i; ss >> i;) {
            int_codes.push_back(i);
            if (ss.peek() == ',')
            {
                ss.ignore();
            }
        }
    }
    process_opt_code(int_codes);
}
