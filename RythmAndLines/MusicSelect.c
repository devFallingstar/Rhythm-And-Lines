#define MAXSIZE 100

#include "MusicSelect.h"
#include "MusicPlayer.h"
#include "GlobalVariables.h"
#include "DataLoader.h"
#include "ShowNotes.h"
#include "NoteChecker.h"

extern int g_maxNotes;
extern char **g_dataStr;
extern MyNote *g_notes;

int keyPress[7] = { 0, };
int line=0;
TmpNote *myTmpNotes;

void musicStart(int id) {
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Rhythm And Lines - Evnas");

	glutDisplayFunc(displayMainWindow);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(keyboardMainWindow);
	glutKeyboardUpFunc(keyboardUpMainWindow);
	glutTimerFunc(30, timerMainWindow, 1);

	g_maxNotes = 2000;
	myTmpNotes = (TmpNote*)malloc(sizeof(TmpNote)*MAXSIZE);
	loadData(id);
	playMusic(id);

	initMainWindow();
	glutMainLoop();
}
void keyboardMainWindow(unsigned char key, int x, int y) {
	switch (key)
	{
	case 's':
		keyPress[0] = 1;
		break;
	case 'd':
		keyPress[1] = 1;
		break;
	case 'f':
		keyPress[2] = 1;
		break;
	case ' ':
		keyPress[3] = 1;
		break;
	case 'j':
		keyPress[4] = 1;
		break;
	case 'k':
		keyPress[5] = 1;
		break;
	case 'l':
		keyPress[6] = 1;
		break;
	default:
		break;
	}
}

void keyboardUpMainWindow(unsigned char key, int x, int y) {
	switch (key)
	{
	case 's':
		keyPress[0] = 0;
		break;
	case 'd':
		keyPress[1] = 0;
		break;
	case 'f':
		keyPress[2] = 0;
		break;
	case ' ':
		keyPress[3] = 0;
		break;
	case 'j':
		keyPress[4] = 0;
		break;
	case 'k':
		keyPress[5] = 0;
		break;
	case 'l':
		keyPress[6] = 0;
		break;
	default:
		break;
	}
}

void highlightKey() {
	int i;
	int cnt = 0;
	for (i = 0; i < 7; i++)
	{
		if (keyPress[i]==1)
		{
			int offsetX = 150+(50*i);
			glBegin(GL_QUADS);
			glColor4d(1, 1, 1, 1);
			glVertex2d(offsetX, 30);
			glVertex2d(offsetX + 50, 30);
			glColor4d(1, 1, 1, 0);
			glVertex2d(offsetX + 50, 150);
			glVertex2d(offsetX, 150);
			glEnd();

			checkNote(i+1);

			cnt++;
		}
	}
}
void initMainWindow(){
    glClearColor(0, 0, 0, 1);
    gluOrtho2D(0, 1200, 0, 1000);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void drawLines(){
    int startX = 150;
	int i;
    glColor3d(1, 1, 1);

    for (i = 0; i < 8; i++) {
        glBegin(GL_LINES);
        glVertex2d(startX+(i*50), 1000);
        glVertex2d(startX+(i*50), 0);
        glEnd();
    }
	
	for (i = 0; i < 2; i++) {
		glBegin(GL_LINES);
		glVertex2d(150, 30 + (i * 15));
		glVertex2d(150 + (7 * 50), 30 + (i * 15));
		glEnd();
	}
}
void reshapeMainWindow(){
    
}
void displayMainWindow(){
    int tmpIdx=0;
    int j,k;
    glClear(GL_COLOR_BUFFER_BIT);
    drawLines();
    
    if (line < g_maxNotes) {
        for (j = line; j < line+MAXSIZE; j++) {
			strcpy(myTmpNotes[tmpIdx].noteId, g_notes[j].noteId);
            myTmpNotes[tmpIdx].timeslice = g_notes[j].timeslice;
			myTmpNotes[tmpIdx].originIdx = j;
            tmpIdx++;
        }
		
        for (k=0; k<=MAXSIZE; k++) {
            printNoteGUI(myTmpNotes[k].noteId, k);
        }
    }
	highlightKey();
    glutSwapBuffers();
}

void timerMainWindow(){
    
    line++;
    
    glutPostRedisplay();
    glutTimerFunc(10, timerMainWindow, 1);
}
