#include "definitions.h"

void getCurrentDirectory(char* currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}

WordList loadCsv(int level) {
	char filePath[CHARBUFF];
	sprintf_s(filePath, "WordList%c.csv", level);

	FILE* fp;					//csv�t�@�C���i�[�p�̃t�@�C���^�\����
	char word[CHARBUFF];					//������̊i�[�ꏊ
	int wordslen = 0;			//�P��̐�(WordList�\���̂Ɋi�[)

	WordList wordList;
	Word* tmpWord = NULL;
	Word* prevWord = NULL;

	errno_t error;
	error = fopen_s(&fp, filePath, "r");

	if (error != 0) {	//���s�����ꍇ�G���[���b�Z�[�W��\��
		fprintf_s(stderr, "failed to open %s", filePath);
	}
	for (int i = 0; fgets(word, BUFFSIZE, fp) != NULL; i++) {
		tmpWord = new Word();

		sprintf_s(tmpWord->word, word);
		tmpWord->wordlen = strlen(word) - 1;

		tmpWord->nextWord = NULL;

		if (prevWord == NULL) {
			wordList.firstWord = tmpWord;
		}
		else {
			prevWord->nextWord = tmpWord;
		}
		prevWord = tmpWord;
		wordslen++;
	}
	wordList.wordslen = wordslen;
	return wordList;

}

Setting getSetting(char* filePath, int sectionNum) {
	Setting setting;

	char currentDirectory[CHARBUFF];
	char settingFile[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	sprintf_s(settingFile, "%s\\%s", currentDirectory, filePath);

	char section[CHARBUFF];
	sprintf_s(section, "section%c", sectionNum);

	char questionsNumWord[CHARBUFF];
	sprintf_s(questionsNumWord, "questionsNum");
	char questionsNumValue[CHARBUFF];
	int questionsNum = GetPrivateProfileInt(section, questionsNumWord, -1, settingFile);

	char maxMissNumWord[CHARBUFF];
	sprintf_s(maxMissNumWord, "maxMissNum");
	char maxMissNumValue[CHARBUFF];
	int maxMissNum = GetPrivateProfileInt(section, maxMissNumWord, -1, settingFile);

	char timeLimitWord[CHARBUFF];
	sprintf_s(timeLimitWord, "timeLimit");
	char timeLimitValue[CHARBUFF];
	int timeLimit = GetPrivateProfileInt(section, timeLimitWord, -1, settingFile);

	setting.questionsNum = questionsNum;
	setting.maxMissNum = maxMissNum;
	setting.timeLimit = timeLimit;

	return setting;
}

void fwriteResult(char* filePath, int missCnt) {
	FILE* fp;
	errno_t error = fopen_s(&fp, filePath, "w");
	if (error != 0) {
		fprintf_s(stderr, "failed to open");
	}
	fprintf_s(fp, "�~�X�����񐔁F%d\n", missCnt);
	fclose(fp);
}