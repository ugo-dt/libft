#!/usr/bin/python3

import os

def copy_file(file_path, outfile):
	if os.path.isfile(file_path):
		with open(file_path, 'r') as infile:
			for line in infile:
				if not line.strip().startswith('#include') and not line.strip().startswith('# include') and not len(line.strip()) == 0:
					outfile.write(line)
				elif line == '\n':
					outfile.write(line)

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
	directories = [
		"srcs/argparse",
		"srcs/array",
		"srcs/basic_string",
		"srcs/char",
		"srcs/ft_printf/internal",
		"srcs/ft_printf",
		"srcs/get_next_line",
		"srcs/list",
		"srcs/math",
		"srcs/mem",
		"srcs/string",
		"srcs/write"
	]

	output_file = "single_header/libft.h"

	with open(output_file, 'w') as outfile:

		with open("include/libft/libft.h", 'r') as infile:
			for line in infile:
				outfile.write(line)
		outfile.write('\n')
		
		outfile.write("#ifdef LIBFT_IMPL\n")
		outfile.write("#ifndef LIBFT_IMPL_INCLUDED\n")
		outfile.write("#define LIBFT_IMPL_INCLUDED\n\n")

		with open("include/libft/internal/_libft_printf.h", 'r') as infile:
			last_newline = False
			for line in infile:
				if not line.strip().startswith('#include') and not line.strip().startswith('# include'):
					if line == "\n":
						if not last_newline:
							outfile.write(line)
						last_newline = True
					else:
						outfile.write(line)
						last_newline = False

		for directory in directories:
			combine_files(directory, outfile)
			print(f'Contents of {directory} files have been written to {output_file}')
		outfile.write("\n#endif // LIBFT_IMPL_INCLUDED")
		outfile.write("\n#endif // LIBFT_IMPL\n")

if __name__ == "__main__":
	main()
