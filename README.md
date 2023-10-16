# 21_maze

School21 Maze project

## Maze

- Open maze from .txt file (see src/examples)
- Generate perfect maze (no loops & no closed areas) of a given size using Eller's algorithm
- Find solution between two points in perfect maze
- Save genereated maze to .txt

## Cave

- Open cave from .txt file (see src/examples)
- Generate cave of a given size with given probabilty of alive cells
- Simulating cave generation using celluar machine with given life and death limits (from 1 to 7).
  `` If "live" cells are surrounded by "live" cells, the number of which is less than the "death" limit,
     they "die". In the same way, if "dead" cells are next to "live" cells, the number of which is greater
     than the "birth" limit, they become "live". ``
