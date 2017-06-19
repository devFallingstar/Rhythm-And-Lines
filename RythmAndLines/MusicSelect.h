#ifndef MusicSelect_h
#define MusicSelect_h



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
int checkScore(int key);
int checkMiss();
void drawInfoText();
void drawScore(int posX, int posY, int posZ, int rot, char* strMsg);
void drawCombo(int posX, int posY, int posZ, int rot, char* strMsg);
void drawNoteCheck(int posX, int posY, int posZ, int rot, char* strMsg);

#endif
