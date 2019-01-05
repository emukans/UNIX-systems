#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <limits.h>
#include <string.h>

#define MAXLINE 200
#define MAXARG 20

extern char **environ;
void env(void)
{
    int i;
    for (i = 0; environ[i] != NULL; i++)
    {
        printf("%s\n", environ[i]);
    }
}

void exitsh(int status)
{
    _exit(status);
}

void execute(char *arg[])
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid > 0)
    {
        wait(&status);
    }
    else if (pid == 0)
    {
        execvp(arg[0], arg);
        printf("Komanda nav atrasta\n");
        exitsh(0);
    }
    else
    {
        printf("Kluda fork() sistemas izsaukuma\n");
    }
}

int startsWith(const char *str, const char *pre)
{
    return strncmp(pre, str, strlen(pre)) == 0;
}

int main(void)
{
    char cmd[MAXLINE];
    char cwd[PATH_MAX];
    char *cmdp;
    char *av[MAXARG];
    char *directory;
    int i;

    getcwd(cwd, sizeof(cwd));

    while (1)
    {
        printf("$toyshell$: %s>", cwd);
        fgets(cmd, sizeof(cmd), stdin);
        if (strcmp(cmd, "env\n") == 0)
        {
            env();
        }
        else if (strcmp(cmd, "exit\n") == 0)
        {
            exitsh(0);
        }
        else if (startsWith(cmd, "cd "))
        {
            cmdp = cmd;
            directory = strtok(cmdp, " \t\n");
            directory = strtok(NULL, " \t\n");
            chdir(directory);
            getcwd(cwd, sizeof(cwd));
        }
        else
        {
            cmdp = cmd;
            for (i = 0; i < MAXARG; i++)
            {
                av[i] = strtok(cmdp, " \t\n");
                cmdp = NULL;
            }
            execute(av);
        }
    }
    return (0);
}