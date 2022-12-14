#define AUTOSHIFT_ON 0
#define AUTOSHIFT_DIGIT 1
#define AUTOSHIFT_LETTER 2
#define AUTOSHIFT_SPECIAL_CHARACTER 3


#define OUTPUT_PRESSED 2
#define AUTOSHIFT_CAPABLE 3
#define ON_TAP_OSM 4
#define ON_HOLD_OSM 5
#define ON_DOUBLETAP_OSM 6
#define ON_TAPHOLD_OSM 7
#define DOUBLETAP_ENABLED 8
#define TAPHOLD_ENABLED 9
#define HOLD_ENABLED 10

#define COMMAND_KEY constPow(2, 11)

#define AUTOSHIFT_ON_MASK constPow(2, AUTOSHIFT_ON)
#define AUTOSHIFT_DIGIT_MASK constPow(2, AUTOSHIFT_DIGIT)
#define AUTOSHIFT_LETTER_MASK constPow(2, AUTOSHIFT_LETTER)
#define AUTOSHIFT_SPECIAL_CHARACTER_MASK constPow(2,AUTOSHIFT_SPECIAL_CHARACTER)

#define OUTPUT_PRESSED_MASK  	        constPow(2, OUTPUT_PRESSED   )
#define AUTOSHIFT_CAPABLE_MASK	        constPow(2, AUTOSHIFT_CAPABLE)
#define ON_TAP_OSM_MASK  				constPow(2, ON_TAP_OSM       )
#define ON_HOLD_OSM_MASK  				constPow(2, ON_HOLD_OSM      )
#define ON_DOUBLETAP_OSM_MASK  			constPow(2, ON_DOUBLETAP_OSM )
#define ON_TAPHOLD_OSM_MASK  			constPow(2, ON_TAPHOLD_OSM   )
#define DOUBLETAP_ENABLED_MASK  		constPow(2, DOUBLETAP_ENABLED)
#define TAPHOLD_ENABLED_MASK  			constPow(2, TAPHOLD_ENABLED  )
#define HOLD_ENABLED_MASK  				constPow(2, HOLD_ENABLED     )
#define KEY_STATE 						7
#define TAP_OUTPUT_PRESSED_MASK  		0 + OUTPUT_PRESSED_MASK
#define HOLD_OUTPUT_PRESSED_MASK  		1 + OUTPUT_PRESSED_MASK
#define DOUBLETAP_OUTPUT_PRESSED_MASK  	2 + OUTPUT_PRESSED_MASK
#define TAPHOLD_OUTPUT_PRESSED_MASK  	3 + OUTPUT_PRESSED_MASK
#define SINGLE_PRESS_MASK  				1
#define SINGLE_RELEASE_MASK  			2
#define DOUBLE_PRESS_MASK  				3

