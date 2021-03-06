#define _XOPEN_SOURCE 1		/* required under GLIBC for nftw() */
#define _XOPEN_SOURCE_EXTENDED 1	/* same */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <ftw.h>
#include <limits.h>
#include <unistd.h>

#define SPARE_FDS  5

int process(const char *file, const struct stat *sb, int flag, struct FTW *s);

void usage(const char *name)
{
	fprintf(stderr, "usage: %s [-c] directory ...\n", name);
	exit(1);
}

int main(int argc, char *argv[])
{
	int i, c, nfds;
	int errors = 0;
	int flags = FTW_PHYS;
	char start[PATH_MAX], finish[PATH_MAX];

	while ((c = getopt(argc, argv, "c")) != -1) {
		switch (c) {
		case 'c':
			flags |= FTW_CHDIR;
			break;
		default:
			usage(argv[0]);
			break;
		}
	}

	if (optind == argc)
		usage(argv[0]);

	getcwd(start, sizeof(start));

	nfds = getdtablesize() - SPARE_FDS;	/* leave some spare descriptors */
	for (i = optind; i < argc; i++) {
		if (nftw(argv[i], process, nfds, flags) != 0) {
			fprintf(stderr, "%s: %s: stopped early\n",
				argv[0], argv[i]);
			errors++;
		}
	}

	if ((flags & FTW_CHDIR) != 0) {
		getcwd(finish, sizeof(finish));
		printf("Starting dir: %s\n", start);
		printf("Finishing dir: %s\n", finish);
	}

	return (errors != 0);
}

int process(const char *file, const struct stat *sb, int flag, struct FTW *s)
{
	int retval = 0;
	const char *name = file + s->base;

	printf("%*s", s->level * 4, "");	/* indent over */

	switch (flag) {
	case FTW_F:
		printf("%s (file)\n", name);
		break;
	case FTW_D:
		printf("%s (directory)\n", name);
		break;
	case FTW_DNR:
		printf("%s (unreadable directory)\n", name);
		break;
	case FTW_SL:
		printf("%s (symbolic link)\n", name);
		break;
	case FTW_NS:
		printf("%s (stat failed): %s\n", name, strerror(errno));
		break;
	case FTW_DP:
	case FTW_SLN:
		printf("%s: FTW_DP or FTW_SLN: can't happen!\n", name);
		retval = 1;
		break;
	default:
		printf("%s: unknown flag %d: can't happen!\n", name, flag);
		retval = 1;
		break;
	}

	return retval;
}
