#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>

using namespace std;

struct Mahasiswa
{
	int pk;
	string NIM;
	string Nama;
	string Jurusan;
};


int getOption();
void checkDatabase(fstream& data);
void writeData(fstream& data, int posisi, Mahasiswa& inputMahasiswa);
int getDataSize(fstream& data);
void addDataMahasiswa(fstream& data);

int main()
{
	fstream data;

	checkDatabase(data);

	int Pilihan = getOption();
	char is_continue;

	enum Option { CREATE = 1, READ, UPDATE, DELETE, FINISH };

	while (Pilihan != FINISH)
	{
		switch (Pilihan)
		{
		case CREATE:
			cout << "Menambah Data Mahasiswa" << endl;
			addDataMahasiswa(data);
			break;
		case READ:
			cout << "Tampilkan Data Mahasiswa" << endl;
			break;
		case UPDATE:
			cout << "Ubah Data Mahasiswa" << endl;
			break;
		case DELETE:
			cout << "Hapus Data Mahasiswa" << endl;
			break;
		default:
			cout << "Pilihan Tidak Ditemukan!" << endl;
			break;
		}

	label_continue:
		
		cout << "Lanjutkan? (Y/N)  : "; cin >> is_continue;

		if ((is_continue == 'Y') | (is_continue == 'y'))
		{
			Pilihan = getOption();
		}
		else if ((is_continue == 'N') | (is_continue == 'n'))
		{
			break;
		}
		else
		{
			goto label_continue;
		}
	}

	cout << "Akhir Dari Program" << endl;

	_getch();
	return 0;
}

int getOption()
{
	int Input;
	//system("cls");
	cout << "==============================" << endl;
	cout << "Program CRUD - Data Mahasiswa" << endl;
	cout << "==============================" << endl;
	cout << "1. Tambah Data" << endl;
	cout << "2. Tampil Data" << endl;
	cout << "3. Ubah Data" << endl;
	cout << "4. Hapus Data" << endl;
	cout << "5. Akhiri" << endl;
	cout << "==============================" << endl;
	cout << "Pilih [1-5] : "; cin >> Input;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return Input;
}

void checkDatabase(fstream& data)
{
	data.open("data.bin", ios::out | ios::in | ios::binary);

	//Memeriksa File apakah Ada atau Tidak
	if (data.is_open())
	{
		cout << "Database Ditemukan!" << endl;
	}
	else
	{
		cout << "Database Tidak Ditemukan, Buat Database Baru!" << endl;
		data.close();
		data.open("data.bin", ios::trunc | ios::out | ios::in | ios::binary);
	}
}

void writeData(fstream& data, int posisi, Mahasiswa& inputMahasiswa)
{
	data.seekp((posisi - 1) * sizeof(Mahasiswa), ios::beg);
	data.write(reinterpret_cast<char*>(&inputMahasiswa), sizeof(Mahasiswa));
}

int getDataSize(fstream& data)
{
	int start, end;
	data.seekg(0, ios::beg);
	start = data.tellg();
	data.seekg(0, ios::end);
	end = data.tellg();
	return(end - start) / sizeof(Mahasiswa);
}

Mahasiswa readData(fstream& data, int posisi)
{
	Mahasiswa readMahasiswa;
	data.seekg((posisi - 1) * sizeof(Mahasiswa), ios::beg);
	data.read(reinterpret_cast<char*>(&readMahasiswa), sizeof(Mahasiswa));
	return readMahasiswa;
}

void addDataMahasiswa(fstream& data)
{
	Mahasiswa inputMahasiswa, lastMahasiswa;
	
	int size = getDataSize(data);

	cout << "Ukuran Data  : " << size << endl;

	if (size==0)
	{
		inputMahasiswa.pk = 1;
	}
	else
	{
		lastMahasiswa = readData(data, size);
		inputMahasiswa.pk = lastMahasiswa.pk + 1;
	}
	//readData(data, size);

	inputMahasiswa.pk = 1;

	cout << "Nama     : ";
	getline(cin, inputMahasiswa.Nama);
	cout << "Jurusan  : ";
	getline(cin, inputMahasiswa.Jurusan);
	cout << "NIM      : ";
	getline(cin, inputMahasiswa.NIM);

	writeData(data, size + 1, inputMahasiswa);
}