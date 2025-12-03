#include <vector>
#include <list>
#include <print>
#include <algorithm>
#include <deque>

// why static:
// Schutz des Unterprogramms // lokale Hilfsfunktion für DIESE Datei  
// GO for static
static void main_stl_01()
{
	std::vector<int> numbers;

	numbers.reserve(80);   // Performanz
 
	for (int i = 0; i != 100; ++i)
	{
		numbers.push_back(2 * i);

		std::println("size: {:3} - capacity: {:3}", numbers.size(), numbers.capacity());
	}

	numbers.shrink_to_fit();
	std::println("size: {:3} - capacity: {:3}", numbers.size(), numbers.capacity());
}

static void main_stl_02()
{
	std::vector<int> numbers;
	//std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	for (int i = 0; i != numbers.size(); ++i) {
		std::println("{:3}: {:3}", i, numbers[i]);
	}
}

static void main_stl_03()
{
	// STL Container
	std::vector<int> numbers;
	// std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	// STL Iterators: 
	// Was beschreibt ein Iterator: Eine Position in einem Container
	// Achtung: Eine Position ist nicht der WERT des ELements an dieser Stelle !!!
	// Realisierung einer solchen Iterator-Klasse: 
	// Die bringt jeder Container selber mit

	//std::vector<int>::iterator pos = numbers.begin();
	auto pos = numbers.begin();

	if (pos == numbers.end()) {
		std::println("Done");
		return;
	}


	int value = *pos;
	std::println("{:3}", value);

	++pos;
	if (pos == numbers.end()) {
		std::println("Done");
		return;
	}
	value = *pos;
	std::println("{:3}", value);

	++pos;
	if (pos == numbers.end()) {
		std::println("Done");
		return;
	}
	value = *pos;
	std::println("{:3}", value);

	++pos;
	if (pos == numbers.end()) {
		std::println("Done");
		return;
	}
	value = *pos;
	std::println("{:3}", value);

}

static void main_stl_04()
{
	// STL Container
	std::vector<int> numbers;
	//std::list<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	std::vector<int>::iterator pos = numbers.begin();
	//std::vector<int>::iterator last = numbers.end();
	//auto pos = numbers.begin();
	auto last = numbers.end();

	while (pos != last) {

		int value = *pos;
		std::println("{:3}", value);

		++pos;
	}
}

// freie Funktion
static void printer(int value) {
	std::println("{:3}", value);
}

static void main_stl_05()
{
	// STL Container
	// std::vector<int> numbers;
	// std::list<int> numbers;
	std::deque<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	// STL ALgorithmus <==> STL Positionen <==> STL Container 
	std::for_each(
		numbers.begin(),
		numbers.end(),
		printer              // nicht sehr OO
	);
}


class MyPrinter
{
private:
	std::string m_header;

public:
	MyPrinter() : m_header{">: "} {}
	MyPrinter(const std::string& header) : m_header{ header } {}

	void print(int value) {
		std::println("{:3}", value);
	}

	void operator() (int value) {
		std::println("{}{:3}", m_header, value);
	}
};

static void main_stl_06()
{
	MyPrinter printer;
	printer.print(123);

	printer(456);
}

static void main_stl_07()
{
	// STL Container
	// std::vector<int> numbers;
	// std::list<int> numbers;
	std::deque<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	MyPrinter myPrint{ ">>> "};

	// STL ALgorithmus <==> STL Positionen <==> STL Container 
	std::for_each(
		numbers.begin(),
		numbers.end(),
		myPrint             // besser: Habe "State" // Zustand im Callable-Objekt verfügbar
	);
}

static void main_stl_08()
{
	class __lambda_18_3
	{ };


	std::deque<int> numbers;

	numbers.push_back(1);
	numbers.push_back(2);
	numbers.push_back(3);

	//auto myLambda = [](int value) {
	//	std::println("{:3}", value);
	//	};

	std::string header{">>>"};

	// Habe 2 Optionen, um die lokale Variable header in einem Lambda-Objekt
	// zu verwenden:
	// a) als Kopie oder b) über eine Referenz
	std::for_each(
		numbers.begin(),
		numbers.end(),
		[=] (int value) { 
			std::println("{}{:3}", header, value);
		}
	);
}

void main_stl()
{
	main_stl_08();
}