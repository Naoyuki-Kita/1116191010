#include "definitions.h"

#define subCOLS COLS-40
#define subLINES LINES-1

void printRule() {
	mvprintw(9, 95, "%s", "�Q�[�����[��");
	mvprintw(11, 84, "%s", "�u��ʂɕ\�����ꂽ��������͂���v");
	mvprintw(18, 98, "%s", "���ӓ_");
	mvprintw(20, 87, "%s", "�u�啶���E��������ʂ���I�v");;
	mvprintw(22, 85, "%s", "�u�X�y�[�X�͓��͂��Ȃ��ėǂ��I�v");
}

int checkSpell(Word word, Setting setting, int* missCnt) {
	int key;
	char buff[CHARBUFF];
	sprintf_s(buff, "%s", word.word);
	for (int i = 0; i < word.wordlen; i++) { 
		if (*missCnt == setting.maxMissNum) return 0;

		showWord(buff, word.wordlen);
		mvprintw(22, 33, "�~�X�����񐔁F%d", *missCnt);

		if (buff[i] == ' ') continue;
		key = getch();
		if (key == buff[i]) buff[i] = ' ';
		else {
			(*missCnt)++;
			i--;
		}
		
	}
	showWord(buff, word.wordlen);
	return 1;
}

void showWord(char* word, int wordlen) {
	int centerX;
	centerX = (COLS - 40 - wordlen * 2) / 2;
	for (int i = 0; i < wordlen; i++) {
		mvprintw(12, centerX+i*2, "%c", *(word + i));
	}
}

void initScreen(void) {
	erase();
	int centerX, centerY;
	centerY = LINES / 2;
	centerX = (COLS - strlen("Press the Key 'q'")) / 2;
	mvaddstr(centerY, centerX, "Press the Key 'q'");
	refresh();
	while (1) {
		if (getch() == 'q') break;
	}
	erase();
}

void surround(int minX, int maxX, int minY, int maxY) {
	for (int y = minY; y < maxY; y++) {
		for (int x = minX; x < maxX; x++) {
			if (y == minY || y == maxY - 1) mvaddstr(y, x, "-");
			else if (x == minX || x == maxX - 1) mvaddstr(y, x, "|");
		}
	}
	refresh();
}

int selectLevel() {
	int key;
	surround(0, COLS, 0, LINES);
	surround(2, subCOLS, 1, subLINES);
	mvaddstr(10, 35, "TYPING GAME");
	mvaddstr(14, 28, "Level1 : Press the KEY '1'");
	mvaddstr(16, 28, "Level2 : Press the KEY '2'");
	mvaddstr(18, 28, "Level3 : Press the KEY '3'");

	printRule();
	refresh();

	while (1) {
		key = getch();
		if (key >= '1' && key <= '3') break;
	}
	
	return key;
}



int playGame(WordList wordList, Setting setting) {
	erase();
	surround(0, COLS, 0, LINES);
	surround(2, subCOLS, 1, subLINES);
	printRule();

	int missCnt = 0;
	int gameFlag = 0;
	Word* tmpWord = wordList.firstWord;
	for (int i = 0; i < setting.questionsNum; i++) {
		gameFlag = checkSpell(*tmpWord, setting, &missCnt);
		tmpWord = tmpWord->nextWord;
		if (i == wordList.wordslen - 1) tmpWord = wordList.firstWord;
	}

	erase();
	surround(0, COLS, 0, LINES);
	surround(2, subCOLS, 1, subLINES);

	if(gameFlag == 1) mvaddstr(12, 30, "G A M E  C L E A R ! !");
	else mvaddstr(12, 33, "G A M E  O V E R");

	mvaddstr(19, 31, "�Q�[���I���FPress '9'");
	mvprintw(22, 33, "�~�X�����񐔁F%d", missCnt);
	refresh();
	while (1) {
		if (getch() == '9') break;
	}

	return missCnt;
}

