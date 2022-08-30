#define MAX_BUF      4086
#define MID_BUF      2048

typedef struct {
	char *key;
	char *value;
} KVPair;

typedef struct Dictionary_t {
	KVPair *head;
	struct Dictionary_t *tail;
} Dictionary;

Dictionary* dict_new();
void dict_add(Dictionary *dictionary, char *key, char *value);
int dict_has(Dictionary *dictionary, char *key);
void dict_remove(Dictionary *dictionary,  char *key);
void dict_free(Dictionary *dictionary);
