#pragma warning (disable:4786)
#include "pch.h"
#include <string>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>

using namespace std;

void cls(void) {

	system("cls");

} // функция очистки экрана

void DrawLine(void) {

	cout << "\n--------------------------------------\n";

} // функция отрисовки пунктирной линии

void Continue(void) {

	cout << "\nДля продолжения нажмите любую клавишу... \n";
	_getch();

} // функция ожидания нажатия

typedef struct {

	string FIO; // фио
	bool Gender; // гендер
	int GroupNumber; // номер группы
	int PeopleNumber; // номер в списке группы

	int* Marks; // массив оценок

	string StudyForm; // форма обучения
	string EditTime; // отметка времени о внесении/изменении данных (формат: ДД/ММ/ГГГГ HH:MM:SS)

} Student;

void Struct_Constructor(Student* Object, int MaxCount, int CountMarks) {

	for (int i = 0; i < MaxCount; i++) {

		Object[i].FIO = "\0";
		Object[i].Gender = false;
		Object[i].GroupNumber = 0;
		Object[i].PeopleNumber = 0;

		Object[i].Marks = new int[CountMarks];

		for (int c = 0; c < CountMarks; c++)
			Object[i].Marks[c] = 0;

		Object[i].StudyForm = "\0";
		Object[i].EditTime = "\0";

	}

} // функция структуры - конструктор структуры

int Calculate_PeopleNumber_InGroup(Student* Object, int StudentIndex) {

	int Max = 0;

	for (int i = 0; i < StudentIndex; i++) {

		if (i != StudentIndex)
			if (Object[i].GroupNumber == Object[StudentIndex].GroupNumber)
				if (Max < Object[i].PeopleNumber)
					Max = Object[i].PeopleNumber;

	} // поиск максимального порядкого номера студента в данной группе

	return Max + 1;

} // функция подсчета порядкового номера студента в группе

void Struct_Input_Students_Info(Student& Object, Student* Array, int StudentIndex, int CountMarks, const int Element) {

	cout << "\nПорядковый номер студента: " << Element << "\n\n";
	cout << "Введите ФИО (имя фамилия отчество): ";
	cin.get();
	getline(cin, Object.FIO);
	cout << "\nВведите пол (1 - мужской/ 0 - женский): ";
	cin >> Object.Gender;
	cout << "\nВведите номер группы (целое число): ";
	cin >> Object.GroupNumber;

	cout << "\nВведите оценки по дифф. зачетам:\n";

	for (int i = 0; i < CountMarks - 3; i++) {

		cout << "дифф. зачет № " << i + 1 << ") ";
		cin >> Object.Marks[i];

	}

	cout << "\nВведите оценки по экзаменам:\n";

	for (int i = CountMarks - 3; i < CountMarks; i++) {

		cout << "экзамен № " << i - 4 << ") ";
		cin >> Object.Marks[i];

	}

	cout << "\nВведите форму обучения (очная/заочная/очно-заочная): ";
	cin >> Object.StudyForm;

	cout << "\nВведите отметку времени об изменении этих данных (формат: ДД/ММ/ГГГГ HH:MM:SS): ";
	cin.get();
	getline(cin, Object.EditTime);

	Object.PeopleNumber = Calculate_PeopleNumber_InGroup(Array, StudentIndex);

} // функция структуры - функия ввода данных об студентах

void Struct_Show_Students_Info(Student& Object, int StudentIndex, int CountMarks) {

	cout << "\nПорядковый номер: " << StudentIndex + 1 << "\n";
	cout << "ФИО: " << Object.FIO << "\n";
	cout << "Пол: ";

	if (Object.Gender == 0)
		cout << "женский\n";

	else
		cout << "мужской\n";

	cout << "Номер группы: " << Object.GroupNumber << "\n";
	cout << "Номер студента в списке группы: " << Object.PeopleNumber << "\n";
	cout << "Оценки за 3 экзамена и 5 дифф. зачетов:";

	for (int c = 0; c < CountMarks - 3; c++) {

		cout << "\nдифф. зачет № " << c + 1 << ") ";
		cout << Object.Marks[c];

	}

	for (int c = CountMarks - 3; c < CountMarks; c++) {

		cout << "\nэкзамен № " << c - 4 << ") ";
		cout << Object.Marks[c];

	}

	cout << "\nФорма обучения: " << Object.StudyForm << "\n";
	cout << "Последнее изменение данных: " << Object.EditTime << "\n";
	DrawLine();

} // функция структуры - отображение данных обо всех студентах

