#!/usr/bin/python3

import os

def copy_file(file_path, outfile):
	if os.path.isfile(file_path):
		with open(file_path, 'r') as infile:
			for line in infile:
				if not line.strip().startswith('#pragma') and not line.strip().startswith('#include') and not line.strip().startswith('# include') and not len(line) == 0:
					outfile.write(line)
				elif line == '\n':
					outfile.write(line)

def copy_header(file_path, outfile):
	with open(file_path, 'r') as infile:
		last_newline = False
		for line in infile:
			if not line.strip().startswith('#pragma') and not line.strip().startswith('#include') and not line.strip().startswith('# include'):
				if line == "\n":
					if not last_newline:
						outfile.write(line)
					last_newline = True
				else:
					outfile.write(line)
					last_newline = False
	print(f'Contents of {file_path} files have been written to {outfile.name}')

def combine_files(input_directory, outfile):
	try:
		# Iterate over all files in the input directory
		for filename in os.listdir(input_directory):
			if (str(filename).endswith('.c')):
				file_path = os.path.join(input_directory, filename)
				copy_file(file_path, outfile)
		
	except Exception as e:
		print(f'An error occurred: {e}')

def main():
	directories: list[str] = [
		"srcs/argparse",
		"srcs/array",
		"srcs/basic_string",
		"srcs/char",
		"srcs/fileparse",
		"srcs/ft_printf/internal",
		"srcs/ft_printf",
		"srcs/get_next_line",
		"srcs/list",
		"srcs/math",
		"srcs/memory",
		"srcs/string",
		"srcs/timer",
		"srcs/vector",
		"srcs/write"
	]
	additional_header_files: list[str] = [
		"include/libft/iterator.h",
		"include/libft/tester.h",
	]

	output_file = "single_header/libft/libft.h"

	with open(output_file, 'w') as outfile:
		with open("include/libft/libft.h", 'r') as infile:
			for line in infile:
				if not line.strip() == '#endif // LIBFT_H':
					outfile.write(line)

		for header_file in additional_header_files:
			copy_header(header_file, outfile)
		
		outfile.write('#endif // LIBFT_H\n')

		outfile.write('\n')
		outfile.write("#ifdef LIBFT_IMPL\n")
		outfile.write("#ifndef LIBFT_IMPL_INCLUDED\n")
		outfile.write("#define LIBFT_IMPL_INCLUDED\n\n")

		copy_header("include/libft/internal/_libft_printf.h", outfile)

		for directory in directories:
			combine_files(directory, outfile)
			print(f'Contents of {directory} files have been written to {output_file}')
		outfile.write("\n#endif // LIBFT_IMPL_INCLUDED")
		outfile.write("\n#endif // LIBFT_IMPL\n")

if __name__ == "__main__":
	main()
