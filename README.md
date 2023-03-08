### Team B10
- Graphics View & Behaviour: Rio Evrard
- Text View & Comamnds: Antoine Bauer
- Pathfinder & UI: Kerem Okyay
    - there are two weights to adjust:
        1. heuristic weight for chebychev distance.
        2. path weight to penalize diagonals.

Known issues:
- Bug in autoplay, sometimes the game crashes due to the order in which resources are cleared when a game is won or lost
- Animations of attacking are very short becasue of subsequent die/poison/victory animation
- Text view for large maze does not look aligned due to large indexes. This only occurs when displaying the indexes (disabled by default, enable with the SHOW_INDEX preprocessor indication)
- Win message shown when starting a game after a previous one. This is becasue of order in which resources are cleared


