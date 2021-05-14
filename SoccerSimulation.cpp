#include <iostream>
#include <ctime>
using namespace std;

void start_soccer_simulation();
// PURPOSE: Runs the steps of the specified program

void generate_number_of_events(int& event_number);
// PURPOSE: Generates a random number between [1, 20], inclusive.
//          This number represents the number of events that occur during the game.
//      INPUTS: event_number- an integer variable passed by reference that represents the number of events that will occur during the game.
//      OUTPUTS: nothing; value returned by reference.

void generate_number_for_events(int& number_for_event);
// PURPOSE: Generates a random number between [1, 6], inclusive.
//      INPUTS: number_for_events- integer variable passed by reference that will hold a random number between [1,6], inclusive.
//      OUTPUTS: nothing; value returned by reference;

void shot_case(int& team_goals, int& team_shots_on_goal, int& team_shots_off_goal, int& team_blocked_shots, bool& teamA);
// PURPOSE: Handles case if a team shoots at the goal. Determines result of shot by generating random number for different cases
//      INPUTS: team_goals- an integer variable passed by reference that represents how many goals the team has scored so far
//              team_shots_on_goal- an integer variable passed by reference that represents how many shot on goal the team has shot so far
//              team_shots_off_goal- an integer variable passed by reference that represents how many shots off goal the team has so far
//              team_blocked_shots- an integer variable passed by reference that represents how many of the team's shots have been blocked so far
//              teamA- boolean value that refers to what team is being processed for. If teamA == true, it's Team A. If teamA == false, it's Team B.
//      OUTPUTS: none; values returned by reference

void foul_case(int& team_fouls, int& team_yellow_cards, int& team_red_cards, bool& teamA);
// PURPOSE: Handles case when a team has committed a foul
//      INPUTS: team_fouls- an integer variable passed by reference that refers to how many fouls the team has
//              team_yellow_cards- an integer variable passed by reference that represents how many yellow cards the current team has so far
//              team_red_cards- an integer variable passed by reference that represents how many red cards the current team has so far
//              teamA- boolean value that refers to what team is being processed for. If teamA == true, it's Team A. If teamA == false, it's Team B.      
//      OUTPUTS: none; values returned by reference

void penalty_kick(int& team_goals, int& team_shots_on_goal, int& team_shots_off_goal, bool& teamA);
// PURPOSE: Handles case when a team is awarded a penalty kick
//      INPUTS: team_goals- an integer variable passed by reference that refers to how many goals the team has scored so far
//              team_shots_on_goal- an integer variable passed by reference that represents how many shots on goal the team has shot so far
//              team_shots_off_goal- and integer variable passed by reference that represents how many shots off goal the team has shot so far
//              teamA- boolean value that refers to what team is being processed for. If teamA == true, it's Team A. If teamA == false, it's Team B.
//      OUTPUTS: none; values returned by reference 

void outputs_stats(int teamA_goals, int teamA_shots_on_goal, int teamA_shots_off_goal, int teamA_blocked_shots,
                    int teamA_fouls, int teamA_yellow_cards, int teamA_red_cards,
                    int teamB_goals, int teamB_shots_on_goal, int teamB_shots_off_goal, int teamB_blocked_shots,
                    int teamB_fouls, int teamB_yellow_cards, int teamB_red_cards);
// PURPOSE: Outputs all the stats for each team
//          INPUTS: every team statistic for each team passed by value.
//          OUTPUTS: outputs formatted stats to the console

