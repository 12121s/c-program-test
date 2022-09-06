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
