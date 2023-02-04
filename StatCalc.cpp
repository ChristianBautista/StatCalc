#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include "smanip.h"

using namespace std;

/*
Badminton: [MW,ML,GW,GL,PW,PL]
Baseball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
Basketball: [GW,GL,QW,QL,QD,PS,PA,OTW,OTL,OTD]
Bowling: [GW,GL,GD,FW,FL,FD,PS,PA,PKD,OPKD,ST,SP]
Boxing: [MW,ML,MD,RW,RL,RD,KOs,KO'd,PW,PL]
Darts: [MW,ML,SW,SL,LW,LL]
Fencing: [MW,ML,RW,RL,RD,PW,PL,SDW,SDL,SDD]
Football: [GW,GL,GD,QW,QL,QD,PS,PA,OTW,OTL,OTD]
Handball: [MW,ML,MD,HW,HL,HD,GS,GA,OTW,OTL,OTD,OTHW,OTHL,OTHD,SOW,SOL,SOD,PGS,PGA]
Hockey: [GW,GL,PW,PL,PD,GS,GA,OTW,OTL,OTD,SOW,SOL,PGS,PGA]
Kickball: [GW,GL,IW,IL,ID,RS,RA,K,KA]
Pickleball: [MW,ML,GW,GL,PW,PL]
Soccer: [MW,ML,MD,HW,HL,HD,GS,GA,ETW,ETL,ETD,ETHW,ETHL,ETHD,SOW,SOL,SOD,PGS,PGA]
Softball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
Table Tennis: [MW,ML,GW,GL,PW,PL]
Tennis: [MW,ML,SW,SL,GW,GL,TW,TL]
Ultimate Frisbee: [GW,GL,HW,HL,HD,QW,QL,QD,GS,GA,OTW,OTL,OTD]
Volleyball: [MW,ML,SW,SL,PW,PL]
Water Polo: [GW,GL,QW,QL,QD,GS,GA,OTW,OTL,OTD,SOW,SOL,SOD,PGS,PGA]
Wiffleball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
*/

// define const indices
const int W = 0; // Win
const int L = 1; // Loss
const int D = 2; // Draw
const int F = 3; // Points For
const int A = 4; // Points Against
const int TW = 6; // Tiebreak Win (tennis)
const int TL = 7; // Tiebreak Loss (tennis)

void usage() {
    /*
    Badminton: [MW,ML,GW,GL,PW,PL]
    Baseball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
    Basketball: [GW,GL,QW,QL,QD,PS,PA,OTW,OTL,OTD]
    Bowling: [GW,GL,GD,FW,FL,FD,PS,PA,PKD,OPKD,ST,SP]
    Boxing: [MW,ML,MD,RW,RL,RD,KOs,KO'd,PW,PL]
    Darts: [MW,ML,SW,SL,LW,LL]
    Fencing: [MW,ML,RW,RL,RD,PW,PL,SDW,SDL,SDD]
    Football: [GW,GL,GD,QW,QL,QD,PS,PA,OTW,OTL,OTD]
    Handball: [MW,ML,MD,HW,HL,HD,GS,GA,OTW,OTL,OTD,OTHW,OTHL,OTHD,SOW,SOL,SOD,PGS,PGA]
    Hockey: [GW,GL,PW,PL,PD,GS,GA,OTW,OTL,OTD,SOW,SOL,PGS,PGA]
    Kickball: [GW,GL,IW,IL,ID,RS,RA,K,KA]
    Pickleball: [MW,ML,GW,GL,PW,PL]
    Soccer: [MW,ML,MD,HW,HL,HD,GS,GA,ETW,ETL,ETD,ETHW,ETHL,ETHD,SOW,SOL,SOD,PGS,PGA]
    Softball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
    Table Tennis: [MW,ML,GW,GL,PW,PL]
    Tennis: [MW,ML,SW,SL,GW,GL,TW,TL]
    Ultimate Frisbee: [GW,GL,HW,HL,HD,QW,QL,QD,GS,GA,OTW,OTL,OTD]
    Volleyball: [MW,ML,SW,SL,PW,PL]
    Water Polo: [GW,GL,QW,QL,QD,GS,GA,OTW,OTL,OTD,SOW,SOL,SOD,PGS,PGA]
    Wiffleball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
    */
    cout << "SGSC: Sports General Statistic Calculator" << endl;
    cout << "Coded by Christian Bautista\n" << endl;
    cout << "Supported Sports with Valid Fields:" << endl;
    cout << "- Badminton: \"match\" i.t.o. \"games\"; \"game\" i.t.o. \"points\"" << endl;
    cout << "- Baseball: \"game\" i.t.o. \"runs\"; \"inning\" i.t.o. \"runs\"; \"hits\" i.t.o. \"hits\"" << endl;
    cout << "- Basketball: \"game\" i.t.o. \"points\"; \"quarter\" i.t.o. \"points\"; \"overtime\" i.t.o. \"points\"" << endl;
    cout << "- Bowling: \"game\" i.t.o. \"points\"; \"frame\" i.t.o. \"pins\"" << endl;
    cout << "- Boxing: \"match\" i.t.o. \"points\"; \"round\" i.t.o. \"points\"; \"knockouts\" in terms of \"knockouts\"" << endl;
    cout << "- Darts: \"match\" i.t.o. \"sets\"; \"set\" i.t.o. \"legs\"" << endl;
    cout << "- Fencing: \"match\" i.t.o. \"points\"; \"round\" i.t.o. \"points\"; \"sudden death\" i.t.o. \"points\"" << endl;
    cout << "- Football: \"game\" i.t.o. \"points\"; \"quarter\" i.t.o. \"points\"; \"overtime\" i.t.o. \"points\"" << endl;
    cout << "- Handball: \"match\" i.t.o. \"goals\"; \"half\" i.t.o. \"goals\"; \"overtime\" i.t.o. \"goals\"; \"overtime half\" i.t.o. \"goals\"; \"shootout\" i.t.o. \"goals\"" << endl;
    cout << "- Hockey: \"game\" i.t.o. \"goals\"; \"period\" i.t.o. \"goals\"; \"overtime\" i.t.o. \"goals\"; \"shootout\" i.t.o. \"goals\"" << endl;
    cout << "- Kickball: \"game\" i.t.o. \"runs\"; \"inning\" i.t.o. \"runs\"; \"kicks\" i.t.o. \"kicks\"" << endl;
    cout << "- Pickleball: \"match\" i.t.o. \"games\"; \"game\" i.t.o. \"points\"" << endl;
    cout << "- Soccer: \"match\" i.t.o. \"goals\"; \"half\" i.t.o. \"goals\"; \"extra time\" i.t.o. \"goals\"; \"extra time half\" i.t.o. \"goals\"; \"shootout\" i.t.o. \"goals\"" << endl;
    cout << "- Softball: \"game\" i.t.o. \"runs\"; \"inning\" i.t.o. \"runs\"; \"hits\" i.t.o. \"hits\"" << endl;
    cout << "- Table Tennis: \"match\" i.t.o. \"games\"; \"game\" i.t.o. \"points\"" << endl;
    cout << "- Tennis: \"match\" i.t.o. \"sets\"; \"set\" i.t.o. \"games\"" << endl;
    cout << "- Ultimate Frisbee: \"game\" i.t.o. \"goals\"; \"half\" i.t.o. \"goals\"; \"quarter\" i.t.o. \"goals\"; \"overtime\" i.t.o. \"goals\"" << endl;
    cout << "- Volleyball: \"match\" i.t.o. \"sets\"; \"set\" i.t.o. \"points\"" << endl;
    cout << "- Water Polo: \"game\" i.t.o. \"goals\"; \"quarter\" i.t.o. \"goals\"; \"overtime\" i.t.o. \"goals\"; \"shootout\" i.t.o. \"goals\"" << endl;
    cout << "- Wiffleball: \"game\" i.t.o. \"runs\"; \"inning\" i.t.o. \"runs\"; \"hits\" i.t.o. \"hits\"" << endl;
}

