
#include <fstream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
#define MAX 50
static int wait = 0;
typedef struct FCFS{
	int process = 0; 
	int arrive = 0; 
	int burst = 0; 
}FCFS;
FCFS fcfs[MAX];
/* 도착정보 기준으로 정렬 */
bool arriveCompare(FCFS a, FCFS b) {
	/*도착정보 기준으로 정렬하려 했으나 도착정보가 같을시*/
	if (a.arrive == b.arrive) {
		/*프로세스 넘버 순으로 정렬*/
		return a.process < b.process;
	}
	/*도착기준이 작은게 위로 올라가게 정렬*/
	return a.arrive < b.arrive;
}
int main() {
	ifstream input_fp("fcfs.inp");
	ofstream output_fp("fcfs.out");
	int testcase = 0;
	int wait = 0;
	int p, a, b;
	input_fp >> testcase;
	for (int i = 0; i < testcase; i++) {
		input_fp >> fcfs[i].process >> fcfs[i].arrive >> fcfs[i].burst;
	}
	sort(fcfs, fcfs + testcase, arriveCompare);
	int length = fcfs[0].burst; 
	for (int i = 1; i < testcase; i++) {
		wait += length - fcfs[i].arrive; 
		/*cpu가 노는시간이 발생했을시*/
		if ((length - fcfs[i].arrive) <= 0) {
			wait -= length - fcfs[i].arrive;
			length = fcfs[i].arrive;
		}
		length += fcfs[i].burst;
	}
	output_fp << wait;
	return 0;
}