#include "NoteChecker.h"
#include "MusicSelect.h"
#include "GlobalVariables.h"

extern TmpNote *myTmpNotes;
extern MyNote *g_notes;

int checkNote(int keyNum) {
	int i;
	char tmp[10];
	itoa(keyNum, tmp, 10);

	if (strstr(myTmpNotes[1].noteId, tmp))
	{
		printf("Perfect!\n");
		strcpy(g_notes[myTmpNotes[1].originIdx].noteId, "8");
		return 100;
	}
	else if (strstr(myTmpNotes[2].noteId, tmp))
	{
		printf("Perfect!\n");
		strcpy(g_notes[myTmpNotes[2].originIdx].noteId, "8");
		return 100;
	}
	else if (strstr(myTmpNotes[3].noteId, tmp))
	{
		printf("Perfect!\n");
		strcpy(g_notes[myTmpNotes[3].originIdx].noteId, "8");
		return 100;
	}
	else if (strstr(myTmpNotes[4].noteId, tmp))
	{
		printf("Perfect!\n");
		strcpy(g_notes[myTmpNotes[4].originIdx].noteId, "8");
		return 100;
	}
	else if (strstr(myTmpNotes[5].noteId, tmp))
	{
		printf("Good!\n");
		strcpy(g_notes[myTmpNotes[5].originIdx].noteId, "8");
		return 50;
	}
	else if (strstr(myTmpNotes[6].noteId, tmp))
	{
		printf("Good!\n");
		strcpy(g_notes[myTmpNotes[6].originIdx].noteId, "8");
		return 50;
	}
	else if (strstr(myTmpNotes[7].noteId, tmp))
	{
		printf("Good?\n");
		strcpy(g_notes[myTmpNotes[7].originIdx].noteId, "8");
		return 50;
	}
	else if (strstr(myTmpNotes[8].noteId, tmp))
	{
		printf("Good?\n");
		strcpy(g_notes[myTmpNotes[8].originIdx].noteId, "8");
		return 10;
	}
	else if (strstr(myTmpNotes[9].noteId, tmp))
	{
		printf("Not good... %s\n", tmp);
		strcpy(g_notes[myTmpNotes[9].originIdx].noteId, "8");
		return 10;
	}
	else if (strstr(myTmpNotes[0].noteId, tmp))
	{
		printf("Not good... %s\n", myTmpNotes[0].noteId);
		strcpy(g_notes[myTmpNotes[0].originIdx].noteId, "8");
		return 10;
	}
	
	return 0;
}