
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
/* �������� �������� ���� */
bool arriveCompare(FCFS a, FCFS b) {
	/*�������� �������� �����Ϸ� ������ ���������� ������*/
	if (a.arrive == b.arrive) {
		/*���μ��� �ѹ� ������ ����*/
		return a.process < b.process;
	}
	/*���������� ������ ���� �ö󰡰� ����*/
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
		/*cpu�� ��½ð��� �߻�������*/
		if ((length - fcfs[i].arrive) <= 0) {
			wait -= length - fcfs[i].arrive;
			length = fcfs[i].arrive;
		}
		length += fcfs[i].burst;
	}
	output_fp << wait;
	return 0;
}