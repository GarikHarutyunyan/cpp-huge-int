#include <iostream>
#include <string> 
#include <regex>

using namespace std;



int to_int(char char_num) {
    return (int)char_num - '0';
}

char to_char(int num) {
    return num + '0';
}
class HugeInt
{
public:
    // Constructors
    // Constructor for string values
    HugeInt(string value) {
        Construct(value);
    };

    // Constructor for char's arrays
    HugeInt(const char* value){
        string strValue  = value;
        Construct(strValue);
    };

    // Constructor for integers
    HugeInt(int value) {
        string strValue = to_string(value);
        
        Construct(strValue);
    };

    // Plus operator's overloading // HugeInt + HugeInt 
    HugeInt operator + (const HugeInt& arg) const {
        const HugeInt* firstNumber, *secondNumber;
        string result = "";

        // Choosing longer integer as firstNumber
        if (this->length>= arg.length) {
            firstNumber = this;
            secondNumber = &arg;
        } 
        else {
            firstNumber = &arg;
            secondNumber = this;
        }

        for (int i = 0; i < firstNumber->length; i++) {
            int fCurrentDigit, sCurrentDigit = 0;
            fCurrentDigit = firstNumber->length - 1 - i;
            if (i< secondNumber->length) {
                sCurrentDigit = secondNumber->length - 1 - i;
            }
            int resultDigit = to_int(firstNumber->value[fCurrentDigit]) + to_int(secondNumber->value[sCurrentDigit]);
            char charResult = to_char(resultDigit);

            cout << charResult << endl;

            result.insert(0, 1, charResult);
        }
        cout << "REsult: " << result << endl;

        return  this->value + arg.value;
    };

    //HugeInt operator * (const HugeInt& arg) const;

    void print() {
        cout << this->value<<endl;
    }


    int getLength() {
        return this->length;
    }
    

private:
    string value;
    bool isNegative;
    int length;


    // Function for string | const char* values
    void Construct(string value) {
        regex int_expr("([+-]?[1-9]\d*|0)+");

        // Regex validation
        if (regex_match(value, int_expr)){
            bool isNegative = value[0] == '-';

            this->value = value;

            // Chech if value is negative
            this->isNegative = isNegative ? true : false;
            this->length = isNegative ? this->value.length() - 1 : this->value.length();

            cout << endl << this->length  << endl;
         }
        else
        {
            cout <<endl<< "Invalid value : "<<value<<" is not an integer" << endl;
        }
    }

    


};



int main()
{
    int aaa = 54;
    cout << aaa << endl;
    HugeInt a = "12345";
    HugeInt b = 54321;
    HugeInt c = a + b;
    c.print();
}