/* Format:
Flag,Winner,Loser,Game/Set/Match Score 1,Game/Set/Match Score 2,Game/Set/Match Score 3...
Flags: h/H (header), c/C (comment), * (contested/conflicting result)
*/
bool validate(ifstream& matches, string& filename, vector<string>& valid_fields) {
    int count = 1;
    int cols = 0;
    bool first = true;
    bool data = false;
    bool valid = true;
    string row;
    string flag;
    string name;
    // reset matches
    matches.seekg(0);
    // loop through each row
    while (getline(matches, row)) {
        // check if row has data
        if (row.length()) {
            // create a stream for the line
            stringstream line(rcsvtrim(ltrim(row)));
            // get and trim flag
            getline(line, flag, ',');
            flag = trim(flag);
            // check for type of line
            if (!first && flag.length() >= 2) { // invalid flag
                cout << "ERROR: (line " << count << ") invalid flag" << endl;
                valid = false;
            }
            else if (!flag.length() || flag == "*") { // match
                // set data flag to true
                if (!data) {
                    data = true;
                }
                // check if there's a name in the second and third column
                for (int col = 1; col <= 2; col++) {
                    getline(line, name, ',');
                    name = trim(name);
                    if (!name.length()) {
                        cout << "ERROR: (line " << count << ") empty field for player/team " << col << endl;
                        valid = false;
                    }
                }
                // check if each scoring column are formatted correctly
                string score;
                int col = 0;
                bool col_data = false;
                while (getline(line, score, ',')) {
                    // increment column count
                    col++;
                    // trim score
                    score = trim(score);
                    // check if there is data
                    if (!score.length()) {
                        continue;
                    }
                    // check for minimum length of 3
                    if (score.length() < 3) {
                        cout << "ERROR: (line " << count << ") invalid score" << endl;
                        valid = false;
                        continue;
                    }
                    // set col_data to true
                    col_data = true;
                    // get index of '-'
                    int dash = score.find('-');
                    if (dash == string::npos) {
                        cout << "ERROR: (line " << count << ") invalid score" << endl;
                        valid = false;
                        continue;
                    }
                    // check if numbers before and after dash are ints>=0
                    int wscore;
                    int lscore;
                    try {
                        wscore = stoi(score.substr(0, dash));
                        lscore = stoi(score.substr(dash + 1, score.length() - dash + 1));
                    }
                    catch (invalid_argument e) {
                        cout << "ERROR: (line " << count << ") invalid score" << endl;
                        valid = false;
                        continue;
                    }
                    if (wscore < 0 || lscore < 0) {
                        cout << "ERROR: (line " << count << ") invalid score" << endl;
                        valid = false;
                        continue;
                    }
                }
                /* NOTE: Score can be empty, handle in stat
                // check if there are no columns
                if (!col) {
                    cout << "ERROR: (line " << count << ") no scoring data" << endl;
                    valid = false;
                }
                */
                // check if there are too many columns
                if (col > cols) {
                    cout << "ERROR: (line " << count << ") extra columns" << endl;
                    valid = false;
                }
                /* NOTE: Score can be empty, handle in stat
                // check if there is col_data
                if (!col_data) {
                    cout << "ERROR: (line " << count << ") no scoring data" << endl;
                    valid = false;
                }
                */
            }
            else if (first || flag == "h" || flag == "H") { // header
                // set first to false
                if (first) {
                    if (upper(flag) != "FLAG") {
                        cout << "ERROR: (line " << count << ") flag field header not labeled \"flag\"" << endl;
                        valid = false;
                    }
                    first = false;
                }
                string field;
                // check if second column has a valid header (player 1, team 1, winner)
                getline(line, field, ',');
                field = upper(trim(field));
                if (field != "PLAYER 1" && field != "TEAM 1" && field != "WINNER") {
                    cout << "ERROR: (line " << count << ") second column header is improperly labeled" << endl;
                    valid = false;
                }
                // check if third column has a valid header (player 2, team 2, loser)
                getline(line, field, ',');
                field = upper(trim(field));
                if (field != "PLAYER 2" && field != "TEAM 2" && field != "LOSER") {
                    cout << "ERROR: (line " << count << ") third column header is improperly labeled" << endl;
                    valid = false;
                }
                // make sure all subsequent column titles are valid fields
                cols = 0;
                bool found = false;
                while (!line.eof()) {
                    // get field
                    getline(line, field, ',');
                    field = lower(trim(field));
                    // loop through vector of fields
                    int i = 0;
                    while (i < valid_fields.size() && field.find(valid_fields[i]) == string::npos) {
                        i++;
                    }
                    if (i==valid_fields.size()) {
                        cout << "ERROR: (line " << count << ") invalid field (" << field << ")" << endl;
                        valid = false;
                    }
                    // increment cols
                    cols++;
                }
            }
            else if (flag == "c" || flag == "C") { // comment
                continue;
            }
            else {
                cout << "ERROR: (line " << count << ") invalid flag" << endl;
                valid = false;
            }
        }
        // increment line number
        count++;
    }
    if (!data) {
        cout << "ERROR: " << filename << " does not have match data" << endl;
        valid = false;
    }
    return valid;
}

