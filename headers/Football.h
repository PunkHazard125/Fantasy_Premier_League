#ifndef FOOTBALL_H
#define FOOTBALL_H

#include <bits/stdc++.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

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

    Team(string n, int p, int gd, int w, int d, int l) {

        name = n;

        points = p;
        wins = w;
        losses =l;
        draws = d;
        goal_difference = gd;

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
    void set_points(int num) { points = num; }
    void set_wins(int num) { wins = num; }
    void set_losses(int num) { losses = num; }
    void set_draws(int num) { draws = num; }
    void set_goals_scored(int num) { goals_scored = num; }
    void set_goals_conceded(int num) { goals_conceded = num; }
    void set_goal_difference(int num) { goal_difference = num; }

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

    void remove_win() { 
        
        if (wins > 0) 
        {
            wins--; 
            points -= 3;
        }
    
    }
    void remove_loss() { 
        
        if (losses > 0) 
        {
            losses--; 
        }
    
    }
    void remove_draw() { 
        
        if (draws > 0) {
            draws--;
            points -= 1;
        }
    
    }
    void remove_goals_scored(int num) { 
        
        goals_scored = max(0, goals_scored - num);
        goal_difference = goals_scored - goals_conceded;
    
    }
    void remove_goals_conceded(int num) { 
        
        goals_conceded = max(0, goals_conceded - num);
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

inline void to_json(json& j, const Team& t) {

    j = json {

        {"team_id", t.get_id()},
        {"name", t.get_name()},
        {"strength", t.get_strength()},
        {"points", t.get_points()},
        {"wins", t.get_wins()},
        {"losses", t.get_losses()},
        {"draws", t.get_draws()},
        {"goals_scored", t.get_goals_scored()},
        {"goals_conceded", t.get_goals_conceded()},
        {"goal_difference", t.get_goal_difference()}

    };

}

inline void from_json(const json& j, Team& t) {

    t.set_id(j.at("team_id").get<int>());
    t.set_name(j.at("name").get<string>());
    t.set_strength(j.at("strength").get<int>());
    t.set_points(j.at("points").get<int>());
    t.set_wins(j.at("wins").get<int>());
    t.set_losses(j.at("losses").get<int>());
    t.set_draws(j.at("draws").get<int>());
    t.set_goals_scored(j.at("goals_scored").get<int>());
    t.set_goals_conceded(j.at("goals_conceded").get<int>());
    t.set_goal_difference(j.at("goal_difference").get<int>());

}

#endif
