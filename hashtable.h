using namespace std;

struct hash_table_entry;
struct bst;

typedef hash_table_entry* List;
typedef hash_table_entry* Element;

struct HashTable {
	int m;
	List *theChain;
};

HashTable* initHash(int m);
int hashF(int k, int m);
Element findHash(HashTable* HashTable, int key, int m);
void insertHash(HashTable* HashTable, bst* pre, int key);