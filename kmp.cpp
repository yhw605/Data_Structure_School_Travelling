#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "kmp.h"

int fail[100]; // 定义fail[]数组

void kmpAutomation(char* P) { // 构建fail[1..p]数组
	fail[0] = 0;
	fail[1] = 0;
	for (int i = 1; i < strlen(P); ++i) {
		int j = fail[i];
		while (j && P[i] != P[j]) {
			j = fail[j];
		}
		if (P[i] == P[j]) {
			fail[i + 1] = j + 1;
		} else {
			fail[i + 1] = 0;
		}		
	}
}

int kmpMachine(char* T, char* P) {
	int match = -1;
	int tLen = strlen(T), pLen = strlen(P);
	int j = 0;
	int cnt = 0, tmp = 0;
	for (int i = 0; i < tLen; i++) {
		if (T[i] == '_') {
			cnt += 1; // 遇到1个'_'说明编号增长了1
		}
		while (j && T[i] != P[j]) {
			j = fail[j];
		}
		if (T[i] == P[j]) {
			j++;
		}
		if (j == pLen) {
			match = i + 1 - pLen;
			while (T[match] != '_') { // 找到这一段的开头，字符串以'_'开头
				match--;
			}
			for (int m = match + 1; T[m] != '_'; ++m) { // 字符串的结尾也为'_'
				printf("%c", T[m]);
			}
			printf("\n编号：%d\n", cnt);
			tmp = cnt;
		}
	}
	if (match == -1) {
		printf("没有找到你要去的地方！\n");
	}
	printf("若有多个匹配或没有匹配，请输入n，若只有一个匹配，请输入y：");

	return tmp - 1;
}

int kmp(char* T, char* P) {
	kmpAutomation(P);
	int count = kmpMachine(T, P);
	return count;
}