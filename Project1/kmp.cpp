#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <string.h>
#include "kmp.h"

int fail[100]; // ����fail[]����

void kmpAutomation(char* P) { // ����fail[1..p]���飬fail�������ָʾ����Ƶ�λ��
	fail[0] = 0; // fail[0]ʵ���ϱ�������
	fail[1] = 0; 
	for (int i = 1; i < strlen(P); ++i) {
		int j = fail[i]; 
		while (j && P[i] != P[j]) { // Ѱ��P[0..i]��׺��P��ǰ׺�����ƥ��λ��
			j = fail[j];
		}
		if (P[i] == P[j]) {
			fail[i + 1] = j + 1; // ��Ҳ��fail[0]�����õ�һ��ϸ��
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
			cnt += 1; // ����1��'_'˵�����������1
		}
		while (j && T[i] != P[j]) {
			j = fail[j];
		}
		if (T[i] == P[j]) {
			j++;
		}
		if (j == pLen) {
			match = i + 1 - pLen;
			while (T[match] != '_') { // �ҵ���һ�εĿ�ͷ���ַ�����'_'��ͷ
				match--;
			}
			for (int m = match + 1; T[m] != '_'; ++m) { // �ַ����Ľ�βҲΪ'_'
				printf("%c", T[m]);
			}
			printf("\n��ţ�%d\n", cnt);
			tmp = cnt;
		}
	}
	if (match == -1) {
		printf("û���ҵ���Ҫȥ�ĵط���\n");
	}
	printf("���ж��ƥ���û��ƥ�䣬������n����ֻ��һ��ƥ�䣬������y��");

	return tmp - 1;
}

int kmp(char* T, char* P) {
	kmpAutomation(P);
	int count = kmpMachine(T, P);
	return count;
}