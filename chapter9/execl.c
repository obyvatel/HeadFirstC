#include <stdio.h>
#include <unistd.h>

int main()
{
	execl("c:\\Windows\\notepad.exe", "c:\\Windows\\notepad.exe", "readme1.txt", NULL);
	//execlp("notepad.exe", "notepad.exe", "readme2.txt", NULL);
	return 0;
}