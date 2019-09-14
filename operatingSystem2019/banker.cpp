#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

typedef struct Allocation { int alloc[50]; }Allocation;
typedef struct MAX { int max_resource[50]; }MAX;
typedef struct Avaliable { int avali[50]; }Avaliable;
typedef struct Need { int need_arr[50]; }Need;
typedef struct Requset { int process_num; int requset_resource[50]; } Requset;
typedef struct Release { int process_num; int release_resource[50]; } Release;

Avaliable av; //��밡���Ѱ� 
MAX maax; // �ִ� �ʿ��Ѱ�
Allocation allocation; //������ΰ�
Release release; // �ݳ�
Requset requset; // ��û

vector<MAX> max_v; //�ƽ�ť
vector<Allocation> alloc_v; //����� ����
vector<Avaliable> av_v; //��밡�� ����
vector<Requset> req_v; //��û ����
vector<Release> rel_v; //�ݳ� ����
vector<Need> need_v; //�ϵ� ����
vector<Requset> ready_queue; //����ť

void safe(int n, int m) {
	bool check1 = false;
	// ��̺��� ������Ʈ ���ְ�
	// ������Ʈ�� �˷����̼ǿ� ������
	int p_num = req_v[0].process_num; //��û�� ���μ����ѹ�

	//��û�� �����Ѱ� ?
	//MAX �� �ʰ��ϸ� ���ʿ� ��û��ü �Ұ�
	for (int i = 0; i < m; i++) {
		if (req_v[0].requset_resource[i] + alloc_v[p_num].alloc[i] > max_v[p_num].max_resource[i]) {
			return;
		}
	}
	//INPUT �� ���� ��û
	for (int i = 0; i < m; i++) {
		if (av_v[0].avali[i] - req_v[0].requset_resource[i] < 0) {
			ready_queue.push_back(requset);
			return;
		}
		else if (req_v[0].requset_resource[i] + alloc_v[p_num].alloc[i] > max_v[p_num].max_resource[i]) {
			return;
		}
	}
	int needCheck = 0;
	bool tempCheck;
	//��û�� ����� �� ������ �ٸ� p�� ��û�� �ϳ��� ����� �� �ֳ� üũ
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			int temp;
			if (i != p_num) {
				temp = (av_v[0].avali[j] - req_v[0].requset_resource[j]);
				temp -= (need_v[i].need_arr[j]);
			}
			else {
				temp = (av_v[0].avali[j] - req_v[0].requset_resource[j]);
				temp -= (need_v[i].need_arr[j] - req_v[0].requset_resource[j]);
			}
			if (temp < 0) {
				//��û�� ������ٶ� false
				tempCheck = false;
				break;
			}
			else {
				//����ָ� true
				tempCheck = true;
			}
		}
		if (tempCheck == true) {
			needCheck++;
		}
	}
	//��û�� �ϳ��� ����� �� �������� ���� ��̺� ���
	if (needCheck > 0) {
		for (int i = 0; i < m; i++) {
			av_v[0].avali[i] -= req_v[0].requset_resource[i]; //1
			alloc_v[p_num].alloc[i] += req_v[0].requset_resource[i]; //2
			need_v[p_num].need_arr[i] -= req_v[0].requset_resource[i]; //3
		}
		return;
	}
	//��û�� ����� �� ������ �ٸ� p�� ��û�� �ϳ��� ������� �� (�����)
	else {
		ready_queue.push_back(requset);
		return;
	}
}

