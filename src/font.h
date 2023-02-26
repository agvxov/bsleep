#include <string.h>
#include <stdlib.h>

#define FONT_WIDTH 6	/*(sizeof("  __  ")-1)*/
#define FONT_HEIGHT 4
const char* const font[] = {
				"   _  "
				"  (_) "
				"   _  "
				"  (_) "
				,
				"  __  "
				" /  \\ "
				"| () |"
				" \\__/ "
				,
				"   _  "
				"  / | "
				"  | | "
				"  |_| "
				,
				"  ___ "
				" |_  )"
				"  / / "
				" /___|"
				,
				"  ____"
				" |__ /"
				"  |_ \\"
				" |___/"
				,
				" _ _  "
				"| | | "
				"|_  _|"
				"  |_| "
				,
				"  ___ "
				" | __|"
				" |__ \\"
				" |___/"
				,
				"   __ "
				"  / / "
				" / _ \\"
				" \\___/"
				,
				" ____ "
				"|__  |"
				"  / / "
				" /_/  "
				,
				"  ___ "
				" ( _ )"
				" / _ \\"
				" \\___/"
				,
				"  ___ "
				" / _ \\"
				" \\_, /"
				"  /_/ "
};

size_t font_hash(char i){
	switch(i){
		case '0' ... '9':
			return i-47; 
		default:
			return 0;
	}
}

char* to_banner(const char* const input){
	const size_t input_len = strlen(input);
	const size_t line_size = (FONT_WIDTH*input_len)+1;
	const size_t ret_size = line_size*FONT_HEIGHT;
	char* ret = (char*)malloc(ret_size);

	for(int i = 0; i < FONT_HEIGHT; i++){
		for(int h = 0; h < input_len; h++){
			memcpy(ret + FONT_WIDTH*h + line_size*i,
					font[font_hash(input[h])]+(i*FONT_WIDTH),
					FONT_WIDTH
			);
		}
		memset(ret + line_size-1 + line_size*i, '\n', 1);
	}
	ret[ret_size-1] = '\00';

	return ret;
}
