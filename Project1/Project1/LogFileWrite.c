#include <time.h>

#include "LogFileWrite.h"


int LoadSetting(char* pk, char* sk, char* tk)
{
	FILE* SettingFile;
	char buff[2400];

	fopen_s(&SettingFile, "./Log/Setting.txt", "r");

	if (SettingFile == NULL)
		return 21;

	// Get Public Key
	fgets(buff, 6, SettingFile);
	fgets(buff, 2400, SettingFile);
	for (int i = 0; i < PUBLIC_KEY_SIZE; i++) {
		pk[i] = HexToChar(buff[i * 2], buff[i * 2 + 1]);
	}

	// Get Secret Key
	fgets(buff, 6, SettingFile);
	fgets(buff, 2400, SettingFile);
	for (int i = 0; i < SECRET_KEY_SIZE; i++) {
		sk[i] = HexToChar(buff[i * 2], buff[i * 2 + 1]);
	}

	// Get Temporary Key
	fgets(buff, 6, SettingFile);
	fgets(buff, 2400, SettingFile);
	for (int i = 0; i < SECRET_KEY_SIZE; i++) {
		tk[i] = HexToChar(buff[i * 2], buff[i * 2 + 1]);
	}

	fclose(SettingFile);

	return 0;
}

int SaveSetting(const char* pk, const char* sk, const char* tk)
{
	FILE* SettingFile;

	fopen_s(&SettingFile, "./Log/Setting.txt", "w");

	if (SettingFile == NULL)
		return 22;

	// Write Public Key
	fputs("pk : ", SettingFile);
	for (int i = 0; i < PUBLIC_KEY_SIZE; i++) {
		CharToHexAndWrite((unsigned char) pk[i], SettingFile);
	}
	fputc('\n', SettingFile);

	// Write Secret Key
	fputs("sk : ", SettingFile);
	for (int i = 0; i < SECRET_KEY_SIZE; i++) {
		CharToHexAndWrite((unsigned char) sk[i], SettingFile);
	}
	fputc('\n', SettingFile);

	// Write Temporary Key
	fputs("tk : ", SettingFile);
	for (int i = 0; i < SECRET_KEY_SIZE; i++) {
		CharToHexAndWrite((unsigned char) tk[i], SettingFile);
	}
	fputc('\n', SettingFile);

	fclose(SettingFile);

	return 0;
}

int LoadMessage(char ot[SAMPLE_COUNT][ORIGIN_TEXT_SIZE],
				char ct[SAMPLE_COUNT][CIPHER_TEXT_SIZE],
				char ss[SAMPLE_COUNT][KYBER_SYMBYTES])
{
	FILE* MessageFile;
	char buff[2400];

	fopen_s(&MessageFile, "./Log/Message.txt", "r");

	if (MessageFile == NULL)
		return 23;
	
	for (int sample = 0; sample < SAMPLE_COUNT; sample++)
	{
		// Get Origin Text
		fgets(buff, 6, MessageFile);
		fgets(buff, 2400, MessageFile);
		for (int i = 0; i < ORIGIN_TEXT_SIZE; i++) {
			ot[sample][i] = HexToChar(buff[i * 2], buff[i * 2 + 1]);
		}

		// Get Cipher Text
		fgets(buff, 6, MessageFile);
		fgets(buff, 2400, MessageFile);
		for (int i = 0; i < CIPHER_TEXT_SIZE; i++) {
			ct[sample][i] = HexToChar(buff[i * 2], buff[i * 2 + 1]);
		}

		// Get Shared Secret
		fgets(buff, 6, MessageFile);
		fgets(buff, 2400, MessageFile);
		for (int i = 0; i < KYBER_SYMBYTES; i++) {
			ss[sample][i] = HexToChar(buff[i * 2], buff[i * 2 + 1]);
		}

		fgets(buff, 6, MessageFile);
	}
	
	return 0;
}

int SaveMessage(const char ot[SAMPLE_COUNT][ORIGIN_TEXT_SIZE],
				const char ct[SAMPLE_COUNT][CIPHER_TEXT_SIZE],
				const char ss[SAMPLE_COUNT][KYBER_SYMBYTES])
{
	FILE* MessageFile;

	fopen_s(&MessageFile, "./Log/Message.txt", "w");

	if (MessageFile == NULL)
		return 24;

	for (int sample = 0; sample < SAMPLE_COUNT; sample++) 
	{
		// Write Origin Text
		fputs("ot : ", MessageFile);
		for (int i = 0; i < ORIGIN_TEXT_SIZE; i++) {
			CharToHexAndWrite((unsigned char) ot[sample][i], MessageFile);
		}
		fputc('\n', MessageFile);

		// Write Cipher Text
		fputs("ct : ", MessageFile);
		for (int i = 0; i < CIPHER_TEXT_SIZE; i++) {
			CharToHexAndWrite((unsigned char) ct[sample][i], MessageFile);
		}
		fputc('\n', MessageFile);

		// Write Shared Secret
		fputs("ss : ", MessageFile);
		for (int i = 0; i < KYBER_SYMBYTES; i++) {
			CharToHexAndWrite((unsigned char) ss[sample][i], MessageFile);
		}
		fputc('\n', MessageFile);
		fputc('\n', MessageFile);
	}
	
	fclose(MessageFile);

	return 0;
}

int FileOpen() {
	// Get Current Time
	time_t seconds = time(NULL);
	struct tm* now = localtime(&seconds);

	char buff[30];
	sprintf_s(buff, 30, "./Log/%2d%02d%02d_%02d%02d%02d.txt", now->tm_year - 100, now->tm_mon, now->tm_wday, now->tm_hour, now->tm_min, now->tm_sec);
	
	// File open
	fopen_s(&fp, buff, "w");

	if (fp == NULL) {
		return 25;
	}

	return 0;
}

void WriteLog(char* publicKey, char* secretKey)
{
	char buff[30];

	sprintf_s(buff, 30, "MAX Round : %d\n", MAX_ROUND);
	fputs(buff, fp);


	fputs("Public Key : ", fp);
	for (int i = 0; i < PUBLIC_KEY_SIZE; i++) {
		CharToHexAndWrite((unsigned char)publicKey[i], fp);
	}
	fputc('\n', fp);


	fputs("Secret Key : ", fp);
	for (int i = 0; i < SECRET_KEY_SIZE; i++) {
		CharToHexAndWrite((unsigned char)secretKey[i], fp);
	}
	fputc('\n', fp);
	fputc('\n', fp);
}

void FileWrite(int cnt, char* originText, int result) {
	char buff[4];

	sprintf_s(buff, 4, "%d  ", cnt);
	fputs(buff, fp);

	for (int i = 0; i < ORIGIN_TEXT_SIZE; i++) {
		CharToHexAndWrite((unsigned char) originText[i], fp);
	}

	sprintf_s(buff, 4, " %d\n", result);
	fputs(buff, fp);
}

void FileClose()
{
	fclose(fp);
}

void CharToHexAndWrite(unsigned char c, FILE* f) {
	fputc((c >> 4) + ((c >> 4) < 10 ? 48 : 55), f);
	fputc((c & 0b1111) + ((c & 0b1111) < 10 ? 48 : 55), f);
}

unsigned char HexToChar(char a, char b) {
	unsigned char ret = 0;

	ret += (a - (a < 65 ? 48 : 55)) * 16;
	return ret + (b - (b < 65 ? 48 : 55));
}