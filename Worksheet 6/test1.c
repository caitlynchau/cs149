#include "apue.h"

int
main(void)
{
	pid_t	pid;

	printf("hello world (pid:%d)\n", (int) getpid());

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* parent */
		fprintf(stdout, "Parent (pid:%d)\n\n", (int) getpid());
		sleep(2);
		exit(2);				/* terminate with exit status 2 */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* first child */
		fprintf(stdout, "First Child (pid:%d)\n\n", (int) getpid());
		sleep(4);
		abort();				/* terminate with core dump */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* second child */
		fprintf(stdout, "Second child (pid:%d)\n\n", (int) getpid());
		execl("/bin/dd", "dd", "if=/etc/passwd", "of=/dev/null", NULL);
		exit(7);				/* shouldn't get here */
	}

	if ((pid = fork()) < 0)
		err_sys("fork error");
	else if (pid != 0) {		/* third child */
		fprintf(stdout, "Third child (pid:%d)\n\n", (int) getpid());
		sleep(8);
		exit(0);				/* normal exit */
	}

	sleep(6);					/* fourth child */
	fprintf(stdout, "Fourth child (pid:%d)\n\n", (int) getpid());
	kill(getpid(), SIGKILL);	/* terminate w/signal, no core dump */
	exit(6);					/* shouldn't get here */
}
