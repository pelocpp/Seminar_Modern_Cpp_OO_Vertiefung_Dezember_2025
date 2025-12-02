// =====================================================================================
// class MyString
// =====================================================================================

#define _CRT_SECURE_NO_WARNINGS 1

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

#include <cstring>
#include <memory>
#include <print>
#include <string>

class MyString
{
public:
    MyString() {}

    // KEIN Destruktor erforderlich:
    // Vaterklasse (MyString) kümmert sich im enthaltene Kindeklassen (m_string)
    // bzgl. des Destruktorenaufrufs

    MyString(const char* string)
    {
        // std::find ... nach 0  .. STL Context
        std::size_t len = std::strlen(string);
        char* cp = new char[len + 1];  // term. Null

        // std::copy ....
        std::strncpy(cp, string, len);
        cp[len] = '\0';

        // wie in 
        // https://stackoverflow.com/questions/44950439/shared-ptr-to-an-array
        m_string = std::shared_ptr<char>(cp, std::default_delete<char[]>());
    }

    void print()
    {
        if (m_string.get() == nullptr) {
            std::println("<null>");
        }
        else {
            std::println("{}", m_string.get());
        }
    }

    // subscript operator
    char& operator[] (int index) { return m_string.get()[index]; }

    // copy c'tor
    MyString(const MyString& other) {
    
        m_string = other.m_string;

        // ODER

        //std::size_t len = std::strlen(other.m_string.get());
        //char* cp = new char[len + 1];

        //std::strncpy(cp, other.m_string.get(), len);
        //cp[len] = '\0';

        //m_string = std::shared_ptr<char>(cp, std::default_delete<char[]>());
    }


    // Bemerkung: KEIN operator= erforderlich:
    // Vaterklasse (MyString) kümmert sich um enthaltene operator= Implementierungen
    // in den Kindklassen (m_string)

    // operator=
    MyString& operator=(const MyString& other) {

        if (this == &other) {
            return *this;
        }

     //   m_string = other.m_string;  // WRONG

        // oder

        // Korrekte Weg: Ein neues std::shared_ptr - Objekt erzeugen !!!

        std::size_t len = std::strlen(other.m_string.get());
        char* cp = new char[len + 1];  // 'array new' !!!

        std::strncpy(cp, other.m_string.get(), len);
        cp[len] = '\0';

        // Beachte: den array - 'array deleter' hier beifügen
        m_string = std::shared_ptr<char>(cp, std::default_delete<char[]>());

        // ab C++ 17:  suchen .......
        // m_string = std::shared_ptr<char[]>(cp);

        return *this;
    }

private:
    std::shared_ptr<char> m_string;
};

// =====================================================================================

// KEIN Destruktor erforderlich:
// Vaterklasse (MyStringEx) kümmert sich um enthaltene Kindklassen (m_string / unique_ptr)
// bzgl. des Destruktorenaufrufs

// Rule-of-Three:

class MyStringEx
{
public:
    MyStringEx() {}

    MyStringEx(const char* string)
    {
        std::size_t len = std::strlen(string);

        m_string = std::make_unique<char[]> (len+1);

        // std::copy
        std::strncpy(m_string.get(), string, len);
        m_string.get()[len] = '\0';
    }

    void print()
    {
        if (m_string.get() == nullptr) {
            std::println("<null>");
        }
        else {
            std::println("{}", m_string.get());
        }
    }

    // subscript operator
    char& operator[] (int index) { return m_string.get()[index]; }

    //// copy c'tor
    //MyStringEx(const MyStringEx& other) {

    //    std::size_t len = std::strlen(other.m_string.get());

    //    m_string = std::make_unique<char[]>(len + 1);

    //    std::strncpy(m_string.get(), other.m_string.get(), len);
    //    m_string.get()[len] = '\0';
    //}


    // Bemerkung: operator= IST erforderlich, wenn ich die Wertzuweisung
    // von MyStringEx - Objekten haben / unterstützen möchte !!!
    // Vaterklasse (MyString) kümmert sich um enthaltene operator= Implementierungen
    // in den Kindklassen (m_string), ABER std::unique_ptr unterstützt KEINEN operator=
    
    // operator=
    MyStringEx& operator=(const MyStringEx& other) {

        if (this == &other) {
            return *this;
        }

        std::size_t len = std::strlen(other.m_string.get());

        m_string = std::make_unique<char[]>(len + 1);

        std::strncpy(m_string.get(), other.m_string.get(), len);
        m_string.get()[len] = '\0';

        return *this;
    }

    // X&       operator=(X&&)                noexcept
    MyStringEx& operator=(MyStringEx&& other) noexcept {

        if (this == &other) {
            return *this;
        }

        m_string = std::move(other.m_string);

        return *this;
    }

private:
    std::unique_ptr<char[]> m_string;
};

static void main_my_string_01()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MyString ms{ };
}

static void main_my_string_02()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MyString ms{ };
    ms.print();

    MyString ms1{ "ABC" };
    ms1.print();

    MyString ms2{ "XYZ" };
    ms2.print();

    ms1 = ms2;   // WERTZUWEISUNG 
    ms1.print();

    ms2[0] = '?';

    ms1.print();
    ms2.print();
}

static void main_my_string_03()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MyString ms1{ "ABC" };
    ms1.print();

    MyString ms2{ "XYZ" };
    ms2.print();

    ms1 = ms2;
    ms1.print();

    ms2[0] = '?';

    ms1.print();
    ms2.print();
}

static void main_my_string_04()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MyStringEx ms1{ "ABC" };
    ms1.print();

    MyStringEx ms2{ "XYZ" };
    ms2.print();

    ms1 = ms2;
    ms1.print();

    ms2[0] = '?';

    ms1.print();
    ms2.print();
}

static void main_my_string_05()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    MyStringEx ms1{ "ABC" };
    ms1.print();

    MyStringEx ms2{ "XYZ" };
    ms2.print();

    ms1 = std::move(ms2);

    ms1.print();
    ms2.print();
}

void main_my_string()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


    //int* ptr = new int[10];
    //return;

    // main_my_string_01();
    //main_my_string_02();
    //main_my_string_03();
    // main_my_string_04();
    main_my_string_05();
}

// =====================================================================================
// End-of-File
// =====================================================================================
