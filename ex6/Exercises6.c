#define _CRT_SECURE_NO_WARNINGS // không dùng visual studio thì xóa dòng này đi
#include <stdio.h>
// Bài tập đọc ghi file text số 6
/*
* @author Branium Academy
* @version 2023.05
* @see https://braniumacademy.net
*/

// cấu trúc tài khoản
typedef struct {
	int id;				// mã tài khoản
	char fullName[40];	// tên tài khoản
	char accNumber[30];	// số tài khoản
	float ballance;		// số dư
	float interestRate;	// lãi suất
	float interes;		// tiền lãi
} BankAcc;

// các hàm nguyên mẫu
// hàm đọc dữ liệu từ file
void readFile(BankAcc* accounts, int* n);
// hàm tính tiền lãi
void calculateInteres(BankAcc* accounts, int n);
// hàm sắp xếp danh sách tài khoản theo số dư giảm dần
void sortAcc(BankAcc* accounts, int n);
// hàm ghi file
void writeFile(const BankAcc* accounts, int n, const char* fileName);

int main() {
	int n; // số tk thực tế trong file
	BankAcc accounts[100];
	char fileName[30]; // chứa tên file để lưu kq
	puts("Nhap ten file de ghi ket qua: ");
	scanf("%29s", fileName);

	// gọi hàm đọc danh sách tài khoản
	readFile(accounts, &n);
	// gọi hàm tính lãi suất
	calculateInteres(accounts, n);
	// gọi hàm sắp xếp tài khoản theo số dư giảm dần
	sortAcc(accounts, n);
	// gọi hàm ghi file
	writeFile(accounts, n, fileName);

	return 0;
}

void readFile(BankAcc* accounts, int* n) {
	FILE* fin = fopen("ACC.INP", "r"); // mở file để đọc
	if (fin) {
		fscanf(fin, "%d", n); // đọc số lượng tk
		int i;
		for (i = 0; i < *n; i++) {
			// dùng %*c để đọc bỏ kí tự thừa của lần đọc trước đó
			fscanf(fin, "%d", &accounts[i].id);
			fscanf(fin, "%*c%39[^|]", accounts[i].fullName);
			fscanf(fin, "%*c%29[^|]", accounts[i].accNumber);
			fscanf(fin, "%*c%f%*c%f%*c", &accounts[i].ballance,
				&accounts[i].interestRate);
			accounts[i].interes = 0; // ban đầu gán tiền lãi = 0
		}
		fclose(fin);
	}
	else {
		puts("==> Khong the mo file. Vui long kiem tra lai.");
	}
}

void writeFile(const BankAcc* accounts, int n, const char* fileName) {
	FILE* fout = fopen(fileName, "w"); // mở file để ghi
	if (fout) {
		fprintf(fout, "%d\n", n);
		int i;
		for (i = 0; i < n; i++) {
			fprintf(fout, "%d|%s|%s|%0.2f|%0.2f|%0.3f\n",
				accounts[i].id, accounts[i].fullName,
				accounts[i].accNumber, accounts[i].ballance,
				accounts[i].interestRate, accounts[i].interes);
		}
		fclose(fout);
	}
	else {
		puts("==> Khong the tao file. Vui long kiem tra lai.");
	}
}

void sortAcc(BankAcc* accounts, int n) {
	void swap(BankAcc * a, BankAcc * b);
	if (n > 0) {
		int i, j;
		for (i = 0; i < n - 1; i++)
		{
			for (j = n - 1; j > i; j--)
			{
				if (accounts[j].ballance > accounts[j - 1].ballance) {
					swap(&accounts[j], &accounts[j - 1]);
				}
			}
		}
	}
	else {
		puts("==> Danh sach rong khong the sap xep.");
	}
}

// hàm đổi chỗ hai phần tử
void swap(BankAcc* a, BankAcc* b) {
	BankAcc s = *a;
	*a = *b;
	*b = s;
}

void calculateInteres(BankAcc* accounts, int n) {
	int i;
	for (i = 0; i < n; i++)
	{
		accounts[i].interes = accounts[i].ballance *
			accounts[i].interestRate / 100;
	}
}
