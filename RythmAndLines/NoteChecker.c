#include "NoteChecker.h"
#include "MusicSelect.h"
#include "GlobalVariables.h"

extern TmpNote *myTmpNotes;
extern MyNote *g_notes;

int checkNote(int keyNum) {
	int i;

	if (myTmpNotes[1].noteId == keyNum)
	{
		printf("Perfect!\n");
		g_notes[myTmpNotes[1].originIdx].noteId = 8;
		return 100;
	}
	else if (myTmpNotes[2].noteId == keyNum)
	{
		printf("Perfect!\n");
		g_notes[myTmpNotes[2].originIdx].noteId = 8;
		return 100;
	}
	else if (myTmpNotes[3].noteId == keyNum)
	{
		printf("Perfect!\n");
		g_notes[myTmpNotes[3].originIdx].noteId = 8;
		return 100;
	}
	else if (myTmpNotes[4].noteId == keyNum)
	{
		printf("Perfect!\n");
		g_notes[myTmpNotes[4].originIdx].noteId = 8;
		return 100;
	}
	else if (myTmpNotes[5].noteId == keyNum)
	{
		printf("Good!\n");
		g_notes[myTmpNotes[5].originIdx].noteId = 8;
		return 50;
	}
	else if (myTmpNotes[6].noteId == keyNum)
	{
		printf("Good!\n");
		g_notes[myTmpNotes[6].originIdx].noteId = 8;
		return 50;
	}
	else if (myTmpNotes[7].noteId == keyNum)
	{
		printf("Good?\n");
		g_notes[myTmpNotes[7].originIdx].noteId = 8;
		return 50;
	}
	else if (myTmpNotes[8].noteId == keyNum)
	{
		printf("Good?\n");
		g_notes[myTmpNotes[8].originIdx].noteId = 8;
		return 10;
	}
	else if (myTmpNotes[9].noteId == keyNum)
	{
		printf("Not good...\n");
		g_notes[myTmpNotes[9].originIdx].noteId = 8;
		return 10;
	}
	else if (myTmpNotes[0].noteId == keyNum)
	{
		printf("Not good...\n");
		g_notes[myTmpNotes[0].originIdx].noteId = 8;
		return 10;
	}

	return 0;
}