#ifndef MusicSelect_h
#define MusicSelect_h

#include <stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <Windows.h>

typedef struct {
	int timeslice;
	char noteId[10];
	int originIdx;
}TmpNote;

void musicStart(int id);
void initMainWindow();
void drawLines();
void reshapeMainWindow();
void displayMainWindow();
void timerMainWindow();
void keyboardMainWindow(unsigned char key, int x, int y);
void keyboardUpMainWindow(unsigned char key, int x, int y);
void highlightKey();

#endif
