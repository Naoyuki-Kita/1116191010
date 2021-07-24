#pragma once
#include <stdio.h>
#include <curses.h>
#include <Windows.h>
#include <time.h>
#define CHARBUFF 124
#define BUFFSIZE 1024

struct Word {
	char word[CHARBUFF];	//単語
	int wordlen;			//単語の長さ
	Word* nextWord;			//次の単語(単方向リスト用)
};

struct WordList {
	int wordslen;			//単語の数
	Word* firstWord;		//先頭の単語(単方向リスト用)
};

struct Setting {
	int questionsNum;		//出題数
	int maxMissNum;			//タイプミスの許容値(タイプミスでゲームオーバーにしないなら負の値)
	int timeLimit;			//制限時間(時間制限でゲームオーバーにしないなら負の値)(実装できてません！)
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


