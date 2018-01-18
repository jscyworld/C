#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>

// Global variables
#define buf_size 1024
static char history[buf_size][buf_size];
static int counter = 0;
sigset_t bm;
struct sigaction def;
static char **cmds, input[buf_size];

// Pre-defined variables
#define col 11
#define PIPE 12
#define ARG 13
#define SEMICOLON 14

//#define buf_size 1024

// Handling errors
void fatal(char *s) {
	perror(s);
}

// Functions
int Process_A(char *);
int Process_B(char *);
int Process_C(char *);
int Process_D(char *);
void Process_E(char *, int, int);
void Execute_A(char *);
void Execute_B(int);

int start_input(void);
void myPipe(char *);
char* stringss(char *);
int tokenizer(const char *, const char *, char ***);
int temp_History(char *);

int main(void) {
	int count;

	strcat(input," [MYSHELL]:");
	strcat(input, getenv("PWD"));

	while (1) {
		if ((count = start_input()) == 0)
            continue;
		Execute_B(count);
	}
}

// Handling Redirection command '<'
int Process_A(char *command) {
    int fd;
    char *redirect;
    
    if ((redirect = strchr(command, '<')) == NULL)
        return 0;
    
    *redirect = 0;
    redirect = strtok(redirect + 1, " ");
    
    if (redirect == NULL)
        return 0;
    
    if ((fd = open(redirect, O_RDONLY)) == -1)
        return -1;
    
    if (dup2(fd, STDIN_FILENO) == -1)  {
        close(fd);
        return -1;
    }
    
    return close(fd);
}

// Handling Redirection command '>'
int Process_B(char *command) {
    int fd;
    char *red;
    
    if ((red = strchr(command, '>')) == NULL)
        return 0;
    *red = 0;
    red = strtok(red + 1, " ");
    if (red == NULL)
        return 0;
    if ((fd = open(red, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR)) == -1)
        return -1;
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        return -1;
    }
    return close(fd);
}

// Handling Redirection command '>>'
int Process_C(char *command) {
    int fd;
    char *red;
    
    if ((red = strstr(command, ">>")) == NULL)
        return 0;
    
    *red = 0;
    red = strtok(red + 2, " ");
    
    if (red == NULL) {
        return 0;
    }
    if ((fd = open(red, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR)) == -1)
        return -1;
    
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return -1;
    }
    
    return close(fd);
}

