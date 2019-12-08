#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <libgen.h>

void print_usage(const char *p_name);

int main(int argc, char *argv[]) {
	int opt, user_no = 0;
	unsigned int checksum = 0;
	long f_size = 0;
	FILE *in_file;

	unsigned char r_data;

	opterr = 0;
	while ((opt = getopt(argc, argv, "u:")) != -1) {
		switch(opt) {
			case 'u':
				user_no = atoi(optarg);
				break;
			default:
				print_usage(argv[0]);
				break;
		}
	}

	if (optind >= argc) {
		print_usage(argv[0]);
		exit(EXIT_FAILURE);
    }

	in_file = fopen(argv[optind], "rb");
	if (!in_file) {
		perror(argv[optind]);
		exit(EXIT_FAILURE);
	}

	// Get size
	fseek(in_file, 0L, SEEK_END);
	f_size = ftell(in_file);
	fseek(in_file, 0L, SEEK_SET);

	// The checksum is two pairs of HEX values:
	// The first one is the low-byte of the length of the file being uploaded.
	// Because CP/M files are normally saved in blocks of 128, this is normally
	// "80" or "00", but doesn't need to be.
	// The second one is the low-byte of the SUM of each byte being uploaded.
	// The checksum is very simple, but more than adequate for confirming a simple
	// data transfer, as it can detect missing, extra or changed characters.

	fprintf(stdout, "A:DOWNLOAD %s\r\nU%u\r\n:", basename(argv[optind]), user_no);
	while (fread(&r_data, 1, 1, in_file) == 1) {
		fprintf(stdout, "%.02X", r_data);
		checksum += r_data;
	}
	fprintf(stdout, ">%.04X\r\n", (unsigned short)((checksum & 0xFF) | ((f_size & 0xFF) << 8)));


	fclose(in_file);


	return 0;
}

void print_usage(const char *p_name) {
	fprintf(stderr, "Usage: %s [-u user_no] file\n", p_name);
}
