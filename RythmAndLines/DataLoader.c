//
//  DataLoader.c
//  RhythmGame1
//
//  Created by Fallingstar on 2017. 5. 22..
//  Copyright © 2017년 Fallingstar. All rights reserved.
//

#include "TotalHeader.h"
#include "DataLoader.h"
#include "GlobalVariables.h"

extern char g_str[50][2];
extern char **g_dataStr;
extern int g_maxNotes;
extern MyNote *g_notes;

void makeTestData(){
	
	FILE *wf;
    
    wf = fopen("./MData/Notes/noteTest.txt", "w");
    for (int i = 0; i < g_maxNotes; i++) {
        if (i < 1500) {
            fprintf(wf, "%d\t%d\n", i, 8);
        }else{
            fprintf(wf, "%d\t%d\n", i, (rand()%8)+1);
        }
    }
    fclose(wf);
	
}
void loadData(int songId){
	FILE *rf;
	char str1[10], str2[15];
	if (songId == 1)
	{
		rf = fopen("./MData/Notes/note1.txt", "r");
	}
	else if (songId == 2) {
		rf = fopen("./MData/Notes/note2.txt", "r");
	}
	else if (songId == 999) {
		rf = fopen("./MData/Notes/note_test.txt", "r");
	}
	g_notes = (MyNote*)malloc(sizeof(MyNote)*g_maxNotes);
	for (int i = 0; i < g_maxNotes; i++) {
		if (fscanf(rf, "%s %s", str1, str2) > 0) {
			g_notes[i].timeslice = atoi(str1);
			strcpy(g_notes[i].noteId, str2);
		}
	}
	fclose(rf);
}