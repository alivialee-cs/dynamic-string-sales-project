// File:        string.cpp   
//
// Version:     1.1
// Date:        9/5/25
// Author:      Alivia Lee
//

#include "string.hpp"

String::String() {
    stringSize = 1;          // 1 byte for '\0'
    str = new char[stringSize];
    str[0] = '\0';
}

String::String(char ch) {
    if (ch == '\0') {
        stringSize = 1;
        str = new char[stringSize];
        str[0] = '\0';
    }
    else {
        stringSize = 2;        // one char + '\0'
        str = new char[stringSize];
        str[0] = ch;
        str[1] = '\0';
    }
}

String::String(const char s[]) {
    int count = 0;
    while (s[count] != '\0') ++count;   // compute length

    stringSize = count + 1;             // +1 for null terminator
    str = new char[stringSize];

    for (int i = 0; i < count; ++i)
        str[i] = s[i];

    str[count] = '\0';                  // always null terminate
}

int String::length() const{
    int i = 0;
    while(str[i] != 0){
        ++i;
    }
    return i;
}

int String::capacity() const {
    return stringSize - 1;  // excludes null terminator
}

char& String::operator[](int index) {
    return str[index];
}

char String::operator[](int index) const {
    return str[index];
}

String& String::operator+=(const String& rhs) {
    int leftLen = 0;
    while (str[leftLen] != '\0') ++leftLen;

    int rightLen = 0;
    while (rhs.str[rightLen] != '\0') ++rightLen;

    char* newStr = new char[leftLen + rightLen + 1];

    // Copy left
    for (int i = 0; i < leftLen; ++i)
        newStr[i] = str[i];

    // Copy right
    for (int i = 0; i < rightLen; ++i)
        newStr[leftLen + i] = rhs.str[i];

    newStr[leftLen + rightLen] = '\0';

    delete[] str;
    str = newStr;

    _capacity = leftLen + rightLen;
    stringSize = leftLen + rightLen + 1;

    return *this;
}

String operator+(String lhs, const String& rhs) {
    lhs += rhs;
    return lhs;
}

bool String::operator==(const String& rhs) const{
    if(length() != rhs.length()) return false;
    for(int i = 0; i < length(); ++i){
        if(str[i] != rhs.str[i]) return false;
    }
    return true;
}

bool operator==(const char lhs[], const String& rhs) {
    int i = 0;
    while (lhs[i] != '\0') ++i;
    if (i != rhs.length()) return false;  // lengths differ

    for (int j = 0; j < i; ++j) {
        if (lhs[j] != rhs[j]) return false;  // mismatch
    }
    return true;
}

bool operator==(char ch, const String& rhs) {
    return (rhs.length() == 1 && rhs[0] == ch);
}

bool operator!=(const String& lhs, const String& rhs){
    return !(lhs == rhs);
}

bool String::operator<(const String& rhs) const {
    int minLength;
    if (length() < rhs.length()) {
        minLength = length();
    } else {
        minLength = rhs.length();
    }

    for (int i = 0; i < minLength; ++i) {
        if (str[i] < rhs.str[i]) return true;
        if (str[i] > rhs.str[i]) return false;
    }

    // All compared characters are equal; shorter string is smaller
    if (length() < rhs.length()) return true;
    return false;
}

bool operator<(const char lhs[], const String& rhs) {
    String temp(lhs);      // make a String from the C-string
    return temp < rhs;     // call your member operator<
}

bool operator<(char ch, const String& rhs) {
    String temp(ch);       // single-char String
    return temp < rhs;     // call your member operator<
}

bool operator>(const String& lhs, const String& rhs) {
    return !(lhs < rhs) && !(lhs == rhs);
}

bool operator<=(const String& lhs, const String& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>=(const String& lhs, const String& rhs) {
    return !(lhs < rhs);
}

String String::substr(int start, int endIndex) const {
    int n = length();

    if (start < 0) start = 0;
    if (endIndex >= n) endIndex = n - 1;
    if (start > endIndex) return String(""); // empty string if start > end

    int newLen = endIndex - start + 1; // inclusive

    char* buffer = new char[newLen + 1];
    for (int i = 0; i < newLen; ++i)
        buffer[i] = str[start + i];
    buffer[newLen] = '\0';

    String result(buffer);
    delete[] buffer;
    return result;
}

int String::findch(int start, char ch) const {
    if (start < 0) start = 0;
    if (start >= length()) return -1;

    for (int i = start; i < length(); ++i) {
        if (str[i] == ch) return i;
    }

    return -1;
}

int String::findstr(int start, const String& strToFind) const {
    if (start < 0) start = 0;
    if (strToFind.length() == 0) return start;  // check empty substring first
    if (start >= length()) return -1;

    int thisLen = length();
    int subLen = strToFind.length();

    for (int i = start; i <= thisLen - subLen; ++i) {
        bool match = true;
        for (int j = 0; j < subLen; ++j) {
            if (str[i + j] != strToFind[j]) {
                match = false;
                break;
            }
        }
        if (match) return i;
    }

    return -1;
}

std::istream& operator>>(std::istream& in, String& rhs) {
    delete[] rhs.str;
    rhs.stringSize = 1;
    rhs._capacity = 0;
    rhs.str = new char[rhs.stringSize];
    rhs.str[0] = '\0';

    char ch;
    int len = 0;

    // Skip leading whitespace
    while (in.get(ch) && std::isspace(ch)) { }

    if (!in) return in;

    // Read characters until next whitespace
    do {
        char* newStr = new char[len + 2]; // +1 for new char, +1 for '\0'
        for (int i = 0; i < len; ++i)
            newStr[i] = rhs.str[i];
        newStr[len] = ch;
        newStr[len + 1] = '\0';

        delete[] rhs.str;
        rhs.str = newStr;

        len++;
        rhs.stringSize = len + 1;  // includes null terminator
        rhs._capacity = len;       // usable characters
    } while (in.get(ch) && !std::isspace(ch));

    return in;
}


std::ostream& operator<<(std::ostream& out, const String& rhs) {
    for (int i = 0; i < rhs.length(); ++i) {
        out.put(rhs[i]);
    }
    return out;
}

String::~String(){
    delete[] str;
}

String::String(const String& rhs) {
    int len = rhs.length();           // actual number of chars
    stringSize = len + 1;             // +1 for '\0'
    _capacity = len;

    str = new char[stringSize];
    for (int i = 0; i < len; ++i)
        str[i] = rhs.str[i];
    str[len] = '\0';
}

void String::swap(String& rhs) {
    char* tempStr = str;
    str = rhs.str;
    rhs.str = tempStr;

    int tempSize = stringSize;
    stringSize = rhs.stringSize;
    rhs.stringSize = tempSize;
}

String& String::operator=(String rhs) {
    swap(rhs);      // constant-time swap
    return *this;
}

std::vector<String> String::split(char ch) const {
    std::vector<String> result;
    int start = 0;
    int end;

    while (start < length()) {
        end = findch(start, ch);

        if (end == -1) {
            result.push_back(substr(start, length() - 1));
            return result;
        }

        result.push_back(substr(start, end - 1));
        start = end + 1;
    }

    // handle trailing delimiter
    if (start == length()) {
        result.push_back(String(""));
    }

    return result;
}

