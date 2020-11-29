# EasyDice
EasyDice is a CLI application that allows the user to quickly and easily roll a large number of dice.
Furthermore, it can also filter the rolls that are higher than a given number or count the rolls and display the value.

## Installation
### Windows
Download the .exe file

### Linux
Compile the given C-code using:
`insert gcc command here`

## Usage
Navigate to the folder where the program is downloaded.
In the command line, type:
`easy roll [number]d[type] [+{bonus}] [-dc={filter}] [-c]`
example: `easy roll 5d20 +5 -dc=15`
- `[number]` number of dice to roll
- `[type]` number of faces a single die has
- `[+{bonus}]` a bonus applied once per roll
- `[-dc={filter}]` removes rolls that are (including bonus) lower than this number
- `[-c]` count the total of all the rolls (after bonus and filtering) and display it