int Struct_Checker_BadStudents(Student* Object, int TotalStudents, int CountMarks) {

	for (int i = 0; i < TotalStudents; i++)
		for (int c = 0; c < CountMarks; c++)
			if (Object[i].Marks[c] == 2)
				return i;

	return -1;

} // функция, проверяющая есть ли двоечники среди студентов (если есть - он будет удален)

void Struct_Find_Best_Students(Student* Object, int TotalStudentIndex, int CountMarks, int N) {

	typedef struct {

		double AverageMark; // средняя оценка
		int Index; // индекс студента в базе

	} StructTopStudents; // структура, хранящая в себе конкретные данные по студентам (для дальнейшей сортировки)

	StructTopStudents* TopStudents = new StructTopStudents[TotalStudentIndex];

	for (int i = 0; i < TotalStudentIndex; i++) {

		double Sum = 0.0;

		for (int c = 0; c < CountMarks; c++)
			Sum += Object[i].Marks[c];

		TopStudents[i].AverageMark = Sum / CountMarks; // определяем среднюю оценку каждого студента
		TopStudents[i].Index = i;

	}

	for (int i = 0; i < TotalStudentIndex; i++) {

		double TempMark = 0.0;
		int TempIndex = 0;

		for (int c = 0; c < TotalStudentIndex - i - 1; c++) {

			if (TopStudents[c].AverageMark > TopStudents[c + 1].AverageMark) {

				TempMark = TopStudents[c].AverageMark;
				TempIndex = TopStudents[c].Index;

				TopStudents[c].AverageMark = TopStudents[c + 1].AverageMark;
				TopStudents[c].Index = TopStudents[c + 1].Index;

				TopStudents[c + 1].AverageMark = TempMark;
				TopStudents[c + 1].Index = TempIndex;

			}

		}

	} // обыкновенная сортировка пузырьком для установления лучших студентов (по возрастанию)

	for (int i = TotalStudentIndex - 1; i > -1; i--) {

		cout << "\nСредняя оценка: " << TopStudents[i].AverageMark << "\n";
		Struct_Show_Students_Info(Object[TopStudents[i].Index], TopStudents[i].Index, CountMarks);

	}

} // функция структуры - вывод топа лучших студентов

bool Struct_Upload_Info_All_Students(Student* Object, int TotalStudentsIndex, int CountMarks) {

	ofstream Write("students.txt");

	for (int i = 0; i < TotalStudentsIndex; i++) {

		Write << "\nПорядковый номер: " << i + 1 << "\n";
		Write << "ФИО: " << Object[i].FIO << "\n";
		Write << "Пол: ";

		if (Object[i].Gender == 0)
			Write << "женский\n";

		else
			Write << "мужской\n";

		Write << "Номер группы: " << Object[i].GroupNumber << "\n";
		Write << "Номер студента в списке группы: " << Object[i].PeopleNumber << "\n";
		Write << "Оценки за 3 экзамена и 5 дифф. зачетов:";

		for (int c = 0; c < CountMarks - 3; c++) {

			Write << "\nдифф. зачет № " << c + 1 << ") ";
			Write << Object[i].Marks[c];

		}

		for (int c = CountMarks - 3; c < CountMarks; c++) {

			Write << "\nэкзамен № " << c - 4 << ") ";
			Write << Object[i].Marks[c];

		}

		Write << "\nФорма обучения: " << Object[i].StudyForm << "\n";
		Write << "Последнее изменение данных: " << Object[i].EditTime << "\n";

	}

	Write.close();

	bool Flag = true;

	ifstream Read("students.txt");

	if (!Read.is_open())
		Flag = false;

	Read.close();

	return Flag;

} // функция структуры - выгрузка данных обо всех студентах в файл students.txt