void start_soccer_simulation() {
    // [SETUP]
    // step 1.1- declare and initialize general simulation variables
    int event_number = 0, number_for_event = 0;

    // step 1.2 declare and initialize variables related to Team A
    int teamA_goals = 0, teamA_shots_on_goal = 0, teamA_shots_off_goal = 0, teamA_blocked_shots = 0;
    int teamA_fouls = 0, teamA_yellow_cards = 0, teamA_red_cards = 0;

    // step 1.3 declare and initialize variables related to Team B
    int teamB_goals = 0, teamB_shots_on_goal = 0, teamB_shots_off_goal = 0, teamB_blocked_shots = 0;
    int teamB_fouls = 0, teamB_yellow_cards = 0, teamB_red_cards = 0;

    // step 1.4- boolean value "teamA" refers to the team that the event is for. This will be passed into the
    //          various functions to ensure the output is for the correct team.
    //          TeamB correlates to if teamA == false. TeamA correlates to if teamA == true.
    bool teamA = false;

    // step 2- set randomization seed
    srand(time(0));

    // [PROCESSING]
    // step 1- calculate number of events
    generate_number_of_events(event_number);

    // step 2- generate halftime number by taking the modulo event_number of a random number
    int halftime = rand() % event_number;

    // step 3.1- iterate over all the events
    for (int event = 0; event < event_number; event++) {

        // step 3.2- generate a random number between [1, 6] inclusive by calling function generate_number_for_events()
        generate_number_for_events(number_for_event);

        // [OUTPUT]
        // step 3.3- output halftime stats once the loop reaches halftime
        if (event == halftime) {
            cout << "Halftime stats:" << endl;
            outputs_stats(teamA_goals, teamA_shots_on_goal,  teamA_shots_off_goal, teamA_blocked_shots,
                 teamA_fouls, teamA_yellow_cards, teamA_red_cards,
                 teamB_goals, teamB_shots_on_goal, teamB_shots_off_goal, teamB_blocked_shots,
                 teamB_fouls, teamB_yellow_cards, teamB_red_cards); 
        }

        // step 3.4- if number_for_event is 1, then Team A took a shot
        if (number_for_event == 1) {
            
            // step 3.41- update teamA to true since this event is related to Team A
            teamA = true;

            // step 3.42- call shot_case and pass in appropiate variables
            shot_case(teamA_goals, teamA_shots_on_goal, teamA_shots_off_goal, teamA_blocked_shots, teamA);
        }

        // step 3.5- if number_for_event is 2, then Team B took a shot
        if (number_for_event == 2) {
            
            // step 3.51- update teamA to false since this event is related to Team B
            teamA = false;

            // step 3.52- call shot_case and pass in appropiate variables
            shot_case(teamB_goals, teamB_shots_on_goal, teamB_shots_off_goal, teamB_blocked_shots, teamA);
        }

        // step 3.6- if number_for_event is 3, then Team B committed a foul and Team A was awarded a free kick
        if (number_for_event == 3) {

            // step 2.61- update teamA to false since this sub-event is related to Team B
            teamA = false;

            // step 3.62 call function foul_case() and pass in appropiate variables
            foul_case(teamB_fouls, teamB_yellow_cards, teamB_red_cards, teamA);

            // step 3.63- update teamA to true since this sub-evenet is related to Team A
            teamA = true;

            // step 3.64- call function shot_case() and pass in appropiate variables
            shot_case(teamA_goals, teamA_shots_on_goal, teamA_shots_off_goal, teamA_blocked_shots, teamA);
        }

        // step 3.7- if number_for_event is 4, then Team A committed a foul and Team B was awarded a free kick
        if (number_for_event == 4) {

            // step 3.71- update teamA to true since this sub-event is related to Team A
            teamA = true;

            // step 3.72 call function foul_case() and pass in appropiate variables
            foul_case(teamA_fouls, teamA_yellow_cards, teamA_red_cards, teamA);

            // step 3.73- update teamA to false since this sub-evenet is related to Team B
            teamA = false;

            // step 3.64- call function shot_case() and pass in appropiate variables
            shot_case(teamB_goals, teamB_shots_on_goal, teamB_shots_off_goal, teamB_blocked_shots, teamA);
        }

        // step 3.7- if number_for_event is 5, then Team B committed a foul and Team A was awarded a penalty kick
        if (number_for_event == 5) {

            // step 3.71- update teamA to false since this sub-event is related to Team B
            teamA = false;

            // step 3.72- call function foul_case() and pass in appropiate variables
            foul_case(teamB_fouls, teamB_yellow_cards, teamB_red_cards, teamA);

            // step 3.73- update teamA to true since this sub-event is related to Team A
            teamA = true;

            // step 3.74- call function penalty_kick() and pass in appropiate variables
            penalty_kick(teamA_goals, teamA_shots_on_goal, teamA_shots_off_goal, teamA);
        }

        // step 3.8- if number_for_event is 6, then Team A committed a foul and Team B was awarded a penalty kick
        if (number_for_event == 6) {

            // step 3.81- update teamA to true since this sub-event is related to Team A
            teamA = true;

            // step 3.82- call function foul_case() and pass in appropiate variables
            foul_case(teamA_fouls, teamA_yellow_cards, teamA_red_cards, teamA);

            // step 3.83- update teamA to false since this sub-event is related to Team B
            teamA = false;

            // step 3.84- call function penalty_kick() and pass in appropiate variables
            penalty_kick(teamB_goals, teamB_shots_on_goal, teamB_shots_off_goal, teamA);
        }
        
    }

    // [OUTPUT]
    // step 4- output game stats once the game is finished
    cout << "Final stats:" << endl;
    outputs_stats(teamA_goals, teamA_shots_on_goal,  teamA_shots_off_goal, teamA_blocked_shots,
                 teamA_fouls, teamA_yellow_cards, teamA_red_cards,
                 teamB_goals, teamB_shots_on_goal, teamB_shots_off_goal, teamB_blocked_shots,
                 teamB_fouls, teamB_yellow_cards, teamB_red_cards); 
}

