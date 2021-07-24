// PDCursesSample.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "definitions.h"

int main(int argc, char* argv[])
{
	initscr();
	noecho();
	cbreak();
	
	initScreen();
	int key = selectLevel();
	WordList wordList = loadCsv(key);
	Setting setting = getSetting((char* )"setting.ini", key);
	int missCnt = playGame(wordList, setting);
	fwriteResult((char* )"result.txt", missCnt);

	endwin();
	
	return 0;
}

