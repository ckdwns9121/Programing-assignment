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

Avaliable av; //사용가능한거 
MAX maax; // 최대 필요한거
Allocation allocation; //사용중인거
Release release; // 반납
Requset requset; // 요청

vector<MAX> max_v; //맥스큐
vector<Allocation> alloc_v; //사용중 벡터
vector<Avaliable> av_v; //사용가능 벡터
vector<Requset> req_v; //요청 벡터
vector<Release> rel_v; //반납 벡터
vector<Need> need_v; //니드 벡터
vector<Requset> ready_queue; //레디큐

void safe(int n, int m) {
	bool check1 = false;
	// 어베이블에서 리퀘스트 빼주고
	// 리퀘스트를 알로케이션에 더해줌
	int p_num = req_v[0].process_num; //요청한 프로세스넘버

	//요청이 가능한가 ?
	//MAX 를 초과하면 애초에 요청자체 불가
	for (int i = 0; i < m; i++) {
		if (req_v[0].requset_resource[i] + alloc_v[p_num].alloc[i] > max_v[p_num].max_resource[i]) {
			return;
		}
	}
	//INPUT 에 대한 요청
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
	//요청을 들어줄 수 있을때 다른 p의 요청을 하나라도 들어줄 수 있나 체크
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
				//요청을 못들어줄때 false
				tempCheck = false;
				break;
			}
			else {
				//들어주면 true
				tempCheck = true;
			}
		}
		if (tempCheck == true) {
			needCheck++;
		}
	}
	//요청을 하나라도 들어줄 수 있을때는 실제 어레이블 계산
	if (needCheck > 0) {
		for (int i = 0; i < m; i++) {
			av_v[0].avali[i] -= req_v[0].requset_resource[i]; //1
			alloc_v[p_num].alloc[i] += req_v[0].requset_resource[i]; //2
			need_v[p_num].need_arr[i] -= req_v[0].requset_resource[i]; //3
		}
		return;
	}
	//요청은 들어줄 수 있지만 다른 p의 요청을 하나라도 못들어줄 때 (데드락)
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
	int p_num = ready_queue[start].process_num; //가능한 프로세스넘버
	while (Qsize--) {

		for (int i = 0; i < m; i++) {
			//반납 한걸로 요청을 들어 줄 수 있는지 체크
			if ((av_v[0].avali[i] - ready_queue[start].requset_resource[i] < 0) || ((alloc_v[ready_queue[start].process_num].alloc[i] + ready_queue[start].requset_resource[i]) > max_v[ready_queue[start].process_num].max_resource[i])) {
				check = false; //요청 불가
				start++;
				break; //반납을 했음에도 불구하고 요청을 못들어주면 다음레디큐꺼 확인
			}
			else check = true;
		}

		//레디큐에 있는 요청이 가능하면 요청을 들어줬을때 세이프 상태 확인( 하나라도 요청 들어줄께 있는가?)
		if (check == true) {
			bool tempCheck = false;
			int p_num = ready_queue[start].process_num; //가능한 프로세스넘버
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					int temp;
					//요청을 하지 않는 프로세스 연산
					if (i != p_num) {
						temp = (av_v[0].avali[j] - ready_queue[start].requset_resource[j]);
						temp -= (need_v[i].need_arr[j]);
					}
					//요청을 한 프로세스의 연산
					else {
						temp = (av_v[0].avali[j] - ready_queue[start].requset_resource[j]);
						temp -= (need_v[i].need_arr[j] - ready_queue[start].requset_resource[j]);
					}
					//요청을 못들어줄 때
					if (temp < 0) {
						tempCheck = false;
						break;
					}
					else {
						//들어주면 true
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
//자원 반납
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