void generate_number_of_events(int& event_number) {
    // step 1- generate a random number between [1, 20], inclusive. Store value in variable "event_number"
    event_number = rand() % 20;

    // step 1.1- add 1 to event_number in order to get in [1, 20] range
    event_number++;
}

void generate_number_for_events(int& number_for_event) {
    // step 1- generate a random number between [1, 6], inclusive. Store value in variable "number_for_event"
    number_for_event = rand() % 6;

    // step 1.1- add 1 to number_for_event in order to get in [1, 6] range
    number_for_event++;
}

void shot_case(int& team_goals, int& team_shots_on_goal, int& team_shots_off_goal, int& team_blocked_shots, bool& teamA) {
    // step 1- generate a random number between [0, 3], inclusive, in order to determine what happens with the shot
    int random_result = rand() % 4;

    // step 2- handle case if Team A took a shot
    if (teamA == true) {
        
        // step 2.1- case if random_result is 0
        if (random_result == 0) {
            
            // step 2.11- add one to Team A's goal count
            team_goals++;

            // step 2.12- add one to Team A's on goal count
            team_shots_on_goal++;

            // step 2.13- communicate what happened
            cout << "Team A has scored a goal! Great shot!" << endl;
        }

        // step 2.2- case if random_result is 1
        if (random_result == 1) {

            // step 2.21- add one to Team A's on goal count
            team_shots_on_goal++;

            // step 2.22- communicate what happened
            cout << "Team A took a shot on goal, but it was saved by the goalkeeper or last defender on Team B!" << endl;
        }

        // step 2.3- case if random_result is 2
        if (random_result == 2) {
            
            // step 2.31- add one to Team A's shots off goal count
            team_shots_off_goal++;

            // step 2.32- communicate what happened
            cout << "Team A took a shot but missed the goal." << endl;

        }

        // step 2.4- case if random_result is 3
        if (random_result == 3) {

            // step 2.41- add one to Team A's blocked shots
            team_blocked_shots++;

            // step 2.42- communicate what happened
            cout << "Team A took a shot, but it was blocked by a player who isn't the last defender on Team B! Nice block!" << endl;

        }
    }

    // step 3- handle case if Team B took a shot
    if (teamA == false) {
        
        // step 3.1- case if random_result is 0
        if (random_result == 0) {
            
            // step 3.11- add one to Team B's goal count
            team_goals++;

            // step 3.12- add one to Team B's on goal count
            team_shots_on_goal++;

            // step 3.13- communicate what happened
            cout << "Team B has scored a goal! Great shot!" << endl;
        }

        // step 3.2- case if random_result is 1
        if (random_result == 1) {

            // step 3.21- add one to Team B's on goal count
            team_shots_on_goal++;

            // step 3.22- communicate what happened
            cout << "Team B took a shot on goal, but it was saved by the goalkeeper or last defender on Team A!" << endl;
        }

        // step 3.3- case if random_result is 2
        if (random_result == 2) {
            
            // step 3.31- add one to Team B's shots off goal count
            team_shots_off_goal++;

            // step 3.32- communicate what happened
            cout << "Team B took a shot but missed the goal." << endl;

        }

        // step 3.4- case if random_result is 3
        if (random_result == 3) {

            // step 3.4- add one to Team B's blocked shots
            team_blocked_shots++;

            // step 3.42- communicate what happened
            cout << "Team B took a shot, but it was blocked by a player who isn't the last defender on Team A! Nice block!" << endl;

        }

    }
    
}

void foul_case(int& team_fouls, int& team_yellow_cards, int& team_red_cards, bool& teamA) {
    // step 1- generate a random number between [0, 2], inclusive, in order to determine what happens after the foul is given
    int random_result = rand() % 3;

    // step 2- handle case if Team A committed a foul
    if (teamA == true) {
        
        // step 2- case if random_result is 0
        if (random_result == 0) {

            // step 2.11- add one to Team A's foul count
            team_fouls++;

            // step 2.12- communicate what happened
            cout << "Team A committed a foul and Team B was awarded a free kick. No card was given for the foul." << endl;
            
        }

        // step 3- case if random_result is 1
        if (random_result == 1) {

            // step 3.11- add a foul to Team A's foul count
            team_fouls++;

            // step 3.12- add one to Team A's yellow card count
            team_yellow_cards++;

            // step 3.13- communicate what happened
            cout << "Team A committed a foul and Team B was awarded a free kick. Team A is given a yellow card for the foul." << endl;
            
        }

        // step 4- case if random_result is 2
        if (random_result == 2) {

            // step 4.11- add a foul to Team A's foul count
            team_fouls++;

            // step 4.12- add one to Team A's red card count
            team_red_cards++;

            // step 4.13- communicate what happened
            cout << "Team A committed a foul and Team B was awarded a free kick. Team A is given a red card for the foul." << endl;
            
        }
    }


    // step 5- handle case if Team B committed a foul
    if (teamA == false) {
        
        // step 5- case if random_result is 0
        if (random_result == 0) {

            // step 5.11- add one to Team B's foul count
            team_fouls++;

            // step 5.12- communicate what happened
            cout << "Team B committed a foul and Team A was awarded a free kick. No card was given for the foul." << endl;
            
        }

        // step 6- case if random_result is 1
        if (random_result == 1) {

            // step 6.11- add a foul to Team B's foul count
            team_fouls++;

            // step 6.12- add one to Team B's yellow card count
            team_yellow_cards++;

            // step 6.13- communicate what happened
            cout << "Team B committed a foul and Team A was awarded a free kick. Team B is given a yellow card for the foul." << endl;
            
        }

        // step 7- case if random_result is 2
        if (random_result == 2) {

            // step 7.11- add a foul to Team B's foul count
            team_fouls++;

            // step 7.12- add one to Team B's red card count
            team_red_cards++;

            // step 7.13- communicate what happened
            cout << "Team B committed a foul and Team A was awarded a free kick. Team B is given a red card for the foul." << endl;
            
        }
    }


}

