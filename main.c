/************字典树匹配字符串*************/
#include <stdio.h>
#include <stdlib.h>

#define SIZE 26

struct TrieNode{
    int count;
    struct TrieNode *children[SIZE];
};

struct TrieNode *create_Trie()
{
    struct TrieNode *node = NULL;

    node = malloc(sizeof(struct TrieNode));
    if (!node) return NULL;
    for (int i =0; i < SIZE; i++) node->children[i] = NULL;
    node->count = 0;
    return node;
}

int insert_trie(struct TrieNode *root, char *str)
{
    struct TrieNode *node = NULL;
    char *cur = NULL;

    if (!root || !str) return -1;

    node = root;
    cur = str;

    while(*cur){
        if (node->children[*cur - 'a'] == NULL) {
            node->children[*cur - 'a'] = create_Trie();
        }
        node = node->children[*cur - 'a'];
        cur++;
    }
    node->count+=1;
    return 0;
}

/**查找字串**/
int match_trie(struct TrieNode *root, char *str)
{
    struct TrieNode *node = NULL;
    char *cur = NULL;

    if (!root || !str || !str[0]) return -1;

    node = root;    cur = str;

    while(*cur && (node = node->children[*cur++ - 'a']));

    if (!node) return -2;

    return node->count;
}

/**递归释放内存，递归太深可能会栈溢出，听说递归必有对应的迭代，但是尝试过了，心有余而力不足**/
void free_trie(struct TrieNode *root)
{
    struct TrieNode *node = NULL;

    if (!root) return;

    for (int i = 0; i < SIZE; i++) {
        node = root->children[i];
        if (node) {
            root->children[i] = NULL;
            free_trie(node);
        }
    }
    free(root);
    root = NULL;
}

/**删除以某子串为前缀的字串**/
int delete_trie(struct TrieNode *root, char *str)
{
    struct TrieNode *curnode = NULL;
    struct TrieNode *prenode = NULL;
    struct TrieNode *freenode = NULL;
    int pos = 0;
    char *cur = NULL;

    if (!root || !str) return -1;

    curnode = root;
    freenode = root;
    cur = str;

    while(*cur) {
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            if (curnode->children[i]) {
                count++;
            }
        }
        if (count != 1) {
            pos = *cur - 'a';
            prenode = freenode;
            freenode = curnode->children[*cur - 'a'];
        }
        curnode = curnode->children[*cur - 'a'];
        cur++;
    }
    if (!curnode) return -2;

    prenode->children[pos] = NULL;
    free_trie(freenode);
    freenode = NULL;

    return 0;
}

int main()
{
    char arr[][128] = {"syshaw", "renhao", "maplestory", "header","jn","jenhawnaaaaaaaaaaaaaaaaaaaaaaaaaa", NULL};
    int count = 0;

    struct TrieNode *root = create_Trie();
    if (!root) {printf("create root failed\n");exit(-1);}
    for (int i = 0; arr[i][0]; i++) insert_trie(root, arr[i]);
    count = match_trie(root, "syshaw");
    printf("%d-%s\n", count, count>0?"ok":"no");
    count = match_trie(root, "renhao");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "maplestory");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "header");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jenhawn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jenhawnaaaaaaaaaaaaaaaaaaaaaaaaaa");
    printf("%d-%s\n", count,count>0?"ok":"no");

    delete_trie(root, "jen");

    printf("\n1\n");
    count = match_trie(root, "syshaw");
    printf("%d-%s\n", count, count>0?"ok":"no");
    count = match_trie(root, "renhao");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "maplestory");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "header");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jenhawn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jenhawnaaaaaaaaaaaaaaaaaaaaaaaaaa");
    printf("%d-%s\n", count,count>0?"ok":"no");

    printf("\n2\n");

    free_trie(root);

    count = match_trie(root, "s");
    printf("%d-%s\n", count, count>0?"ok":"no");
    count = match_trie(root, "renhao");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "maplestory");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "header");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jenhawn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jensfhawn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    count = match_trie(root, "jengsdghawn");
    printf("%d-%s\n", count,count>0?"ok":"no");
    return 0;
}
