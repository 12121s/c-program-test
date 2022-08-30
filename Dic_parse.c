
#include "Dictionary.h"
#include "Timer.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

int removeLen = 0;

void SEUFileToDic(char buff[MID_BUF], int len, Dictionary* dicA[MID_BUF * sizeof(KVPair)], int addDate){
	int i = 0;
	char* ptr = strtok(buff, ",");
	char date[10];
	memset(date,0x00,sizeof(date));

	getTime(date);

	for(i = 0; i < len; i++){
		Dictionary *dic = dict_new();

		char key[MID_BUF];
		char value[MID_BUF];

		memset(key, 0x00, sizeof(key));
		memset(value, 0x00, sizeof(value));

		strcat(key, ptr);		//Index

		ptr = strtok(NULL, ",");	//변경 설정값
		strcat(value, ",");
		strcat(value, ptr);

		ptr = strtok(NULL, ",");	//설정값 상세 설명
		strcat(value, ",");
		strcat(value, ptr);
		strcat(value, ",");

		if(addDate == 1){
			strcat(value, date);		//msg 수신 날짜(에이전트 날짜)
		} else {
			ptr = strtok(NULL,",");		//msg 수신 날짜 (저장된 날짜)
			strcat(value, ptr);
		}
		strcat(value, ",");

		int key_length = strlen(key) + 1;
		int value_length = strlen(value) + 1;

		dic->head = (KVPair*)malloc(sizeof(KVPair));
		assert(dic->head != NULL);

		dic->head->key = (char *)malloc(key_length * sizeof(char));
		assert(dic->head->key != NULL);
		strcpy(dic->head->key, key);

		dic->head->value = (char *)malloc(value_length * sizeof(char));
		assert(dic->head->value != NULL);
		strcpy(dic->head->value, value);

		dicA[i] = dic;

		ptr = strtok(NULL, ",");		//다음 문자열

	}
}

void changeValue(int Before_len, int After_len, Dictionary* dicBefore[MID_BUF * sizeof(KVPair)], Dictionary* dicAfter[MID_BUF * sizeof(KVPair)], Dictionary* originData[MID_BUF * sizeof(KVPair)]){
	int i, j = 0;
	int baseCnt = 0;
	int addCnt = 0;
	Dictionary* addData[MID_BUF * sizeof(KVPair)];

	baseCnt = Before_len;
	addCnt = After_len;

	for (i = 0; i < baseCnt; i++){
		originData[i] = dicBefore[i];
	}

	for (i = 0; i < addCnt; i++){
		addData[i] = dicAfter[i];
	}

	removeLen = baseCnt;

	i = 0;

	for(i = 0; i < addCnt; i ++){
		addKey(originData, baseCnt, addData[i]->head->key, addData[i]->head->value);
	}
}

int str_chr(char* s, char c) {
	int i;
	int count=0;

	for (i=0; i < strlen(s); i++) {
		if( s[i] == c ) {
			count++;
		}
	}

	return count;
}

void addKey(Dictionary* originData[MID_BUF * sizeof(KVPair)], int baseCnt, char* key, char* value){
	int i, j = 0;

	int dicKeySize = 0;
	int flag = 0;

	while(originData[j] != NULL){
		dicKeySize ++;
		j++;
	}

	dicKeySize--;
	j--;

	for (i = 0; i < baseCnt; i++){
		char *originKey = originData[i]->head->key;

		if (originKey != NULL){

			if(strcmp(originKey, key) == 0){
				originData[i]->head->key = NULL;
				originData[i]->head->value = NULL;

				flag = 1;
				break;
			}
		}
	}

	if(flag == 0){
		dicKeySize++;
	}

	removeNULL(originData, dicKeySize);

	//dictonary 끝에 key, value 추가
	Dictionary *dic = dict_new();

	int key_length = strlen(key) + 1;
	int value_length = strlen(value) + 1;

	dic->head = (KVPair*)malloc(sizeof(KVPair));
	assert(dic->head != NULL);

	dic->head->key = (char *)malloc(key_length * sizeof(char));
	assert(dic->head->key != NULL);
	strcpy(dic->head->key, key);

	dic->head->value = (char *)malloc(value_length * sizeof(char));
	assert(dic->head->value != NULL);
	strcpy(dic->head->value, value);

	originData[dicKeySize] = dic;
}