void check_ready(int n, int m) {

	int Qsize = ready_queue.size();
	bool check = true;
	int start = 0;
	int needCheck = 0;
	int p_num = ready_queue[start].process_num; //������ ���μ����ѹ�
	while (Qsize--) {

		for (int i = 0; i < m; i++) {
			//�ݳ� �Ѱɷ� ��û�� ��� �� �� �ִ��� üũ
			if ((av_v[0].avali[i] - ready_queue[start].requset_resource[i] < 0) || ((alloc_v[ready_queue[start].process_num].alloc[i] + ready_queue[start].requset_resource[i]) > max_v[ready_queue[start].process_num].max_resource[i])) {
				check = false; //��û �Ұ�
				start++;
				break; //�ݳ��� �������� �ұ��ϰ� ��û�� ������ָ� ��������ť�� Ȯ��
			}
			else check = true;
		}

		//����ť�� �ִ� ��û�� �����ϸ� ��û�� ��������� ������ ���� Ȯ��( �ϳ��� ��û ����ٲ� �ִ°�?)
		if (check == true) {
			bool tempCheck = false;
			int p_num = ready_queue[start].process_num; //������ ���μ����ѹ�
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					int temp;
					//��û�� ���� �ʴ� ���μ��� ����
					if (i != p_num) {
						temp = (av_v[0].avali[j] - ready_queue[start].requset_resource[j]);
						temp -= (need_v[i].need_arr[j]);
					}
					//��û�� �� ���μ����� ����
					else {
						temp = (av_v[0].avali[j] - ready_queue[start].requset_resource[j]);
						temp -= (need_v[i].need_arr[j] - ready_queue[start].requset_resource[j]);
					}
					//��û�� ������� ��
					if (temp < 0) {
						tempCheck = false;
						break;
					}
					else {
						//����ָ� true
						tempCheck = true;
					}
				}
				if (tempCheck == true) {
					needCheck++;
				}
			}
			if (needCheck > 0) {
				int p_num = ready_queue[start].process_num;
				for (int i = 0; i < m; i++) {
					av_v[0].avali[i] -= ready_queue[start].requset_resource[i]; //1
					alloc_v[p_num].alloc[i] += ready_queue[start].requset_resource[i]; //2
					need_v[p_num].need_arr[i] -= ready_queue[start].requset_resource[i]; //3
				}
				ready_queue.erase(ready_queue.begin() + start);
				needCheck = 0;

			}
			else {
				start++;
			}
		}
	}
}
//�ڿ� �ݳ�
void release_resource(int n, int m) {
	int p_num = rel_v[0].process_num;
	for (int i = 0; i < m; i++) {
		av_v[0].avali[i] += rel_v[0].release_resource[i];
		alloc_v[p_num].alloc[i] -= rel_v[0].release_resource[i];
		need_v[p_num].need_arr[i] += rel_v[0].release_resource[i];
	}
	if (!ready_queue.empty()) {
		check_ready(n, m);
	}
	else return;
}

int main() {

	ifstream input_fp("banker.inp");
	ofstream output_fp("banker.out");
	string str;
	int n, m;
	/* input process count && resource count*/
	input_fp >> n >> m;
	/* input all count*/
	for (int i = 0; i < m; i++) {
		input_fp >> av.avali[i];
	}
	/*input Max resource count*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			input_fp >> maax.max_resource[j];
		}
		max_v.push_back(maax);
	}
	/*input Allocation resouce count*/
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			input_fp >> allocation.alloc[j];
			av.avali[j] -= allocation.alloc[j];
		}
		alloc_v.push_back(allocation);
	}
	av_v.push_back(av);
	/*save need arr*/
	for (int i = 0; i < n; i++) {
		Need need;
		for (int j = 0; j < m; j++) {
			need.need_arr[j] = max_v[i].max_resource[j] - alloc_v[i].alloc[j];
		}
		need_v.push_back(need);
	}
	while (true) {
		input_fp >> str;

		if (str == "request") {
			input_fp >> requset.process_num;
			for (int i = 0; i < m; i++) {
				input_fp >> requset.requset_resource[i];
			}
			req_v.push_back(requset);
			safe(n, m);
			req_v.pop_back();
			for (int i = 0; i < m; i++) output_fp << av_v[0].avali[i] << " ";
			output_fp << endl;
		}

		else if (str == "release") {
			input_fp >> release.process_num;
			for (int i = 0; i < m; i++) {
				input_fp >> release.release_resource[i];
			}
			rel_v.push_back(release);
			release_resource(n, m);
			rel_v.pop_back();
			for (int i = 0; i < m; i++) output_fp << av_v[0].avali[i] << " ";
			output_fp << endl;
		}
		else break;
	}
	return 0;

}