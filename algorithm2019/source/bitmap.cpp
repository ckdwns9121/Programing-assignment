/**
 * Assignment 08 : Bitmap
 */

#include <fstream>
using namespace std;

ifstream inp("bitmap.inp");
ofstream out("bitmap.out");

char bitmap[202][202];
int row = 0, col = 0, cnt = 0;

bool isSame(int x, int y, int row, int col) {
	for (int i = x; i < row; i++) {
		for (int j = y; j < col; j++) {
			if (bitmap[i][j] != bitmap[x][y])
				return false;
		}
	}
	return true;
}

void partition_BtoD(int x, int y, int row, int col) {
	if (isSame(x, y, row, col)) {
		out << bitmap[x][y];
		cnt++;
		if (cnt % 50 == 0) out << '\n';
	}
	else {  
		// 원소가 같지않으면 분할
		out << 'D';
		cnt ++;
		if (cnt % 50 == 0) out << '\n';
		int tCol = (col + y + 1) / 2;
		int tRow = (row + x+ 1)/2;
		if (row - x == 1) {
			partition_BtoD(x, y, tRow, tCol);  
			partition_BtoD(x, tCol, row, col);   
		} 
	
		else if (col - y == 1) {
			partition_BtoD(x, y, tRow, col); 
			partition_BtoD(tRow, y, row, col); 
		}
		else {
 			partition_BtoD(x, y, tRow, tCol); 
			partition_BtoD(x, tCol, tRow, col);  
			partition_BtoD(tRow, y, row, tCol);  
			partition_BtoD(tRow, tCol, row, col);
		}
	}
}

void partition_DtoB(int x, int y, int row, int col) {
	char ch;
	inp >> ch;
	if (ch == '\n') inp >> ch;
	if (ch != 'D') {
		for (int i = x; i < row; i++)
			for (int j = y; j < col; j++) bitmap[i][j] = ch;
	}
	else {
		int tCol = (col + y + 1) / 2;
		int tRow = (row + x+1)/2;

		if (row - x == 1) {
			partition_DtoB(x, y, tCol, tRow);  
			partition_DtoB(x, tRow, row, col);
		}
		
		else if (col - y == 1) {
			partition_DtoB(x, y, tCol, col);
			partition_DtoB(tRow, y, row, col); 
		}
		
		else {
			partition_DtoB(x, y, tCol, tRow);  
			partition_DtoB(x, tRow, tCol, col);  
			partition_DtoB(tCol, y, row, tRow);  
			partition_DtoB(tCol, tRow, row, col);  
		}
	}
}

int main() {
	while (true) {
		char type, ch;
		inp >> type >> row >> col;
		if (type == '#') return 0;
		if (type == 'B') {
			out << "D  " << row << "  " << col << '\n';
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					inp >> ch;

					bitmap[i][j] = ch;
				}
			}
			partition_BtoD(0, 0, row, col);
			out << '\n';
		}
		else {
			out << "B  " << row << "  " << col << '\n';
			partition_DtoB(0, 0, row, col);
			for (int i = 0; i < row; i++)
				for (int j = 0; j < col; j++) {
					out << bitmap[i][j];
					cnt++;
					if (cnt % 50 == 0) out << '\n';
				}
			if (cnt % 50 != 0) out << '\n';
		}
		cnt = 0;
	}

	inp.close();
	out.close();
	return 0;
}