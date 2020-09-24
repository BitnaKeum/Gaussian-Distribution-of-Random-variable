#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

#pragma warning(disable : 4996)

using namespace std;

HWND hwnd;
HDC hdc;

enum color {
	BLUE, RED, WHITE, GREEN
};




void Draw(float val, int x_origin, int y_origin, int curx, color c);
float normal_pdf(int x, float rate, float  mu = 0, float sigma = 1);
float normal_cdf(float x, float mu = 0, float sigma = 1);
float inverse_normal_cdf(float p, float mu = 0, float sigma = 1, float tolerance = 0.00001);
void DrawHistogram(int histogram[400], int x_origin, int y_origin, int cnt);
void DrawHistogram(float histogram[400], int x_origin, int y_origin, int cnt);
float Dminus(float gaussianCDF[], float gaussianCDF_true[]);
float Dplus(float gaussianCDF[], float gaussianCDF_true[]);
float largest(float data[]);
float Dplus(float gaussianCDF[], float gaussianCDF_true[]);
float Dminus(float gaussianCDF[], float gaussianCDF_true[]);
float largest(float data[]);


int main(void)
{
	system("color F0");
	hwnd = GetForegroundWindow();
	hdc = GetWindowDC(hwnd);

	int range = 400; // 0~400 범위 랜덤 변수
	int rcnt = 10000; // rcnt times 랜덤 변수 발생
	int y_axis = 300;

	float avg = 0; // 평균
	float sigma = 1; // 표준편차


	int random_variable[401] = { 0, }; // 랜덤 변수 count
	int Gaussian_random_variable[401] = { 0, }; // 가우시안 변수 count
	float gaussianCDF[401] = { 0, }; // 랜덤 가우시안 분포 CDF
	float gaussianCDF_true[401] = { 0, }; // 실제 정답 가우시안 분포 CDF


	srand(time(NULL));
	for (int i = 0; i < rcnt; i++) {
		// 0~400 범위의 난수를 10000번 생성하며, 해당 난수의 생성 횟수를 카운트
		random_variable[rand() % 401] += 1;
	}
	DrawHistogram(random_variable, 30, y_axis - 100, range);  // 랜덤 변수 분포 출력
	

	// random variable의 CDF
	float randomCDF[401] = { 0, };
	int cnt = 0;
	for (int i = 0; i < 401; i++) {
		cnt += random_variable[i];	// 난수 생성 횟수를 누적으로 더함
		randomCDF[i] = (float)cnt / 10000;	// cnt를 10000으로 나눔으로써 cdf 구할 수 있음
		//printf("[%d]: %f\n", i, randomCDF[i]);
	}
	//DrawHistogram(randomCDF, 30, y_axis, range);


	// normal_cdf의 역함수 
	float inverse_value[401] = { 0, };	// inverse_normal_cdf의 리턴 값
	for (int j = 0; j < 401; j++) {
		// 해당 난수의 생성 횟수만큼 반복하여 가우시안 변수 카운트
		for (int k = 0; k < random_variable[j]; k++) {	
			inverse_value[j] = inverse_normal_cdf(randomCDF[j], avg, sigma, 0.00001);

			int index = (int)20 * inverse_value[j] + 200;	// 0~400 값으로 만듦
			Gaussian_random_variable[index] += 1;	// 가우시안 변수 카운트
		}
	}
	DrawHistogram(Gaussian_random_variable, 500, y_axis, range); // 가우시안 변수 분포 출력
	/*for (int i = 0; i <= 400; i++) {
		printf("[%d]: %d\n", i, Gaussian_random_variable[i]);
	}*/

	// 실제 Gaussian pdf 출력 (빨간색 그래프)
	for (int i = 1; i < range; i++) {
		float value = normal_pdf(i - 1 * range / 2, range / 20, avg, sigma);
		Draw(value * 250, 500, y_axis, i, RED);
	}


	// Gaussian_random_variable의 CDF 구함
	cnt = 0;
	for (int i = 0; i < 401; i++)
	{
		cnt += Gaussian_random_variable[i];	// 가우시안 변수 생성 횟수를 누적으로 더함
		gaussianCDF[i] = (float)cnt / 10000;	// cnt를 10000으로 나눔으로써 CDF 얻음
		//printf("[%d]: %f\n", i, gaussianCDF[i]);
	}
	//DrawHistogram(gaussianCDF, 500, y_axis+300, range);


	// 실제 Gaussian CDF 구함
	for (int i = 0; i < 401; i++)
	{
		gaussianCDF_true[i] = normal_cdf((float)i / 20.0 - 10.0, avg, sigma);
		//printf("[%d]: %f\n", i, gaussianCDF_true[i]);
	}
	DrawHistogram(gaussianCDF_true, 30, y_axis + 300, range);


	return 0;
}



