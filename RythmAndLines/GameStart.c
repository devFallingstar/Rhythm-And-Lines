#define MAX_X 1920
#define MAX_Y 1080

#include <stdio.h>
#include <process.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <GL\wglext.h>
#include <Windows.h>
#include <string.h>
#include "MusicSelect.h"

void setVSync(int sync);

int main(int argc, const char * argv[]) {
	int code = 9988;

	printf("Enter the code of music : ");
	scanf("%d", &code);

	if (code > 0)
	{
		setVSync(0);
		glutInit(&argc, (char**)argv);
		musicStart(code);
	}
	
	return 0;
}

void setVSync(int sync)
{
	typedef BOOL(APIENTRY *PFNWGLSWAPINTERVALPROC)(int);
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT = 0;

	char *extensions = (char*)glGetString(GL_EXTENSIONS);
	
	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");

	if (wglSwapIntervalEXT) {
		wglSwapIntervalEXT(sync);
	}
}