#include "iostream"
#include "fstream"
#include "string"
#include <vector>

using namespace std;
ifstream f("1.txt");

class Time
{
public:
	int h, m;
	bool ld=false;
	void set_time(string s)
	{
		h = stoi(s.substr(0, 1));
		m = stoi(s.substr(3, 4));
	}
	string get_time()
	{
		return to_string(h) + ":" + to_string(m);
	}
};
Time operator - (Time c1, Time c2)
{
	int h1 = c1.h, m1 = c1.m;
	int	h2 = c2.h, m2 = c2.m;
	h1 *= 60;
	h2 *= 60;
	int t1 = h1 + m1;
	int t2 = h2 + m2;
	if (t1 - t2 < 0)
	{
		t1 -= t2;
		t1 += 60 * 24;
		Time b;
		b.h = t1/60;
		b.m = t1 % 60;
		b.ld = true;
		return b;
	}
	else
	{
		t1 -= t2;
		Time b;
		b.h = t1 / 60;
		b.m = t1 % 60;
		return b;
	}
}
bool operator > (Time c1, Time c2)
{
	int h1 = c1.h, m1 = c1.m;
	int	h2 = c2.h, m2 = c2.m;
	h1 *= 60;
	h2 *= 60;
	int t1 = h1 + m1;
	int t2 = h2 + m2;
	if (!(!c1.ld && !c2.ld)) { return t1 > t2; }
	if (c1.ld && c2.ld) { return t1 > t2; }
	else
	{
		if (c1.ld) { return t1 > t2 + 24 * 60; }
		if (c2.ld) { return t1 + 24 * 60 > t2; }
	}
}

bool operator < (Time c1, Time c2)
{
	int h1 = c1.h, m1 = c1.m;
	int	h2 = c2.h, m2 = c2.m;
	h1 *= 60;
	h2 *= 60;
	int t1 = h1 + m1;
	int t2 = h2 + m2;
	if (!(!c1.ld && !c2.ld)) { return t1 < t2; }
	if (c1.ld && c2.ld) { return t1 < t2; }
	else
	{
		if (c1.ld) { return t1 < t2 + 24 * 60; }
		if (c2.ld) { return t1 + 24 * 60 < t2; }
	}
}
struct bus
{
	int num;
	string tip, point;
	Time t1, t2;
	void print();
};
void bus::print()
{
	cout << num << " " << tip << " " << "Время прибытия:" << t2.get_time() << endl;
}



int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");

	int n = 0;
	string s, l;

	vector<bus> list;
	bus b;
	while (f.peek() != EOF)
	{
		list.push_back(b);

		getline(f, l);
		list[n].num = stoi(l);

		getline(f, l);
		list[n].tip = l;

		getline(f, l);
		list[n].point = l;

		getline(f, l);
		list[n].t1.set_time(l);

		getline(f, l);
		list[n].t2.set_time(l);

		n++;
		getline(f, l);
	}
	cout << "Задайте время вида hh:mm:";
	Time tf;
	cin >> l;
	tf.set_time(l);
	Time m;
	m.set_time("12:00");
	Time ts = tf - m;
	for (int i=0; i < list.size(); i++)
	{
		if (list[i].t2 > ts && list[i].t2 < tf) list[i].print();
	}
	

}
/*В справочной автовокзала хранится расписание движения автобусов. Для каждого рейса
указаны: номер рейса; тип автобуса; пункт назначения; время отправления; время прибытия на
конечный пункт. Вывести информацию о всех рейсах, которыми можно воспользоваться для прибытия в пункт
назначения не позднее чем за 12 часов до заданного времени (интересующее время прибытия
вводится с клавиатуры)*/