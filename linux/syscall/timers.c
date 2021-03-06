/*
 * Demonstrate iterval timers.
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

/*
 * handle SIGALRM
 */
void handler(int signo)
{
	static const char msg[] = "\n*** Timer expired, you lose ***\n";

	assert(signo == SIGALRM);

	write(2, msg, sizeof(msg) - 1);
	exit(1);
}

/*
 * set up timer, read data with timeout
 */
int main(void)
{
	struct itimerval tval;
	char string[BUFSIZ];

	timerclear(&tval.it_interval);	/* zero interval means to reset of timer */
	timerclear(&tval.it_value);

	tval.it_value.tv_sec = 10;	/* 10 second timeout */

	(void)signal(SIGALRM, handler);

	printf("You have ten seconds to enter\n"
	       "you name, rank, and serial number: ");
	(void)setitimer(ITIMER_REAL, &tval, NULL);

	if (fgets(string, sizeof(string), stdin) != NULL) {
		(void)setitimer(ITIMER_REAL, NULL, NULL);	/* turn off timer */
		/* process reset of data, diagnostic print for illustration */
		printf("I'm glad you are being cooperative.\n");
	} else {
		printf("\nEOF, eh? We won't give up so easily!\n");
	}

	exit(0);
}
