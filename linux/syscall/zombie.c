/*
 * Making a zombie process
 */

#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t child_pid;

	/* Create a child process. */
	child_pid = fork();
	if (child_pid > 0) {
		/* This is the parent process. Sleep for a minute. */
		sleep(60);
	} else {
		/* This is the child process. */
		exit(0);
	}

	return 0;
}
