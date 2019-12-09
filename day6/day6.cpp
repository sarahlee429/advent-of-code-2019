#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <set>
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

static std::vector<int> phase_codes_pt1 = {0, 1, 2, 3, 4};
static std::vector<int> phase_codes_pt2 = {5, 6, 7, 8, 9};
static std::vector<int> int_codes_a = {};
static std::vector<int> int_codes_b = {};
static std::vector<int> int_codes_c = {};
static std::vector<int> int_codes_d = {};
static std::vector<int> int_codes_e = {};
static int a_curr = 0;
static int b_curr = 0;
static int c_curr = 0;
static int d_curr = 0;
static int e_curr = 0;

std::vector<std::vector<int> > generate_phase_settings(std::vector<int> phase_codes)
{
    std::vector<std::vector<int> > combs;
    do {
        std::vector<int> tmp_code = phase_codes;
        combs.push_back(tmp_code);
    } while (std::next_permutation(phase_codes.begin(), phase_codes.end()));
    return combs;
}

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

void get_output(std::vector<int> &input, int &program_step, std::vector<int> &input_values, bool &has_halt,  std::vector<int> &output_values)
{
    bool stop = false;
    while (!stop)
    {
        int int_code = input[program_step];
        int opt = int_code % 100;
        int param_arg1 = (int_code / 100) %  10;
        int param_arg2 = (int_code / 1000) %  10;

        int arg1_value = get_param_value(input, param_arg1, program_step + 1);
        int arg2_value = get_param_value(input, param_arg2, program_step + 2);

        switch (opt)
        {
        case ADD:
            input[input[program_step + 3]] = arg1_value + arg2_value;
            program_step += 4;
            break;
        case MULT: // code to be executed if n = 2;
            input[input[program_step + 3]] = arg1_value * arg2_value;
            program_step += 4;
            break;
        case INPUT:
            //std::cout << "Enter Input Number : ";
            //std::cin >> user_input;
            if (input_values.size() == 0)
            {
                stop = true;
                break;
            }
            input[input[program_step + 1]] = input_values[0];
            input_values.erase(input_values.begin());
            program_step += 2;
            break;
        case OUTPUT:
            std::cout << "Output : " << input[input[program_step + 1]] << std::endl;
            output_values.push_back(input[input[program_step + 1]]);
            stop = true;
            program_step += 2;
            return;
        case JUMPIFT:
            program_step = arg1_value != 0 ? arg2_value : program_step + 3;
            break;
        case JUMPIFF:
            program_step = arg1_value == 0 ? arg2_value : program_step + 3;
            break;
        case LT:
            input[input[program_step + 3]] = arg1_value < arg2_value;
            program_step += 4;
            break;
        case EQ:
            input[input[program_step + 3]] = arg1_value == arg2_value;
            program_step += 4;
            break;
        case HALT:
            stop = true;
            has_halt = true;
            break;
        default:
            std::cout << "invalid opt code : " << opt << std::endl;
            stop = true;
            break;// code to be executed if n doesn't match any cases
        }
    }
}

int get_thrust_value(std::vector<int> phase_settings)
{
    bool has_halt = false;
    std::vector<int> e_to_a;
    e_to_a.push_back(phase_settings[0]);
    e_to_a.push_back(0);

    std::vector<int> a_to_b;
    a_to_b.push_back(phase_settings[1]);

    std::vector<int> b_to_c;
    b_to_c.push_back(phase_settings[2]);

    std::vector<int> c_to_d;
    c_to_d.push_back(phase_settings[3]);

    std::vector<int> d_to_e;
    d_to_e.push_back(phase_settings[4]);

    while (true)
    {
        get_output(int_codes_a, a_curr, e_to_a, has_halt, a_to_b);
        get_output(int_codes_b, b_curr, a_to_b, has_halt, b_to_c);
        get_output(int_codes_c, c_curr, b_to_c, has_halt, c_to_d);
        get_output(int_codes_d, d_curr, c_to_d, has_halt, d_to_e);
        get_output(int_codes_e, e_curr, d_to_e, has_halt, e_to_a);
        if (has_halt) break;
    }
    return e_to_a.back();
}

int main()
{
    std::ifstream infile("input.txt");
    std::string line;
    std::vector<int> int_codes;
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

    std::vector<std::vector<int> > combs_pt2 = generate_phase_settings(phase_codes_pt2);
    int max = INT_MIN;
    int count = 0;
    for (auto it = combs_pt2.begin(); it != combs_pt2.end(); ++it)
    {
        //need to reset for each run
        int_codes_a = int_codes;
        int_codes_b = int_codes;
        int_codes_c = int_codes;
        int_codes_d = int_codes;
        int_codes_e = int_codes;

        a_curr = 0;
        b_curr = 0;
        c_curr = 0;
        d_curr = 0;
        e_curr = 0;

        int tmp = get_thrust_value(*it);
        if (tmp > max)
        {
            max = tmp;
        }
        count++;
    }

    std::cout << "MAX VALUE OF THRUST OUTPUT IS : " << max << std::endl;
    //process_opt_code(int_codes);
}
