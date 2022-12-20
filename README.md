# StatCalc
This application analyzes inputted match/game scores and outputs a overall statline for each player/team. The **input** file must be a `csv` file. The program will write the calculated statistics into a file named `stats.csv`. **NOTE:** If an existing file in the same directory as `StatCalc.exe` is named `stats.csv`, the program may **overwrite** any data in this file. Below is a list of supported sports with their corresponding valid fields as well as instructions and guidelines on how to properly run and use the application.
## Input Requirements
1. Must be a `csv` file
2. Top row must be a header that meets the following requirements:
	1. The first column must be labeled "Flag"
	2. The second and third columns must have one of these 2 keywords: "Player" or "Team". Alternatively, the second and third columns can be labeled as "Winner" and "Loser" respectively. **NOTE:** Doing so will result in any tied matches counting as a **win** for the player/team in the "Winner" column and a **loss** for the player/team in the "Loser" column if the selected sport **does not allow draws**.
	3. There must be one or more subsequent columns and they must contain any of the valid fields from the selected sport.
3. There must be one or more rows after the header containing correctly formatted match/game scores that meet the following requirements:
	1. The second and third columns must have a player or team name.
	2. Each scoring column must follow the following format "<Player 1/Team 1/Winner Score>-<Player 2/Team 2/Loser Score>"
4. Every row must either have an empty flag field or valid flag field. See below for more details on flag use cases.
## Flag Use Cases
- " " (empty): **must be a match/game** row, will automatically calculate statistics for row.
- "*": **must be a match/game** row, will manually calculate statistics for row based on user input.
- "C"/"c": commented row, will disregard.
- "H"/"h": **must follow input requirements 2.ii and 2.iii**, will only apply to subsequent match/game rows below.
## Supported Sports & Valid Fields
- **Badminton** 
	- *match* i.t.o. *games*
	- *game* i.t.o. *points*
- **Baseball**
	- *game* i.t.o. *runs*
	- *inning* i.t.o. *runs*
	- *hits* i.t.o. *hits*
- **Basketball**
	- *game* i.t.o. *points*
	- *quarter* i.t.o. *points*
	- *overtime* i.t.o. *points*
- **Bowling**
	- *game* i.t.o. *points*
	- *frame* i.t.o. *pins*
- **Boxing**
	- *match* i.t.o. *points*
	- *round* i.t.o. *points*
	- *knockouts* i.t.o. *knockouts*
- **Darts**
	- *match* i.t.o. *sets*
	- *set* i.t.o. *legs*
- **Fencing**
	- *match* i.t.o. *points*
	- *round* i.t.o. *points*
	- *sudden death* i.t.o. *points*
- **Football**
	- *game* i.t.o. *points*
	- *quarter* i.t.o. *points*
	- *overtime* i.t.o. *points*
- **Handball**
	- *match* i.t.o. *goals*
	- *half* i.t.o. *goals*
	- *overtime* i.t.o. *goals*
	- *overtime half* i.t.o. *goals*
	- *shootout* i.t.o. *goals*
- **Hockey**
	- *game* i.t.o. *goals*
	- *period* i.t.o. *goals*
	- *overtime* i.t.o. *goals*
	- *shootout* i.t.o. *goals*
- **Kickball**
	- *game* i.t.o. *runs*
	- *inning* i.t.o. *runs*
	- *kicks* i.t.o. *kicks*
- **Pickleball**
	- *match* i.t.o. *games*
	- *game* i.t.o. *points*
- **Soccer**
	- *match* i.t.o. *goals*
	- *half* i.t.o. *goals*
	- *extra time* i.t.o. *goals*
	- *extra time half* i.t.o. *goals*
	- *shootout* i.t.o. *goals*
- **Softball**
	- *game* i.t.o. *runs*
	- *innning* i.t.o. *runs*
	- *hits* i.t.o. *hits*
- **Table Tennis**
	- *match* i.t.o. *games*
	- *game* i.t.o. *points*
- **Tennis**
	- *match* i.t.o. *sets*
	- *set* i.t.o. *games*
- **Ultimate Frisbee**
	- *game* i.t.o. *goals*
	- *half* i.t.o. *goals*
	- *quarter* i.t.o. *goals*
	- *overtime* i.t.o. *goals*
- **Volleyball**
	- *match* i.t.o. *sets*
	- *set* i.t.o. *points*
- **Water Polo**
	- *game* i.t.o. *goals*
	- *quarter* i.t.o. *goals*
	- *overtime* i.t.o. *goals*
	- *shootout* i.t.o. *goals*
- **Wiffleball**
	- *game* i.t.o. *runs*
	- *inning* i.t.o. *runs*
	- *hits* i.t.o. *hits*

**i.t.o.* - in terms of
## Running the Program
1. Download the ZIP file from this repository.
2. Extract the contents of the ZIP file into a directory.
3. Navigate to the directory of the extracted content. 
4. Ensure there is a `csv` file in this directory that follows the input requirements listed above.
5. Double-click the file titled `StatCalc.exe`.
6. When prompted, type in a valid sport, then press `Enter`. 
7. When prompted, type in the name of the `csv` file you wish to run the program on, then press `Enter`.
8. Program will output into a file titled `stats.csv` in the same directory as `StatCalc.exe`.
## Future Updates
- Statistical Calculation for tiebreaks in Tennis and score, strikes, and spares in Bowling.
- Row and Column tracker to be displayed when prompting user.
