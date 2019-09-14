#include <fstream>
#include <vector>

using namespace std;

ifstream input_fp("page.inp");
ofstream output_fp("page.out");
#define MAX 99999

static int frame;
static int pagefalut_count = 0;

void FIFO();
void LRU();
void OPT();
void printing(int num);
bool findSamePage_inPage_table(int PID, int page_num);
int notPagefalut_returnIndex_inPage_table(int PID, int page_num);
int findindOPT_victom(int PID, int page_num, int start);
int returnIndex(int PID, int pop);

typedef struct INPUT {
	int PID, page_num;
}INPUT;
typedef struct MEMORY {
	int PID, page_num;
}MEMORY;
typedef struct PAGE_TABLE {
	int page_num, pointer;
}PAGE_TABLE;

vector<INPUT> input_v;
vector<MEMORY> memory_v;
vector<vector<PAGE_TABLE> >page_table;

bool findSamePage_inPage_table(int PID, int page_num) {
	int loop = page_table[PID].size();
	for (int i = 0; i < loop; i++) {
		if (page_table[PID][i].page_num == page_num)
			return true;
	}
	return false;
}
int notPagefalut_returnIndex_inPage_table(int PID, int page_num) {
	int loop = page_table[PID].size();
	for (int index = 0; index < loop; index++) {
		if (page_table[PID][index].page_num == page_num)
			return index;
	}
}
int returnIndex(int PID, int pop) {
	int loop = page_table[PID].size();
	for (int i = 0; i < loop; i++) {
		if (pop == page_table[PID][i].pointer) {
			return i;
		}
	}
}
int findindOPT_victom(int PID, int page_num ,int start) {
	vector<MEMORY> temp_v;
	int loop = input_v.size();
	int loop2 = page_table[PID].size();
	int index = 0;
	int max_index = -1;
	int temp = -1;
	bool check = false;
	while (loop2--) {
		int find_PID = PID;
		int find_page_num = page_table[PID][index].page_num;
		for (int i = start+1; i < loop; i++) {
			if (input_v[i].PID == find_PID && input_v[i].page_num == find_page_num) {
				temp = i;
				check = true;
				if (max_index < temp)
					max_index = temp;
				break;
			}
		}

		if (check == false)
			temp_v.push_back({ find_PID, find_page_num });
		
		check= false;
		index++;
		temp = -1;
	}
	if (max_index == -1)
		return page_table[PID][0].pointer;

	else if (!temp_v.empty()) {
		int result =temp_v[0].page_num;
		int loop = page_table[PID].size();
		for (int i = 0; i < loop; i++) {
			if (result == page_table[PID][i].page_num)
				return page_table[PID][i].pointer;
		}
	}
	else {
		int result = input_v[max_index].page_num;
		int loop = page_table[PID].size();
		for (int i = 0; i < loop; i++) {
			if (result == page_table[PID][i].page_num)
				return page_table[PID][i].pointer;
		}
	}
}

