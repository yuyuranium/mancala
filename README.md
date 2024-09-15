# mancala
Simple Mancala game and strategies written in C

## Game play
```
# chaotic vs. minimal_first

[Round 0]
                5     4     3     2     1     0   
              ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ 
        ┌───┐ │  4│ │  4│ │  4│ │  4│ │  4│ │  4│ ┌───┐ 
        │   │ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ │   │ 
chaotic │  0│                                     │  0│ minimal_first
─────── │   │ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ │   │ 
        └───┘ │  4│ │  4│ │  4│ │  4│ │  4│ │  4│ └───┘ 
              └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ 
                0     1     2     3     4     5   

>>> chaotic selects 3


[Round 1]
                5     4     3     2     1     0   
              ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ 
        ┌───┐ │  5│ │  5│ │  0│ │  4│ │  4│ │  4│ ┌───┐ 
        │   │ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ │   │ 
chaotic │  1│                                     │  0│ minimal_first
        │   │ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ │   │ ─────────────
        └───┘ │  5│ │  4│ │  4│ │  4│ │  4│ │  4│ └───┘ 
              └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ 
                0     1     2     3     4     5   

>>> minimal_first selects 1

...

                5     4     3     2     1     0   
              ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ 
        ┌───┐ │  0│ │  0│ │  0│ │  0│ │  0│ │  0│ ┌───┐ 
        │   │ └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ │   │ 
chaotic │ 18│                                     │ 30│ minimal_first
        │   │ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ ┌───┐ │   │ ═════════════
        └───┘ │  0│ │  0│ │  0│ │  0│ │  0│ │  0│ └───┘ 
              └───┘ └───┘ └───┘ └───┘ └───┘ └───┘ 
                0     1     2     3     4     5   

>>> The winner is minimal_first

```

### Symbols

- **Left/rightmost box:** the players' store
- **Numbers above/under the pocket:** the pocket index
- **Underline:** the active player of the round
- **Double underline:** the winner
