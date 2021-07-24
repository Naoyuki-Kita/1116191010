#pragma once
#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#define CHARBUFF 124
#define BUFFSIZE 1024

struct Word {
	char word[CHARBUFF];	//�P��
	int wordlen;			//�P��̒���
	Word* nextWord;			//���̒P��(�P�������X�g�p)
};

struct WordList {
	int wordslen;			//�P��̐�
	Word* firstWord;		//�擪�̒P��(�P�������X�g�p)
};

struct Setting {
	int questionsNum;		//�o�萔
	int maxMissNum;			//�^�C�v�~�X�̋��e�l(�^�C�v�~�X�ŃQ�[���I�[�o�[�ɂ��Ȃ��Ȃ畉�̒l)
	int timeLimit;			//��������(���Ԑ����ŃQ�[���I�[�o�[�ɂ��Ȃ��Ȃ畉�̒l)(�����ł��Ă܂���I)
};

void getCurrentDirectory(char* currentDirectory);
WordList loadCsv(int level);
Setting getSetting(char* filePath, int sectionNum);
void fwriteResult(char* filePath, int missCnt);

void printRule();
int checkSpell(Word word, Setting setting, int* missCnt);
void showWord(char* word, int wordlen);
void initScreen(void);
void surround(int minX, int maxX, int minY, int maxY);
int selectLevel();
int playGame(WordList wordList, Setting setting);


