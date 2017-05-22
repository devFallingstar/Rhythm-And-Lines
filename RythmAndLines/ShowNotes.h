#ifndef ShowNotes_h
#define ShowNotes_h

#include <stdio.h>
#include <stdlib.h>
#include <gl\glut.h>
#include <Windows.h>

void showNotes();
void getNotesGUI();
void printNote(int _id);
void printNoteGUI(int _id, int line);
void drawOneNote(int offsetX, int line);

#endif
