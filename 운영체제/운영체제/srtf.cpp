#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#pragma warning(disable:4996)
using namespace std;
#define MAX 51

int wait = 0;
int n = 0;
int nowIndex = 0;
int now_pos = 0;
int readyIndex = 1;

typedef struct SRTF {
	int process = 0;
	int arrive = 0;
	int CPU_burst = 0;
}SRTF;
// wait = burst - trun;
vector<SRTF> ready;
vector<SRTF> execution;
/* 도착시간 우선정렬 */

bool arriveCompare(SRTF &a, SRTF &b) {
	if (a.arrive == b.arrive) {
		if (a.arrive == 0 && b.arrive == 0) {
			return a.CPU_burst < b.CPU_burst;
		}
		return a.process < b.process;
	}
	return a.arrive < b.arrive;
}
/*기준점 burst 안에 있는 arrive 만 정렬*/
bool burstCompare(SRTF &a, SRTF &b) {
	/*도착 시간이 같고*/
	if (a.arrive == b.arrive) {
		/*cpu 실행 시간마저 같으면*/
		if (a.CPU_burst == b.CPU_burst) {
			/* 프로세스 넘버 순으로 정렬*/
			return a.process < b.process;
		}
		else a.CPU_burst < b.CPU_burst;
	}
	return a.CPU_burst < b.CPU_burst;
}
int func(int start) {
	/*처음 실행중인 프로세스 넣기*/
	execution.push_back(ready[start]);
	while (true) {
		/*다음 대기하고 있는 큐가 있으면 도착시간 검사 */
		if ((readyIndex) <= ready.size() - 1) {
			/*실행중인 프로세스의 포지션과 대기하고있는 프로세스의 도착시간이 같으면*/
			if(now_pos == ready[readyIndex].arrive){
				/*대기중인 도착시간이 같은거 찾아서 다넣기*/
				for (int i = readyIndex; i < ready.size(); i++) {
					if (now_pos == ready[readyIndex].arrive) {
						execution.push_back(ready[readyIndex]);
						sort(execution.begin(), execution.end(), burstCompare);
						start++;
						readyIndex++;
					}
				}
			}
		}
		/*CPU 실행시간을 다쓰면*/
		if (execution[0].CPU_burst == 0) {
			/*실행중인 벡터에서 지운다*/
			execution.erase(execution.begin() + nowIndex);
			/*실행중인 벡터가 비어있으나 레디큐에 실행할 데이터가 남아있다면*/
			if (execution.empty() && (readyIndex) != ready.size()) {
				/*cpu 가노는 시간이 발생하므로 현재포지션을 옮겨준다*/
				now_pos = ready[readyIndex].arrive;
				if (now_pos == ready[readyIndex].arrive) {
					/*대기중인 도착시간이 같은거 찾아서 다넣기*/
					for (int i = readyIndex; i < ready.size(); i++) {
						if (now_pos == ready[readyIndex].arrive) {
							execution.push_back(ready[readyIndex]);
							sort(execution.begin(), execution.end(), burstCompare);
							start++;
							readyIndex++;
						}
					}
				}
				else {
					execution.push_back(ready[readyIndex]);
					sort(execution.begin(), execution.end(), burstCompare);
					start++;
					readyIndex++;
				}
			}
		}
		/*더이상 실행할 프로세스가 없고 레디큐의 끝에 도달했으면*/
		if (execution.empty() && (readyIndex) == ready.size())
		{
			return wait;
		}
		else {
			execution[0].CPU_burst--; //실행한시간 만큼 빼주고
			now_pos++; //얼만큼 실행한지의 포지션 ++
			wait += execution.size() - 1;
		}
	}
}

int main() {
	ifstream input_fp("srtf.inp");
	ofstream output_fp("srtf.out");
	int p, a, b;
	input_fp >> n;
	ready.reserve(n);
	/* get process info*/
	for (int i = 0; i < n; i++) {
		SRTF srtf;
		input_fp >> srtf.process >> srtf.arrive >> srtf.CPU_burst;
		ready.push_back(srtf);
	}
	/*도착시간 우선 정렬*/
	sort(ready.begin(), ready.end(), arriveCompare);
	output_fp<<func(0);
	return 0;
}