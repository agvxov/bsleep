#ifndef CONFIG_H
#define CONFIG_H

/* List of color options:
			COLOR_BLACK
			COLOR_RED
			COLOR_GREEN
			COLOR_YELLOW
			COLOR_BLUE
			COLOR_MAGENTA
			COLOR_CYAN
			COLOR_WHITE
			-1				// for transparent (only works if that is your default terminal background)
*/

#define FG			COLOR_WHITE
#define BG			COLOR_BLACK
#define BORDER_FG	COLOR_WHITE
#define BORDER_BG	COLOR_BLACK
#define COUNTER_FG	COLOR_WHITE
#define COUNTER_BG	COLOR_BLACK
#define HELP_FG		COLOR_WHITE
#define HELF_BG		COLOR_BLACK
#define HELF_BG_BG	COLOR_BLACK

/* Other options:
			A_NORMAL			: Normal display (no highlight)
			A_UNDERLINE			: Underlining
			A_REVERSE			: Reverse video
			A_BLINK				: Blinking
			A_BOLD				: Extra bright or bold
			A_STANDOUT			: Best highlighting mode of the terminal.
	NOTE: you can specify more than one by separating the options by a '|' sign.
		{ A_BLINK | A_BOLD }
*/
#define SCR_A		A_NORMAL
#define BORDER_A	A_NORMAL
#define COUNTER_A	A_NORMAL
#define HELP_A		A_NORMAL

#endif
