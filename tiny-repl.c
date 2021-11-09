#include <stdio.h>

// ----------------------------------------------------------------------------

#define BUFSIZE      256

#define END_LOOP      -1
#define GOTO_NEXT      0

#define CYAN(str) ("\x1b[36m" str "\x1b[0m")

// ----------------------------------------------------------------------------

int VerifyLength(const char* str)
{
    int strCount; for(strCount = 0; str[strCount] != '\0'; ++strCount);
    return ++strCount;
}

// ----------------------------------------------------------------------------

int Compare(const char* str1, const char* str2)
{
    if(VerifyLength(str1) != VerifyLength(str2)) {
        return 0;
    }

    for(int i = 0; str1[i] != '\0'; i++) {
        if(str1[i] != str2[i]) {
            return 0;
        }
    }

    return 1;
}

// ----------------------------------------------------------------------------

void HandleCommand1(char* buffer)
{
    printf(CYAN("   %s"), buffer);
}

// ----------------------------------------------------------------------------

void HandleCommand2(char* buffer)
{
    printf("   %s", buffer);
}

// ----------------------------------------------------------------------------

void HandleCommand3(char* buffer)
{
    printf("   different %s", buffer);
}

// ----------------------------------------------------------------------------

void HandleFallback(char* buffer)
{
    printf(CYAN("   ERROR: Unrecognized instruction! <Buffer: %s>"), buffer);
}

// ----------------------------------------------------------------------------

int ProcessInstruction(char* cmd, char* buffer)
{
    if(Compare(cmd, "quit")) {
        return END_LOOP;
    }

    if (Compare(cmd, "command1")) {
        HandleCommand1(buffer);
    } else if (Compare(cmd, "command2")) {
        HandleCommand2(buffer);
    } else if (Compare(cmd, "command3")) {
        HandleCommand3(buffer);
    } else {
        HandleFallback(buffer);
    }

    return GOTO_NEXT;
}

// ----------------------------------------------------------------------------

int ReadInstruction()
{
    char buffer[BUFSIZE];

    printf(CYAN(">> "));
    fgets(buffer, BUFSIZE, stdin);

    if(buffer[0] == '\n' || buffer[0] == '\0') {
        return GOTO_NEXT;
    }

    int bufLen = VerifyLength(buffer);
    int nullCharPos = bufLen - 1;
    buffer[nullCharPos - 1] = '\0';

    char cmd[32];
    sscanf(buffer, "%s", cmd);

    int returnCode = ProcessInstruction(cmd, buffer);
    if(returnCode != END_LOOP) {
        printf("\n");
    }

    return returnCode;
}

// ----------------------------------------------------------------------------

int main()
{
    while(ReadInstruction() != END_LOOP);
    return 0;
}

// ----------------------------------------------------------------------------
