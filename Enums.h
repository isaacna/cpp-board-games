#pragma once
#include <string>

//enums for various error messages
enum er_mes {
	success = 0,
	wrong_num_args = -1,
	file_open_fail = -2,
	no_line_in_stream = -3,
	no_extract = -4,
	pieces_dont_fit = -5,
	no_pieces = -6,
	user_quit = -7,
	game_drawn = -8,
	out_of_bounds = -9,
	null_pointer = -10,
	not_null_ptr = -11,
	user_restore = -12,
	wrong_num_pieces = -13,
	bad_piece_in_file = -14
};



std::string er_to_string(er_mes);
std::string to_lowcase(std::string);
enum index{program_name, game_type};

