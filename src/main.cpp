#include <stdio.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <getopt.h>
#include <ncurses.h>
#include <thread>
#include "font.h"
#include "tui.h"

#define NAME "bsleep"

using namespace std;

const char help_msg[] =
NAME " <options> [-e <args>] : invoke UNIX sleep in cooler way than usual\n"
"	-h             : print help message and quit\n"
"	-p             : start paused\n"
"	-s <int>       : add seconds to the countdown\n"
"	-m <int>       : add minutes to the countdown\n"
"	-H <int>       : add hours to the countdown\n"
"	-e <args>      : exec <args> on 0\n"
;
time_t start_time,
		stop_time,
		end_time;
time_t oridiff = 0;
char** execve_args = NULL;
bool running;
bool counting = true;
int sig = 0;

void opts(int argc, char* argv[]);
bool init();
void input(const char &i);
void print_time(time_t t);
[[ noreturn ]] void quit(int sig);
inline void tstart(){
	start_time = time(NULL);
	end_time = start_time + oridiff;
};
auto quitreq_handler = [](int sig_){
	sig = sig_;
	running = false;
};

signed main(int argc, char* argv[]){
	opts(argc, argv);
	running = init();

	thread thget_input([](){
		while(running){
			input(getch());
		}
	});

	const struct timespec delay = { .tv_nsec = 850000 };
	while(running){
		if(do_redraw){
			redraw();
			do_redraw = false;
		}
		if(counting){
			start_time = time(NULL);
			time_t dt = (time_t)difftime(end_time, start_time);
			if(dt < 0){
				running = false;
				break;
			}
			print_time(dt);
		}
		print_help(counting);
		nanosleep(&delay, NULL);
	}

	thget_input.join();

	quit(sig);
}

void opts(int argc, char* argv[]){
	char c;
	while((c = getopt(argc, argv, "phH:m:s:e"), c) != -1){
		putc(c, stdout);
		switch(c){
			case 'h':
				puts(help_msg);
				exit(0);
			case 'p':
				counting = false;
				break;
			case 'H':
				oridiff += atoi(optarg)*60*60;
				break;
			case 'm':
				oridiff += atoi(optarg)*60;
				break;
			case 's':
				oridiff += atoi(optarg);
				break;
			case 'e':
				execve_args = argv + optind;
				break;
			case '?':
				exit(1);
		}
	}
}

bool init(){
	// ### Signals ###
	signal(SIGWINCH, sigwinch_handler);
	signal(SIGINT, quitreq_handler);
	signal(SIGQUIT, quitreq_handler);
	signal(SIGSEGV, quitreq_handler);

	// ### Ncurses ###
	if(not tui_init()){ return false; }

	// ### Timer ###
	tstart();

	return true;
}
[[ noreturn ]] void quit(int sig){
	endwin();
	if(execve_args){
		execvpe(execve_args[0], execve_args, NULL);
	}

	exit(sig);
}

void input(const char &i){
	switch(i){
		case 'h':
			tstart();
			break;
		case 'j':
			if(counting){
				stop_time = time(NULL);
				counting = false;
			}
			break;
		case 'k':
			if(not counting){
				start_time = time(NULL);
				end_time = start_time + (time_t)difftime(end_time, stop_time);
				counting = true;
			}
			break;
		case 'l':
			quitreq_handler(0);
			break;
		case 'u':
			execve_args = NULL;
			quitreq_handler(0);
			break;
	}
}
