/*
	SJF Scheduling Simulator
*/
#include <fstream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
#define MAX 51

int wait = 0; //웨이팅 타임
int n = 0; //테스트 케이스
int standard = 0; //처음 시작점.
int startIndex = 1; // 연산하기 시작하는 인덱스
int endIndex = 0; // 마지막 인덱스

typedef struct SJF {
	int process = 0; //프로세스 넘버
	int arrive = 0; //도착시간
	int burst = 0; //CPU 사용시간
}SJF;
SJF arr[MAX];
/* 도착시간 우선정렬 */
bool arriveCompare(SJF a, SJF b) {
	if (a.arrive == b.arrive) {
		if (a.arrive == 0 && b.arrive == 0) {
			return a.burst < b.burst;
		}
		return a.process < b.process;
	}
	return a.arrive < b.arrive;
}
/*기준점 burst 안에 있는 arrive 만 정렬*/
bool burstCompare(SJF a, SJF b) {
	/*도착 시간이 같고*/
	if (a.arrive == b.arrive) {
		/*cpu 실행 시간마저 같으면*/
		if (a.burst == b.burst) {
			/* 프로세스 넘버 순으로 정렬*/
			return a.process < b.process;
		}
		else a.burst < b.burst;
	}
	return a.burst < b.burst;
}

int func(int present_pos) {
	endIndex = 0;
	/* 제일처음 시작지점 기준 안으로 ready queue 에 대기하고 있는 범위 찾기*/
	for (int i = startIndex; i < n; i++) {
		if (present_pos >= arr[i].arrive)
			endIndex++;
	}
	/* 찾은 범위 기준으로 그 범위 까지만 burst 순위로 정렬*/
	sort(arr + startIndex, arr + startIndex + endIndex, burstCompare);
	for (int i = 1; i < n; i++) {
		wait += present_pos - arr[i].arrive;
		/*cpu 가 노는 시간이 발생 했을시 */
		if ((present_pos - arr[i].arrive) <= 0) {
			wait -= present_pos - arr[i].arrive;
			present_pos = arr[i].arrive;
		}
		arr[i].burst += present_pos;
		endIndex = 0;
		/* 한 프로세스가 실행되고 끝나면 다음 프로세스로 ++*/
		startIndex++;
		present_pos = arr[i].burst;
		/*현재 기준인 프로세스의 burst 값 기준으로 ready queue 에 대기중인 프로세스 갯수찾기*/
		for (int j = startIndex; j < n; j++) {
			if (present_pos >= arr[j].arrive) {
				endIndex++;
			}
		}
		/*대기중인 프로세스가 0 개가 아니면 cpu가 노는 시간이 아니므로 다시 정렬*/
		if (endIndex != 0) {
			sort(arr + startIndex, arr + startIndex + endIndex, burstCompare);
		}
	}
	return wait;
}
int main() {
	ifstream input_fp("sjf.inp");
	ofstream output_fp("sjf.out");
	int p, a, b;
	input_fp >> n;
	/* get process info*/
	for (int i = 0; i < n; i++) {
		input_fp >> arr[i].process >> arr[i].arrive >> arr[i].burst;
	}
	/*제일 처음 도착시간이 낮은거 부터 정렬을 시작함*/
	sort(arr, arr + n, arriveCompare);
	/*정렬이 끝나고나면 도착시간이 0 인놈이
	 배열의 제일 앞에 와있음 그래서 기준점(standard)를 
	 0번째로 시작
	*/
	standard = arr[0].burst; //기준점을 0번째로 시작
	output_fp << func(standard); 
	return 0;
}