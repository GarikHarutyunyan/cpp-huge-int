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

string concatZero(string s, int n) {
    for (int i = 0; i < n; i++) {
        s+='0';
    }
    return s;
}

class HugeInt
{
public:
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
        const HugeInt* longNum, *shortNum;
        string strResult = "";
        int keepedInMind = 0;

        // Choosing longer integer as longNum
        if (this->length>= arg.length) {
            longNum = this;
            shortNum = &arg;
        } 
        else {
            longNum = &arg;
            shortNum = this;
        }

        for (int i = 0; i < longNum->length; i++) {
            // For both longer and shorter number's current digit's position
            int lCurDigit, sCurDigit = -1, resultNum, point;
            char charPoint;

            lCurDigit = longNum->length - 1 - i;
            if (i< shortNum->length) {
                sCurDigit = shortNum->length - 1 - i;
            }

            resultNum = keepedInMind + to_int(longNum->value[lCurDigit]) + (sCurDigit != -1 ? to_int(shortNum->value[sCurDigit]) : 0);
            keepedInMind = resultNum / 10;
            point = resultNum % 10;
            charPoint = to_char(point);

            strResult.insert(0, 1, charPoint);
        }
        if(keepedInMind) strResult.insert(0, 1, to_char(keepedInMind));
        HugeInt result = strResult;

        return  result;
    };

    HugeInt operator * (const HugeInt& arg) const {
        const HugeInt* longNum, * shortNum;
        HugeInt result = 0;
        int keepedInMind = 0;
        // Choosing longer integer as longNum
        if (this->length >= arg.length) {
            longNum = this;
            shortNum = &arg;
        }
        else {
            longNum = &arg;
            shortNum = this;
        }

        for (int i = 0; i < shortNum->length; i++) {
            // For both longer and shorter number's current digit's position
            int sCurDigit = shortNum->length - 1 - i;
            HugeInt sumer = 0;

            for(int j = 0; j < longNum->length; j++) {
                int lCurDigit = longNum->length - 1 - j;
                HugeInt currentResult = to_int(longNum->value[lCurDigit]) * to_int(shortNum->value[sCurDigit]);
                string helper = concatZero(currentResult.value, j);

                sumer = sumer + helper;
            }
            string helper = concatZero(sumer.value, i);
            result = result + helper;

        }

        return result;
    };

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
        regex int_expr("^[+-]?(0|[1-9][0-9]*)$");

        // Regex validation
        if (regex_match(value, int_expr)){
            bool isNegative = value[0] == '-';

            this->value = value;

            // Chech if value is negative
            this->isNegative = isNegative;
            this->length = isNegative ? this->value.length() - 1 : this->value.length();
         }
        else {
            cout <<endl<< "Invalid value : "<<value<<" is not an integer" << endl;
        }
    }
};

int main()
{
    int aaa = 2419;
    // cout << aaa << endl;
    HugeInt a = "316";
    HugeInt b = 999;
    HugeInt c = a * aaa;
    c.print();
}