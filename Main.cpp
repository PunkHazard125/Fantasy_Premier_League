#include <bits/stdc++.h>
#include <iomanip>
#include "headers/ArrayList.h"
#include "headers/Stack.h"
#include "headers/Queue.h"
#include "headers/Football.h"
#include "headers/json.hpp"

using namespace std;
using json = nlohmann::json;

typedef long long ll;

#define ln "\n"
#define PRINT_RESULT cout << "Result: "
#define FIXED(x) cout << fixed << setprecision(x)

const int64_t LIMIT = 1e6;
const string blue = "\033[34m";
const string green = "\033[32m";
const string red = "\033[31m";
const string yellow = "\033[33m";
const string reset = "\033[0m";
const string clear = "\033[2J\033[1;1H";

#define exit_msg cout << red << "Exited!" << reset << endl
#define invalid_msg cout << red << "Invalid Choice!\n" << reset << endl
#define clear_screen cout << clear

ifstream team_file("json/teams.json");
ifstream fixtures_file("json/fixtures.json");
json j_teams;
json j_fixtures;

ArrayList<Team> teams;
ArrayList<Team> standings;
Queue<Match> fixtures;
Stack<Match> results;

int matchday_count = 0;

void load_teams() {

    if (!team_file.is_open()) 
    {
        throw runtime_error("Error: Could not open file teams.json");
    }

    team_file >> j_teams;

    for(const auto& item : j_teams)
    {
        Team t(item["name"], item["team_id"], item["strength"]);
        teams.push_back(t); 
    }

    standings = teams;

}

void load_fixtures() {

    if (!fixtures_file.is_open()) 
    {
        throw runtime_error("Error: Could not open file fixtures.json");
    }

    fixtures_file >> j_fixtures;

    for(const auto& item : j_fixtures)
    {
        Match m(item["team_a"], item["team_b"]);
        fixtures.enqueue(m); 
    }

}

void display_standings() {

    cout << "======================================================\n";
    cout << blue << "        Premier League Standings | Matchday " << matchday_count << "         \n" << reset;
    cout << "======================================================\n";
    cout << blue << left << setw(5) << "Rank"
        << setw(25) << "Team"
        << setw(8) << "Points"
        << setw(6) << "GD"
        << green
        << setw(4) << "W" << reset
        << setw(4) << "D"
        << red
        << setw(4) << "L" << reset
        << endl;
    cout << "------------------------------------------------------\n";

    for (int i = 0; i < standings.get_size(); i++) 
    {
        if (i < 3)
        {
            if (matchday_count == 18 && i == 0)
            {
                cout << yellow << left << setw(5) << "C" << reset
                << setw(25) << standings[i].get_name()
                << setw(8) << standings[i].get_points()
                << setw(6) << standings[i].get_goal_difference()
                << setw(4) << standings[i].get_wins()
                << setw(4) << standings[i].get_draws()
                << setw(4) << standings[i].get_losses()
                << endl;
            }
            else
            {
                cout << green << left << setw(5) << (i + 1) << reset
                << setw(25) << standings[i].get_name()
                << setw(8) << standings[i].get_points()
                << setw(6) << standings[i].get_goal_difference()
                << setw(4) << standings[i].get_wins()
                << setw(4) << standings[i].get_draws()
                << setw(4) << standings[i].get_losses()
                << endl;
            }
            
        }
        else if (i > 7)
        {
            cout << red << left << setw(5)<< (i + 1) << reset
            << setw(25) << standings[i].get_name()
            << setw(8) << standings[i].get_points()
            << setw(6) << standings[i].get_goal_difference()
            << setw(4) << standings[i].get_wins()
            << setw(4) << standings[i].get_draws()
            << setw(4) << standings[i].get_losses()
            << endl;
        }
        else
        {
            cout << left << setw(5) << (i + 1)
            << setw(25) << standings[i].get_name()
            << setw(8) << standings[i].get_points()
            << setw(6) << standings[i].get_goal_difference()
            << setw(4) << standings[i].get_wins()
            << setw(4) << standings[i].get_draws()
            << setw(4) << standings[i].get_losses()
            << endl;
        }
        
    }

    cout << "======================================================\n";

}

void simulate_match(Match& current) {

    int strength_a = teams[current.get_team_a() - 1].get_strength();
    int strength_b = teams[current.get_team_b() - 1].get_strength();

    int bias_a = rand() % (strength_a + 1);
    int bias_b = rand() % (strength_b + 1);

    int score_a = (rand() % 3) + bias_a;
    int score_b = (rand() % 3) + bias_b;

    score_a = min(score_a, 8);
    score_b = min(score_b, 8);

    current.set_score_a(score_a);
    current.set_score_b(score_b);

}

void simulate_league() {

    int day;

    while (true)
    {
        cout << "Enter the matchday number to simulate up to ("
        << matchday_count + 1 << "-" << 18 << "): ";
        cout.flush();

        cin >> day;

        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(1000, '\n');

            clear_screen;
            invalid_msg;
            continue;
        }

        if (day <= matchday_count || day > 18)
        {
            clear_screen;
            invalid_msg;
            continue;
        }
        else
        {
            break;
        }
    }
    
    for (int i = 0; i < ((day - matchday_count) * 5); i++)
    {
        Match current = fixtures.dequeue();
        simulate_match(current);

        results.push(current);

        if (current.get_score_a() > current.get_score_b())
        {
            teams[current.get_team_a() - 1].add_win();
            teams[current.get_team_b() - 1].add_loss();
        }
        else if (current.get_score_a() < current.get_score_b())
        {
            teams[current.get_team_a() - 1].add_loss();
            teams[current.get_team_b() - 1].add_win();
        }
        else
        {
            teams[current.get_team_a() - 1].add_draw();
            teams[current.get_team_b() - 1].add_draw();
        }
        
        teams[current.get_team_a() - 1].add_goals_scored(current.get_score_a());
        teams[current.get_team_b() - 1].add_goals_scored(current.get_score_b());

        teams[current.get_team_a() - 1].add_goals_conceded(current.get_score_b());
        teams[current.get_team_b() - 1].add_goals_conceded(current.get_score_a());
    }

    standings = teams;
    matchday_count = day;

}


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
