/*
	SJF Scheduling Simulator
*/
#include <fstream>
#include <algorithm>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
#define MAX 51

int wait = 0; //������ Ÿ��
int n = 0; //�׽�Ʈ ���̽�
int standard = 0; //ó�� ������.
int startIndex = 1; // �����ϱ� �����ϴ� �ε���
int endIndex = 0; // ������ �ε���

typedef struct SJF {
	int process = 0; //���μ��� �ѹ�
	int arrive = 0; //�����ð�
	int burst = 0; //CPU ���ð�
}SJF;
SJF arr[MAX];
/* �����ð� �켱���� */
bool arriveCompare(SJF a, SJF b) {
	if (a.arrive == b.arrive) {
		if (a.arrive == 0 && b.arrive == 0) {
			return a.burst < b.burst;
		}
		return a.process < b.process;
	}
	return a.arrive < b.arrive;
}
/*������ burst �ȿ� �ִ� arrive �� ����*/
bool burstCompare(SJF a, SJF b) {
	/*���� �ð��� ����*/
	if (a.arrive == b.arrive) {
		/*cpu ���� �ð����� ������*/
		if (a.burst == b.burst) {
			/* ���μ��� �ѹ� ������ ����*/
			return a.process < b.process;
		}
		else a.burst < b.burst;
	}
	return a.burst < b.burst;
}

int func(int present_pos) {
	endIndex = 0;
	/* ����ó�� �������� ���� ������ ready queue �� ����ϰ� �ִ� ���� ã��*/
	for (int i = startIndex; i < n; i++) {
		if (present_pos >= arr[i].arrive)
			endIndex++;
	}
	/* ã�� ���� �������� �� ���� ������ burst ������ ����*/
	sort(arr + startIndex, arr + startIndex + endIndex, burstCompare);
	for (int i = 1; i < n; i++) {
		wait += present_pos - arr[i].arrive;
		/*cpu �� ��� �ð��� �߻� ������ */
		if ((present_pos - arr[i].arrive) <= 0) {
			wait -= present_pos - arr[i].arrive;
			present_pos = arr[i].arrive;
		}
		arr[i].burst += present_pos;
		endIndex = 0;
		/* �� ���μ����� ����ǰ� ������ ���� ���μ����� ++*/
		startIndex++;
		present_pos = arr[i].burst;
		/*���� ������ ���μ����� burst �� �������� ready queue �� ������� ���μ��� ����ã��*/
		for (int j = startIndex; j < n; j++) {
			if (present_pos >= arr[j].arrive) {
				endIndex++;
			}
		}
		/*������� ���μ����� 0 ���� �ƴϸ� cpu�� ��� �ð��� �ƴϹǷ� �ٽ� ����*/
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
	/*���� ó�� �����ð��� ������ ���� ������ ������*/
	sort(arr, arr + n, arriveCompare);
	/*������ �������� �����ð��� 0 �γ���
	 �迭�� ���� �տ� ������ �׷��� ������(standard)�� 
	 0��°�� ����
	*/
	standard = arr[0].burst; //�������� 0��°�� ����
	output_fp << func(standard); 
	return 0;
}