#include <bits/stdc++.h>
#include "headers/ArrayList.h"
#include "headers/Stack.h"
#include "headers/Deque.h"
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
    load_history();

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
        cout << "5. View Standings of Previous Season\n";
        cout << "6. Exit\n\n";

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
                    println;
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
                auto_simulate();
                save_history();

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

                if (matchday_count == 38)
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

            display_teams();

            int id;

            while (true)
            {
                cout << ln << "Enter Team ID: ";
                cout.flush();

                cin >> id;

                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
        
                    println;
                    invalid_msg;
                    continue;
                }

                if (id < 1 || id > 20)
                {
                    println;
                    invalid_msg;
                    continue;
                }
                
                break;
            }

            clear_screen;

            display_team_info(id);

            bool op_3_back = false;
            
            while (true)
            {
                cout << "\n1. Go Back to Main Menu\n2. Exit\n\nEnter: ";
                cout.flush();

                int op_3_choice;
                cin >> op_3_choice;

                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
        
                    println;
                    invalid_msg;
                    continue;
                }
                
                if (op_3_choice == 1)
                {
                    op_3_back = true;
                    break;
                }
                else if (op_3_choice == 2)
                {
                    break;
                }
                else
                {
                    println;
                    invalid_msg;
                    continue;
                }
            }

            if (op_3_back)
            {
                continue;
            }
            else
            {
                auto_simulate();
                save_history();

                clear_screen;
                exit_msg;
                return 0;
            }
            
        }
        else if (option == 4)
        {
            clear_screen;

            int undo_count;

            while (true)
            {
                cout << "Enter number of matchdays to undo (1-" << matchday_count << "): ";
                cout.flush();

                cin >> undo_count;

                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
        
                    println;
                    invalid_msg;
                    continue;
                }

                if (undo_count < 1 || undo_count > matchday_count)
                {
                    println;
                    invalid_msg;
                    continue;
                }

                break;
            }

            undo_matchdays(undo_count);

            clear_screen;
            cout << green << "Successfully undid " << undo_count << " matchday(s)!" << reset << ln; 

            bool op_4_back = false;
            
            while (true)
            {
                cout << "\n1. Go Back to Main Menu\n2. Exit\n\nEnter: ";
                cout.flush();

                int op_4_choice;
                cin >> op_4_choice;

                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
        
                    println;
                    invalid_msg;
                    continue;
                }
                
                if (op_4_choice == 1)
                {
                    op_4_back = true;
                    break;
                }
                else if (op_4_choice == 2)
                {
                    break;
                }
                else
                {
                    println;
                    invalid_msg;
                    continue;
                }
            }

            if (op_4_back)
            {
                continue;
            }
            else
            {
                auto_simulate();
                save_history();

                clear_screen;
                exit_msg;
                return 0;
            }

        }
        else if (option == 5)
        {
            clear_screen;

            display_history();

            bool op_5_back = false;
            
            while (true)
            {
                cout << "\n1. Go Back to Main Menu\n2. Exit\n\nEnter: ";
                cout.flush();

                int op_5_choice;
                cin >> op_5_choice;

                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
        
                    println;
                    invalid_msg;
                    continue;
                }
                
                if (op_5_choice == 1)
                {
                    op_5_back = true;
                    break;
                }
                else if (op_5_choice == 2)
                {
                    break;
                }
                else
                {
                    println;
                    invalid_msg;
                    continue;
                }
            }

            if (op_5_back)
            {
                continue;
            }
            else
            {
                auto_simulate();
                save_history();

                clear_screen;
                exit_msg;
                return 0;
            }

        }
        else if (option == 6)
        {
            auto_simulate();
            save_history();

            clear_screen;
            exit_msg;
            return 0;
        }
        else
        {
            continue;
        }
        
    }
    
    return 0;

}
