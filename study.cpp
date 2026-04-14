#include <string>
#include <iostream>
#include <fstream>
using std::string;

enum class Flight_type {
	CHARTER,
	TRANSIT,
	CONNECTING,
};


struct Time {
	int hours;
	int minutes;
};


struct ScheduleAirline {
	string pickup_point;
	Time departure_time;
	Time arrival_time;
	double flight_time;
	double ticket_price;
	Flight_type flight_type;
};


bool endsWith(string name) {
	int lenth = name.length();
	if (lenth < 4)
		return false;
	return (name.substr(lenth - 4) == "инск");

}

void printScheduleArray(const ScheduleAirline* arr, int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << "Рейс " << i + 1 << ":\n";
		std::cout << "  Пункт посадки: " << arr[i].pickup_point << "\n";
		std::cout << "  Время отправления: " << arr[i].departure_time.hours << ":"
			<< arr[i].departure_time.minutes << "\n";
		std::cout << "  Время прибытия: " << arr[i].arrival_time.hours << ":"
			<< arr[i].arrival_time.minutes << "\n";
		std::cout << "  Время полета: " << arr[i].flight_time << " ч\n";
		std::cout << "  Стоимость билета: " << arr[i].ticket_price << " руб.\n";
		std::cout << "  Тип рейса: ";
		if (arr[i].flight_type == Flight_type::CHARTER)
			std::cout << "Чартер";
		else if (arr[i].flight_type == Flight_type::TRANSIT)
			std::cout << "Транзит";
		else
			std::cout << "Стыковка";
		std::cout << "\n------------------------\n";
	}
}


void printSpecificFlight(const ScheduleAirline* arr, int index) {
	if (index < 0) {
		std::cout << "Неверный индекс\n";
		return;
	}
	std::cout << "Данные по рейсу №" << index << ":\n";
	std::cout << "  Пункт посадки: " << arr[index].pickup_point << "\n";
	std::cout << "  Время отправления: " << arr[index].departure_time.hours << ":"
		<< arr[index].departure_time.minutes << "\n";
	std::cout << "  Время прибытия: " << arr[index].arrival_time.hours << ":"
		<< arr[index].arrival_time.minutes << "\n";
	std::cout << "  Время полета: " << arr[index].flight_time << " ч\n";
	std::cout << "  Стоимость билета: " << arr[index].ticket_price << " руб.\n";
	std::cout << "  Тип рейса: ";
	if (arr[index].flight_type == Flight_type::CHARTER)
		std::cout << "Чартер";
	else if (arr[index].flight_type == Flight_type::TRANSIT)
		std::cout << "Транзит";
	else
		std::cout << "Стыковка";
	std::cout << "\n------------------------\n";
}

void modifyFlight(ScheduleAirline& flight, double new_price, int new_hour, int new_minute) {
	flight.ticket_price = new_price;
	flight.departure_time.hours = new_hour;
	flight.departure_time.minutes = new_minute;
	std::cout << "Рейс изменён: новая цена = " << new_price << " руб., новое время отправления = " << new_hour << ":" << new_minute << "\n";
}


void bubbleSortByFlightTime(ScheduleAirline* arr, int size) {
	int a, b;
	ScheduleAirline temp;
	for (a = 0; a < size - 1; a++) {
		for (b = size - 1; b > a; b--) {
			if (arr[b - 1].flight_time > arr[b].flight_time) {
				temp = arr[b - 1];
				arr[b - 1] = arr[b];
				arr[b] = temp;
			}
		}
	}
}


void findTwoMorningCharters(const ScheduleAirline* arr, int size) {
	int found = 0; int hour;
	std::cout << "Два чартерных рейса, вылетающих утром:\n";
	for (int i = 0; i < size && found < 2; ++i) {
		if (arr[i].flight_type == Flight_type::CHARTER) {
			hour = arr[i].departure_time.hours;
			if (hour >= 6 && hour < 12) {
				printSpecificFlight(arr, i);
				++found;
			}
		}
	}
	if (found == 0)
		std::cout << "Нет подходящих рейсов.\n";
}

// Фильтрация чартерных рейсов с ценой > N
int filterChartersByPrice(const ScheduleAirline* src, int srcSize,
	ScheduleAirline* dest, double N) {
	int count = 0;
	for (int i = 0; i < srcSize; ++i) {
		if (src[i].flight_type == Flight_type::CHARTER && src[i].ticket_price > N) {
			dest[count] = src[i];
			++count;
		}
	}
	return count;
}

string encode(string s) {
	for (char& c : s)
		if (c == ' ') c = '_';
	return s;
}

string decode(string s) {
	for (char& c : s)
		if (c == '_') c = ' ';
	return s;
}

void writeToTxt(ScheduleAirline* arr, int size) {
	std::ofstream fout("file.txt");

	for (int i = 0; i < size; i++) {
		fout << encode(arr[i].pickup_point) << " "
			<< arr[i].departure_time.hours << " "
			<< arr[i].departure_time.minutes << " "
			<< arr[i].arrival_time.hours << " "
			<< arr[i].arrival_time.minutes << " "
			<< arr[i].flight_time << " "
			<< arr[i].ticket_price << " "
			<< (int)arr[i].flight_type << "\n";
	}

	fout.close();
}


