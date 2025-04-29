#include <bits/stdc++.h>
#include "headers/ArrayList.h"
#include "headers/Stack.h"
#include "headers/Queue.h"
#include "headers/Football.h"
#include "headers/LeagueUtils.h"
#include "headers/json.hpp"

using namespace std;
using json = nlohmann::json;
using namespace League;


int main(void) {

    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(0));

    load_teams();
    load_fixtures();

    while (true)
    {
        cout << clear;
        cout << blue;
    
        cout << setw(52) << right << "//////// Welcome to Fantasy Premier League \\\\\\\\\\\\\\\\" << ln << ln;
    
        cout << reset;

        cout << "1. View Current Standings\n";
        cout << "2. Simulate the League\n";
        cout << "3. View Team Information\n";
        cout << "4. Undo Matchday(s)\n";
        cout << "5. Exit\n\n";

        cout << "Select an option from above: ";
        cout.flush();

        int option;
        cin >> option;

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(1000, '\n');

            clear_screen;
            invalid_msg;
            continue;
        }

        if (option == 1)
        {
            clear_screen;

            standings.sort(true);
            display_standings();

            bool op_1_back = false;
            
            while (true)
            {
                cout << "\n1. Go Back to Main Menu\n2. Exit\n\nEnter: ";
                cout.flush();

                int op_1_choice;
                cin >> op_1_choice;

                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
        
                    clear_screen;
                    invalid_msg;
                    continue;
                }
                
                if (op_1_choice == 1)
                {
                    op_1_back = true;
                    break;
                }
                else if (op_1_choice == 2)
                {
                    break;
                }
                else
                {
                    cout << ln;
                    invalid_msg;
                    continue;
                }
            }

            if (op_1_back)
            {
                continue;
            }
            else
            {
                clear_screen;
                exit_msg;
                return 0;
            }
        }
        else if (option == 2)
        {
            bool op_2_back = false;
            int op_2_choice;

            while (true)
            {
                clear_screen;

                if (matchday_count == 18)
                {
                    cout << red <<"Season is over! Cannot simulate\n" << reset;

                    while (true)
                    {
                        cout << "\n1. Go Back to Main Menu\n2. Simulate Again\n\nEnter: ";
                        cout.flush();

                        cin >> op_2_choice;

                        if (cin.fail()) 
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                
                            clear_screen;
                            invalid_msg;
                            continue;
                        }
                        
                        if (op_2_choice == 1)
                        {
                            op_2_back = true;
                            break;
                        }
                        else if (op_2_choice == 2)
                        {
                            break;
                        }
                        else
                        {
                            clear_screen;
                            invalid_msg;
                            continue;
                        }
                    }
                    
                    if (op_2_back)
                    {
                        break;
                    }
                    
                    if (op_2_choice == 2)
                    {
                        continue;
                    }
                }
                
                simulate_league();

                clear_screen;

                cout << green << "Simulation Successful!\n" << reset;
                
                while (true)
                {
                    cout << "\n1. Go Back to Main Menu\n2. Simulate Again\n\nEnter: ";
                    cout.flush();

                    cin >> op_2_choice;

                    if (cin.fail()) 
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
            
                        clear_screen;
                        invalid_msg;
                        continue;
                    }
                    
                    if (op_2_choice == 1)
                    {
                        op_2_back = true;
                        break;
                    }
                    else if (op_2_choice == 2)
                    {
                        break;
                    }
                    else
                    {
                        clear_screen;
                        invalid_msg;
                        continue;
                    }
                }

                if (op_2_back)
                {
                    break;
                }
                else
                {
                    clear_screen;
                    continue;
                }
            }

            if (op_2_back)
            {
                continue;
            }
            else
            {
                break;
            }
            
        }
        else if (option == 3)
        {
            clear_screen;
        }
        else if (option == 4)
        {
            clear_screen;
        }
        else if (option == 5)
        {
            clear_screen;
            exit_msg;
            return 0;
        }
        else
        {
            continue;
        }
        
    }

    clear_screen;
    exit_msg;

    return 0;

}