vector<string> fieldtypes(stringstream& header, vector<string>& valid_fields) {
    vector<string> fields;
    string field;
    int i = 0;
    while (getline(header, field, ',')) {
        field = lower(trim(field));
        while (i < valid_fields.size() && field.find(valid_fields[i]) == string::npos) {
            i++;
        }
        // assumes that i will never equal valid_fields.size()
        fields.push_back(valid_fields[i]);
    }
    return fields;
}

void stat(map<string, vector<int>>& stats, map<string, int*> indices, vector<string>& fields, vector<bool>& used, stringstream& match, string sport, bool check, bool& draw, bool& winleft) {
    // get names
    string n1; // player/team 1
    getline(match, n1, ',');
    n1 = trim(n1);
    string n2; // player/team 2
    getline(match, n2, ',');
    n2 = trim(n2);
    // create statlines for both n1 & n2 if necessary
    if (stats.find(n1) == stats.end()) {
        vector<int> n1sl;
        for (int i = 0; i < used.size(); i++) {
            n1sl.push_back(0);
        }
        stats[n1] = n1sl;
    }
    if (stats.find(n2) == stats.end()) {
        vector<int> n2sl;
        for (int i = 0; i < used.size(); i++) {
            n2sl.push_back(0);
        }
        stats[n2] = n2sl;
    }
    // create a used_now vector to for pre-decider and decider check
    vector<bool> used_now;
    for (int i = 0; i < used.size(); i++) {
        used_now.push_back(false);
    }
    // loop through all stat fields
    int col = 0; // iterator for fields
    int dash;
    int n1s;
    int n2s;
    int n1ts = 0;
    int n2ts = 0;
    int use_case;
    int* field_indices;
    bool valid = false;
    bool pre_decided = indices.count("pre-decider") ? false : true;
    bool decided = false;
    string ip;
    string score;
    while (getline(match, score, ',') || !pre_decided || !decided) {
        // TODO: Account for Bowling stats (points, strikes, and spares)
        if (score.length()) {
            dash = score.find('-');
            // get score for n1 and n2
            n1s = stoi(score.substr(0, dash));
            n2s = stoi(score.substr(dash + 1, score.length() - dash + 1));
            // add scores to scoring columns of statlines
            field_indices = indices[fields[col]];
            stats[n1][field_indices[F]] += n1s;
            stats[n1][field_indices[A]] += n2s;
            stats[n2][field_indices[F]] += n2s;
            stats[n2][field_indices[A]] += n1s;
            // mark as used
            used[field_indices[F]] = true;
            used[field_indices[A]] = true;
            used_now[field_indices[F]] = true;
            used_now[field_indices[A]] = true;
            // set use_case
            use_case = 0;
        }
        else if (!pre_decided) {
            field_indices = indices["pre-decider"];
            n1s = stats[n1][field_indices[F]];
            n2s = stats[n2][field_indices[F]];
            use_case = 1;
        }
        else if (!decided) {
            field_indices = indices["decider"];
            n1s = stats[n1][field_indices[W]];
            n2s = stats[n2][field_indices[W]];
            if (field_indices[2] != -1 && field_indices[3] != -1) {
                n1ts = stats[n1][field_indices[2]];
                n2ts = stats[n2][field_indices[2]];
            }
            use_case = 2;
        }
        else {
            continue;
        }
        /* Determine whether to calculate:
        *  - score: always
        *  - pre_decided: !used_now[W/L] && (no draw or !used_now[D])
        *  - decided: used_now[0/1] && (!draw or !used_now[2])
        */
        if (use_case == 0 || \
           (use_case == 1 && (!used_now[field_indices[W]] && !used_now[field_indices[L]] && (field_indices[D] == -1 || !used_now[field_indices[D]]))) || \
           (use_case == 2 && (!used_now[0] && !used_now[1] && (!draw || !used_now[2])))) {
            /* Determine whether to perform manual calc or auto calc
            *  - score: check || (n1s == n2s && field_indices[D]==-1  && !winleft)
            *  - pre_decided: check || (n1s == n2s && field_indices[D]==-1)
            *  - decided: check || ((n1s == n2s && n1ts == n2ts) && !winleft)
            */
            if (check || (((use_case == 0 || use_case == 1) && (n1s == n2s && field_indices[D] == -1 && !winleft)) || (use_case == 2 && n1s == n2s && n1ts == n2ts && !winleft))) {
                valid = false;
                // loop until user gives valid answer
                while (!valid) {
                    // TODO: Incorporate line number, column number, and potentially full match
                    // Ask for user input on winner of match
                    if (use_case == 0) {
                        cout << "Please select the winner for the following " << fields[col] << " (" << n1s << "-" << n2s << "):" << endl;
                    }
                    else if (use_case == 1) {
                        cout << "Please select the winner for overtime/extra time (" << n1s << "-" << n2s << "):" << endl;
                    }
                    else {
                        cout << "Please select the match winner (" << n1s << "-" << n2s;
                        if (field_indices[2] != -1 && field_indices[3] != -1) {
                            cout << "; " << n1ts << "-" << n2ts;
                        }
                        cout << "):" << endl;
                    }
                    cout << "0: No Score" << endl;
                    cout << "1: " << n1 << endl;
                    cout << "2: " << n2 << endl;
                    if (((use_case == 0 || use_case == 1) && field_indices[D] != -1) || (use_case==2 && draw)) {
                        cout << "3: No Winner" << endl;
                    }
                    cout << "Enter your selection: ";
                    cin >> ip;
                    ip = trim(ip);
                    if (ip == "0" || ip == "1" || ip == "2" || (ip == "3" && field_indices[D] != -1)) { // valid input
                        if (ip != "0") {
                            if (use_case == 2) {
                                // increment appropriate field
                                stats[n1][(ip == "3" && draw) ? D : (ip == "1" ? W : L)] += 1;
                                stats[n2][(ip == "3" && draw) ? D : (ip == "2" ? W : L)] += 1;
                                // mark as used
                                used[(ip == "3" && draw) ? D : (ip == "1" ? W : L)] = true;
                                used[(ip == "3" && draw) ? D : (ip == "2" ? W : L)] = true;
                                used_now[(ip == "3" && draw) ? D : (ip == "1" ? W : L)] = true;
                                used_now[(ip == "3" && draw) ? D : (ip == "2" ? W : L)] = true;
                            }
                            else {
                                // increment appropriate field
                                stats[n1][field_indices[(ip == "3" && field_indices[D] != -1) ? D : (ip == "1" ? W : L)]] += 1;
                                stats[n2][field_indices[(ip == "3" && field_indices[D] != -1) ? D : (ip == "2" ? W : L)]] += 1;
                                // mark as used
                                used[field_indices[(ip == "3" && field_indices[D] != -1) ? D : (ip == "1" ? W : L)]] = true;
                                used[field_indices[(ip == "3" && field_indices[D] != -1) ? D : (ip == "2" ? W : L)]] = true;
                                used_now[field_indices[(ip == "3" && field_indices[D] != -1) ? D : (ip == "1" ? W : L)]] = true;
                                used_now[field_indices[(ip == "3" && field_indices[D] != -1) ? D : (ip == "2" ? W : L)]] = true;
                                // Account for Tennis tiebreaks and Bowling stats (points, strikes, and spares)
                                if (sport == "tennis" && fields[col] == "set" && ((n1s == 7 && n2s == 6) || (n1s == 6 && n2s == 7))) {
                                    while (!valid) {
                                        cout << "Please select the winner for the tiebreaker:" << endl;
                                        cout << "0: No Score" << endl;
                                        cout << "1: " << n1 << endl;
                                        cout << "2: " << n2 << endl;
                                        cout << "Enter your selection: ";
                                        cin >> ip;
                                        ip = trim(ip);
                                        if (ip == "0" || ip == "1" || ip == "2") { // valid input
                                            if (ip != "0") {
                                                // increment tiebreak field
                                                stats[n1][ip == "1" ? TW : TL] += 1;
                                                stats[n2][ip == "2" ? TW : TL] += 1;
                                                // mark as used
                                                used[TW] = true;
                                                used[TL] = true;
                                                used_now[TW] = true;
                                                used_now[TL] = true;
                                            }
                                            valid = true;
                                            break;
                                        }
                                        else {
                                            cout << "ERROR: Invalid Input" << endl;
                                        }
                                    }
                                }
                            }
                        }
                        valid = true;
                        break;
                    }
                    else {
                        cout << "ERROR: Invalid Input" << endl;
                    }
                }
            }
            else {
                if (use_case == 2) { // account for winleft
                    // increment appropriate field
                    stats[n1][(n1s == n2s && draw) ? D : ((n1s > n2s || winleft) ? W : L)] += 1;
                    stats[n2][(n2s == n1s && draw) ? D : ((n2s > n1s && !winleft) ? W : L)] += 1;
                    // mark as used
                    used[(n1s == n2s && draw) ? D : ((n1s > n2s || winleft) ? W : L)] = true;
                    used[(n2s == n1s && draw) ? D : ((n2s > n1s && !winleft) ? W : L)] = true;
                    used_now[(n1s == n2s && draw) ? D : ((n1s > n2s || winleft) ? W : L)] = true;
                    used_now[(n2s == n1s && draw) ? D : ((n2s > n1s && !winleft) ? W : L)] = true;
                }
                else { // account for winleft
                    // increment appropriate field
                    stats[n1][field_indices[(n1s == n2s && field_indices[D] != -1) ? D : ((n1s > n2s || (n1s == n2s && winleft)) ? W : L)]] += 1;
                    stats[n2][field_indices[(n2s == n1s && field_indices[D] != -1) ? D : ((n2s > n1s) ? W : L)]] += 1;
                    // mark as used
                    used[field_indices[(n1s == n2s && field_indices[D] != -1) ? D : ((n1s > n2s || (n1s == n2s && winleft)) ? W : L)]] = true;
                    used[field_indices[(n2s == n1s && field_indices[D] != -1) ? D : ((n2s > n1s) ? W : L)]] = true;
                    used_now[field_indices[(n1s == n2s && field_indices[D] != -1) ? D : ((n1s > n2s) ? W : L)]] = true;
                    used_now[field_indices[(n2s == n1s && field_indices[D] != -1) ? D : ((n2s > n1s) ? W : L)]] = true;
                    // Account for Tennis tiebreaks and Bowling stats (points, strikes, and spares)
                    if (sport == "tennis" && fields[col] == "set" && ((n1s == 7 && n2s == 6) || (n1s == 6 && n2s == 7))) {
                        // increment tiebreak field
                        stats[n1][n1s > n2s ? TW : TL] += 1;
                        stats[n2][n2s > n1s ? TW : TL] += 1;
                        // mark as used
                        used[TW] = true;
                        used[TL] = true;
                        used_now[TW] = true;
                        used_now[TL] = true;
                    }
                }
            }
        }
        // update decider flags
        if (!score.length()) {
            if (pre_decided) {
                decided = true;
            }
            else {
                pre_decided = true;
            }
        }
        // clear score
        score.clear();
        // increment col
        col++;
    }    
}

