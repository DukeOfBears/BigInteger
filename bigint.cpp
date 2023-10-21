#include <iostream>
#include <vector>

class BigInt {
private:
  static const int base = 10;
  size_t length = 0;
  std::vector<int> digits; 
  bool positive = true;
  void converse() {
    for (size_t i = 0; i < length/2; ++i) {
      std::swap(digits[i], digits[digits.size() - 1 - i]);
    }
  }

  void resize(const BigInt& right) {
    if (length < right.length) {
      length = right.length;
      digits.resize(length);
    }
  }

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

  BigInt(int64_t num) {
    if (num < 0) {
      positive = false;
      num *= -1;
    }
    while (num > 0) {
      digits.push_back(num % base);
      ++length;
      num /= base;  
    }
  }

  BigInt& operator+=(const BigInt& right) {
    if (positive && right.positive) {
      resize(right); 
      size_t excess = 0;
      for (size_t i = 0; i < right.length; ++i) {
        (digits[i] += right.digits[i]) += excess;
        excess = 0;
        if (digits[i] >= base) {
          excess += 1;
          digits[i] %= base;
        }
      }
      if (excess) {
        digits.push_back(excess);
        ++length;
      }
      return *this;
    } 
    return *this -= right;
  } 

  BigInt& operator-=(const BigInt& right) {
    resize(right);
    size_t less = 0;
      for (size_t i = 0; i < right.length; ++i) {
        if (right.positive) {
          (digits[i] -= right.digits[i]) -= less; 
        } else {
          (digits[i] += right.digits[i]) -= less;
        }
        less = 0;
        if (digits[i] < 0) {
          less += 1;
          digits[i] += base;
        }
      }
      if (less) {
        positive = !positive;
        digits.front() -= base;
        digits.front() *= -1;
        for (size_t i = 1; i < length; ++i) {
          digits[i] -= base - 1;
          digits[i] *= -1;
        }
      }
      return *this;
  }

  bool operator<(const BigInt& right) const {
    if (!positive && right.positive) return true;
    if (positive && right.positive && (length < right.length)) return true;
    if (positive && right.positive && length == right.length) {
      for (size_t i = 0; i < length; ++i) {
        if (digits[length - i - 1] < right.digits[length - i - 1]) return true;  
      }
    }
    if (!positive && !right.positive && (right.length < length)) return true;
    if (!positive && !right.positive && (right.length == length)) {
      for (size_t i = 0; i < length; ++i) {
        if (right.digits[length - i - 1] < digits[length - i - 1]) return true;
      }
    }
    return false;
  }

  bool operator>(const BigInt& right) const {
    return right < *this;
  }

  bool operator==(const BigInt& right) const {
    if (length == right.length && positive == right.positive) {
      for (size_t i = 0; i < length; ++i) {
        if (digits[i] != right.digits[i]) return false;
      }
      return true;
    }
    return false;
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
 /* std::string s1 = "123";
  std::string s2 = "-111";
  BigInt a = s1;
  BigInt b = s2;
  std::cout << a << '\n';
  std::cout << b << '\n';
  int64_t num = 123456789;
  BigInt c = num;
  std::cout << c.size() << '\n';
  std::cout << c << '\n';
  */
  std::string s1 = "186";
  std::string s2 = "3215";
  BigInt a = s1;
  BigInt b = s2;
  std::cout << (a -= b) << '\n';
  

}

