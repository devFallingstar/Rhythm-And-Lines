#define MAXSIZE 140
#define MAX_X 1920
#define MAX_Y 1080

#include "TotalHeader.h"
#include "MusicSelect.h"
#include "MusicPlayer.h"
#include "GlobalVariables.h"
#include "DataLoader.h"
#include "ShowNotes.h"
#include "NoteChecker.h"

extern int g_maxNotes;
extern char **g_dataStr;
extern MyNote *g_notes;
extern int g_noteOffset[7];

int score = 0, combo = 0;
char noteCheckStr[20];
char scoreStr[50];
char comboStr[50];
int keyPress[7] = { 0, };
int line=0;
int gameWinID, gameSubWinID;
int startX = MAX_X / 2 - 200;
TmpNote *myTmpNotes;

void musicStart(int id) {
	int i;
	int delay;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(300, 0);
	if (id == 1) {
		glutCreateWindow("Rhythm And Lines - Evans");
		delay = 150;
	}
	else if (id == 2) {
		glutCreateWindow("Rhythm And Lines - FLOWER");
		delay = 150;
	}
	
	glutDisplayFunc(displayMainWindow);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(keyboardMainWindow);
	glutKeyboardUpFunc(keyboardUpMainWindow);
	glutTimerFunc(delay, timerMainWindow, 1);

	score = 0;
	g_maxNotes = 6000;
	myTmpNotes = (TmpNote*)malloc(sizeof(TmpNote)*MAXSIZE);
	loadData(id);
	
	/* init note offset for note draw */
	for ( i = 0; i < 7; i++)
	{
		g_noteOffset[i] = 760+(i*50);
	}

	initMainWindow();
	playMusic(id);
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
	case 27:
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
	for (i = 0; i < 7; i++)
	{
		if (keyPress[i]==1)
		{
			int plusScore;
			int offsetX = startX+(50*i);
			glBegin(GL_QUADS);
			glColor4d(1, 1, 1, 1);
			glVertex3d(offsetX, 30, 0);
			glVertex3d(offsetX + 50, 30,0);
			glColor4d(1, 1, 1, 0);
			glVertex3d(offsetX + 50, 150,0);
			glVertex3d(offsetX, 150,0);
			glEnd();

			checkScore(i + 1);
		}
	}
}
int checkScore(int key) {
	int plusScore = checkNote(key);

	if (plusScore > 0) {
		score += plusScore;
		combo++;
		if (plusScore >= 100) {
			sprintf(noteCheckStr, "Perfect!!");
		}
		else
		{
			sprintf(noteCheckStr, "Good!");
		}
	}
}
int checkMiss() {
	int i;
	if (strcmp(myTmpNotes[0].noteId, "8") != 0) {
		sprintf(noteCheckStr, "MISS");
		return 1; //Miss
	}
	else {
		return 0; //No miss
	}
}
void initMainWindow(){
    glClearColor(0, 0, 0, 1);
	glOrtho(0, MAX_X, 0, MAX_Y, -1000, 1000);
	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void drawLines(){
	int i;
    glColor3d(1, 1, 1);

    for (i = 0; i < 8; i++) {
        glBegin(GL_LINES);
        glVertex3d(startX+(i*50), MAX_Y, 0);
        glVertex3d(startX+(i*50), 0, 0);
        glEnd();
    }
	
	for (i = 0; i < 2; i++) {
		glBegin(GL_LINES);
		glVertex3d(startX, 30 + (i * 15), 0);
		glVertex3d(startX + (7 * 50), 30 + (i * 15), 0);
		glEnd();
	}
}
void reshapeMainWindow(){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (float)MAX_X / MAX_Y, 1.0, 20000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void displayMainWindow(){
    int tmpIdx=0;
    int j,k;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt((MAX_X / 2)-25, -150, 130, (MAX_X / 2) - 25, MAX_Y/2, 0, 0, 0, 1);
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
	if (checkMiss() == 1) {
		combo = 0;
	}

	drawText(890, 800, 200, noteCheckStr);
	sprintf(scoreStr, "Score : %d", score);
	drawText(300, 550, 350, scoreStr);
	sprintf(comboStr, "Combo : %d", combo);
	drawText(295, 550, 330, comboStr);

	glutSwapBuffers();
}

void timerMainWindow(){
    line++;
    
    glutPostRedisplay();
    glutTimerFunc(10, timerMainWindow, 1);
}

void drawText(int posX, int posY, int posZ, char* strMsg){
	int i;
	int len;
	double FontWidth = 0.02;

	len = strlen(strMsg);
	glColor3f(1, 0, 0);
	glRasterPos3f(posX, posY, posZ);
	glPushMatrix();
	glScaled(2.0, 2.0, 2.0);
	for (i = 0; i < len; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, strMsg[i]);
	}
	glPopMatrix();
}
