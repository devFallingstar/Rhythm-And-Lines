#include <stdio.h>
#include "MusicSelect.h"

int main(int argc, const char * argv[]) {
	int code = 0;

	printf("Enter the code of music : ");
	scanf("%d", &code);
	if (code > 0)
	{
		musicStart(code);
	}

	glutInit(&argc, (char**)argv);

	return 0;
}