int main() {
    // print usage
    usage();
    // create vars
    string sport; // sport name 
    map<string, int*> indices; // field -> [W,L,D,itoF,itoA]
    vector<string> valid_fields; 
    vector<string> header;
    vector<bool> used;
    // bool used[19] = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
    // string header[20] = { "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" }; // each header should have a \0 to signify end
    bool valid = false;
    // loop until user gives valid sport
    while (!valid) {
        // ask user for sport
        cout << "Select a sport: ";
        cin >> sport;
        // trim and lowercase sport
        sport = lower(trim(sport));
        // determine what sport "sport" is
        /*
        Badminton: [MW,ML,GW,GL,PW,PL]
        Baseball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
        Basketball: [GW,GL,QW,QL,QD,PS,PA,OTW,OTL,OTD]
        Bowling: [GW,GL,GD,FW,FL,FD,PS,PA,PKD,OPKD,ST,SP]
        Boxing: [MW,ML,MD,RW,RL,RD,KOs,KO'd,PW,PL]
        Darts: [MW,ML,SW,SL,LW,LL]
        Fencing: [MW,ML,RW,RL,RD,PW,PL,SDW,SDL,SDD]
        Football: [GW,GL,GD,QW,QL,QD,PS,PA,OTW,OTL,OTD]
        Handball: [MW,ML,MD,HW,HL,HD,GS,GA,OTW,OTL,OTD,OTHW,OTHL,OTHD,SOW,SOL,SOD,PGS,PGA]
        Hockey: [GW,GL,PW,PL,PD,GS,GA,OTW,OTL,OTD,SOW,SOL,PGS,PGA]
        Kickball: [GW,GL,IW,IL,ID,RS,RA,K,KA]
        Pickleball: [MW,ML,GW,GL,PW,PL]
        Soccer: [MW,ML,MD,HW,HL,HD,GS,GA,ETW,ETL,ETD,ETHW,ETHL,ETHD,SOW,SOL,SOD,PGS,PGA]
        Softball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
        Table Tennis: [MW,ML,GW,GL,PW,PL]
        Tennis: [MW,ML,SW,SL,GW,GL,TW,TL]
        Ultimate Frisbee: [GW,GL,HW,HL,HD,QW,QL,QD,GS,GA,OTW,OTL,OTD]
        Volleyball: [MW,ML,SW,SL,PW,PL]
        Water Polo: [GW,GL,QW,QL,QD,GS,GA,OTW,OTL,OTD,SOW,SOL,SOD,PGS,PGA]
        Wiffleball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
        */
        valid = true;
        // decider -> [W,L,D,PS,PA,TPS,TPA]
        if (!sport.length()) {
            cout << "ERROR: empty input" << endl;
            valid = false;
        }
        else if (sport == "badminton") { // Badminton: [MW,ML,GW,GL,PW,PL]
            int decider[4] = { 2,3,-1,-1 };
            int match[5] = { 0,1,-1,2,3 };
            int game[5] = { 2,3,-1,4,5 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["game"] = game;
            valid_fields = { "match","game" };
            header = { "MW","ML","GW","GL","PW","PL" };
            used = { false,false,false,false,false,false };
        }
        else if (sport == "baseball") { // Baseball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
            int decider[4] = { 5,6,-1,-1 };
            int game[5] = { 0,1,-1,5,6 };
            int inning[5] = { 2,3,4,5,6 };
            int hits[5] = { -1,-1,-1,7,8 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["inning"] = inning;
            indices["hits"] = hits;
            valid_fields = { "game","inning","hits" };
            header = { "GW","GL","IW","IL","ID","RS","RA","H","HA" };
            used = { false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "basketball") { // Basketball: [GW,GL,QW,QL,QD,PS,PA,OTW,OTL,OTD]
            int decider[4] = { 5,6,-1,-1 };
            int game[5] = { 0,1,-1,5,6 };
            int quarter[5] = { 2,3,4,5,6 };
            int overtime[5] = { 7,8,9,5,6 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["quarter"] = quarter;
            indices["overtime"] = overtime;
            valid_fields = { "game","quarter","overtime" };
            header = { "GW","GL","QW","QL","QD","PS","PA","OTW","OTL","OTD" };
            used = { false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "bowling") { // Bowling: [GW,GL,GD,FW,FL,FD,PS,PA,PKD,OPKD,ST,SP]
            int decider[4] = { 6,7,-1,-1 };
            int game[5] = { 0,1,2,6,7 };
            int frame[5] = { 3,4,5,8,9 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["frame"] = frame;
            valid_fields = { "game","frame" };
            header = { "GW","GL","GD","FW","FL","FD","PS","PA","PKD","OPKD","ST","SP" };
            used = { false,false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "boxing") { // Boxing: [MW,ML,MD,RW,RL,RD,KOs,KO'd,PW,PL]
            int decider[4] = { 6,7,8,9 };
            int match[5] = { 0,1,2,8,9 };
            int round[5] = { 3,4,5,8,9 };
            int knockout[5] = { -1,-1,-1,6,7 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["round"] = round;
            indices["knockout"] = knockout;
            valid_fields = { "match","round","knockout" };
            header = { "MW","ML","MD","RW","RL","RD","KOs","KO'd","PW","PL" };
            used = { false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "darts") { // Darts: [MW,ML,SW,SL,LW,LL]
            int decider[4] = { 2,3,-1,-1 };
            int match[5] = { 0,1,-1,2,3 };
            int set[5] = { 2,3,-1,4,5 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["set"] = set;
            valid_fields = { "match","set" };
            header = { "MW","ML","SW","SL","LW","LL" };
            used = { false,false,false,false,false,false };
        }
        else if (sport == "fencing") { // Fencing: [MW,ML,RW,RL,RD,PW,PL,SDW,SDL,SDD]
            int decider[4] = { 5,6,-1,-1 };
            int match[5] = { 0,1,-1,5,6 };
            int round[5] = { 2,3,4,5,6 };
            int sudden_death[5] = { 7,8,9,5,6 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["round"] = round;
            indices["sudden death"] = sudden_death;
            valid_fields = { "match","round","sudden death" };
            header = { "MW","ML","RW","RL","RD","PW","PL","SDW","SDL","SDD" };
            used = { false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "football") { // Football: [GW,GL,GD,QW,QL,QD,PS,PA,OTW,OTL,OTD]
            int decider[4] = { 6,7,-1,-1 };
            int game[5] = { 0,1,2,6,7 };
            int quarter[5] = { 3,4,5,6,7 };
            int overtime[5] = { 8,9,10,6,7 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["quarter"] = quarter;
            indices["overtime"] = overtime;
            valid_fields = { "game","quarter","overtime" };
            header = { "GW","GL","GD","QW","QL","QD","PS","PA","OTW","OTL","OTD" };
            used = { false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "handball") { // Handball: [MW,ML,MD,HW,HL,HD,GS,GA,OTW,OTL,OTD,OTHW,OTHL,OTHD,SOW,SOL,SOD,PGS,PGA]
            int decider[4] = { 6,7,17,18 };
            int match[5] = { 0,1,2,6,7 };
            int half[5] = { 3,4,5,6,7 };
            int overtime[5] = { 8,9,10,6,7 };
            int overtime_half[5] = { 11,12,13,6,7 };
            int pre_decider[5] = { 8,9,10,6,7 };
            int shootout[5] = { 14,15,16,17,18 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["half"] = half;
            indices["overtime"] = overtime;
            indices["overtime half"] = overtime_half;
            indices["pre-decider"] = pre_decider;
            indices["shootout"] = shootout;
            valid_fields = { "match","half","overtime","overtime half","shootout" };
            header = { "MW","ML","MD","HW","HL","HD","GS","GA","OTW","OTL","OTD","OTHW","OTHL","OTHD","SOW","SOL","SOD","PGS","PGA" };
            used = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "hockey") { // Hockey: [GW,GL,PW,PL,PD,GS,GA,OTW,OTL,OTD,SOW,SOL,PGS,PGA]
            int decider[4] = { 5,6,12,13 };
            int game[5] = { 0,1,-1,5,6 };
            int period[5] = { 2,3,4,5,6 };
            int overtime[5] = { 7,8,9,5,6 };
            int shootout[5] = { 10,11,-1,12,13 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["period"] = period;
            indices["overtime"] = overtime;
            indices["shootout"] = shootout;
            valid_fields = { "game","period","overtime","shootout" };
            header = { "GW","GL","PW","PL","PD","GS","GA","OTW","OTL","OTD","SOW","SOL","PGS","PGA" };
            used = { false,false,false,false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "kickball") { // Kickball: [GW,GL,IW,IL,ID,RS,RA,K,KA]
            int decider[4] = { 5,6,-1,-1 };
            int game[5] = { 0,1,-1,5,6 };
            int inning[5] = { 2,3,4,5,6 };
            int kicks[5] = { -1,-1,-1,7,8 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["inning"] = inning;
            indices["kicks"] = kicks;
            valid_fields = { "game","inning","kicks" };
            header = { "GW","GL","IW","IL","ID","RS","RA","K","KA" };
            used = { false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "pickleball") { // Pickleball: [MW,ML,GW,GL,PW,PL]
            int decider[4] = { 2,3,-1,-1 };
            int match[5] = { 0,1,-1,2,3 };
            int game[5] = { 2,3,-1,4,5 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["game"] = game;
            valid_fields = { "match","game" };
            header = { "MW","ML","GW","GL","PW","PL" };
            used = { false,false,false,false,false,false };
        }
        else if (sport == "soccer") { // Soccer: [MW,ML,MD,HW,HL,HD,GS,GA,ETW,ETL,ETD,ETHW,ETHL,ETHD,SOW,SOL,SOD,PGS,PGA]
            int decider[4] = { 6,7,17,18 };
            int match[5] = { 0,1,2,6,7 };
            int half[5] = { 3,4,5,6,7 };
            int extra_time[5] = { 8,9,10,6,7 };
            int extra_time_half[5] = { 11,12,13,6,7 };
            int pre_decider[5] = { 8,9,10,6,7 };
            int shootout[5] = { 14,15,16,17,18 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["half"] = half;
            indices["extra time"] = extra_time;
            indices["extra time half"] = extra_time_half;
            indices["pre-decider"] = pre_decider;
            indices["shootout"] = shootout;
            valid_fields = { "match","half","extra time","extra time half","shootout" };
            header = { "MW","ML","MD","HW","HL","HD","GS","GA","ETW","ETL","ETD","ETHW","ETHL","ETHD","SOW","SOL","SOD","PGS","PGA" };
            used = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "softball") { // Softball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
            int decider[4] = { 5,6,-1,-1 };
            int game[5] = { 0,1,-1,5,6 };
            int inning[5] = { 2,3,4,5,6 };
            int hits[5] = { -1,-1,-1,7,8 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["inning"] = inning;
            indices["hits"] = hits;
            valid_fields = { "game","inning","hits" };
            header = { "GW","GL","IW","IL","ID","RS","RA","H","HA" };
            used = { false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "table tennis") { // Table Tennis: [MW,ML,GW,GL,PW,PL]
            int decider[4] = { 2,3,-1,-1 };
            int match[5] = { 0,1,-1,2,3 };
            int game[5] = { 2,3,-1,4,5 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["game"] = game;
            valid_fields = { "match","game" };
            header = { "MW","ML","GW","GL","PW","PL" };
            used = { false,false,false,false,false,false };
        }
        else if (sport == "tennis") { // Tennis: [MW,ML,SW,SL,GW,GL,TW,TL]
            int decider[4] = { 2,3,-1,-1 };
            int match[5] = { 0,1,-1,2,3 };
            int set[5] = { 2,3,-1,4,5 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["set"] = set;
            valid_fields = { "match","set" };
            header = { "MW","ML","SW","SL","GW","GL","TW","TL" };
            used = { false,false,false,false,false,false,false,false };
        }
        else if (sport == "ultimate frisbee") { // Ultimate Frisbee: [GW,GL,HW,HL,HD,QW,QL,QD,GS,GA,OTW,OTL,OTD]
            int decider[4] = { 8,9,-1,-1 };
            int game[5] = { 0,1,-1,8,9 };
            int half[5] = { 2,3,4,8,9 };
            int quarter[5] = { 5,6,7,8,9 };
            int overtime[5] = { 10,11,12,8,9 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["half"] = half;
            indices["quarter"] = quarter;
            indices["overtime"] = overtime;
            valid_fields = { "game","half","quarter","overtime" };
            header = { "GW","GL","HW","HL","HD","QW","QL","QD","GS","GA","OTW","OTL","OTD" };
            used = { false,false,false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "volleyball") { // Volleyball: [MW,ML,SW,SL,PW,PL]
            int decider[4] = { 2,3,-1,-1 };
            int match[5] = { 0,1,-1,2,3 };
            int set[5] = { 2,3,-1,4,5 };
            indices["decider"] = decider;
            indices["match"] = match;
            indices["set"] = set;
            valid_fields = { "match","set" };
            header = { "MW","ML","SW","SL","PW","PL" };
            used = { false,false,false,false,false,false };
        }
        else if (sport == "water polo") { // Water Polo: [GW,GL,QW,QL,QD,GS,GA,OTW,OTL,OTD,SOW,SOL,SOD,PGS,PGA]
            int decider[4] = { 5,6,13,14 };
            int game[5] = { 0,1,-1,5,6 };
            int quarter[5] = { 2,3,4,5,6 };
            int overtime[5] = { 7,8,9,5,6 };
            int shootout[5] = { 10,11,12,13,14 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["quarter"] = quarter;
            indices["overtime"] = overtime;
            indices["shootout"] = shootout;
            valid_fields = { "game","quarter","overtime","shootout" };
            header = { "GW","GL","QW","QL","QD","GS","GA","OTW","OTL","OTD","SOW","SOL","SOD","PGS","PGA" };
            used = { false,false,false,false,false,false,false,false,false,false,false,false,false,false,false };
        }
        else if (sport == "wiffleball") { // Wiffleball: [GW,GL,IW,IL,ID,RS,RA,H,HA]
            int decider[4] = { 5,6,-1,-1 };
            int game[5] = { 0,1,-1,5,6 };
            int inning[5] = { 2,3,4,5,6 };
            int hits[5] = { -1,-1,-1,7,8 };
            indices["decider"] = decider;
            indices["game"] = game;
            indices["inning"] = inning;
            indices["hits"] = hits;
            valid_fields = { "game","inning","hits" };
            header = { "GW","GL","IW","IL","ID","RS","RA","H","HA" };
            used = { false,false,false,false,false,false,false,false,false };
        }
        else {
            cout << "ERROR: sport not recognized" << endl;
            valid = false;
        }
    }
    string filename;
    ifstream matches;
    valid = false;
    // loop until user gives valid csv file
    while (!valid) {
        // ask user for csv file name
        cout << "Enter file name: ";
        cin >> filename;
        // trim filename
        filename = trim(filename);
        // check if file is csv
        if (filename.substr(filename.length() - 4, 4) == ".csv") {
            matches.open(filename);
        }
        else {
            cout << "ERROR: " << filename << " is not a csv file" << endl;
            continue;
        }
        // check if file exists
        if (!matches) {
            matches.close();
            cout << "ERROR: " << filename << " does not exist" << endl;
            continue;
        }
        // Validate entire file before processing
        if (validate(matches, filename, valid_fields)) {
            valid = true;
        }
        else {
            matches.close();
        }
    }
    // reset reader to top
    matches.clear();
    matches.seekg(0);
    // create vars
    map<string, vector<int>> stats;
    vector<string> fields;
    bool first = true;
    bool draw = (sport == "bowling" || sport == "boxing" || sport == "football" || sport == "handball" || sport == "soccer") ? true : false;
    bool winleft = false;
    string line;
    string flag;
    string name;
    // run stat for each match
    while (getline(matches, line)) {
        if (line.length()) {
            // create a stream for the line
            stringstream match(rcsvtrim(ltrim(line)));
            // get and trim flag
            getline(match, flag, ',');
            flag = trim(flag);
            // check for type of line
            if (!flag.length() || flag == "*") { // match
                stat(stats, indices, fields, used, match, sport, (flag.length() ? true : false), draw, winleft);
            }
            else if (first || flag == "h" || flag == "H") { // header
                // getline twice to skip the columns
                getline(match, name, ',');
                // check whether the first uses winner
                winleft = (upper(trim(name)) == "WINNER") ? true : false;
                // skip second name column
                getline(match, name, ',');
                // get field types
                fields = fieldtypes(match, valid_fields);
                // set first to false
                first = false;
            }
        }
    }
    // get names
    vector<string> names;
    for (pair<string, vector<int>> player : stats) {
        names.push_back(player.first);
    }
    // sort names alphabetically case-insensitive
    sort(names.begin(), names.end(), [](string a, string b) -> bool {
        a = upper(trim(a));
        b = upper(trim(b));
        int c = 0;
        int l = a.length() < b.length() ? a.length() : b.length();
        while (c < l && a[c] == b[c]) {
            c++;
        }
        if (c == l) {
            return a.length() < b.length();
        }
        return a[c] < b[c];
        });
    // write into csv file
    ofstream csv;
    string row;
    csv.open("stats.csv");
    int n = -1;
    while (n == -1 || n < names.size()) {
        if (n != -1) {
            cout << names[n] << ": ";
        }
        // initialize a row string
        row = n == -1 ? "Name," : names[n] + ",";
        // add all used fields to the row
        for (int col = 0; col < (n == -1 ? header.size() : stats[names[n]].size()); col++) {
            if (used[col]) {
                if (n != -1) {
                    cout << stats[names[n]][col] << " ";
                }
                row += (n == -1 ? header[col] + "," : to_string(stats[names[n]][col]) + ",");
            }
        }
        cout << endl;
        // delete the last comma
        row.pop_back();
        // create a new line
        row += "\n";
        // add row to csv file
        csv << row;
        // increment n
        n++;
    }
    // close csv file
    csv.close();
    // TODO: display stats at the end
    return 0;
}