void Draw(float val, int x_origin, int y_origin, int curx, color c) {
	if (c == BLUE) {
		SetPixel(hdc, x_origin + curx, y_origin - val, RGB(0, 0, 255));
	}
	else if (c == RED) {
		SetPixel(hdc, x_origin + curx, y_origin - val, RGB(255, 0, 0));
	}
	else if (c == GREEN) {
		SetPixel(hdc, x_origin + curx, y_origin - val, RGB(0, 255, 0));
	}
	else {
		SetPixel(hdc, x_origin + curx, y_origin - val, RGB(255, 255, 255));
	}
}

// Gaussian pdf를 구함
float normal_pdf(int x, float rate, float  mu = 0, float sigma = 1) {
	double pi = M_PI;

	double sqrt_two_pi = sqrt(2 * pi);
	double _exp = exp(-pow(((double)x / rate - mu), 2) / (2 * pow(sigma, 2)));
	return _exp / (sqrt_two_pi * sigma);
}

// Gaussian cdf를 구함
float normal_cdf(float x, float mu = 0, float sigma = 1) {
	return (1 + erf((x - mu) / sqrt(2) / sigma)) / 2;
}

// Gaussian cdf의 역함수를 구함
float inverse_normal_cdf(float p, float mu = 0, float sigma = 1, float tolerance = 0.00001)
{
	// 표준정규분포가 아닌 경우
	if (mu != 0 || sigma != 1) {
		return mu + sigma * inverse_normal_cdf(p, 0, 1, tolerance = tolerance);
	}

	float low_x = -10.0, low_p = 0.0; // normal_cdf(-10)는 0에 근접
	float hi_x = 10.0, hi_p = 1.0;	  // normal_cdf(10)는 1에 근접
	float mid_x = 0.0, mid_p = 0.0;

	while (hi_x - low_x > tolerance)	// 해당 p를 찾을 때까지 반복
	{
		mid_x = (low_x + hi_x) / 2; // 중간 값 계산
		mid_p = normal_cdf(mid_x, mu, sigma); // 중간 값의 cdf 값을 계산
		if (mid_p < p) {  // mid_p가 찾는 값보다 작으면 더 큰 값에서 탐색
			low_x = mid_x;
			low_p = mid_p;
		}
		else if (mid_p > p) { // mid_p가 찾는 값보다 크면 더 작은 값에서 탐색
			hi_x = mid_x;
			hi_p = mid_p;
		}
		else {	// p 값을 찾으면 break
			break;
		}
	}
	return mid_x;	// normal_cdf 값이 p인 x 반환
}

// 히스토그램 출력
void DrawHistogram(int histogram[400], int x_origin, int y_origin, int cnt) {
	MoveToEx(hdc, x_origin, y_origin, 0);
	LineTo(hdc, x_origin + cnt, y_origin);

	MoveToEx(hdc, x_origin, 100, 0);
	LineTo(hdc, x_origin, y_origin);

	for (int CurX = 0; CurX < cnt; CurX++) {
		for (int CurY = 0; CurY < histogram[CurX]; CurY++) {
			MoveToEx(hdc, x_origin + CurX, y_origin, 0);
			LineTo(hdc, x_origin + CurX, y_origin - histogram[CurX] / 2);
		}
	}
}
// 히스토그램 출력
void DrawHistogram(float histogram[400], int x_origin, int y_origin, int cnt) {
	MoveToEx(hdc, x_origin, y_origin, 0);
	LineTo(hdc, x_origin + cnt, y_origin);

	MoveToEx(hdc, x_origin, y_origin, 0);
	LineTo(hdc, x_origin, y_origin - 200);

	for (int CurX = 0; CurX < cnt; CurX++) {
		for (int CurY = 0; CurY < histogram[CurX]; CurY++) {
			MoveToEx(hdc, x_origin + CurX, y_origin, 0);
			LineTo(hdc, x_origin + CurX, y_origin - histogram[CurX] * 100);
		}
	}
}

// gaussianCDF에서 gaussianCDF_true를 뺀 값들 중 가장 큰 값을 반환
float Dminus(float gaussianCDF[], float gaussianCDF_true[])
{
	float data[401];

	for (int i = 0; i < 401; i++)
	{
		data[i] = gaussianCDF[i] - gaussianCDF_true[i];
	}

	return largest(data);
}

//gaussianCDF_true에서 gaussianCDF를 뺀 값들 중 가장 큰 값을 반환
float Dplus(float gaussianCDF[], float gaussianCDF_true[])
{
	float data[401];

	for (int i = 0; i < 401; i++)
	{
		data[i] = gaussianCDF_true[i] - gaussianCDF[i];
	}

	return largest(data);
}

// 배열에서 가장 큰 값을 반환
float largest(float data[])
{
	float large = data[0];

	for (int i = 1; i < 401; i++)
	{
		if (large < data[i])
			large = data[i];
	}

	return large;
}
