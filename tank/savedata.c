#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "whole.h"
#include "define.h"

void SavetoFile(void){
	FILE *fp;
	char path[10000];
	Player *temp = head;

	BulidPath(path);
	fp = fopen(path,"w");
	if(fp == NULL){
		printf("无法打开文件！\n");
		return;
	}

	while(temp != NULL){
		fprintf(fp,"%s %d %d %d %d %d %d\n",temp->name,temp->level_num,temp->score_num,temp->diffi_num,temp->tank_num,temp->my_cd_num,temp->ai_cd_num);
		temp = temp->next;
	}

	if(fclose(fp) == EOF){
		printf("无法关闭文件！\n");
		return;
	}

	return;
}

void GetfromFile(void){
	FILE *fp;
	Player *m1,*m2;
	char path[10000],temp[10000];
	
	m2 = m1 = (Player *)malloc(LEN);
	BulidPath(path);

	if( (fp = fopen (path,"r") ) == NULL ){
		printf("无法打开文件！\n");
		return;
	}

	head = m1;
	fscanf(fp,"%s",temp);
	while (strlen(temp) != 0){
		strcpy(m1->name,temp);
		fscanf(fp,"%d %d %d %d %d %d",&m1->level_num,&m1->score_num,&m1->diffi_num,&m1->tank_num,&m1->my_cd_num,&m1->ai_cd_num);
		m2 = m1;
		m1 = (Player *)malloc(LEN);
		m2->next = m1;
		strcpy(temp,"\0");
		fscanf(fp,"%s",temp);
		sum++;
	}
	m2->next = NULL;	

	return;

}

void BulidPath(char path[]){

	DWORD len = GetModuleFileName(NULL, path, 10000);
	for (int i = strlen(path); i >= 0; --i) {
        if(path[i] == '\\') {
            path[i+1] = '\0';
            break;
        }
    }
    strcat(path,"data.txt");
	return;
}

