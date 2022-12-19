# StatCalc
This application analyzes inputted match/game scores and outputs a overall statline for each player/team. The **input** file must be a `csv` file. The program will write the calculated statistics into a file named `stats.csv`. **NOTE:** If an existing file in the same directory as `StatCalc.exe` is named `stats.csv`, the program may **overwrite** any data in this file. Below is a list of supported sports with their corresponding valid fields as well as instructions and guidelines on how to properly run and use the application.
## Input Requirements
1. Must be a `csv` file
2. Top row must be a header that meets the following requirements:
	1. The first column must be labeled "Flag"
	2. The second and third columns must have one of these 2 keywords: "Player" or "Team". Alternatively, the second and third columns can be labeled as "Winner" and "Loser" respectively. **NOTE:** Doing so will result in any tied matches counting as a **win** for the player/team in the "Winner" column and a **loss** for the player/team in the "Loser" column if the selected sport **does not allow draws**.
	3. There must be one or more subsequent columns and they must contain any of the valid fields from the selected sport.
3.  There must be one or more rows after the header containing correctly formatted match/game scores.
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
