#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
	char data[50];
	int count;
	struct Node* next;
};

struct Node* createNode(char* data) {
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	strcpy(newNode->data, data);
	newNode->count = 1;
	newNode->next = NULL;
	return newNode;
}

struct Node* findNode(struct Node* head, char* data) {
	struct Node* current = head;
	while (current != NULL) {
		if (strcmp(current->data, data) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

void insertNode(struct Node** head, char* data) {
	struct Node* node = findNode(*head, data);
	if (node != NULL) {
		node->count++;
	} else {
		struct Node* newNode = createNode(data);
		newNode->next = *head;
		*head = newNode;
	}
}

void freeList(struct Node* head) {
	while (head != NULL) {
		struct Node* temp = head;
		head = head->next;
		free(temp);
	}
}

int main() {
	FILE* file = fopen("input.txt", "r");
	if (file == NULL) {
		printf("无法打开input.txt\n");
		return 1;
	}

	char word[50];
	struct Node* wordList = NULL;
	struct Node* symbolList = NULL;
	while (fscanf(file, "%s", word) != EOF) {
		if (isalpha(word[0])) {
			// word
			insertNode(&wordList, word);
		} else if (word[0] != ' ') {
			// symbol(" " expect)
			insertNode(&symbolList, word);
		}
	}
	fclose(file);

	FILE* output = fopen("tongji.txt", "w");
	if (output == NULL) {
		printf("无法打开tongji.txt, 程序退出\n");
		freeList(wordList);
		freeList(symbolList);
		return 1;
	}

	// write word
	struct Node* current = wordList;
	struct Node* mostCommonWord = current;
	while (current != NULL) {
		fprintf(output, "单词 \"%s\" 出现次数：%d\n", current->data, current->count);
		if (current->count > mostCommonWord->count) {
			mostCommonWord = current;
		}
		current = current->next;
	}
	// write symbol
	current = symbolList;
	struct Node* mostCommonSymbol = current;
	while (current != NULL) {
		fprintf(output, "符号 \"%s\" 出现次数：%d\n", current->data, current->count);
		if (current->count > mostCommonSymbol->count) {
			mostCommonSymbol = current;
		}
		current = current->next;
	}

	// stat word
	if (wordList != NULL) {
		int totalWords = 0;
		struct Node* current = wordList;
		while (current != NULL) {
			totalWords += current->count; // 写 ++ 也算对
			current = current->next;
		}
		fprintf(output, "共英文单词 %d 个，", totalWords);
	} else {
		fprintf(output, "共英文单词 0 个，");
	}
	// stat symbol
	if (symbolList != NULL) {
		int totalSymbols = 0;
		struct Node* current = symbolList;
		while (current != NULL) {
			totalSymbols += current->count; // 写 ++ 也算对
			current = current->next;
		}
		fprintf(output, "其他符号 %d 个。\n", totalSymbols);
	} else {
		fprintf(output, "其他符号 0 个。\n");
	}

	// most word
	if (mostCommonWord != NULL) {
		fprintf(output, "出现最多的英文单词为 \"%s\"，出现次数 %d。\n", mostCommonWord->data, mostCommonWord->count);
	} else {
		fprintf(output, "出现最多的英文单词为 \"\"，出现次数 0。\n");
	}
	// most symbol
	if (mostCommonSymbol != NULL) {
		fprintf(output, "出现最多的符号为 \"%s\"，出现次数 %d。\n", mostCommonSymbol->data, mostCommonSymbol->count);
	} else {
		fprintf(output, "出现最多的符号为 \"\"，出现次数 0。\n");
	}

	// query
	char query[50];
	printf("please query:");
	scanf("%s", query);
	struct Node* queryNode = findNode(wordList, query);
	if (queryNode != NULL) {
		printf("result:\"%s\" count:%d\n", queryNode->data, queryNode->count);
	} else {
		queryNode = findNode(symbolList, query);
		if (queryNode != NULL) {
			printf("result:\"%s\" count:%d\n", queryNode->data, queryNode->count);
		} else {
			printf("result:cannot find string: \"%s\"\n", query);
		}
	}
	fclose(output);

	// free
	freeList(wordList);
	freeList(symbolList);

	return 0;
}