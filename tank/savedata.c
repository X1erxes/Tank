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
		fprintf(fp,"%s %d %d %d %d %d %d %d %d %d %d %d\n",temp->name,temp->level_num,temp->score_num,temp->diffi_num,temp->tank_num,temp->my_cd_num,temp->ai_cd_num,temp->year,temp->month,temp->day,temp->hour,temp->min);
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
	
	m2 = m1 = (Player *)malloc(LEN);			//分配动态空间
	BulidPath(path);							//读取当前文件位置存在path中

	if( (fp = fopen (path,"r") ) == NULL ){
		printf("无法打开文件！\n");
		return;
	}

	head = m1;
	fscanf(fp,"%s",temp);
	while (strlen(temp) != 0){
		strcpy(m1->name,temp);
		//读取文件数据
		fscanf(fp,"%d %d %d %d %d %d %d %d %d %d %d",&m1->level_num,&m1->score_num,&m1->diffi_num,&m1->tank_num,&m1->my_cd_num,&m1->ai_cd_num,&m1->year,&m1->month,&m1->day,&m1->hour,&m1->min);
		m2 = m1;
		m1 = (Player *)malloc(LEN);
		m2->next = m1;
		strcpy(temp,"\0");
		fscanf(fp,"%s",temp);
		sum++;									//记录链表长度
	}
	//构建链表
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
	//获取当前文件的路径
    strcat(path,"data.txt");	//替换为文本文件
	return;
}

void StartFile(void){
	FILE *fp;
	char path[10000];
	BulidPath(path);
	fp = fopen(path,"w");
	if(fp == NULL){
		printf("无法打开文件！\n");
		return;
	}
	fprintf(fp,"test 1 0 1 16 7 15 2024 1 9 21 10\n");
	if(fclose(fp) == EOF){
		printf("无法关闭文件！\n");
		return;
	}
	return;
}