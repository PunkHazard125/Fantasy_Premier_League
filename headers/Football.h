#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define ln "\n"
#define PRINT_RESULT cout << "Result: "
#define FIXED(x) cout << fixed << setprecision(x)

class Team {

private:

    string name;
    int team_id;
    int strength;

    int points;
    int wins;
    int losses;
    int draws;
    int goals_scored;
    int goals_conceded;
    int goal_difference;

public:

    Team() {

        name = "Unknown";
        team_id = 0;
        strength = 0;

        points = 0;
        wins = 0;
        losses = 0;
        draws = 0;
        goals_scored = 0;
        goals_conceded = 0;
        goal_difference = 0;

    }

    Team(string str, int num1, int num2) {

        name = str;
        team_id = num1;
        strength = num2;

        points = 0;
        wins = 0;
        losses = 0;
        draws = 0;
        goals_scored = 0;
        goals_conceded = 0;
        goal_difference = 0;

    }

    Team(const Team& other) {

        name = other.name;
        team_id = other.team_id;
        strength = other.strength;

        points = other.points;
        wins = other.wins;
        losses = other.losses;
        draws = other.draws;
        goals_scored = other.goals_scored;
        goals_conceded = other.goals_conceded;
        goal_difference = other.goal_difference;

    }

    string get_name() const { return name; }
    int get_id() const { return team_id; }
    int get_strength() const { return strength; }
    int get_points() const { return points; }
    int get_wins() const { return wins; }
    int get_losses() const { return losses; }
    int get_draws() const { return draws; }
    int get_goals_scored() const { return goals_scored; }
    int get_goals_conceded() const { return goals_conceded; }
    int get_goal_difference() const { return goal_difference; }

    void set_name(string str) { name = str; }
    void set_id(int num) { team_id = num; }
    void set_strength(int num) { strength = num; }
    void add_win() { 
        
        wins++; 
        points += 3;
    
    }
    void add_loss() { losses++; }
    void add_draw() { 
        
        draws++;
        points += 1;
    
    }
    void add_goals_scored(int num) { 
        
        goals_scored += num;
        goal_difference = goals_scored - goals_conceded;
    
    }
    void add_goals_conceded(int num) { 
        
        goals_conceded += num; 
        goal_difference = goals_scored - goals_conceded;
    
    }

    Team& operator=(const Team& other) {

        if (this == &other) 
        {
            return *this;
        }
    
        name = other.name;
        team_id = other.team_id;
        strength = other.strength;

        points = other.points;
        wins = other.wins;
        losses = other.losses;
        draws = other.draws;
        goals_scored = other.goals_scored;
        goals_conceded = other.goals_conceded;
        goal_difference = other.goal_difference;
    
        return *this;
    }
    bool operator==(const Team& other) const {

        return (name == other.name);
        
    }
    bool operator>(const Team& other) const {

        if (points != other.points)
        {
            return points > other.points;
        }
        else if (goal_difference != other.goal_difference)
        {
            return goal_difference > other.goal_difference;
        }
        else
        {
            return goals_scored > other.goals_scored;
        }
        
    }
    bool operator<(const Team& other) const {

        if (points != other.points)
        {
            return points < other.points;
        }
        else if (goal_difference != other.goal_difference)
        {
            return goal_difference < other.goal_difference;
        }
        else
        {
            return goals_scored < other.goals_scored;
        }
        
    }

    bool operator<=(const Team& other) const {

        return !(*this > other);

    }
    
    bool operator>=(const Team& other) const {

        return !(*this < other);
        
    }

};

class Match {

private:

    int team_a;
    int team_b;
    int score_a;
    int score_b;

public:

    Match() {

        team_a = 0;
        team_b = 0;
        score_a = 0;
        score_b = 0;

    }

    Match(int a, int b) {

        team_a = a;
        team_b = b;
        score_a = 0;
        score_b = 0;

    }

    Match(const Team& a, const Team& b) {

        team_a = a.get_id();
        team_b = b.get_id();
        score_a = 0;
        score_b = 0;

    }

    Match operator=(const Match& other) {

        if (this == &other) 
        {
            return *this;
        }
    
        team_a = other.team_a;
        team_b = other.team_b;
        score_a = other.score_a;
        score_b = other.score_b;
    
        return *this;
    }

    int get_team_a() const { return team_a; }
    int get_team_b() const { return team_b; }
    int get_score_a() const { return score_a; }
    int get_score_b() const { return score_b; }

    void set_team_a(int num) { team_a = num; }
    void set_team_b(int num) { team_b = num; }
    void set_score_a(int num) { score_a = num; }
    void set_score_b(int num) { score_b = num; }

};

#endif
