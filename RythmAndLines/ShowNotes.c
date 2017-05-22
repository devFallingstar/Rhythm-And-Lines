#include "ShowNotes.h"
#include "GlobalVariables.h"

extern char g_str[50][2];
extern char **g_dataStr;
extern int g_maxNotes;
extern MyNote *g_notes;

void showNotes(){
    for (int i = 0; i < g_maxNotes; i++) {
        //printNote(g_notes[i].noteId);
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
    int startOffsetX = 150;
    int noteStartOffsetX = 175; 
	char tmpStr[10];
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
    int x1,x2, y1,y2;
    
    x1 = offsetX+5;
    x2 = offsetX+45;
    y1 = ((10*line))+2;
    y2 = (15+(10*line))-2;

    glColor3d(1, 0, 0);
    glRecti(x1, y1, x2, y2);
}