void readFromTxt(ScheduleAirline* arr, int size) {
	std::ifstream fin("file.txt");

	for (int i = 0; i < size; i++) {
		fin >> arr[i].pickup_point
			>> arr[i].departure_time.hours
			>> arr[i].departure_time.minutes
			>> arr[i].arrival_time.hours
			>> arr[i].arrival_time.minutes
			>> arr[i].flight_time
			>> arr[i].ticket_price;

		arr[i].pickup_point = decode(arr[i].pickup_point);
		int type;
		fin >> type;
		arr[i].flight_type = (Flight_type)type;
	}

	fin.close();
}




int main()
{
	setlocale(LC_ALL, "");
	struct ScheduleAirline Schedules[20];
	Schedules[0] = { "Санкт-Петербург", { 8, 0 }, { 9, 30 }, 1.5, 3500.00, Flight_type::CHARTER };
	Schedules[1] = { "Сочи", { 10, 15 }, { 12, 45 }, 2.5, 5200.00, Flight_type::TRANSIT };
	Schedules[2] = { "Казань", { 6, 30 }, { 8, 0 }, 1.5, 2800.00, Flight_type::CHARTER };
	Schedules[3] = { "Екатеринбург", { 14, 0 }, { 16, 30 }, 2.5, 4800.00, Flight_type::CONNECTING };
	Schedules[4] = { "Новосибирск", { 23, 45 }, { 5, 15 }, 4.5, 8900.00, Flight_type::TRANSIT };
	Schedules[5] = { "Сочи", { 9, 0 }, { 12, 0 }, 3.0, 6700.00, Flight_type::CHARTER };
	Schedules[6] = { "Владивосток", { 22, 0 }, { 10, 30 }, 8.5, 18500.00, Flight_type::TRANSIT };
	Schedules[7] = { "Калининград", { 12, 30 }, { 14, 0 }, 1.5, 4200.00, Flight_type::CONNECTING };
	Schedules[8] = { "Красноярск", { 19, 0 }, { 23, 45 }, 3.75, 7600.00, Flight_type::TRANSIT };
	Schedules[9] = { "Ростов-на-Дону", { 7, 15 }, { 9, 0 }, 1.75, 3100.00, Flight_type::CHARTER };
	Schedules[10] = { "Самара", { 16, 30 }, { 18, 15 }, 1.75, 3300.00, Flight_type::CONNECTING };
	Schedules[11] = { "Уфа", { 11, 0 }, { 12, 45 }, 1.75, 3400.00, Flight_type::TRANSIT };
	Schedules[12] = { "Пермь", { 20, 15 }, { 22, 0 }, 1.75, 3600.00, Flight_type::CHARTER };
	Schedules[13] = { "Волгоград", { 5, 45 }, { 7, 30 }, 1.75, 2900.00, Flight_type::CONNECTING };
	Schedules[14] = { "Воронеж", { 9, 30 }, { 10, 45 }, 1.25, 2200.00, Flight_type::CHARTER };
	Schedules[15] = { "Нижний Новгород", { 13, 0 }, { 14, 15 }, 1.25, 2500.00, Flight_type::TRANSIT };
	Schedules[16] = { "Челябинск", { 17, 45 }, { 20, 15 }, 2.5, 4700.00, Flight_type::CONNECTING };
	Schedules[17] = { "Омск", { 21, 30 }, { 2, 0 }, 3.5, 6800.00, Flight_type::TRANSIT };
	Schedules[18] = { "Тюмень", { 8, 45 }, { 11, 15 }, 2.5, 7500.00, Flight_type::CHARTER };
	Schedules[19] = { "Ногинск", { 23, 15 }, { 11, 45 }, 7.5, 16200.00, Flight_type::CONNECTING };

	struct ScheduleAirline newSchedules[20];

	// 1
	int count = 0;
	for (int i = 0; i < 20; i++)
		if (endsWith(Schedules[i].pickup_point) && Schedules[i].flight_type == Flight_type::CONNECTING) 
		{
			newSchedules[count] = Schedules[i];
			count++;
		}

	std::cout << "Рейсы, оканчивающиеся на 'инск' и стыковочные\n";
	printScheduleArray(newSchedules, count);

	// 2
	bubbleSortByFlightTime(newSchedules, count);
	std::cout << "\nПосле сортировки по времени полёта\n";
	printScheduleArray(newSchedules, count);

	// 3
	if (count > 0) {
		std::cout << "\nКонкретный рейс\n";
		printSpecificFlight(newSchedules, 0);
	}

	// 4
	findTwoMorningCharters(Schedules, 20);


	// 5
	std::cout << "\n=== Изменение рейса (Санкт-Петербург) ===\n";
	printSpecificFlight(Schedules, 0);
	modifyFlight(Schedules[0], 4000.00, 9, 0);
	std::cout << "После изменения:\n";
	printSpecificFlight(Schedules, 0);

	
	// 6
	double N = 5000.0;
	ScheduleAirline expensiveCharters[20];
	int expensiveCount = filterChartersByPrice(Schedules, 20, expensiveCharters, N);
	std::cout << "\n=== Чартерные рейсы дороже " << N << " руб. ===\n";
	printScheduleArray(expensiveCharters, expensiveCount);

	// запись в файл
	writeToTxt(Schedules, 20);

	// чтение файла
	ScheduleAirline test[20];
	readFromTxt(test, 20);
	std::cout << "\n Данные из txt файла: \n";
	printScheduleArray(test, 20);

	return 0;
}
