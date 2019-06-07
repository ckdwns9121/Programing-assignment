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
/* �����ð� �켱���� */

bool arriveCompare(SRTF &a, SRTF &b) {
	if (a.arrive == b.arrive) {
		if (a.arrive == 0 && b.arrive == 0) {
			return a.CPU_burst < b.CPU_burst;
		}
		return a.process < b.process;
	}
	return a.arrive < b.arrive;
}
/*������ burst �ȿ� �ִ� arrive �� ����*/
bool burstCompare(SRTF &a, SRTF &b) {
	/*���� �ð��� ����*/
	if (a.arrive == b.arrive) {
		/*cpu ���� �ð����� ������*/
		if (a.CPU_burst == b.CPU_burst) {
			/* ���μ��� �ѹ� ������ ����*/
			return a.process < b.process;
		}
		else a.CPU_burst < b.CPU_burst;
	}
	return a.CPU_burst < b.CPU_burst;
}
int func(int start) {
	/*ó�� �������� ���μ��� �ֱ�*/
	execution.push_back(ready[start]);
	while (true) {
		/*���� ����ϰ� �ִ� ť�� ������ �����ð� �˻� */
		if ((readyIndex) <= ready.size() - 1) {
			/*�������� ���μ����� �����ǰ� ����ϰ��ִ� ���μ����� �����ð��� ������*/
			if(now_pos == ready[readyIndex].arrive){
				/*������� �����ð��� ������ ã�Ƽ� �ٳֱ�*/
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
		/*CPU ����ð��� �پ���*/
		if (execution[0].CPU_burst == 0) {
			/*�������� ���Ϳ��� �����*/
			execution.erase(execution.begin() + nowIndex);
			/*�������� ���Ͱ� ��������� ����ť�� ������ �����Ͱ� �����ִٸ�*/
			if (execution.empty() && (readyIndex) != ready.size()) {
				/*cpu ����� �ð��� �߻��ϹǷ� ������������ �Ű��ش�*/
				now_pos = ready[readyIndex].arrive;
				if (now_pos == ready[readyIndex].arrive) {
					/*������� �����ð��� ������ ã�Ƽ� �ٳֱ�*/
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
		/*���̻� ������ ���μ����� ���� ����ť�� ���� ����������*/
		if (execution.empty() && (readyIndex) == ready.size())
		{
			return wait;
		}
		else {
			execution[0].CPU_burst--; //�����ѽð� ��ŭ ���ְ�
			now_pos++; //��ŭ ���������� ������ ++
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
	/*�����ð� �켱 ����*/
	sort(ready.begin(), ready.end(), arriveCompare);
	output_fp<<func(0);
	return 0;
}