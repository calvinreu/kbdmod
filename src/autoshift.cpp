#include "autoshift.h"

extern std::vector<mapping> keyMapBase;
extern uint8_t autoShift;

void autoshift_init(const KeyCode &code, TypeOutputConf *outputConf) {
	if (*outputConf & HOLD_ENABLED_MASK)
		return;

	if (autoShift & AUTOSHIFT_DIGIT_MASK && code >= KEY_1 && code <= KEY_0)
		*outputConf |= AUTOSHIFT_CAPABLE_MASK;

	if (autoShift & AUTOSHIFT_LETTER_MASK &&
		((code >= KEY_Q && code <= KEY_P) || (code >= KEY_A && code <= KEY_L) || (code >= KEY_Z && code <= KEY_M)))
		*outputConf |= AUTOSHIFT_CAPABLE_MASK;

	if (autoShift & AUTOSHIFT_SPECIAL_CHARACTER_MASK &&
	(code == KEY_MINUS || code == KEY_EQUAL || code == KEY_LEFTBRACE || code == KEY_RIGHTBRACE || (code >= KEY_COMMA && code <= KEY_SLASH)))
		*outputConf |= AUTOSHIFT_CAPABLE_MASK;
}

void enable_autoshift() {
	for (auto &it : keyMapBase) {
		if (it.key & AUTOSHIFT_CAPABLE_MASK)
			it.key |= HOLD_ENABLED_MASK;
	}
}

void disable_autoshift() {
	for (auto &it : keyMapBase) {
		if (it.key & AUTOSHIFT_CAPABLE_MASK)
			it.key &= ~HOLD_ENABLED_MASK;
	}
}

void toggle_autoshift() {
	if (autoShift)
		disable_autoshift();
	else
		enable_autoshift();
}
