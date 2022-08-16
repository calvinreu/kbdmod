autoshift example and mod remaping for laptop example
```yaml
# my zsa autoshift timing
TIMING:
    #longer timing due to slower key releases on laptop
    TAP_MILLISEC: 170

MAPPINGS:
    ### remap of modifier keys ###

    #use alt as thumb punctuation
  - KEY: KEY_LEFTALT
    TAP: KEY_E
    HOLD: KEY_LEFTALT
    
    #make caps key compose key without losing caps functionallity
    #scrolllock since it does not exist on my keyboard and therefore is a free modifier compatible with xkb compose
  - KEY: KEY_CAPSLOCK
    TAP: KEY_SCROLLLOCK
    HOLD: KEY_LEFTMETA
    #use shift as shift and capslock
  - KEY: KEY_LEFTSHIFT
    TAP: KEY_CAPSLOCK
    HOLD: KEY_LEFTSHIFT
    #remap right alt for layout switch
  - KEY: KEY_RIGHTALT
    TAP: KEY_MENU
    HOLD: KEY_RIGHTALT

  - KEY: KEY_RIGHTSHIFT
    TAP: KEY_COFFEE # just because there is a key named coffee
    HOLD: KEY_RIGHTSHIFT

    #unused key if i need another one
    ## ctrl remap possible

    ## semicolon return for developing need to create code to support it first
    #- KEY: KEY_ENTER
    #    TAP: KEY_ENTER
    #    HOLD: [ KEY_SEMICOLON, KEY_ENTER ]

    ### autoshift keys ###
	#swap so on dvorak little fingers dont have to be moved
  - KEY: KEY_W
    TAP: KEY_P
    HOLD: [KEY_LEFTSHIFT ,KEY_P]

  - KEY: KEY_E
    TAP: KEY_SLASH
    HOLD: [KEY_LEFTSHIFT, KEY_SLASH]

  - KEY: KEY_SLASH
    TAP: KEY_E
    HOLD: [KEY_LEFTSHIFT, KEY_E]

  - KEY: KEY_P
    TAP: KEY_W
    HOLD: [KEY_LEFTSHIFT, KEY_W]

  - KEY: KEY_A
    TAP: KEY_A
    HOLD: [KEY_LEFTSHIFT, KEY_A]

  - KEY: KEY_B
    TAP: KEY_B
    HOLD: [KEY_LEFTSHIFT, KEY_B]

  - KEY: KEY_C
    TAP: KEY_C
    HOLD: [KEY_LEFTSHIFT, KEY_C]

  - KEY: KEY_D
    TAP: KEY_D
    HOLD: [KEY_LEFTSHIFT, KEY_D]

  - KEY: KEY_F
    TAP: KEY_F
    HOLD: [KEY_LEFTSHIFT, KEY_F]

  - KEY: KEY_G
    TAP: KEY_G
    HOLD: [KEY_LEFTSHIFT, KEY_G]

  - KEY: KEY_H
    TAP: KEY_H
    HOLD: [KEY_LEFTSHIFT, KEY_H]

  - KEY: KEY_I
    TAP: KEY_I
    HOLD: [KEY_LEFTSHIFT, KEY_I]

  - KEY: KEY_J
    TAP: KEY_J
    HOLD: [KEY_LEFTSHIFT, KEY_J]

  - KEY: KEY_K
    TAP: KEY_K
    HOLD: [KEY_LEFTSHIFT, KEY_K]

  - KEY: KEY_L
    TAP: KEY_L
    HOLD: [KEY_LEFTSHIFT, KEY_L]

  - KEY: KEY_M
    TAP: KEY_M
    HOLD: [KEY_LEFTSHIFT, KEY_M]

  - KEY: KEY_N
    TAP: KEY_N
    HOLD: [KEY_LEFTSHIFT, KEY_N]

  - KEY: KEY_O
    TAP: KEY_O
    HOLD: [KEY_LEFTSHIFT, KEY_O]

  - KEY: KEY_Q
    TAP: KEY_Q
    HOLD: [KEY_LEFTSHIFT, KEY_Q]

  - KEY: KEY_R
    TAP: KEY_R
    HOLD: [KEY_LEFTSHIFT, KEY_R]

  - KEY: KEY_S
    TAP: KEY_S
    HOLD: [KEY_LEFTSHIFT, KEY_S]

  - KEY: KEY_T
    TAP: KEY_T
    HOLD: [KEY_LEFTSHIFT, KEY_T]

  - KEY: KEY_U
    TAP: KEY_U
    HOLD: [KEY_LEFTSHIFT, KEY_U]

  - KEY: KEY_V
    TAP: KEY_V
    HOLD: [KEY_LEFTSHIFT, KEY_V]

  - KEY: KEY_X
    TAP: KEY_X
    HOLD: [KEY_LEFTSHIFT, KEY_X]

  - KEY: KEY_Y
    TAP: KEY_Y
    HOLD: [KEY_LEFTSHIFT, KEY_Y]

  - KEY: KEY_Z
    TAP: KEY_Z
    HOLD: [KEY_LEFTSHIFT, KEY_Z]
 
  - KEY: KEY_1
    TAP: KEY_1
    HOLD: [KEY_LEFTSHIFT, KEY_1]
 
  - KEY: KEY_2
    TAP: KEY_2
    HOLD: [KEY_LEFTSHIFT, KEY_2]

  - KEY: KEY_3
    TAP: KEY_3
    HOLD: [KEY_LEFTSHIFT, KEY_3]
 
  - KEY: KEY_4
    TAP: KEY_4
    HOLD: [KEY_LEFTSHIFT, KEY_4]
 
  - KEY: KEY_5
    TAP: KEY_5
    HOLD: [KEY_LEFTSHIFT, KEY_5]
 
  - KEY: KEY_6
    TAP: KEY_6
    HOLD: [KEY_LEFTSHIFT, KEY_6]
 
  - KEY: KEY_7
    TAP: KEY_7
    HOLD: [KEY_LEFTSHIFT, KEY_7]
 
  - KEY: KEY_8
    TAP: KEY_8
    HOLD: [KEY_LEFTSHIFT, KEY_8]
 
  - KEY: KEY_9
    TAP: KEY_9
    HOLD: [KEY_LEFTSHIFT, KEY_9]
     
  - KEY: KEY_0
    TAP: KEY_0
    HOLD: [KEY_LEFTSHIFT, KEY_0]
      
  - KEY: KEY_GRAVE
    TAP: KEY_GRAVE
    HOLD: [KEY_LEFTSHIFT, KEY_GRAVE]
      
  - KEY: KEY_APOSTROPHE
    TAP: KEY_APOSTROPHE
    HOLD: [KEY_LEFTSHIFT, KEY_APOSTROPHE]
      
  - KEY: KEY_SEMICOLON
    TAP: KEY_SEMICOLON
    HOLD: [KEY_LEFTSHIFT, KEY_SEMICOLON]
      
  - KEY: KEY_BACKSLASH
    TAP: KEY_BACKSLASH
    HOLD: [KEY_LEFTSHIFT, KEY_BACKSLASH]
      
  - KEY: KEY_COMMA
    TAP: KEY_COMMA
    HOLD: [KEY_LEFTSHIFT, KEY_COMMA]
      
  - KEY: KEY_DOT
    TAP: KEY_DOT
    HOLD: [KEY_LEFTSHIFT, KEY_DOT]
      
  - KEY: KEY_MINUS
    TAP: KEY_MINUS
    HOLD: [KEY_LEFTSHIFT, KEY_MINUS]
      
  - KEY: KEY_EQUAL
    TAP: KEY_EQUAL
    HOLD: [KEY_LEFTSHIFT, KEY_EQUAL]
      
  - KEY: KEY_LEFTBRACE
    TAP: KEY_LEFTBRACE
    HOLD: [KEY_LEFTSHIFT, KEY_LEFTBRACE]
```