void FIFO() {
	int loop = input_v.size();
	int pointer = 0;
	for (int i = 0; i <loop;i++){
		int PID = input_v[i].PID;
		int page_num = input_v[i].page_num;
		/*������ ����ŭ ������ ���� ������*/
		if (page_table[PID].size() != frame) {
			/*������ ���̺� �ȿ� ���� �������ѹ� �ֳ� �˻�*/
			if (!findSamePage_inPage_table(PID, page_num)) { //������
				page_table[PID].push_back({ page_num,pointer }); //[11] = <2,3>
				memory_v.push_back({ PID,page_num });
				pagefalut_count++;
				pointer++;
			}
		}
		/*������ ����ŭ ������ ������ victom Ž���� ���ڸ� ����*/
		else {
			/*������ ���̺� �ȿ� ���� �������ѹ� �ֳ� �˻�*/
			if (!findSamePage_inPage_table(PID, page_num)) {
				int pop = page_table[PID][0].pointer;
				memory_v[pop].page_num = page_num;
				memory_v[pop].PID = PID;
				page_table[PID].erase(page_table[PID].begin() + 0); 
				page_table[PID].push_back({ page_num,pop });
				pagefalut_count++;
			}
		}
	}
}
void LRU() {
	int loop = input_v.size();
	int pointer = 0;
	for (int i = 0; i < loop; i++) {
		int PID = input_v[i].PID;
		int page_num = input_v[i].page_num;
		/*������ ����ŭ ������ ���� ������ */
		if (page_table[PID].size() != frame) {
			/*������ ��Ʈ�� �Ͼ�� �˻� */
			if (!findSamePage_inPage_table(PID, page_num)) { //�Ͼ���� 
				page_table[PID].push_back({ page_num,pointer });
				memory_v.push_back({ PID,page_num });
				pagefalut_count++;
				pointer++;
			}
			/*������ ��Ʈ�� �Ͼ�� �ʾ�����*/
			else {
				int index = notPagefalut_returnIndex_inPage_table(PID, page_num);
				int pop = page_table[PID][index].pointer;
				page_table[PID].erase(page_table[PID].begin() + index);
				page_table[PID].push_back({ page_num,pop });
			}
		}
		/*������ ����ŭ ������ ������ victom Ž���� ���ڸ� ����*/
		else {
			/*������ ��Ʈ�� �Ͼ�� �˻� */
			if (!findSamePage_inPage_table(PID, page_num)) { //�Ͼ����
				int pop = page_table[PID][0].pointer;
				memory_v[pop].page_num = page_num;
				memory_v[pop].PID = PID;
				page_table[PID].erase(page_table[PID].begin() + 0); //������ ���̺� ����
				page_table[PID].push_back({ page_num,pop });
				pagefalut_count++;
			}
			/*������ ��Ʈ �Ȼ����� ���*/
			else {
				int index = notPagefalut_returnIndex_inPage_table(PID, page_num);
				int pop = page_table[PID][index].pointer;
				page_table[PID].erase(page_table[PID].begin() + index);
				page_table[PID].push_back({ page_num,pop });
			}
		}
	}
}
void OPT() {
	/*���¾��� �� �����¾�
	  ��δ� ������ �ִ¾��� �� �ָ�
	  n�����ְ� k���� ������ k���߿� �� �����¾�
	  */
	int loop = input_v.size();
	int pointer = 0;
	for (int i = 0; i < loop; i++) {
		int PID = input_v[i].PID;
		int page_num = input_v[i].page_num;
		/*������ ����ŭ ������ ���� ������*/
		if (page_table[PID].size() != frame) {
			/*������ ��Ʈ�� �Ͼ�� ��*/
			if(!findSamePage_inPage_table(PID,page_num)){
				page_table[PID].push_back({ page_num,pointer });
				memory_v.push_back({ PID,page_num });
				pagefalut_count++;
				pointer++;
			}
		}
		/*������ ����ŭ ������ ���� �� victom Ž��*/
		else {
			if (!findSamePage_inPage_table(PID, page_num)) { //�Ͼ����
				int pop = findindOPT_victom(PID, page_num, i);
				int index = returnIndex(PID, pop);
				memory_v[pop].page_num = page_num;
				memory_v[pop].PID = PID;
				page_table[PID].erase(page_table[PID].begin() + index); //������ ���̺� ����
				page_table[PID].push_back({ page_num,pop });
				pagefalut_count++;
			}
		}

	}
}
void printing(int num) {
	int loop = memory_v.size();
	if (num == 1) {
		output_fp << "FIFO: "<< pagefalut_count<<endl;
		for (int i = 0; i < loop; i++)
			output_fp << i << " " << memory_v[i].PID << " " << memory_v[i].page_num<<endl;
	}
	else if (num == 2) {
		output_fp << "LRU: " << pagefalut_count << endl;
		for (int i = 0; i < loop; i++)
			output_fp << i << " " << memory_v[i].PID << " " << memory_v[i].page_num << endl;

	}
	else {
		output_fp << "OPT: " << pagefalut_count << endl;
		for (int i = 0; i < loop; i++)
			output_fp << i << " " << memory_v[i].PID << " " << memory_v[i].page_num << endl;
	}
	pagefalut_count = 0;
	memory_v.clear();
	page_table.clear();
	page_table.resize(MAX);
}
int main() {
	page_table.resize(MAX);
	input_fp >> frame;
	while (true) {
		INPUT input;
		input_fp >> input.PID >> input.page_num;
		if (input.PID == -1 && input.page_num == -1)
			break;
		else
			input_v.push_back(input);
	}
	FIFO();printing(1);
	LRU();printing(2);
	OPT();printing(3);
	return 0;
}
