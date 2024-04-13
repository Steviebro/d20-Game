# Optimizations TODO

## Multiple files:
- Change (almost) all vectors to hashmaps to simplify/shorten code and for constant search times
- Move Character creation from GameManager to ObjectEditor


## ObjectEditor:
### All:
- Repair input validation
### Character:
- Add enemy and friendly creation
### Map:
- Use new functions in Map for validity


## Map:
- Rename class to Map
- change display of enemies on map to unique identifiers
- Add bool functions for checking validity of positions


## Character:
- Improve UI for character display
- Add a mini character display for showing level, health and experience


## Combat:
- Improve user interactiveness of combat to make it more rewarding for the user


## GameManager
- Fix game crash when exiting map boundary
- Shorten code for movement by using dx/dy instead of a case for each direction
- Include friendlies in the turn order

