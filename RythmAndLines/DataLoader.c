//
//  DataLoader.c
//  RhythmGame1
//
//  Created by Fallingstar on 2017. 5. 22..
//  Copyright © 2017년 Fallingstar. All rights reserved.
//

#include "DataLoader.h"
#include "GlobalVariables.h"

extern char g_str[50][2];
extern char **g_dataStr;
extern int g_maxNotes;
extern MyNote *g_notes;
/*
 첫번째 줄 - '곡명      전체 라인 수'
 두번째 줄부터 - '라인 넘버    노트 위치'
 */

void makeTestData(){
	
	FILE *wf;
    
    wf = fopen("./MData/Notes/note1.txt", "w");
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
	//makeTestData();
	FILE *rf;
	char str1[10], str2[10];
	if (songId == 1)
	{
		rf = fopen("./MData/Notes/test1.txt", "r");
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
