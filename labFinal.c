#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct TrieNode
{
    struct TrieNode *children[26]; // One for each lowercase letter
    int count; // Number of occurrences of the word
};

// Creates a new Trie node
struct TrieNode *createNode()
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node)
    {
        for (int i = 0; i < 26; ++i)
        {
            node->children[i] = NULL;
        }
        node->count = 0;
    }
    return node;
}

// Inserts the word to the Trie structure
void insert(struct TrieNode *root, char *word)
{
    struct TrieNode *node = root;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (node->children[index] == NULL)
        {
            node->children[index] = createNode();
        }
        node = node->children[index];
    }
    node->count++;
}

// Computes the number of occurrences of the word
int numberOfOccurrences(struct TrieNode *root, char *word)
{
    struct TrieNode *node = root;
    for (int i = 0; word[i] != '\0'; ++i)
    {
        int index = word[i] - 'a';
        if (node->children[index] == NULL)
        {
            return 0; // Word not found
        }
        node = node->children[index];
    }
    return node->count;
}

// Deallocates the Trie structure
void deallocateTrie(struct TrieNode *root)
{
    if (root)
    {
        for (int i = 0; i < 26; ++i)
        {
            if (root->children[i])
            {
                deallocateTrie(root->children[i]);
            }
        }
        free(root);
    }
}

// Reads the dictionary file, populates the array, and returns the number of words
int readDictionary(char *filename, char ***pInWords)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    int numWords = 0;
    char **inWords = NULL;
    char buffer[256];
    int a;
    fscanf(file,"%d\n",&a);
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = 0; 
        inWords = (char **)realloc(inWords, (numWords + 1) * sizeof(char *));
        inWords[numWords] = strdup(buffer);
        numWords++;
    }

    fclose(file);
    *pInWords = inWords;
    return numWords;
}

int main(void)
{
    char **inWords = NULL;

    // Read the number of words in the dictionary
    int numWords = readDictionary("dictionary.txt", &inWords);
    for (int i = 0; i < numWords; ++i)
    {
        printf("%s\n", inWords[i]);
    }

    struct TrieNode *pTrie = createNode();
    for (int i = 0; i < numWords; i++)
    {
        //printf("hello");
        insert(pTrie, inWords[i]);
    }

    // Test with sample words
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
    {
        printf("\t%s : %d\n", pWords[i], numberOfOccurrences(pTrie, pWords[i]));
    }

    // Deallocate memory
    deallocateTrie(pTrie);

    for (int i = 0; i < numWords; ++i)
    {
        free(inWords[i]);
    }
    free(inWords);

    return 0;
}
