#ifndef LEAGUE_MANAGER_H
#define LEAGUE_MANAGER_H

#include <bits/stdc++.h>
#include "ArrayList.h"
#include "Stack.h"
#include "Deque.h"
#include "Football.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

const string blue = "\033[34m";
const string green = "\033[32m";
const string red = "\033[31m";
const string yellow = "\033[33m";
const string magneta = "\033[35m";
const string cyan = "\033[36m";
const string reset = "\033[0m";
const string clear = "\033[2J\033[1;1H";

#define exit_msg cout << red << "Exited!" << reset << endl
#define invalid_msg cout << red << "Invalid Choice!\n" << reset << endl
#define clear_screen cout << clear
#define ln "\n"
#define println cout << "\n"

namespace League {

    inline ArrayList<Team> teams;
    inline ArrayList<Team> standings;
    inline ArrayList<Team> history;
    inline ArrayList<Match> match_history;

    inline Deque<Match> fixtures;
    inline Stack<Match> results;

    inline int matchday_count = 0;

    inline ifstream team_file("json/teams.json");
    inline ifstream fixtures_file("json/fixtures.json");
    inline ifstream history_file_read("json/history.json");

    inline json j_teams;
    inline json j_fixtures;
    inline json j_history;
    inline json j_history_array = json::array();

