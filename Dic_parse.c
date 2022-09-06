
#include "Dictionary.h"
#include "Timer.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>

int removeLen = 0;

Dictionary* dict_new(){
	Dictionary *dictionary = (Dictionary*) malloc(sizeof(Dictionary));
	assert(dictionary != NULL);
	dictionary->head = NULL;
    dictionary->tail = NULL;
	return dictionary;
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

void removeNULL(Dictionary* data[MID_BUF * sizeof(KVPair)], int dicKeySize){
	int i, j = 0;

	for(i = 0; i <dicKeySize; i++){
		if (data[i]->head->key == NULL){
			for (j = i; j < dicKeySize; j++){
				data[j]->head->key = data[j+1]->head->key;		//다음 데이터로 덮기
				data[j]->head->value = data[j+1]->head->value;

			}

			break;
		}
	}
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

//replaceValue - 전달된 데이터와 키가 같은데 값이 바뀌면 해당 포지션 값 갱신, 새로운 데이터가 있으면 마지막에 추가
void replaceValue(Dictionary *originData[MID_BUF * sizeof(KVPair)], int baseCnt, char *key, char *value) {
	int i, j = 0;

	int dicKeySize = 0;
	int flag = 0;

	while (originData[j] != NULL) { // 새로운 데이터 공간 크기
		dicKeySize++;
		j++;
	}

	dicKeySize--;
	j--;

	for (i = 0; i < baseCnt; i++) {
		char *originKey = originData[i]->head->key;
		char *originValue = originData[i]->head->value;

		// 원본 데이터에 영향 없도록 string dump
		char *originTempValue = strdup(originValue);
		char *addTempValue = strdup(value);

		if (originKey != NULL) {

			// 원본 데이터와 키가 같은 데이터가 들어오면
			if (strcmp(originKey, key) == 0) {

				// 첫번째 value 파싱
				strsep(&originTempValue, ",");
				strsep(&addTempValue, ",");

				char *originSeuData = strsep(&originTempValue, ",");
				char *addSeuData = strsep(&addTempValue, ",");

				// 첫번째 value가 원본과 같지 않으면 데이터 갱신
				if (strcmp(originSeuData, addSeuData) != 0) {
					originData[i]->head->key = key;
					originData[i]->head->value = value;
				}

				// 키가 같은 경우 마지막에 데이터 추가 안하도록
				flag = 1;
				break;
			}
		}
	}

	// flag가 0인 경우 키가 같은 데이터가 없다 == 마지막에 새로운 데이터 추가
	if (flag == 0) {
		dicKeySize++;

		removeNULL(originData, dicKeySize);

		// dictonary 마지막에 key, value 추가
		Dictionary *dic = dict_new();

		int key_length = strlen(key) + 1;
		int value_length = strlen(value) + 1;

		dic->head = (KVPair *)malloc(sizeof(KVPair));
		assert(dic->head != NULL);

		dic->head->key = (char *)malloc(key_length * sizeof(char));
		assert(dic->head->key != NULL);
		strcpy(dic->head->key, key);

		dic->head->value = (char *)malloc(value_length * sizeof(char));
		assert(dic->head->value != NULL);
		strcpy(dic->head->value, value);

		originData[dicKeySize] = dic;
	}
}

void SEUFileToDic(char buff[MID_BUF], int len, Dictionary* dicA[MID_BUF * sizeof(KVPair)], int addDate){
	char *from;
	from = strdup(buff); // 원본 데이터에 영향이 없도록 string dump

	int i = 0;
	char* ptr = strsep(&from, ","); // 공백 문자열도 정상 처리 되도록 strtok -> strsep

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

		ptr = strsep(&from, ",");	//변경 설정값
		strcat(value, ",");
		strcat(value, ptr);

		ptr = strsep(&from, ",");	//설정값 상세 설명
		strcat(value, ",");
		strcat(value, ptr);
		strcat(value, ",");

		if(addDate == 1){
			strcat(value, date);		//msg 수신 날짜(에이전트 날짜)
		} else {
			ptr = strsep(&from, ",");		//msg 수신 날짜 (저장된 날짜)
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

		ptr = strsep(&from, ",");		//다음 문자열

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
		// addKey(originData, baseCnt, addData[i]->head->key, addData[i]->head->value);
		replaceValue(originData, baseCnt, addData[i]->head->key, addData[i]->head->value);
	}
}