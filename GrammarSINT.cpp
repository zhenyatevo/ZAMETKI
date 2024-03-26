/* E -> 5|5+E
Задание с пары Рогонова
Неплохо бы сюда ещё левую фаторизацию для 5 накинуть...
*/

#include <iostream>
#include <string>


using namespace std;

string stroka;
string symbOl;
string prev = "";
int i = 0;




bool E() {
	symbOl = stroka[i];
	string prev;
	if (symbOl != "5") {
		return false;
	}
	i++;
	symbOl = stroka[i];
	if (symbOl == "$") {
		return true;
	}
	if (symbOl != "+") {
		return false;
	}
	i++;
	return E();
}


int main()
{
	cin >> stroka;
	stroka += "$";
	cout << E();


}