    inline void load_teams() {

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
    
    inline void load_fixtures() {
    
        if (!fixtures_file.is_open()) 
        {
            throw runtime_error("Error: Could not open file fixtures.json");
        }
    
        fixtures_file >> j_fixtures;
    
        for(const auto& item : j_fixtures)
        {
            Match m(item["team_a"].get<int>(), item["team_b"].get<int>());
            fixtures.push_back(m); 
        }
    
    }

    inline void load_history() {

        if (!history_file_read.is_open())
        {
            throw runtime_error("Error: Could not open file history.json");
        }
        
        history_file_read >> j_history;

        if (j_history.empty())
        {
            throw runtime_error("Error: The file history.json is empty");
        }

        for(const auto& item : j_history)
        {
            Team t;
            from_json(item, t);
            history.push_back(t);
        }

    }

    inline void display_standings() {
    
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
            if (i < 5)
            {
                if (matchday_count == 38 && i == 0)
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
            else if (i > 16)
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

        if (matchday_count == 38)
        {
            if (standings[0].get_name() == "Manchester City")
            {
                cout << ln << yellow << "115 charges for a reason!\n" << reset; 
            }
            else if (standings[0].get_name() == "Manchester United")
            {
                cout << ln << yellow << "CR7 was never wrong!\n" << reset; 
            }
            else if (standings[0].get_name() == "Arsenal")
            {
                cout << ln << yellow << "Haram tactics finally worked!\n" << reset; 
            }
            else if (standings[0].get_name() == "Liverpool")
            {
                cout << ln << yellow << "Jurgen Klopp is punching the air right now!\n" << reset; 
            }
            else if (standings[0].get_name() == "Chelsea")
            {
                cout << ln << yellow << "Billions spent to win a trophy worth millions!\n" << reset; 
            }
            else if (standings[0].get_name() == "Tottenham Hotspur")
            {
                cout << ln << yellow << "Perhaps Harry Kane really is the cursed one!\n" << reset;
            }
        }
    
    }

    inline void display_teams() {

        cout << "=====================================\n";
        cout << blue << "         Premier League Teams         \n" << reset;
        cout << "=====================================\n";
        cout << blue << left << setw(5) << "ID"
            << setw(20) << "Name" << reset << endl;
        cout << "-------------------------------------\n";

        for (int i = 0; i < teams.get_size(); i++) 
        {
            cout << left << setw(5) << teams[i].get_id()
            << setw(20) << teams[i].get_name()
            << endl;
        }

        cout << "=====================================\n";

    }

    inline void display_team_info(int id) {

        const Team& team = teams[id - 1];

        cout << blue << left << setw(17) << "Team Name:" << reset << team.get_name() << ln << ln;

        cout << left << setw(17) << "Matches Played:"
        << (team.get_wins() + team.get_losses() + team.get_draws()) << ln << ln;
        cout << left << setw(17) << "Points:" << team.get_points() << ln;

        cout << green << left << setw(17) << "Wins:" << reset << team.get_wins() << ln;
        cout << left << setw(17) << "Draws:" << team.get_draws() << ln;
        cout << red << left << setw(17) << "Losses:" << reset << team.get_losses() << ln << ln;

        cout << left << setw(17) << "Goals Scored:" << team.get_goals_scored() << ln;
        cout << left << setw(17) << "Goals Conceded:" << team.get_goals_conceded() << ln;
        cout << left << setw(17) << "Goal Difference:" << team.get_goal_difference() << ln;

    }

    inline void simulate_match(Match& current) {
    
        int strength_a = teams[current.get_team_a() - 1].get_strength();
        int strength_b = teams[current.get_team_b() - 1].get_strength();
    
        int bias_a = rand() % ((strength_a / 2) + 2);
        int bias_b = rand() % ((strength_b / 2) + 1);
    
        int score_a = (rand() % 2) + bias_a;
        int score_b = (rand() % 2) + bias_b;
    
        score_a = min(score_a, 5);
        score_b = min(score_b, 5);
    
        current.set_score_a(score_a);
        current.set_score_b(score_b);
    
    }
    
    inline void simulate_league() {

        int day;
    
        while (true)
        {
            cout << "Enter the matchday number to simulate up to ("
            << matchday_count + 1 << "-" << 38 << "): ";
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
    
            if (day <= matchday_count || day > 38)
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
        
        for (int i = 0; i < ((day - matchday_count) * 10); i++)
        {
            Match current = fixtures.pop_front();
            simulate_match(current);
    
            results.push(current);
            match_history.push_back(current);
    
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

    inline void undo_matchdays(int undo_count) {

        for (int i = 0; i < (undo_count * 10); i++)
        {
            Match current = results.pop();
            match_history.pop_back();

            if (current.get_score_a() > current.get_score_b())
            {
                teams[current.get_team_a() - 1].remove_win();
                teams[current.get_team_b() - 1].remove_loss();
            }
            else if (current.get_score_a() < current.get_score_b())
            {
                teams[current.get_team_a() - 1].remove_loss();
                teams[current.get_team_b() - 1].remove_win();
            }
            else
            {
                teams[current.get_team_a() - 1].remove_draw();
                teams[current.get_team_b() - 1].remove_draw();
            }
            
            teams[current.get_team_a() - 1].remove_goals_scored(current.get_score_a());
            teams[current.get_team_b() - 1].remove_goals_scored(current.get_score_b());
    
            teams[current.get_team_a() - 1].remove_goals_conceded(current.get_score_b());
            teams[current.get_team_b() - 1].remove_goals_conceded(current.get_score_a());

            current.set_score_a(0);
            current.set_score_b(0);

            fixtures.push_front(current);
        }
        
        standings = teams;
        matchday_count -= undo_count; 
    }

    inline void save_history() {

        ofstream history_file_write("json/history.json");

        for (int i = 0; i < standings.get_size(); i++)
        {
            json j;
            to_json(j, standings[i]);
            j_history_array.push_back(j);
        }

        if (!history_file_write.is_open())
        {
            throw runtime_error("Error: Could not open file history.json");
        }
        
        history_file_write << setw(4) << j_history_array << endl;
        history_file_write.close();

    }

    inline void display_history() {

        cout << "======================================================\n";
        cout << blue << "      Premier League Standings | Previous Season      \n" << reset;
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
    
        for (int i = 0; i < history.get_size(); i++) 
        {
            if (i < 5)
            {
                if (i == 0)
                {
                    cout << yellow << left << setw(5) << "C" << reset
                    << setw(25) << history[i].get_name()
                    << setw(8) << history[i].get_points()
                    << setw(6) << history[i].get_goal_difference()
                    << setw(4) << history[i].get_wins()
                    << setw(4) << history[i].get_draws()
                    << setw(4) << history[i].get_losses()
                    << endl;
                }
                else
                {
                    cout << green << left << setw(5) << (i + 1) << reset
                    << setw(25) << history[i].get_name()
                    << setw(8) << history[i].get_points()
                    << setw(6) << history[i].get_goal_difference()
                    << setw(4) << history[i].get_wins()
                    << setw(4) << history[i].get_draws()
                    << setw(4) << history[i].get_losses()
                    << endl;
                }
                
            }
            else if (i > 16)
            {
                cout << red << left << setw(5)<< (i + 1) << reset
                << setw(25) << history[i].get_name()
                << setw(8) << history[i].get_points()
                << setw(6) << history[i].get_goal_difference()
                << setw(4) << history[i].get_wins()
                << setw(4) << history[i].get_draws()
                << setw(4) << history[i].get_losses()
                << endl;
            }
            else
            {
                cout << left << setw(5) << (i + 1)
                << setw(25) << history[i].get_name()
                << setw(8) << history[i].get_points()
                << setw(6) << history[i].get_goal_difference()
                << setw(4) << history[i].get_wins()
                << setw(4) << history[i].get_draws()
                << setw(4) << history[i].get_losses()
                << endl;
            }
            
        }
    
        cout << "======================================================\n";

    }

    inline void auto_simulate() {

        for (int i = 0; i < ((38 - matchday_count) * 10); i++)
        {
            Match current = fixtures.pop_front();
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
    
        matchday_count = 38;
        standings = teams;
        standings.sort(true);

    }

    inline void display_matchday(int day) {

        clear_screen;

        cout << "==========================================================\n";
        cout << blue << "                        Matchday "
        << day << "            \n" << reset;
        cout << "==========================================================\n";

        for (int i = (day - 1) * 10; i < (((day - 1) * 10) + 10); i++)
        {
            cout << right
            << setw(23) << teams[match_history[i].get_team_a() - 1].get_name()
            << setw(5) << " " << match_history[i].get_score_a() << "-"
            << match_history[i].get_score_b() << " "
            << "    " << teams[match_history[i].get_team_b() - 1].get_name()
            << reset << endl;
        }
        
        cout << "----------------------------------------------------------\n";

    }

}

#endif
