/*
AUTHOR: mitlex
TITLE: Wave Generator
DATE: 22/10/2021
VERSION: v2
INPUT: User inputs number of waves, size of waves and whether or not they want them to increase in size.
OUTPUT: A wave pattern on the output terminal, wave size constant or increasing.

Description of key choices and assumptions in algorithm:

The waves will be formed in the terminal by a "building block": *
I think of the wave "size" as the maximum number of columns in the wave, or the amplitude of the wave. e.g. wave size = 2:

* //row size 1
** //amplitude, row size 2
* //row size 1

Each "row" of the wave has a certain number of columns, or a "size" as shown in above example.
the first and last rows of a wave always have 1 column
the number of columns increments with each row to the amplitude,
then the number of columns decrements back down to 1 in the last row.

*/

#include <iostream>
#include <time.h> //for wave delay
using namespace std;

//function provided as part of assignment
//delays terminal outputs to slow down wave
void delay()
{
    const int MILLISECONDS = 200; // time-delay in milliseconds
    clock_t goal = MILLISECONDS + clock();
    while (goal > clock());
}

//display error message
//clear terminal for input re-entry - general idea credit https://www.youtube.com/watch?v=m2P5A4nR51g
void error()
{
    cout << "Invalid input, please try again: " << endl;
    cin.clear();
    cin.ignore(256, '\n');
}

//get desired wave size or number of waves
int get_wave_params(int min_w_param)
{
    double user_input;

    while (!(cin >> user_input) || user_input < min_w_param)
    {
        error();
    }

    user_input = int(user_input); //cast w_size as integer
    return user_input;
}

//ask user for const or increasing waves
bool increase_or_not()
{
    cout << endl << "If you would like the waves to stay the same size, type 0 on your keyboard and press enter." << endl;
    cout << "If you want your waves to sequentially increase in size, enter any number other than 0 (e.g. 1): " << endl;

    bool wave_increase;
    int user_input;

    while (!(cin >> user_input)) //some input protection against non-integer inputs
    {
        error();
    }

    if (user_input == 0)
    {
        wave_increase = false; //constant waves
    }
    else
    {
        wave_increase = true; //increasing size waves
    }

    return wave_increase;
}

//prints the waves
void print_waves(char bb, double num_w, double w_size, bool increase)
{
    for (int i = 0; i < num_w; i++) //repeat waves
    {

        int current_row_size = 1; //every wave starts with 1 *

        //print lowest to highest point
        for (; current_row_size <= w_size; current_row_size++) //print rows
        {
            for (int j = 0; j < current_row_size; j++) //print columns
            {
                cout << '*';
            }
            cout << endl;
            delay(); //delay each row
        }

        current_row_size--; //prevent repitition of amplitude output

        //print (highest point - 1) to lowest point
        for (; current_row_size > 1; current_row_size--) //print rows
        {
            for (int j = 0; j < current_row_size - 1; j++) //print columns
            {
                cout << '*';
            }
            cout << endl;
            delay();
        }

        if (increase == true) //if user requested increasing waves
        {
            w_size++; //make next wave one size bigger
        }
    }
}

int main()
{
    //variable declerations
    char build_block = '*'; //forms the wave
    int wave_size, num_waves;
    int min_wave_size = 2, min_num_waves = 1;
    bool increase_wave_size;

    //welcome message
    cout << "Welcome to the wave generator!\n" << endl;
    cout << "Here is an example wave, with the minimum allowable wave size, which is 2:\n" << endl;
    print_waves('*', 1, 2, false);

    //get wave size
    cout << endl << "What would you like the size of your first wave to be? Type a whole number >= 2 (integer) and press enter. ";
    cout << endl << "Note: if you enter a number like 4.7, it will be rounded down to 4 waves." << endl;
    wave_size = get_wave_params(min_wave_size);

    //get number of waves
    cout << endl << "How many waves would you like to output? Type a whole number >= 1 (integer) and press enter: " << endl;
    num_waves = get_wave_params(min_num_waves);

    //determine if constant or increasing waves
    increase_wave_size = increase_or_not();

    cout << endl << "Here come the waves!\n" << endl;

    //print constant or increasing waves
    if (increase_wave_size == true)
    {
        print_waves(build_block, num_waves, wave_size, true);
    }
    else {
        print_waves(build_block, num_waves, wave_size, false);
    }

    return 0;
}

