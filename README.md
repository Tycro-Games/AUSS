# An Unrealistic Spaceship Simulator
A top-down shooter made using this [template](https://www.3dgep.com/wp-content/uploads/2019/08/TheTemplate.zip).

This project is a top-down shooter where bullets bounce off the edges of obstacles, edges of the map and shields of enemies. The game is structured in waves of enemies where the player needs to clean the current wave to go to the next one. An interesting feature of the project is that a game designer(or a player) could modify the json files of the project with little to no programming experience, thus, changing the waves of enemies as well as the properties of enemies themselves such as health, speed damage and so on.

There are different types of enemies, the wave system uses weight and a list of possible enemies. Every enemy has a specific weight, so a wave could have many combinations of enemies depending on the list. This makes it flexible and gives spawning a little randomization.
## Players can change the waves of enemies by modifying [this](json/enemy_waves.json) json file.
This library is used for parsing the json files:https://github.com/nlohmann/json
### Guideline for modifying the enemy waves:
- every wave needs to have:
  - a weight that is a positive integer
  - array of enemy types from the [list](https://github.com/OneBogdan01/TopDownShooter/edit/master/README.md#enemy-types) below
- one can also validate the [enemy waves](json/enemy_waves.json) using this [link](https://www.jsonschemavalidator.net/s/9zhf3M4W) or any other json schema validators, use the [schema](json/schema.json) from the project 
  - ***Note that this may still result in an invalid json file if the enemy types have typos***
  - ***If the game does not start and does not throw any error, there is most probably a problem parsing the json files into the game***
- the code does not add duplicates to the current wave when it does the parsing, when it encounters a duplicate in the same wave it will skip over it

## Enemy Types:
- Runner
- Hoarder
- Shooter

## Playable on [itch](https://tycro-games.itch.io/auss)

# Diagram of the code
![](https://github.com/OneBogdan01/TopDownShooter/blob/master/Diagram/Game.png)

# License
This work is licensed under a
[Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License][cc-by-nc-sa].

[![CC BY-NC-SA 4.0][cc-by-nc-sa-image]][cc-by-nc-sa]

[cc-by-nc-sa]: http://creativecommons.org/licenses/by-nc-sa/4.0/
[cc-by-nc-sa-image]: https://licensebuttons.net/l/by-nc-sa/4.0/88x31.png
[cc-by-nc-sa-shield]: https://img.shields.io/badge/License-CC%20BY--NC--SA%204.0-lightgrey.svg
