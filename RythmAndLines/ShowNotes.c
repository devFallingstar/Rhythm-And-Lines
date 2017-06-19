#include "TotalHeader.h"
#include "ShowNotes.h"
#include "GlobalVariables.h"

#define MAX_X 1920

extern char g_str[50][2];
extern char **g_dataStr;
extern int g_maxNotes;
extern MyNote *g_notes;
extern int g_noteOffset[7];

void showNotes(){
    for (int i = 0; i < g_maxNotes; i++) {
    }
}

void printNote(int _id) {
    switch (_id) {
        case 1:
            printf("|======|      |      |      |      |      |      |\n");
            break;
        case 2:
            printf("|      |======|      |      |      |      |      |\n");
            break;
        case 3:
            printf("|      |      |======|      |      |      |      |\n");
            break;
        case 4:
            printf("|      |      |      |======|      |      |      |\n");
            break;
        case 5:
            printf("|      |      |      |      |======|      |      |\n");
            break;
        case 6:
            printf("|      |      |      |      |      |======|      |\n");
            break;
        case 7:
            printf("|      |      |      |      |      |      |======|\n");
            break;
        case 8:
            printf("|      |      |      |      |      |      |      |\n");
            break;
        default:
            break;
    }
}

void getNotesGUI(){
    int i,j;
    for (i = 0; i < g_maxNotes; i++) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        for (j = i+99; j >= i; j--) {
            //printf("%d - %d\n", j, g_notes[j].noteId);
            //printNoteGUI(g_notes[j].noteId, j);
        }
        
		Sleep(100);
    }
}

void printNoteGUI(char _id[10], int line) {
    int startOffsetX = MAX_X/2-200;
    int noteStartOffsetX = (MAX_X / 2 - 200)+25;
	char tmpStr[15];
	char *tok = NULL;
	
	strcpy(tmpStr, _id);

	if (strcmp(tmpStr, "8")!=0)
	{
		tok = strtok(tmpStr, "|");
		
		while (tok != NULL)
		{
			drawOneNote(startOffsetX + (50 * (atoi(tok) - 1)), line);
			tok = strtok(NULL, "|");
		}
	}
}

void drawOneNote(int offsetX, int line){
	
	if (offsetX == g_noteOffset[0] || offsetX == g_noteOffset[6])
	{
		glColor4f(1, 1, 1, 1);
	}
	else if (offsetX == g_noteOffset[1] || offsetX == g_noteOffset[5])
	{
		glColor4f(0, 0, 1, 1);
	}
	else if (offsetX == g_noteOffset[2] || offsetX == g_noteOffset[4])
	{
		glColor4f(1, 0, 0, 1);
	}
	else if (offsetX == g_noteOffset[3])
	{
		glColor4f(1, 0.5, 0, 1);
	}

	glPushMatrix();
	glTranslatef(offsetX + 25, ((10 * line)), 0);
	glScalef(9, 2, 2);
	glutSolidCube(5);
	glPopMatrix();
}