int Return_CountStudents_InFile(void) {

	string Temp = "\0";
	int Count = 0;
	ifstream Read("students.txt");

	while (getline(Read, Temp))
		Count++;

	Read.close();

	return Count / 16;

} // функция для подсчета кол-ва студентов в текстовом файле

bool Struct_File_Download(Student* Students, int& StudentCount) {

	bool Flag = true; // успех/неудача выгрузки из файла
	StudentCount = Return_CountStudents_InFile();

	string Temp = "\0";
	ifstream Read("students.txt");

	if (Read.is_open()) {

		for (int i = 0; i < StudentCount; i++) {

			for (int c = 0; c < 4; c++)
				Read >> Temp;

			Temp = "\0";

			Read >> Temp;
			Students[i].FIO = Temp;
			Read >> Temp;
			Students[i].FIO = Students[i].FIO + " " + Temp;
			Read >> Temp;
			Students[i].FIO = Students[i].FIO + " " + Temp;

			// считали имя

			Read >> Temp;
			Read >> Temp;

			if (Temp == "мужской")
				Students[i].Gender = 1;

			else if (Temp == "женский")
				Students[i].Gender = 0;

			// считали пол

			Read >> Temp;
			Read >> Temp;
			Read >> Students[i].GroupNumber;

			// считали номер группы

			for (int c = 0; c < 5; c++)
				Read >> Temp;

			Read >> Students[i].PeopleNumber;

			// считали номер человека в группе

			for (int c = 0; c < 8; c++)
				Read >> Temp;

			for (int c = 0; c < 5; c++) {

				for (int k = 0; k < 4; k++)
					Read >> Temp;

				Read >> Students[i].Marks[c];

			}

			// считали дифф. зачеты

			for (int c = 0; c < 3; c++) {

				for (int k = 0; k < 3; k++)
					Read >> Temp;

				Read >> Students[i].Marks[c + 5];

			}

			// считали экзамены

			Read >> Temp;
			Read >> Temp;
			Read >> Students[i].StudyForm;

			// считали форму обучения


			for (int c = 0; c < 4; c++)
				Read >> Temp;

			Students[i].EditTime = Temp;
			Read >> Temp;
			Students[i].EditTime = Students[i].EditTime + " " + Temp;

			// считали дату изменения
		}

	}

	else if (!Read.is_open())
		Flag = false;

	Read.close();

	return Flag;

} // функция считывания данных из файла

typedef struct {

	string FIO; // фио гостя
	bool Status; // статус (выступающий/слушатель)
	int Degree; // ученая степень (0 - студент, 1 - кандидат наук, 2 - доктор наук, 3 - доцент, 4 - профессор)
	string UniversityName; // наименование университета
	string Theme; // тема выступления

} Scientific_Conference;

string Return_String_Degree(Scientific_Conference& Participants) {

	if (Participants.Degree == 0)
		return "студент";

	else if (Participants.Degree == 1)
		return "кандидат наук";

	else if (Participants.Degree == 2)
		return "доктор наук";

	else if (Participants.Degree == 3)
		return "доцент";

	else if (Participants.Degree == 4)
		return "профессор";

	return "None";

} // функция по возвращению строки ученой степени

void StructScientificConference_Constructor(Scientific_Conference* Participants, Student* Students, const int TotalCount) {

	for (int i = 0; i < TotalCount; i++) {

		Participants[i].FIO = Students[i].FIO;
		Participants[i].Status = 0;
		Participants[i].Degree = 0;
		Participants[i].UniversityName = "\0";
		Participants[i].Theme = "\0";

	}

} // функция структуры конференции - конструктор

void StructScientificConference_Input_Info(Scientific_Conference& Participants, Student& Students, int Index) {

	cout << "\nПорядковый номер участника: " << Index + 1 << "\n\n";
	cout << "ФИО выступающего: " << Participants.FIO << "\n";
	cout << "\nВведите статус участника (1 - выступающий, 0 - слушатель): ";
	cin >> Participants.Status;
	cout << "\nВведите ученую степень участника (0 - студент, 1 - кандидат наук, 2 - доктор наук, 3 - доцент, 4 - профессор): ";
	cin >> Participants.Degree;
	cout << "\nВведите наименование университета: ";
	cin >> Participants.UniversityName;

	if (Participants.Status == 1) {

		cout << "\nВведите тему выступления: ";
		cin.get();
		getline(cin, Participants.Theme);

	}

} // функция структуры конференции - внесение информации

