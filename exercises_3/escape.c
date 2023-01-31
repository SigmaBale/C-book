/* Write a function escape(s,t) that converts characters like newline and tab into
visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a
function for the other direction as well, converting escape sequences into the real characters. */
#include<stdio.h>
#define SIZE 1000

void escape(char buffer[], char s[]);
void unescape(char buffer[], char s[]);

int main()
{
    char buffer[SIZE];
    char string[] = "This is a test\\nWe will see \\\"if it\\\" will\\twork\\nas\\a\\bintended.\\r\\v\\n";
    unescape(buffer, string);
    printf("%s\n", string);
    printf("%s\n", buffer);
    return 0;
}

void escape(char buffer[], char s[])
{
    int i, j, c;

    i = j = 0;
    while((c = s[i++]) != '\0') {
        switch(c) {
            case '\a':
                buffer[j++] = '\\';
                buffer[j++] = 'a';
                break;
            case '\b':
                buffer[j++] = '\\';
                buffer[j++] = 'b';
                break;
            case '\f':
                buffer[j++] = '\\';
                buffer[j++] = 'f';
                break;
            case '\n':
                buffer[j++] = '\\';
                buffer[j++] = 'n';
                break;
            case '\r':
                buffer[j++] = '\\';
                buffer[j++] = 'r';
                break;
            case '\t':
                buffer[j++] = '\\';
                buffer[j++] = 't';
                break;
            case '\v':
                buffer[j++] = '\\';
                buffer[j++] = 'v';
                break;
            default:
                buffer[j++] = c;
                break;
        }
    }
    buffer[++j] = '\0';
    return;
}

void unescape(char buffer[], char s[])
{
    int i, j, c;

    i = j = 0;
    while((c = s[i]) != '\0') {
        switch(c) {
            case '\\':
                switch(s[++i]) {
                    case 'a':
                        buffer[j++] = '\a';
                        break;
                    case 'b':
                        buffer[j++] = '\b';
                        break;
                    case 'f':
                        buffer[j++] = '\f';
                        break;
                    case 'n':
                        buffer[j++] = '\n';
                        break;
                    case 'r':
                        buffer[j++] = '\r';
                        break;
                    case 't':
                        buffer[j++] = '\t';
                        break;
                    case 'v':
                        buffer[j++] = '\v';
                        break;
                    case '\'':
                        buffer[j++] = '\'';
                        break;
                    case '\\':
                        buffer[j++] = '\\';
                        break;
                    case '\"':
                        buffer[j++] = '\"';
                        break;
                    case '\?':
                        buffer[j++] = '\?';
                        break;
                    default:
                        buffer[j++] = '\\';
                        buffer[j++] = s[i];
                        break;
                }
                break;
            default:
                buffer[j++] = c;
                break;
        }
        ++i;
    }
    buffer[++j] = '\0';
    return;
}