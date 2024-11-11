#!/usr/bin/python3

import os

def copy_file(file_path, outfile):
	# Check if it's a file (not a directory)
	if os.path.isfile(file_path):
		# Open and read the file
		with open(file_path, 'r') as infile:
			# Process and write the contents of the file
			for line in infile:
				# Write the line if it does not start with '/*'
				if not line.strip().startswith('#include') and not line.strip().startswith('# include') and not line.strip().startswith('/*') and not len(line.strip()) == 0:
					outfile.write(line)
				elif line == '\n':
					outfile.write(line)

def combine_files(input_directory, outfile):
	try:
		# Iterate over all files in the input directory
		for filename in os.listdir(input_directory):
			file_path = os.path.join(input_directory, filename)
			copy_file(file_path, outfile)
		
	except Exception as e:
		print(f'An error occurred: {e}')

def main():
	directories = [
		"srcs/array",
		"srcs/char",
		"srcs/ft_printf",
		"srcs/list",
		"srcs/math",
		"srcs/mem",
		"srcs/string",
		"srcs/write"
	]

	output_file = "libft.c"

	with open(output_file, 'a') as outfile:
		outfile.write("#ifdef LIBFT_IMPL\n\n")
		with open("include/libft.h", 'r') as infile:
			for line in infile:
				outfile.write(line)
		outfile.write('\n')
		with open("srcs/ft_printf/internal/_libft_printf.h", 'r') as infile:
			for line in infile:
				if not line.strip().startswith('#include') and not line.strip().startswith('# include') and not line.strip().startswith('/*') and not len(line.strip()) == 0:
					outfile.write(line)
		for directory in directories:
			combine_files(directory, outfile)
			print(f'Contents of {directory} files have been written to {output_file}')
		outfile.write("\n#endif // LIBFT_IMPL\n")

if __name__ == "__main__":
	main()
