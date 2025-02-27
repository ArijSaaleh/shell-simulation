#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_COMMAND_LEN 1024
#define MAX_ARGS 100
#define HISTORY_SIZE 100

char *history[HISTORY_SIZE];
int history_count = 0;

// Function to add a command to history
void add_to_history(char *command) {
    if (history_count < HISTORY_SIZE) {
        history[history_count++] = strdup(command);
    } else {
        // Shift the history if full
        free(history[0]);
        for (int i = 1; i < HISTORY_SIZE; i++) {
            history[i - 1] = history[i];
        }
        history[HISTORY_SIZE - 1] = strdup(command);
    }
}

// Function to display history
void show_history() {
    for (int i = 0; i < history_count; i++) {
        printf("%d %s\n", i + 1, history[i]);
    }
}

// Function to print the shell prompt with color
void print_prompt() {
    printf("\033[1;32marijs-shell>\033[0m ");  // Green color prompt
}

// Function to read a line of input from the user
char *read_command() {
    char *command = malloc(MAX_COMMAND_LEN);
    if (!fgets(command, MAX_COMMAND_LEN, stdin)) {
        free(command);
        return NULL;
    }
    command[strcspn(command, "\n")] = 0; // Remove the newline character
    return command;
}

// Function to split the command into arguments
char **parse_command(char *command) {
    char **args = malloc(MAX_ARGS * sizeof(char*));
    char *token = strtok(command, " ");
    int i = 0;

    while (token != NULL && i < MAX_ARGS) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}

// Function to change directory
void change_directory(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "Expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("cd failed");
        }
    }
}

// Function to execute the command
void execute_command(char **args) {
    if (strcmp(args[0], "cd") == 0) {
        change_directory(args);
        return;
    }

    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    if (strcmp(args[0], "history") == 0) {
        show_history();
        return;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("Command execution failed");
        }
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        // Parent process
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}

int main() {
    char *command;
    char **args;

    while (1) {
        print_prompt();

        // Read command from the user
        command = read_command();
        if (command == NULL) {
            break;
        }

        // Add command to history
        add_to_history(command);

        // Parse the command
        args = parse_command(command);
        
        // Execute the command
        if (args[0] != NULL) {
            execute_command(args);
        }

        free(command);
        free(args);
    }

    return 0;
}