// Handling Redirection command '>!'
int Process_D(char *command) {
    int fd;
    char *red;
    
    if ((red = strstr(command, ">!")) == NULL)
        return 0;
    
    *red = 0;
    red = strtok(red + 2, " ");
    if (red == NULL) {
        return 0;
    }
    
    if ((fd = open(red, O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
        return -1;
    
    if (dup2(fd, STDOUT_FILENO) == -1) {
        close(fd);
        return -1;
    }
    
    return close(fd);
}

// Handling Redirection command
void Process_E(char *Command, int fd_in, int fd_out) {
    int num4;
    char **arg1;
    char *red_1, *red_2;
    red_1 = strchr(Command,'<');
    red_2 = strchr(Command,'>');
    if(fd_in && red_1 != NULL && fd_out && red_2 != NULL && red_1 > red_2) {
        if (Process_A(Command) == -1) {
            fatal("Fail");
            exit(1);
            
        }
        
        fd_in = 0;
    }
    
    if (fd_out&&Process_C(Command) == -1) {
        fatal("Fail");
        exit(1);
    } else if(fd_out&&Process_D(Command) == -1) {
        fatal("Fail");
        exit(1);
    } else if(fd_out&&Process_B(Command) == -1) {
        fatal("Fail");
        exit(1);
    } else if (fd_in && (Process_A(Command) == -1)) {
        fatal("Fail");
        exit(1);
    } else if ((num4=tokenizer(Command, " ", &arg1)) <= 0) {
        fatal("Fail");
        exit(1);
    } else {
        execvp(arg1[0], arg1);
        fatal("Fail");
    }
    exit(1);
}

// Execute
void Execute_A(char * Command)
{
    char cwd[buf_size];
    int counter3, BG;
    char **argu;
    char *Bkk;
    int i;
    pid_t pid;
    
    if ((Bkk = strrchr(Command,'&')) == NULL)
        BG = 0;
    else {
        BG = 1;
        *Bkk = 0;
    }
    
    counter3 = tokenizer(Command," ",&argu);
    
    if (strcmp(argu[0],"history") == 0) {
        for(i = 0 ; i < counter ; i++)
            printf("%6d  %s\n",i+1, history[i]);
        return;
    } else if((strcmp(argu[0],"cd") == 0) && counter3 == 2) {
            if(chdir(argu[1]) < 0) {
                fatal("Fail");
            } else {
                sprintf(input,"%c",' ');
                strcat(input,"[MYSHELL]:");
                getcwd(cwd,buf_size);
                strcat(input,cwd);
            }
            return;
    } else if (sigprocmask(SIG_BLOCK, &bm, NULL) == -1)
                fatal("Fail");
    
    if((pid = fork()) < 0)
        fatal("Fail");
    else if(pid == 0) {
        if ((sigaction(SIGINT, &def, NULL) == -1) ||
            (sigaction(SIGQUIT, &def, NULL) == -1) ||
            (sigprocmask(SIG_UNBLOCK, &bm, NULL) == -1)) {
            fatal("Fail");
            return ;
        }
    
        if(BG) {
            printf("[%d]\n",getpid());
        }
        myPipe(Command);
        return;
    } else {
        if (sigprocmask(SIG_UNBLOCK, &bm, NULL) == -1)
            fatal("Fail");
        
        if (!BG)
            waitpid(pid, NULL, 0);
        
        while (waitpid(-1, NULL, WNOHANG) > 0);
    }
    return;
}

// Execute
void Execute_B(int Counter) {
    int counter4;
    for (counter4 = 0 ; counter4 < Counter ; counter4++) {
        Execute_A(cmds[counter4]);
    }
}

// Handling input
int start_input(void) {
    char inputbuf[buf_size];
    int ctr;
    
    printf("%s >",input);
    if (fgets(inputbuf, buf_size, stdin) == NULL)
        return 0;
    else {
        ctr = (int)strlen(inputbuf);
        if (inputbuf[ctr-1] == '\n')
            inputbuf[ctr-1] = 0;
        
        strcpy(history[counter++],inputbuf);
        return (int)tokenizer(inputbuf,";",&cmds);
    }
}

// Handling Pipe
void myPipe(char *command) {
    pid_t pid;
    char buf[buf_size];
    char **process_list;
    int counter2, i, num5;
    int fd[2];
    
    counter2 = tokenizer(command, "|", &process_list);
    if ((num5 = temp_History(command)) >= 0) {
        strcpy(buf,history[num5]);
        printf("\n%s\n",buf);
        myPipe(buf);
    } else {
        if (counter2 <= 0) {
            fatal("Fail");
            exit(1);
        }
        
        for (i = 0 ; i < counter2 - 1 ; i++) {
            if (pipe(fd) < 0 ) {
                fatal("Fail");
                exit(1);
            } else if ((pid = fork()) < 0) {
                fatal("Fail");
                exit(1);
            } else if (pid == 0) {
                if (dup2(fd[0], STDIN_FILENO) == -1) {
                    fatal("Fail");
                    exit(1);
                }
                
                if (close(fd[0]) || close(fd[1])) {
                    fatal("Fail");
                    exit(1);
                }
            } else {
                if (dup2(fd[1], STDOUT_FILENO) == -1) {
                    fatal("Fail");
                    exit(1);
                }
                
                if (close(fd[0]) || close(fd[1])) {
                    fatal("Fail");
                    exit(1);
                }
                
                Process_E(process_list[i], i == 0, 0);
            }
        }
        Process_E(process_list[i], i == 0, 1);
        exit(1);
    }
    return;
}

// Handling strings
char* stringss(char * command) {
    int stringss_len, i;
    stringss_len = (int)strlen(command);
    
    for (i = stringss_len-1; i >= 0 ; i--) {
        if (command[i] == ' ' || command[i] == '\t' || command[i] == '\0')
            command[i] = '\0';
        else
            break;
    }
    
    stringss_len = (int)strlen(command);
    for (i = 0 ; i < stringss_len ; i++) {
        if (command[i] == ' ' || command[i] == '\t' || command[i] == '\0')
            command[i] = '\0';
        else
            break;
    }
    
    return (&command[i]);
}

// Tokenizer
int tokenizer(const char *string1, const char *string2, char ***string3) {
    int num, num2, i;
    const char *temp;
    char *token;
    
    if ((string1 == NULL) || (string2 == NULL) || (string3 == NULL)) {
        errno = EINVAL;
        return -1;
    }
    
    *string3 = NULL;
    temp = string1 + strspn(string1, string2);
    if ((token = (char*)malloc(strlen(temp) + 1)) == NULL)
        return -1;
    
    strcpy(token, temp);
    num2 = 0;
    
    if (strtok(token, string2) != NULL)
        for (num2 = 1; strtok(NULL, string2) != NULL; num2++) ;
    
    if ((*string3 = (char **)malloc((num2 + 1)*sizeof(char *))) == NULL) {
        num = errno;
        free(token);
        errno = num;
        return -1;
    }
    
    if (num2 == 0) {
        free(token);
    } else {
        strcpy(token, temp);
        **string3 = strtok(token, string2);
        for (i = 1; i < num2; i++) {
            *((*string3) + i) = stringss(strtok(NULL, string2));
        }
    }
    
    *((*string3) + num2) = NULL;
    return (int)num2;
}

// Handling History
int temp_History(char * command) {
    int num3;
    if (command[0] == '!')
        num3 = atoi(&command[1]);
    else
        num3 = 0;
    return num3-1;
}
