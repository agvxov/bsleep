#include "../const/config.h"

#define MAX_MID_H FONT_HEIGHT
#define MAX_MID_W FONT_WIDTH*8

const char** HELP_MSG[] = {
	(char const *[]){"Start [k]", "Reset [h]", "End [l]", "Abort [u]", NULL},
	(char const *[]){"Stop [j]", "Reset [h]", "End [l]", "Abort [u]", NULL}
};
enum color_pairs{
	COLOR_PAIR_STDSCR = 1,
	COLOR_PAIR_BORDER,
	COLOR_PAIR_COUNTER,
	COLOR_PAIR_HELP,
	COLOR_PAIR_HELP_BG
};

WINDOW* wmain;
WINDOW* wmid;
WINDOW* whelpbar;
int LINES, COLS;
bool do_redraw = false;

void print_help(bool counting = false);
void print_time(time_t t);
void redraw();

bool tui_init(){
	initscr();
	noecho();
	curs_set(0);
	halfdelay(1);

	start_color();
	use_default_colors();
	init_pair(COLOR_PAIR_STDSCR, FG, BG);
	init_pair(COLOR_PAIR_BORDER, BORDER_FG, BORDER_BG);
	init_pair(COLOR_PAIR_COUNTER, COUNTER_FG, COUNTER_BG);
	init_pair(COLOR_PAIR_HELP, HELP_FG, HELF_BG);
	init_pair(COLOR_PAIR_HELP_BG, COLOR_WHITE, HELF_BG_BG);
	wbkgd(stdscr, COLOR_PAIR(COLOR_PAIR_STDSCR) | SCR_A);

	redraw();

	return true;
}

void sigwinch_handler(int sig){
	(void)sig;
	do_redraw = true;
}

void redraw(){
	if(do_redraw){
		delwin(wmain);
		delwin(wmid);
		delwin(whelpbar);
		endwin();
		refresh();
		clear();
	}

	//if(LINES < MAX_MID_H || COLS < MAX_MID_W){ return false; }

	const int wmain_y_beg = (LINES-(MAX_MID_H+2))/2;
	const int wmain_x_beg = (COLS-(MAX_MID_W+2))/2;

	wmain = newwin(MAX_MID_H+2,
					MAX_MID_W+2,
					wmain_y_beg,
					wmain_x_beg);
	wmid = subwin(wmain,
					MAX_MID_H,
					MAX_MID_W,
					wmain_y_beg+1,
					wmain_x_beg+1);
	whelpbar = newwin(1, COLS, LINES-1, 0);
	refresh();

	wattron(wmain, COLOR_PAIR(COLOR_PAIR_BORDER) | BORDER_A);
	box(wmain, 0, 0);
	wrefresh(wmain);
	print_help();
}

void print_help(bool counting){
	werase(whelpbar);
	wbkgd(whelpbar, COLOR_PAIR(COLOR_PAIR_HELP_BG));
	wmove(whelpbar, 0, 0);
	for(int i = 0; HELP_MSG[counting][i] != NULL; i++){
		waddch(whelpbar, ' ');
		wattron(whelpbar, COLOR_PAIR(COLOR_PAIR_HELP) | HELP_A);
		waddstr(whelpbar, HELP_MSG[counting][i]);
		wattroff(whelpbar, COLOR_PAIR(COLOR_PAIR_HELP) | HELP_A);
	}
	wrefresh(whelpbar);
}

void print_time(time_t t){
	const char tstr_template[] = "%H:%M:%S";
	char tstr[sizeof(tstr_template)];
	char* tbanner;

	tm* dt = gmtime(&t);
	strftime(tstr, sizeof(tstr_template), tstr_template, dt);
	tbanner = to_banner(tstr);

	wattron(wmid, COLOR_PAIR(COLOR_PAIR_COUNTER) | COUNTER_A);

	char buf[MAX_MID_W+1];
	for(int i = 0; i < MAX_MID_H; i++){
		strncpy(buf, tbanner + i*(MAX_MID_W+1), MAX_MID_W);
		mvwprintw(wmid, i, 0, "%s", buf);
	}
	wrefresh(wmid);

	free(tbanner);
}
