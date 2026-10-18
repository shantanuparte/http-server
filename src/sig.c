
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <stddef.h>

#include "sig.h"


static void handlesig(int signo)
{
    (void)signo;


    int saved_errno = errno;

    // Reap all children that have already there
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
        // Keep collecting  child processes
    }

    errno = saved_errno;
}

int set_sig_handler()
{
    struct sigaction sa = {0};

    sa.sa_handler = handlesig;


    sigemptyset(&sa.sa_mask);


    sa.sa_flags = SA_RESTART;

    if (sigaction(SIGCHLD, &sa, NULL) == -1)
    {
        return -1;
    }

    return 0;
}
