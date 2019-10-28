/*
	DISK Scheduling SIMULATOR
*/

#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

ifstream input_fp("disk.inp");
ofstream output_fp("disk.out");

typedef struct DISK {
	int arrive_time;
	int track_num;
}DISK;

int sstf_nearIndex();
vector<DISK> disk_v;
vector<DISK> ready_q;
int GLOBAL_TIME = 0; //����ð�
int HEAD_POINT = 0; //�����ġ
int LOOK_count = 0; //LOOK �Ҷ� ������ȯ Ƚ��
int direct = 0; // ������ȯ ����

void fcfs(int s) {
	int loop = disk_v.size();
	int service_time = s; //����Ÿ��
	int index = 0;
	bool check = false;
	while (1) {
		/*��û�� ���� �ִ��� �˻�*/
		for (index; index < loop; index++) {
			if (GLOBAL_TIME >= disk_v[index].arrive_time) {
				check = true;
				ready_q.push_back(disk_v[index]);
			}
			else {
				if (!check)
					GLOBAL_TIME = disk_v[index--].arrive_time;
				else
					break;
			}
		}
		/*�˻簡 �������� ����ť�� �ִ³� ����*/
		int loop2 = ready_q.size();
		for (int i = 0; i < loop2; i++) {
			int distance = ready_q[i].track_num - HEAD_POINT;
			if (distance < 0) distance *= -1;
			HEAD_POINT = ready_q[i].track_num;
			GLOBAL_TIME += distance + service_time;
		}
		ready_q.clear();
		check = false;
		if (index == loop) {
			output_fp << GLOBAL_TIME << " " << HEAD_POINT;
			break;
		}
	}
}
int sstf_nearIndex() {
	int loop = ready_q.size();
	int temp = 2147483640;
	int returnIndex = 0;
	for (int i = 0; i < loop; i++) {
		int distance = ready_q[i].track_num - HEAD_POINT;
		if (distance < 0) distance *= -1;
		if (temp > distance) {
			temp = distance;
			returnIndex = i;
		}
	}
	return returnIndex;
}
int sstf_pushQueue(int index, bool check) {
	check = false;
	for (index; index < disk_v.size(); index++) {
		if (GLOBAL_TIME >= disk_v[index].arrive_time) {
			check = true;
			ready_q.push_back(disk_v[index]);
		}
		else {
			if (!check && ready_q.empty()) {
				GLOBAL_TIME = disk_v[index--].arrive_time;
			}
			else {
				break;
			}
		}
	}
	return index;
}

void sstf(int s) {
	int loop = disk_v.size();
	int service_time = s; //����Ÿ��
	int index = 0;
	bool check = false;
	while (1) {
		index = sstf_pushQueue(index, check);
		/*���� ��� �������� ������ ã��*/
		while (!ready_q.empty()) {
			int near_index = sstf_nearIndex();
			int distance = ready_q[near_index].track_num - HEAD_POINT;
			if (distance < 0) distance *= -1;
			HEAD_POINT = ready_q[near_index].track_num;
			GLOBAL_TIME += distance + service_time;
			ready_q.erase(ready_q.begin() + near_index);
			index = sstf_pushQueue(index, check);
		}
		check = false;
		if (index == loop) {
			output_fp << GLOBAL_TIME << " " << HEAD_POINT;
			break;
		}
	}
}
int look_nearIndex() {
	int loop = ready_q.size();
	int temp = 2147483640;
	int returnIndex = 0;
	for (int i = 0; i < loop; i++) {
		int distance = ready_q[i].track_num - HEAD_POINT;
		if (distance < 0) distance *= -1;
		if (temp > distance) {
			temp = distance;
			returnIndex = i;
		}
	}
	return returnIndex;
}

void look_pushQueue(int index) {
	bool check = false;
	bool GT_CHECK = false;
	int loop = disk_v.size();
	for (int i = 0; i < loop; i++) {
		/*������ �����϶�*/
		if (!direct) {
			if (GLOBAL_TIME >= disk_v[index].arrive_time) {
				GT_CHECK = true;
				if (HEAD_POINT < disk_v[index].track_num) {
					check = true;
					ready_q.push_back(disk_v[index]);
					disk_v.erase(disk_v.begin() + index);
				}
				else index++;
			}
		}
		/*���� �����϶�*/
		else if(direct){
			GT_CHECK = true;
			if (GLOBAL_TIME >= disk_v[index].arrive_time) {
				if (HEAD_POINT > disk_v[index].track_num) {
					check = true;
					ready_q.push_back(disk_v[index]);
					disk_v.erase(disk_v.begin() + index);
				}
				else index++;
			}
		}
		if (!check && ready_q.empty() && !GT_CHECK) {
			break;
		}
	}
}

void direction_set() {
	vector<DISK> TEMP_V;
	int distance = 0;
	int check = 2147483640;
	int temp_dis = 0;
	/*���� �������� ��û�� ����� �� �ִ��� �˻�*/
	for (int i = 0; i < disk_v.size(); i++) {
		if (GLOBAL_TIME > disk_v[i].arrive_time) {
			if (direct == 1) {
				if (HEAD_POINT > disk_v[i].track_num)return;
			}
			else {
				if (HEAD_POINT < disk_v[i].track_num) return;
			}
		}
	}

	for (int i = 0; i < disk_v.size(); i++) {
		if (GLOBAL_TIME >= disk_v[i].arrive_time) {
			distance = HEAD_POINT - disk_v[i].track_num;
			temp_dis = distance;
			if (temp_dis < 0) temp_dis *= -1;
			if (check > temp_dis) {
				check = temp_dis;
				if (distance < 0) direct = 0;
				else direct = 1;
			}
			break;
		}
		else {
			GLOBAL_TIME = disk_v[0].arrive_time;
			distance = HEAD_POINT - disk_v[0].track_num;
			if (distance < 0) direct = 0;
			else direct = 1;
			break;
		}
	}
}

void look(int s) {
	int loop = disk_v.size();
	int service_time = s; //����Ÿ��
	int index = 0;
	int distance = 0;
	bool check = false;
	while (!disk_v.empty()) {
		look_pushQueue(index);
		while (!ready_q.empty()) {
			int near_index = look_nearIndex();
			if (!direct) distance = ready_q[near_index].track_num - HEAD_POINT;
			else distance = HEAD_POINT - ready_q[near_index].track_num;
			HEAD_POINT = ready_q[near_index].track_num;
			GLOBAL_TIME += distance + service_time;
			ready_q.erase(ready_q.begin() + near_index);
			if (ready_q.empty()) {
				 direction_set();
			}
			look_pushQueue(index);
		}
	}
	output_fp << GLOBAL_TIME << " " << HEAD_POINT;
}

int main() {
	string str;
	int s;
	input_fp >> str >> s;
	while (1) {
		DISK disk;
		input_fp >> disk.arrive_time >> disk.track_num;
		if (disk.arrive_time == -1 && disk.track_num == -1) break;
		else disk_v.push_back(disk);
	}
	if (str == "FCFS") {
		fcfs(s);
	}
	else if (str == "SSTF") {
		sstf(s);
	}
	else {
		look(s);
	}

}