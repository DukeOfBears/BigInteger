#include <iostream>
#include <vector>

class BigInt {
private:
  static const int base = 10;
  size_t length = 0;
  std::vector<int> digits; 
  bool positive = true;

public:
  BigInt() = default;

  BigInt(const std::string& str): length(str.size()), digits(length) {
    if (str.front() == '-') {
      positive = false;
      digits.resize(--length);
    }
    for (size_t i = 0; i < length; ++i) {
      digits[i] = std::stoi(str.substr(str.size() - 1 - i, 1));
    }
  }
  
  size_t size() const {
    return length;
  }

  bool is_positive() const {
    return positive;
  }

  int operator[](size_t index) const {
    return digits[index];   
  }

  int& operator[](size_t index) {
    return digits[index];
  }

  

};

std::ostream& operator<<(std::ostream& out, const BigInt& num) {
  if (!num.is_positive()) out << '-';
  for (size_t i = 0; i < num.size(); ++i) {
    out << num[num.size() - i - 1]; 
  }
  return out;
}

    

int main() {
  std::string s1 = "123";
  std::string s2 = "-111";
  BigInt a = s1;
  BigInt b = s2;
  std::cout << a << '\n';
  std::cout << b << '\n';
}

