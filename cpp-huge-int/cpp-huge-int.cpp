#include <iostream>
#include <string> 
#include <regex>

using namespace std;

// Utilitie functions
int to_int(char char_num) {
    return (int)char_num - '0';
}

char to_char(int num) {
    return num + '0';
}

string remove_zeros(string str) {
    while (str[0] == '0') {
        str.erase(0, 1);
    }
    if (str.length() != 0) {
        return str;
    }
    else return "0";
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

    // + operator's overloading
    HugeInt operator + (const HugeInt& arg) const {
        const HugeInt* longNum, *shortNum;
        string strResult = "";
        int keepedInMind = 0;

        if (this->isNegative) {
            if (arg.isNegative) {//When (-)+(-)
                HugeInt helper = abs(*this) + abs(arg);
                helper.makeNegative();
                
                return helper;
            }
            else { //When (-)+(+)
                return arg - abs(*this);
            }
        } else{ 
            if (arg.isNegative) {//When (+)+(-)
                return *this - abs(arg);
            }
            else {//When (+)+(+)
                // Choosing longer integer as longNum
                if (this->length >= arg.length) {
                    longNum = this;
                    shortNum = &arg;
                }
                else {
                    longNum = &arg;
                    shortNum = this;
                }

                for (int i = 0; i < longNum->length; i++) {
                    // For both longer and shorter number's current digit's position
                    int lCurIndex, sCurIndex = -1;
                    char charPoint;

                    lCurIndex = longNum->length - 1 - i;
                    if (i < shortNum->length) {
                        sCurIndex = shortNum->length - 1 - i;
                    }

                    int resultNum = keepedInMind + to_int(longNum->value[lCurIndex]) + (sCurIndex != -1 ? to_int(shortNum->value[sCurIndex]) : 0);
                    keepedInMind = resultNum / 10;
                    int point = resultNum % 10;
                    charPoint = to_char(point);

                    strResult.insert(0, 1, charPoint);
                }
                if (keepedInMind) strResult.insert(0, 1, to_char(keepedInMind));
                HugeInt result = strResult;

                return  result;
            }
        }
    };


    // - operator's overloading
    HugeInt operator - (const HugeInt& arg) const {
        string bigNum, smallNum;
        string strResult = "";
        bool isResultNegative = false;

        if (this->isNegative) {
            if (arg.isNegative) { // When (-)-(-) 
                return *this+abs(arg);
            }
            else {// When (-)-(+) 
                HugeInt helper = abs(*this) + abs(arg);
                helper.makeNegative();

                return helper;
            }
        }
        else {
            if (arg.isNegative) {// When (+)-(-) 
                return *this + abs(arg);
            }
            else {// When both of numbers are positives. (+)-(+)
                if (*this >= arg) {
                    bigNum = this->value;
                    smallNum = arg.value;

                }
                else {
                    bigNum = arg.value;
                    smallNum = this->value;
                }
                
                for (int i = 0; i < bigNum.length(); i++) {
                    // For both bigger and smaller number's current digit's position
                    int bCurIndex, sCurIndex = -1;
                    int resultDigit = 0;
                    char charPoint;

                    bCurIndex = bigNum.length() - 1 - i;
                    if (i < smallNum.length()) {
                        sCurIndex = smallNum.length() - 1 - i;
                    }

                    int bCurDigit = to_int(bigNum[bCurIndex]);
                    int sCurDigit = (sCurIndex != -1 ? to_int(smallNum[sCurIndex]) : 0);

                    //
                    if (bCurDigit >= sCurDigit) {
                        resultDigit = bCurDigit - sCurDigit;
                    }
                    else {
                        resultDigit = 10 + bCurDigit - sCurDigit;

                        for (int l = bCurIndex - 1; l >= 0; l--) {
                            if (bigNum[l] == '0') {
                                bigNum[l] = '9';
                            }
                            else {
                                int number = to_int(bigNum[l]);
                                cout << number << endl;
                                bigNum[l] = to_char(--number);
                                cout << bigNum[l] << endl;
                                break;
                            }
                        }

                    }
                    charPoint = to_char(resultDigit);


                    strResult.insert(0, 1, charPoint);

                }
                HugeInt result = remove_zeros(strResult);
                result.isNegative = isResultNegative;

                return  result;


            }
        }
    };

    // * operator's overloading
    HugeInt operator * (const HugeInt& arg) const {
        const HugeInt* longNum, * shortNum;
        HugeInt result = 0;
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
            // Current digit's position for shorter number
            int sCurIndex = shortNum->length - 1 - i;
            HugeInt sumer = 0;

            for(int j = 0; j < longNum->length; j++) {
                // Current digit's position for longer number
                int lCurIndex = longNum->length - 1 - j;
                HugeInt currentResult = to_int(longNum->value[lCurIndex]) * to_int(shortNum->value[sCurIndex]);
                HugeInt helper = concatZero(currentResult, j);

                sumer = sumer + helper;
            }
            HugeInt helper = concatZero(sumer, i);
            result = result + helper;

        }

        // XOR for getting negativity of result, 
        // If one of the numbers is negative the result must be negative, 
        // In case both of them are positive or negative the result must be positive
        bool isResultNegative = longNum->isNegative != shortNum->isNegative;
        if (isResultNegative) {
            result.makeNegative();
        }
        

        return result;
    };

    void print() {
        if (this->isNegative) {
            cout << "-"+this->value << endl;
        }
        else {
            cout << this->value<<endl;
        }
    }

    int getLength() {
        return this->length;
    }
    
    // > operator's overloading
    bool operator > (const HugeInt& arg) const {
        if (this->isNegative) {
            if (arg.isNegative) {
                return abs(*this) < abs(arg);
            }
            else {
                return false;
            }
        }
        else {
            if (arg.isNegative) {
                return true;
            }
            else {
                if (this->length > arg.length) {
                    return true;
                }
                else if (this->length < arg.length) {
                    return false;
                }
                else {
                    for (int i = 0; i < this->length; i++) {
                        int num1, num2;
                        num1 = to_int(this->value[i]);
                        num2 = to_int(arg.value[i]);
                        if (num1 > num2) {
                            return true;
                        }
                        else  if (num2 > num1) {
                            return false;
                        }
                    }

                    return false;
                }
            }
        }
    };

    // == operator's overloading
    bool operator == (const HugeInt& arg) const {
        if (this->isNegative) {
            if (arg.isNegative) {
                for (int i = 0; i < this->length; i++) {
                    int num1, num2;
                    num1 = to_int(this->value[i]);
                    num2 = to_int(arg.value[i]);
                    if (num1 > num2) {
                        return false;
                    }
                    else  if (num2 > num1) {
                        return false;
                    }
                }

                return true;
            }
        }
        else {
            if (arg.isNegative) {
                return false;
            }
            else {
                if (this->length > arg.length) {
                    return false;
                }
                else if (this->length < arg.length) {
                    return false;
                }
                else {
                    for (int i = 0; i < this->length; i++) {
                        int num1, num2;
                        num1 = to_int(this->value[i]);
                        num2 = to_int(arg.value[i]);
                        if (num1 > num2) {
                            return false;
                        }
                        else  if (num2 > num1) {
                            return false;
                        }
                    }

                    return true;
                }
            }
        }
    };

    // <= operator's overloading
    bool operator <= (const HugeInt& arg) const {
        return !(*this > arg);
    };

    // < operator's overloading
    bool operator < (const HugeInt& arg) const {
        return *this <= arg && !(*this == arg);
    };

    // >= operator's overloading
    bool operator >= (const HugeInt& arg) const {
        return *this > arg ||(*this == arg);
    };

    // Function for getting absolut value of HugeInt
    friend HugeInt abs(HugeInt num) {
        HugeInt res = 0;
        if (num.value[0] == '-') {
            res = num.value.erase(0, 1);
        }
        else {
            res = num;
        }
        res.isNegative = false;
        return res;
    }

    friend HugeInt concatZero(HugeInt num, int n){
        if (num.value != "0") {
            return num.value.insert(num.length, n, '0');
        }

        return 0;
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
            this->isNegative = value[0] == '-';

            if (this->isNegative) {    
                this->value = value.erase(0,1);
                if (this->value == "0") {
                    this->isNegative = false;
                }
            }
            else {
                this->value = value;
            }
            this->length = this->value.length();
         }
        else {
            cout <<endl<< "Invalid value : "<<value<<" is not an integer" << endl;
            abort();
        }
    }

    void makeNegative() {
        if (this->value != "0") {
            this->isNegative = true;
        }
    }
};

int main()
{
    HugeInt a = "-4";
    HugeInt b = "-4";
    HugeInt c = a+b;
    c.print();
}