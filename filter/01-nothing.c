#include <stdio.h>
#include <sys/prctl.h>
#include <linux/seccomp.h>
#include <unistd.h>

int main()
{
    printf("step 1: unrestricted\n");

    // Enable filtering
    prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT);
    printf("step 2: only 'read', 'write', '_exit' and 'sigreturn' syscalls\n");

    // Redirect stderr to stdout
    dup2(1, 2);
    printf("step 3: !! YOU SHOULD NOT SEE ME !!\n");

    // Success (well, not so in this case...)
    return 0;
}
