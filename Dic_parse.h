#include "Dictionary.h"
#ifndef DIC_PARSE_H_
#define DIC_PARSE_H_

void SEUFileToDic(char buff[MID_BUF], int len, Dictionary* dicA[MID_BUF * sizeof(KVPair)], int addDate);

void changeValue(int Before_len, int After_len, Dictionary* dicBefore[MID_BUF * sizeof(KVPair)], Dictionary* dicAfter[MID_BUF * sizeof(KVPair)], Dictionary* dicData[MID_BUF * sizeof(KVPair)]);

int str_chr(char* s, char c);
#endif /* DIC_PARSE_H_ */
