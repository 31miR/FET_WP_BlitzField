# About the project
This is a project that's a part of Windows Programming course at Faculty of Electrical Engineering, University of Tuzla.
The task is to make an app/game using WINAPI.

# About the app
This is a top down fighting game where you can jump and slash with your character. There are 4 levels in it, and you can
finish all of them in about 15 minutes.\
To control your character:
- W/A/S/D - move top/left/down/right
- SPACE - slash
- LEFT MOUSE CLICK - dash to cursor (or as close as possible).\
Every level you finish for the first time gives you a point that you can use to level up your character.

# What's in this repository
The repository contains only the code required for compiling this project (assuming you are compiling on windows). The resources/ directory
is not in this repo and the game will not work properly without it (however, I cannot push the resource files because of copyright reasons).
> I might add the resource files in the future when I change them (the bitmaps and music) to something I've made, or something that's not copyrighted.

# Where are all the commits?
The project code, that was written with a colleague, was not inside the git repo [oops]. Hence, it was just copied when it worked.

# How to build?
Currently, the easiest way to build the project is by using some IDE. Codeblocks project file (.cbp) has been added to the repo so if you have codeblocks you can compile from there.
However, you do need a database (game_data.db) and resources/ in order for the app to work properly.\
game_data.db is already provided but you cannot clear it as the delete option for profiles is not implemented in the game. Hence, if you wish to reset the scores, you will need to paste a new game_data.db over the original. You can find the clean .db file inside the clean_db_file directory.
