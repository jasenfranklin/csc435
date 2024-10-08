
#include <stdio.h>
#include <usloss.h>
#include <phase1.h>
#include <string.h>    // for strcmp()

int XXp1(void *), XXp2(void *);

int tm_pid = -1;

int testcase_main()
{
    int status, pid1, kidpid;

    tm_pid = getpid();

    USLOSS_Console("testcase_main(): started\n");
    USLOSS_Console("EXPECTATION: main creates XXp1; XXp1 creates a pair of XXp2 procs; join() each parent with all its children.  (children are always higher priority than parents, in this testcase)\n");

    pid1 = spork("XXp1", XXp1, "XXp1", USLOSS_MIN_STACK, 2);
    USLOSS_Console("Phase 1A TEMPORARY HACK: Manually switching to XXp1()\n");
    TEMP_switchTo(pid1);
    USLOSS_Console("testcase_main(): after spork of child %d -- you should not see this until XXp1, and both of the XXp2 processes, have completed.\n", pid1);

    USLOSS_Console("testcase_main(): performing join\n");
    kidpid = join(&status);
    if (kidpid != pid1 || status != 3)
    {
        USLOSS_Console("ERROR: kidpid %d status %d\n", kidpid,status);
        USLOSS_Halt(1);
    }
    USLOSS_Console("testcase_main(): exit status for child %d is %d\n", kidpid, status); 

    return 0;
}

int xxp1_pid = -1;

int XXp1(void *arg)
{
    int kidpid;
    int status;

    xxp1_pid = getpid();

    USLOSS_Console("XXp1(): started\n");
    USLOSS_Console("XXp1(): arg = '%s'\n", arg);
    if (strcmp(arg,"XXp1") != 0)
    {
        USLOSS_Console("ERROR: wrong process argument.\n");
        USLOSS_Halt(1);
    }

    USLOSS_Console("XXp1(): executing spork of first child\n");
    kidpid = spork("XXp2", XXp2, "XXp2", USLOSS_MIN_STACK, 1);
    USLOSS_Console("Phase 1A TEMPORARY HACK: Manually switching to the first XXp2()\n");
    TEMP_switchTo(kidpid);
    USLOSS_Console("XXp1(): spork of first child returned pid = %d -- you should not see this until the first XXp2 process has completed.\n", kidpid);

    USLOSS_Console("XXp1(): executing spork of second child -- this happens after the first XXp2 process has completed, but before we've done a join() on it.\n");
    kidpid = spork("XXp2", XXp2, "XXp2", USLOSS_MIN_STACK, 1);
    USLOSS_Console("Phase 1A TEMPORARY HACK: Manually switching to the first XXp2()\n");
    TEMP_switchTo(kidpid);
    USLOSS_Console("XXp1(): spork of second child returned pid = %d -- you should not see this until the second XXp2 process has completed.\n", kidpid);

    kidpid = join(&status);
    if (status != 5)
    {
        USLOSS_Console("ERROR: kidpid %d status %d\n", kidpid,status);
        USLOSS_Halt(1);
    }
    USLOSS_Console("XXp1(): first join returned kidpid = %d, status = %d\n", kidpid, status);

    kidpid = join(&status);
    if (status != 5)
    {
        USLOSS_Console("ERROR: kidpid %d status %d\n", kidpid,status);
        USLOSS_Halt(1);
    }
    USLOSS_Console("XXp1(): second join returned kidpid = %d, status = %d\n", kidpid, status);

    quit_phase_1a(3, tm_pid);
}

int XXp2(void *arg)
{
    USLOSS_Console("XXp2(): started\n");
    USLOSS_Console("XXp2(): arg = '%s'\n", arg);
    if (strcmp(arg,"XXp2") != 0)
    {
        USLOSS_Console("ERROR: wrong process argument.\n");
        USLOSS_Halt(1);
    }

    USLOSS_Console("XXp2(): This XXp2() process will now quit().\n");
    quit_phase_1a(5, xxp1_pid);
}