void penalty_kick(int& team_goals, int& team_shots_on_goal, int& team_shots_off_goal, bool& teamA) {
    // step 1- generate a random number between [0, 2], inclusive, in order to determine what happens with the penalty shot
    int random_result = rand() % 3;

    // step 2- handle case if Team A was given a penalty shot
    if (teamA == true) {
        
        // step 2.1- case if random_result is 0
        if (random_result == 0) {
            
            // step 2.11- add one to Team A's goal count
            team_goals++;

            // step 2.12- add one to Team A's on goal count
            team_shots_on_goal++;

            // step 2.13- communicate what happened
            cout << "Team A has scored a goal off their penalty kick! Great shot!" << endl;
        }

        // step 2.2- case if random_result is 1
        if (random_result == 1) {

            // step 2.21- add one to Team A's on goal count
            team_shots_on_goal++;

            // step 2.22- communicate what happened
            cout << "Team A took a shot on goal off their penalty kick, but it was saved by Team B's goalkeeper! Nice save!" << endl;
        }

        // step 2.3- case if random_result is 2
        if (random_result == 2) {
            
            // step 2.31- add one to Team A's shots off goal count
            team_shots_off_goal++;

            // step 2.32- communicate what happened
            cout << "Team A took a shot off their penalty kick, but they missed the goal." << endl;

        }
 
    }

    // step 3- handle case if Team B was given a penalty shot
    if (teamA == false) {
        
        // step 3.1- case if random_result is 0
        if (random_result == 0) {
            
            // step 3.11- add one to Team B's goal count
            team_goals++;

            // step 3.12- add one to Team B's on goal count
            team_shots_on_goal++;

            // step 3.13- communicate what happened
            cout << "Team B has scored a goal off their penalty kick! Great shot!" << endl;
        }

        // step 3.2- case if random_result is 1
        if (random_result == 1) {

            // step 3.21- add one to Team B's on goal count
            team_shots_on_goal++;

            // step 3.22- communicate what happened
            cout << "Team B took a shot on goal off their penalty kick, but it was saved by Team A's goalkeeper! Nice save!" << endl;
        }

        // step 3.3- case if random_result is 2
        if (random_result == 2) {
            
            // step 3.31- add one to Team B's shots off goal count
            team_shots_off_goal++;

            // step 3.32- communicate what happened
            cout << "Team B took a shot off their penalty kick, but they missed the goal." << endl;

        }
 
    }
    
}

void outputs_stats(int teamA_goals, int teamA_shots_on_goal, int teamA_shots_off_goal, int teamA_blocked_shots,
                    int teamA_fouls, int teamA_yellow_cards, int teamA_red_cards,
                    int teamB_goals, int teamB_shots_on_goal, int teamB_shots_off_goal, int teamB_blocked_shots,
                    int teamB_fouls, int teamB_yellow_cards, int teamB_red_cards) {

    // step 1- output results
    cout << "           Goals      Shots on goal       Shots off goal      Blocked shots       Fouls       Yellow cards        Red cards" << endl;
    cout << "Team A:    " << teamA_goals << "          " << teamA_shots_on_goal << "                   " << teamA_shots_off_goal << "                   " << teamA_blocked_shots;
    cout << "                   " << teamA_fouls << "           " << teamA_yellow_cards << "                   " << teamA_red_cards << endl;
    cout << "Team B:    " << teamB_goals << "          " << teamB_shots_on_goal << "                   " << teamB_shots_off_goal << "                   " << teamB_blocked_shots;
    cout << "                   " << teamB_fouls << "           " << teamB_yellow_cards << "                   " << teamB_red_cards << endl;
}

int main() {
    start_soccer_simulation(); // invokes the simulation
}
