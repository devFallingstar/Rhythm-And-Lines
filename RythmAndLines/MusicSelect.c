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

int score = 0, combo = 0, maxCombo = 0;
int missCnt = 0, perfectCnt = 0;
char noteCheckStr[20];
char scoreStr[50];
char comboStr[50];
int keyPress[7] = { 0, };
int line=0;
int gameWinID, gameSubWinID;
int startX = MAX_X / 2 - 200;
double colorCode = 0;
TmpNote *myTmpNotes;

void musicStart(int id) {
	int i;
	int delay;
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1600, 900);
	glutInitWindowPosition(0, 0);
	if (id == 1) {
		glutCreateWindow("Rhythm And Lines - Evans");
		delay = 150;
		g_maxNotes = 2000;
	}
	else if (id == 2) {
		glutCreateWindow("Rhythm And Lines - FLOWER");
		delay = 150;
		g_maxNotes = 3800;
	}
	else if (id == 999) {
		glutCreateWindow("Rhythm And Lines - Test");
		delay = 150;
	}
	score = 0;
	myTmpNotes = (TmpNote*)malloc(sizeof(TmpNote)*MAXSIZE);

	glutDisplayFunc(displayMainWindow);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(keyboardMainWindow);
	glutKeyboardUpFunc(keyboardUpMainWindow);
	glutTimerFunc(delay, timerMainWindow, 1);
	
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
	int limit = 10;
	switch (key)
	{
	case 's':
		keyPress[0] = limit;
		break;
	case 'd':
		keyPress[1] = limit;
		break;
	case 'f':
		keyPress[2] = limit;
		break;
	case ' ':
		keyPress[3] = limit;
		break;
	case 'j':
		keyPress[4] = limit;
		break;
	case 'k':
		keyPress[5] = limit;
		break;
	case 'l':
		keyPress[6] = limit;
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
		if (keyPress[i]>=1)
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
			keyPress[i] -= 1;
		}
	}
}
int checkScore(int key) {
	int plusScore = checkNote(key);

	if (plusScore > 0) {
		score += plusScore;
		combo++;
		if (plusScore >= 100) {
			colorCode = 1;
			sprintf(noteCheckStr, "Perfect!!");
			perfectCnt++;
		}

		if (maxCombo < combo)
		{
			maxCombo = combo;
		}
	}
}
int checkMiss() {
	int i;
	if (strcmp(myTmpNotes[0].noteId, "8") != 0) {
		colorCode = 1;
		sprintf(noteCheckStr, "MISS");
		missCnt++;
		return 1;
	}
	else {
		return 0;
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

    if (line + MAXSIZE < g_maxNotes) {
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
	else {
		printf("END!\n");
		printf("Total score : %d\n", score);
		printf("Max combo : %d\n", maxCombo);
		printf("Perfect : %d\n", perfectCnt);
		printf("Miss : %d\n", missCnt);
		sndPlaySound(NULL, SND_ASYNC);
		glutHideWindow();
		return;
	}
	highlightKey();
	if (checkMiss() == 1) {
		combo = 0;
	}

	drawInfoText();

	glutSwapBuffers();
}

void timerMainWindow(){
    line++;
	if (colorCode > 0)
	{
		colorCode -= 0.03;
	}
    glutPostRedisplay();
    glutTimerFunc(10, timerMainWindow, 1);
}

void drawInfoText() {
	// Note check
	if (noteCheckStr[0] == 'P') {
		glColor3f(colorCode, colorCode, 0);
		drawNoteCheck(MAX_X / 2 + 700, 1200, 100, 40, noteCheckStr);
	}
	else if (noteCheckStr[0] == 'M')
	{
		glColor3f(colorCode, 0, 0);
		drawNoteCheck(MAX_X / 2 + 770, 1200, 100, 40, noteCheckStr);
	}
	else if (noteCheckStr[0] == 'B')
	{
		glColor3f(colorCode, 0, 0);
		drawNoteCheck(MAX_X / 2 + 780, 1200, 100, 40, noteCheckStr);
	}
	
	// Score
	glColor3f(1, 1, 0);
	sprintf(scoreStr, "Score : %d", score);
	drawScore(MAX_X / 2 - 100, 500, 0, 5, scoreStr);

	// Combo
	glColor3f(1, 1, 1);
	sprintf(comboStr, "Combo : %d", combo);
	drawCombo(MAX_X / 2 + 2100, 600, 0, -10, comboStr);
}

void drawScore(int posX, int posY, int posZ, int rot, char* strMsg) {
	int i;
	int len;
	double FontWidth = 5;

	len = strlen(strMsg);

	glPushMatrix();
	glLineWidth(FontWidth);
	glScaled(0.4, 1, 0.5);
	glTranslated(posX, posY, posZ);
	glRotated(90, 1, 0, 0);
	glRotated(rot, 0, 1, 0);
	for (i = 0; i < len; ++i)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, strMsg[i]);
	}
	glPopMatrix();
}
void drawCombo(int posX, int posY, int posZ, int rot, char* strMsg) {
	int i;
	int len;
	double FontWidth = 4;

	len = strlen(strMsg);

	glPushMatrix();
	glLineWidth(FontWidth);
	glScaled(0.4, 1, 0.5);
	glTranslated(posX, posY, posZ);
	glRotated(90, 1, 0, 0);
	glRotated(rot, 0, 1, 0);
	for (i = 0; i < len; ++i)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, strMsg[i]);
	}
	glPopMatrix();
}
void drawNoteCheck(int posX, int posY, int posZ, int rot, char* strMsg) {
	int i;
	int len;
	double FontWidth = 4;

	len = strlen(strMsg);

	glPushMatrix();
	glScaled(0.5, 1, 0.5);
	glTranslated(posX, posY, posZ);
	glRotated(90, 1, 0, 0);

	glPopMatrix();

	glPushMatrix();
	glLineWidth(FontWidth);
	glScaled(0.5, 1, 0.5);
	glTranslated(posX, posY, posZ);
	glRotated(90, 1, 0, 0);
	for (i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, strMsg[i]);
	}
	glPopMatrix();
}