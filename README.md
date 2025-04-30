# **Fantasy Premier League**
## **Project Concept**

### Primary Idea:
A Football League Simulation System that simulates the English Premier League (EPL) with match days and team standings. It is called Fantasy Premier League because all the matches are simulated with randomized results, meaning the results are not connected to real life. It is also completely unrelated to the official Fantasy Premier League (FPL).

### Key Classes:
- **Team**: Represents a football team with relevant attributes.
- **Match**: Represents a match between two teams with scores.

### Data Structures:
- **Dynamic Array/ArrayList**: Used for storing teams in the league.
- **Stack**: Used for storing match results.
- **Deque**: Used for storing the upcoming fixtures (matches).

### Main Structure:
- **Array/ArrayList of Teams**: Holds all the teams participating in the league.
- **Deque of Matches (Fixtures)**: Contains the upcoming matches for the league.
- **Stack of Results**: Stores the results of completed matches.

### Functionalities:
- Simulate the league based on a user-defined number of matchdays.
- View individual team details.
- Undo matchdays
- Display the standings of teams in the league after the specified number of matchdays.
- View standings of the previous season after 38 matchdays by default

### Additional Information:
- The league will consist of 20 teams from the 23/24 English Premier League season.
- Each team will play every other team twice (home and away).
- Team strengths will be factored into the simulation, giving stronger teams a higher chance of winning but allowing for upsets.
- Comparator operators will be overloaded to sort teams based on points and goal differences.
- JSON will be used to store and retrieve team information, fixtures and history of the previous season.
