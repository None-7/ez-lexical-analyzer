
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

char B[10000];
int line = 1;
int l[100];
int error = 0;

const char *key[12] = { "void","int","float", "char", "if", "else", "while", "do", "for", "return", "main" ,"switch"};
int num[12] = { 3,4,5,6,7,8,9,10,11,12,13,36 };

int numjudges(char c) {
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

int wordjudges(char c) {
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}

int Check(char str[]) {
	int i;
	for (i = 0; i < 12; i++) {
		if (strcmp(str, key[i]) == 0) {
			return num[i];
		}
	}
	return 0;
}

void Compile() {
	int n;
	char x;
	int i = 0;
	int j = 0;
	char str[100];
	while ((x = B[j]) != '#') {
		if (x == ' ') {
			j++;
		}
		else if (x == '\n') {
			if (j != 0 && B[j - 1] != '\n') {
				printf("\n");
				line++;
			}
			j++;
		}
		else if (x == '/' && B[j + 1] == '/') {
			do{
				j++;
			} while (B[j] != '\n');
			j++;
		}
		else if (x == '/' && B[j + 1] == '*') {
			do {
				j++;
			} while (B[j - 1] != '/' || B[j - 2] != '*');
			if (B[j] == ' ') {
				do {
					j++;
				} while (B[j] == ' ');
			}
			if (B[j] == '\n') {
				j++;
			}
		}
		else if (numjudges(x) == 1) {
			while (numjudges(x)){
				str[i] = x;
				i++;
				j++;
				x = B[j];
			}
			if (wordjudges(x) == 1) {
				l[error] = line;
				error++;
				printf("LexicalError,");
				j++;
				x = B[j];
				while (wordjudges(x) == 1 || numjudges(x) == 1) {
					j++;
					x = B[j];
				}
			}
			else {
				str[i] = '\0';
				printf("<2,%s>,",str);
			}
			i=0;
		}
		else if (wordjudges(x)) {
			i = 0;
			while (wordjudges(x) || numjudges(x)) {
				str[i] = x;
				i++;
				j++;
				x = B[j];
			}
			str[i] = '\0';
			i = 0;
			n = Check(str);
			if (n != 0) {
				printf("<%d,->,",n);
			}
			else {

				printf("<1,%s>,", str);
			}
		}
		else if (B[j + 1] == '=') {
			if (x == '<') {
				printf("<20,->,");
				j += 2;
			}
			else if (x == '>') {
				printf("<22,->,");
				j += 2;
			}
			else if (x == '=') {
				printf("<23,->,");
				j += 2;
			}
			else if (x == '!') {
				printf("<24,->,");
				j += 2;
			}
		}
		else if (x == '&' && B[j + 1] == '&') {
			printf("<25,->,");
			j += 2;
		}
		else if (x == '|' && B[j + 1] == '|'){
			printf("<26,->,");
			j += 2;
		}
		else {
			switch (x) {
			case '+':
				printf("<14,->,");
				break;
			case '-':
				printf("<15,->,");
				break;
			case '*':
				printf("<16,->,");
				break;
			case '/':
				printf("<17,->,");
				break;
			case '%':
				printf("<18,->,");
				break;
			case '<':
				printf("<19,->,");
				break;
			case '>':
				printf("<21,->,");
				break;
			case '=':
				printf("<27,->,");
				break;
			case '(':
				printf("<28,->,");
				break;
			case ')':
				printf("<29,->,");
				break;
			case '[':
				printf("<30,->,");
				break;
			case ']':
				printf("<31,->,");
				break;
			case '{':
				printf("<32,->,");
				break;
			case '}':
				printf("<33,->,");
				break;
			case ';':
				printf("<34,->,");
				break;
			case ',':
				printf("<35,->,");
				break;
			}
			j++;
		}
	}
}

int main() {
	int i = 0;
	do {
		B[i] = getchar();
		i++;
	} while (B[i - 1] != '#');
	Compile();
	if (error != 0) {
		printf("LexicalError(s) on line(s) ");
		for (int t = 0; t < error; t++) {
			printf("%d,", l[t]);
		}
	}
	system("pause");
	return 0;
}