void StructScientificConference_Show_Info(Scientific_Conference& Participants, int Index) {

	cout << "\nПорядковый номер участника: " << Index + 1 << "\n\n";
	cout << "ФИО выступающего: " << Participants.FIO << "\n";
	cout << "Статус участника: ";

	if (Participants.Status == 1)
		cout << "выступающий\n";

	else if (Participants.Status == 0)
		cout << "слушатель\n";

	cout << "Ученая степень участника: " << Return_String_Degree(Participants) << "\n";
	cout << "Наименование университета: " << Participants.UniversityName << "\n";

	if (Participants.Status == 1)
		cout << "Тема выступления: " << Participants.Theme;

	DrawLine();

} // функция структуры конференции - вывод информации по участнику

int main(void) {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251); // кириллица в консоли
	system("title Лабораторная работа # 7, вариант 7");

	int ButtonNumber = 0; // переменная для работа с функцией getch

	const int MaxTotalStudentsIndex = 100; // максимальное число студентов в базе
	int StudentsIndex = 0; // добавленное число студентов в базу
	const int CountMarks = 8; // кол-во оценок (3 экзамена и 5 дифф. зачетов)

	Student* Students = new Student[MaxTotalStudentsIndex];

	Struct_Constructor(Students, MaxTotalStudentsIndex, CountMarks); // вызов конструктора для каждого объекта структуры	

	while (true) { // начало жизненного цикла программы

		int BadStudent = Struct_Checker_BadStudents(Students, StudentsIndex, CountMarks);

		if (BadStudent != -1) { // если вернутое значение не -1, значит удаляем по индексу студента-двоечника

			int Index = 0;

			for (int i = 0; i < StudentsIndex; i++) {

				Student NewStudent = Students[i];

				if (i != BadStudent) {

					Students[Index] = NewStudent;
					Index++;

				}

			}

			StudentsIndex--;

		}

		ButtonNumber = 0;
		cls();

		cout << "		Меню программы\n\n";
		cout << "1. Создание новой записи о студенте\n";
		cout << "2. Внесение изменений в уже имеющуюся запись\n";
		cout << "3. Вывод всех данных о студентах\n";
		cout << "4. Вывод информации о всех студентов группы N\n";
		cout << "5. Вывод топа самых умных студентов\n";
		cout << "6. Вывод количества студентов мужского и женского пола\n";
		cout << "7. Определение количества студентов со стипендией\n";
		cout << "8. Вывод данных о студентов без стипендии\n";
		cout << "9. Вывод всех записей по времении внесении данных\n";
		cout << "10. Вывод данных о студентах, имеющий номер в списке - k\n";
		cout << "11. Вывод данных о всех студентах в файл students.txt\n";
		cout << "12. Загрузить данные обо всех студентах из файла students.txt\n";
		cout << "13. Научная конференция (доп)\n";
		cout << "0. Выйти из программы\n";

		while (true) { // защита от дурака по нажатию

			cout << "\n\nВведите пункт меню: ";
			cin >> ButtonNumber;

			if (ButtonNumber == 0) {

				delete[] Students; // высвобождение динамической памяти
				return 0; // завершение программы

			}

			else if (ButtonNumber > 0 && ButtonNumber < 14) {

				cls();
				break;

			}

		}

		if (ButtonNumber == 1) {

			cout << "      Создание новой записи о студенте\n\n";

			Struct_Input_Students_Info(Students[StudentsIndex], Students, StudentsIndex, CountMarks, StudentsIndex + 1);
			StudentsIndex++; // увеличиваем счетчик добавленных студентов

			Continue();

		} // Создание новой записи о студенте

		else if (ButtonNumber == 2) {

			int N = 0;
			cout << "      Внесение изменений в уже имеющуюся запись\n\n";

			cout << "Введите порядковый № студента, запись о котором нужно изменить (целое число): ";
			cin >> N;

			if (N < 1 || N > StudentsIndex)
				cout << "Студента с таким порядковым номером не существует!\n";

			else {

				cout << "Введите новые данные о студенте:\n\n";
				Struct_Input_Students_Info(Students[N - 1], Students, StudentsIndex, CountMarks, N);

			}

			Continue();

		} // Внесение изменений в уже имеющуюся запись

		else if (ButtonNumber == 3) {

			cout << "      Вывод всех данных о студентах\n\n";

			for (int i = 0; i < StudentsIndex; i++)
				Struct_Show_Students_Info(Students[i], i, CountMarks);

			Continue();

		} // Вывод всех данных о студентах

		else if (ButtonNumber == 4) {

			int N = 0;
			bool Found = false;

			cout << "      Вывод информации о всех студентов группы N\n\n";
			cout << "Введите номер группы N (целое число): ";
			cin >> N;

			for (int i = 0; i < StudentsIndex; i++) {

				if (Students[i].GroupNumber == N) {

					if (Found == false) {

						cout << "\nСтуденты группы " << N << ":\n\n";
						Found = true;

					}

					Struct_Show_Students_Info(Students[i], i, CountMarks);

				}

			}

			if (Found == false)
				cout << "\nТакой группы не существует!\n";

			Continue();

		} // Вывод информации о всех студентов группы N

		else if (ButtonNumber == 5) {

			cout << "      Вывод топа самых умных студентов\n\n";

			int N = 0;

			cout << "Введите кол-во студентов, которое необходимо вывести в топе: ";
			cin >> N;

			if (N > StudentsIndex) {

				cout << "Такого количества студентов нет!";
				Continue();
				continue;

			}

			DrawLine();
			Struct_Find_Best_Students(Students, StudentsIndex, CountMarks, N);

			Continue();

		} // Вывод топа самых умных студентов

		else if (ButtonNumber == 6) {

			cout << "      Вывод количества студентов мужского и женского пола\n\n";

			int CountMale = 0;
			int CountFemale = 0;

			for (int i = 0; i < StudentsIndex; i++) {

				if (Students[i].Gender == 0)
					CountFemale++;

				else if (Students[i].Gender == 1)
					CountMale++;

			}

			cout << "Кол-во парней: " << CountMale << "\n";
			cout << "Кол-во девушек: " << CountFemale << "\n";

			Continue();

		} // Вывод количества студентов мужского и женского пола

		else if (ButtonNumber == 7) {

			cout << "      Определение количества студентов со стипендией\n\n";

			int CountGoodStudents = 0;

			for (int i = 0; i < StudentsIndex; i++) {

				bool Flag = true;

				for (int c = 0; c < CountMarks; c++) {

					if (Students[i].Marks[c] != 4 && Students[i].Marks[c] != 5) { // если оценка студента не равна 4 или 5

						Flag = false;
						break;

					} // значит не считаем этого студента								

				}

				if (Flag == true) // если же одни 4 и 5
					CountGoodStudents++; // то увеличиваем счетчик таких студентов со стипендией

			}

			cout << "\nКол-во студентов со стипендий (только 4 и 5): " << CountGoodStudents << "\n";

			Continue();

		} // Определение количества студентов со стипендией

		else if (ButtonNumber == 8) {

			bool Found = false;
			bool Flag = false;

			cout << "      Вывод данных о студентов без стипендии\n\n";

			for (int i = 0; i < StudentsIndex; i++) {

				Found = true;

				for (int c = 0; c < CountMarks; c++) {

					if (Students[i].Marks[c] >= 1 && Students[i].Marks[c] <= 3) { // если оценка студента от 1 до 3

						Found = false;

						if (Flag == false)
							Flag = true;

						break;

					} // значит считаем этого студента								

				}

				if (Found == false) {

					if (Found == false) {

						Found = true;
						cout << "Информация о студенте без стипендии:\n";

					}

					Struct_Show_Students_Info(Students[i], i, CountMarks);

				}

			}

			if (Flag == false)
				cout << "Таких студентов нет!\n";

			Continue();

		} // Вывод данных о студентов без стипендии

		else if (ButtonNumber == 9) {

			bool Founded = false;

			cout << "      Вывод всех записей по времении внесении данных\n\n";

			string Stroke = "\0";

			cout << "1. Введите дату конкретного дня, для которого нужно вывести все записи (в формате ДД.ММ.ГГГГ): ";
			cin >> Stroke;

			for (int i = 0; i < StudentsIndex; i++) {

				if (Stroke[0] == Students[i].EditTime[0]) // первая цифра дня
					if (Stroke[1] == Students[i].EditTime[1]) // вторая цифра дня
						if (Stroke[3] == Students[i].EditTime[3]) // первая цифра месяца
							if (Stroke[4] == Students[i].EditTime[4]) // вторая цифра месяца
								if (Stroke[6] == Students[i].EditTime[6]) // первая цифра года
									if (Stroke[7] == Students[i].EditTime[7]) // вторая цифра года
										if (Stroke[8] == Students[i].EditTime[8]) // третья цифра года
											if (Stroke[9] == Students[i].EditTime[9]) { // четвертая цифра года

												if (Founded == false)
													Founded = true;

												cout << "Запись, сделанные в " << Stroke << " день: \n";
												DrawLine();
												Struct_Show_Students_Info(Students[i], i, CountMarks);

											}

			}

			if (Founded == true)
				Founded = false;

			else
				cout << "Таких записей в " << Stroke << " день нет!\n\n";

			DrawLine();

			cout << "Вывод всех записей, сделанных после полудня:\n\n";

			for (int i = 0; i < StudentsIndex; i++) {

				bool Flag = false;

				if (Students[i].EditTime[11] == '2')
					Flag = true;

				else if (Students[i].EditTime[11] == '1')
					if (Students[i].EditTime[12] != '0' && Students[i].EditTime[12] != '1')
						Flag = true;

				if (Flag == true) {

					if (Founded == false)
						Founded = true;

					Struct_Show_Students_Info(Students[i], i, CountMarks);

				}

			}

			if (Founded == true)
				Founded = false;

			else
				cout << "Таких записей после полудня нет!\n\n";

			DrawLine();
			cout << "Вывод всех записей, сделанных до полудня:\n\n";

			for (int i = 0; i < StudentsIndex; i++) {

				bool Flag = false;

				if (Students[i].EditTime[11] == '0')
					Flag = true;

				else if (Students[i].EditTime[11] == '1')
					if (Students[i].EditTime[12] == '0' || Students[i].EditTime[12] == '1')
						Flag = true;

				if (Flag == true) {
					if (Founded == false)
						Founded = true;

					Struct_Show_Students_Info(Students[i], i, CountMarks);

				}

			}

			if (Founded == false)
				cout << "Таких записей до полудня нет!\n\n";

			Continue();

		} // Вывод всех записей по времении внесении данных

		else if (ButtonNumber == 10) {

			int k = 0;
			bool Found = false;

			cout << "      Вывод данных о студентах, имеющий номер в списке - k\n\n";
			cout << "Введите номер студента k (целое число): ";
			cin >> k;

			for (int i = 0; i < StudentsIndex; i++) {

				if (Students[i].PeopleNumber == k) {

					if (Found == false) {

						Found = true;
						cout << "Перечень таких студентов:\n";

					}

					Struct_Show_Students_Info(Students[i], i, CountMarks);

				}

			}

			if (Found == false)
				cout << "Таких студентов нет!\n";

			Continue();

		} // Вывод данных о студентах, имеющий номер в списке - k

		else if (ButtonNumber == 11) {

			cout << "      Вывод данных о всех студентах в файл students.txt\n\n";

			bool Flag = Struct_Upload_Info_All_Students(Students, StudentsIndex, CountMarks);

			if (Flag == true)
				cout << "\n\nВыгрузка данных в файл students.txt выполнена\n";

			else
				cout << "\n\nВыгрузка данных не удалась!\n";

			Continue();

		} // Вывод данных о всех студентах в файл students.txt

		else if (ButtonNumber == 12) {

			cout << "      Загрузка данных о всех студентах из файла students.txt\n\n";

			bool Flag = Struct_File_Download(Students, StudentsIndex);

			if (Flag == true)
				cout << "\n\nЗагрузка данных из файла students.txt выполнена\n";

			else
				cout << "\n\nЗагрузка данных не удалась!\n";

			Continue();

		} // Загрузка данных о всех студентах из файла students.txt

		else if (ButtonNumber == 13) {

			Scientific_Conference* Conference = new Scientific_Conference[MaxTotalStudentsIndex];
			StructScientificConference_Constructor(Conference, Students, StudentsIndex);

			while (true) { // начало жизненного цикла программы

				ButtonNumber = 0;
				cls();

				cout << "		Научная конференция\n\n";
				cout << "1. Внести информацию о выступающих\n";
				cout << "2. Вывести информацию о всех выступающих\n";
				cout << "3. Вывести информацию о всех иногородних приглашенных\n";
				cout << "4. Вывести информацию о всех студентах, которые приглашены выступать\n";
				cout << "5. Вывести информацию о всех студентов университета \"ЛЭТИ\"\n";
				cout << "0. Вернуться в главное меню\n";

				while (true) { // защита от дурака по вводу

					cout << "\n\nВведите пункт меню: ";
					cin >> ButtonNumber;

					if (ButtonNumber == 0) {

						delete[] Conference; // высвобождение динамической памяти
						break; // выход в главное меню

					}

					else if (ButtonNumber > 0 && ButtonNumber < 6) {

						cls();
						break;

					}

				}

				if (ButtonNumber == 0)
					break;

				if (ButtonNumber == 1) {

					cout << "      Внести информацию о выступающих\n\n";

					int Index = 0;
					cout << "Введите индекс студента: ";
					cin >> Index;

					if (Index < 0 && Index > StudentsIndex)
						cout << "Такого студента нет!\n";

					else
						StructScientificConference_Input_Info(Conference[Index], Students[Index], Index);

					Continue();

				} // Внести информацию о выступающих

				else if (ButtonNumber == 2) {

					cout << "      Вывести информацию о всех выступающих\n\n";

					for (int i = 0; i < StudentsIndex; i++)
						StructScientificConference_Show_Info(Conference[i], i);

					Continue();

				} // Вывести информацию о всех выступающих

				else if (ButtonNumber == 3) {

					cout << "      Вывести информацию о всех иногородних приглашенных\n\n";
					bool Found = false;
					cout << "Перечень иногородних студентов:\n\n";

					for (int i = 0; i < StudentsIndex; i++) {

						if (Conference[i].UniversityName != "ЛЭТИ") {

							if (Found == false)
								Found = true;

							StructScientificConference_Show_Info(Conference[i], i);

						} // все, кто не учится в ЛЭТИ - иногородний студент

					}

					if (Found == false)
						cout << "\nТаких участников нет!\n";

					Continue();

				} // Вывести информацию о всех иногородних приглашенных

				else if (ButtonNumber == 4) {

					cout << "      Вывести информацию о всех студентах, которые приглашены выступать\n\n";

					bool Found = false;
					cout << "Перечень выступающих:\n\n";

					for (int i = 0; i < StudentsIndex; i++) {

						if (Conference[i].Status == 1) {

							if (Found == false)
								Found = true;

							StructScientificConference_Show_Info(Conference[i], i);

						} // все, кто выступает

					}

					if (Found == false)
						cout << "\nТаких участников нет!\n";

					Continue();

				} // Вывести информацию о всех студентах, которые приглашены выступать

				else if (ButtonNumber == 5) {

					cout << "      Вывести информацию о всех студентов университета \"ЛЭТИ\"\n\n";

					bool Found = false;
					cout << "Перечень студентов \"ЛЭТИ\":\n\n";

					for (int i = 0; i < StudentsIndex; i++) {

						if (Conference[i].UniversityName == "ЛЭТИ") {

							if (Found == false)
								Found = true;

							StructScientificConference_Show_Info(Conference[i], i);

						} // все, кто учится в ЛЭТИ

					}

					if (Found == false)
						cout << "\nТаких участников нет!\n";

					Continue();

				} // Вывести информацию о всех студентов университета "ЛЭТИ"

			} // конец жизненного цикла программы

		} // научная конференция

	} // конец жизненного цикла программы

}
