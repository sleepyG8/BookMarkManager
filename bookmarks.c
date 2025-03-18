#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

struct bookmarkmgr
{
    char *sitename;
    char *url;
};


int main(int argc, char *argv[]) {
char *option = argv[1];
char *sitename = argv[2];
char *url = argv[3];
if (argc < 2 ) {
    printf("Usage:\n ./bookmarkmgr.exe create sitename url\n ./bookmarkmgr.exe read");
    return 1;
}
if (strcmp(argv[1], "create") == 0) {

HANDLE hfile = CreateFile("library", FILE_APPEND_DATA, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );

if (hfile == INVALID_HANDLE_VALUE) {
printf("Error creating file named library\n");

}
char data[256]; // I will make Dynamic eventually because this is able to be overflowed at 256 bytes becuase of snprintf
DWORD byteswritten;
sprintf(data, "Site: %s\n url: %s\n", sitename, url);
BOOL result = WriteFile(hfile, data, strlen(data), &byteswritten, NULL);
if (!result){
    printf("Error writing to file\n");
} else {
    printf("Wrote to file");
}
CloseHandle(hfile);
return 0;
}

if (strcmp(argv[1], "Read")) {
char *buffer = (char *)malloc(250 * sizeof(char));
DWORD bytesread;
DWORD byteswritten;
HANDLE hfile = CreateFile("library", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

BOOL result = ReadFile(hfile, buffer, 250 - 1, &bytesread, NULL);

buffer[bytesread] = '\0';

if (!result) {
    printf("Error reading file");
} else {
    printf("BOOKMARKS:\n %s", buffer);
}
CloseHandle(hfile);
free(buffer);
}


return 0;
}
