#include <stdio.h>
#include <stdlib.h>
typedef struct node {
char letter;
struct node* next;
} node;
// Returns number of nodes in the linkedList.
int length(node* head)
{
	int count = 0;
	node* current = head;
	while (current != NULL){
		count++;
		current = current->next;
	}
	return count;
}
// parses the string in the linkedList
// if the linked list is head -> |a|->|b|->|c|
// then toCString function wil return "abc"
char* toCString(node* head)
{
	int len = length(head);
	char* cString = malloc((len + 1)* sizeof(char));
	int i = 0;
	node* current = head;
	while (current != NULL){
		cString[i] = current->letter;
		i++;
		current = current->next;
	}
	cString[i] = '\0';
	return cString;
}
// inserts character to the linkedlist
// f the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as foolows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	node* newNode = malloc(sizeof(node));
	newNode->letter = c;
	newNode->next = NULL;
	if(*pHead == NULL){
		*pHead = newNode;
	} else {
		node *current = *pHead;
		while(current->next != NULL){
			current = current->next;
		}
		current->next = newNode;
	}
}
// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	node *current = *pHead;
	while(current != NULL){
		node *next = current->next;
		free(current);
		current = next;
	}
	*pHead = NULL;	
}
int main(void)
{
int i, strLen, numInputs;
node* head = NULL;
char* str;
char c;
FILE* inFile = fopen("input.txt","r");
fscanf(inFile, " %d\n", &numInputs);
while (numInputs-- > 0)
{
fscanf(inFile, " %d\n", &strLen);
for (i = 0; i < strLen; i++)
{
fscanf(inFile," %c", &c);
insertChar(&head, c);
}
str = toCString(head);
printf("String is : %s\n", str);
free(str);
deleteList(&head);
if (head != NULL)
{
printf("deleteList is not correct!");
break;
}
}
fclose(inFile);
}
