#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX_ELEMENT 100001

typedef struct HeapType {
	long long heap[MAX_ELEMENT];
	long long heap_size;
}HeapType;

HeapType* CreateHeap() {
	HeapType* h = (HeapType*)malloc(sizeof(HeapType));
	h->heap_size = 0;
	return h;
}

void insert_min_heap(HeapType* h, long long item) {
	long long i = ++(h->heap_size);
	// Ʈ���� �ö󰡸鼭 �θ� ���� ��
	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
long long delete_min_heap(HeapType* h) {
	// item ������ �ܼ��� ��ȯ�� ���� ���д�.
	long long item = h->heap[1];
	long long temp = h->heap[(h->heap_size)--];
	long parent = 1;
	long child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ�� �� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) && (h->heap[child]) > h->heap[child + 1])
			child++;
		if (temp <= h->heap[child])
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

long long AddingCost(HeapType * h) {
	long long cost = 0;
	while (1) {
		long long num1 = delete_min_heap(h);
		long long num2 = delete_min_heap(h);
		cost += num1 + num2;
		if (h->heap_size == 0) {
			return cost;
		}
		else insert_min_heap(h, num1 + num2);
	}
}

int main() {
	FILE* input_fp = fopen("add.inp", "rt");
	FILE* output_fp = fopen("add.out", "wt");

	HeapType* heap = CreateHeap();
	long long n, value;

	while (1) {
		fscanf(input_fp, "%d", &n);
		if (n == 0) break;
		for (int i = 0; i < n; i++) {
			fscanf(input_fp, "%d", &value);
			insert_min_heap(heap, value);
		}
		fprintf(output_fp, "%lld\n", AddingCost(heap));
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}