#include <fstream>
#include <vector>
using namespace std;

vector<int> list, sorted;
long long ans = 0;


void merge(int left, int mid, int right) {
	int i, j, k, l;
	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right) {
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else {
			sorted[k++] = list[j++];
			ans += (mid - i + 1);
		}
	}
	if (i > mid) {
		for (int x = j; x <= right; x++)
			sorted[k++] = list[x];
	}
	else {
		for (int x = i; x <= mid; x++)
			sorted[k++] = list[x];
	}

	for (int i = left; i <= right; i++) 
		list[i] = sorted[i];
}

void merge_sort(int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		merge_sort(left, mid);
		merge_sort(mid + 1, right);
		merge(left, mid,right);
	}
}

int main() {

	ifstream input("inv.inp");
	ofstream output("inv.out");
	int t,n;
	input >> t;
	while (t--) {
		input >> n;
		list.clear();
		sorted.clear();
		list.resize(n);
		sorted.resize(n);
		ans = 0;
		for (int i = 0; i < n; i++) {
			input >> list[i];
		}
		merge_sort(0, n - 1);
		output << ans << "\n";
	}


	input.close();
	output.close();
	return 0;
}