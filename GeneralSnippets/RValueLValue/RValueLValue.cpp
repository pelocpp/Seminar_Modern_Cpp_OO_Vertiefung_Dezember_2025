// =====================================================================================
// LValue / RValue
// =====================================================================================

module modern_cpp:rvalue_lvalue;

namespace LValueRValue {

    // lvalue reference 
    static void sayHello(std::string& message) {
        std::println("sayHello [std::string&]:  {}", message);
    }

    // rvalue reference
    static void sayHello(std::string&& message) {
        std::println("sayHello [std::string&&]: {}", message);
    }

    static void test01() {

        std::string a = "Hello";

        std::string b = " World";

        sayHello(a);
        // a.append ..........
                          //     std::string
        sayHello(a + b);  // + : Konkatenation a+b: "Hello World"
        // hier ist a+b nicht mehr verfügbar
    }

    // -------------------------------------------------------------------

    static void helper(std::string&& message)  // RValue Referenz
    {
        sayHello(message);  // hmmm, welches wird aufgerufen ????
                            // A) &&: message ist vom Typ std::string&&
                            // B) &:  Der Parameter IST ein Name
     
    
        sayHello( std::move ( message ) );
    }

    static void test02()
    {
        std::string a ("ABC");

        // helper(a);  // mit a ??? NEIN

        helper(std::string("Where are we going ..."));  // Kein Namen
    }

    // -------------------------------------------------------------------

    static void test03() {

        std::string s = "Hello";

        sayHello(s);
        // versus
        sayHello(std::move(s));  // casts an lvalue to an rvalue
    }

    // -------------------------------------------------------------------

    static void test04() {

        int a = 2;
        int b = 3;

        int& ri = a;          // works: (lvalue) reference to a (named) variable

        // int& i = 123;      // invalid: (lvalue) reference to a constant

        int&& i = 123;        // works: (rvalue) reference to a constant

        const int& j = 123;   // works: const references binds to everything

        // int& k = a + b;    // invalid: (lvalue) reference to a temporary object

        int&& k = a + b;      // works: (rvalue) reference to a temporary object
    }
}

void main_rvalue_lvalue()
{
    using namespace LValueRValue;
    test01();
    test02();
    test03();
    test04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
