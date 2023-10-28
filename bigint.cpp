#include <iostream>
#include <vector>
// binary division
class BigInt {
private:
  static const int base = 10;
  std::vector<int> digits; 
  bool positive = true;
  void converse() {
    for (size_t i = 0; i < digits.size()/2; ++i) {
      std::swap(digits[i], digits[digits.size() - 1 - i]);
    }
  }

  void resize(const BigInt& right) {
    if (digits.size() < right.digits.size()) {
      digits.resize(digits.size());
    }
  }

public:
  BigInt() = default;

  BigInt(const std::string& str): digits(str.size()) {
    if (str.front() == '-') {
      positive = false;
      digits.resize(digits.size() - 1);
    }
    for (size_t i = 0; i < digits.size(); ++i) {
      digits[i] = std::stoi(str.substr(str.size() - 1 - i, 1));
    }
  }

  explicit BigInt(int64_t num) {
    if (num < 0) {
      positive = false;
      num *= -1;
    }
    while (num > 0) {
      digits.push_back(num % base);
      num /= base;  
    }
  }

  BigInt& operator+=(const BigInt& right) {
    if (positive && right.positive) {
      resize(right); 
      size_t excess = 0;
      for (size_t i = 0; i < right.digits.size(); ++i) {
        (digits[i] += right.digits[i]) += excess;
        excess = 0;
        if (digits[i] >= base) {
          excess += 1;
          digits[i] %= base;
        }
      }
      if (excess) {
        digits.push_back(excess);
      }
      return *this;
    } 
    return *this -= right;
  } 

  BigInt& operator-=(const BigInt& right) {
    resize(right);
    size_t less = 0;
      for (size_t i = 0; i < right.digits.size(); ++i) {
        if (right.positive) {
          (digits[i] -= right.digits[i]) -= less; 
        } else {
          
        }
        less = 0;
        if (digits[i] < 0) {
          less += 1;
          digits[i] += base;
        }
        
      }
      if (less) {
        if (!positive && right.positive) {
          digits.push_back(less);
        } else {
          positive = !positive;
          digits.front() -= base;
          digits.front() *= -1;
          for (size_t i = 1; i < digits.size(); ++i) {
            digits[i] -= base - 1;
            digits[i] *= -1;
          }
        }
      }
      return *this;
  }
  BigInt& operator*=(const BigInt& right) {
    std::vector<int> res(digits.size() + right.digits.size() + 1);
    for (size_t i = 0; i < digits.size(); ++i) {
      for (size_t j = 0; j < right.digits.size(); ++j) {
        res[i + j] += digits[i] * right.digits[j];
        if (res[i + j] >= base) {
          res[i + j + 1] += res[i + j] / base;
          res[i + j] %= base;
        }
      }
    }
    while (res.back() == 0 && res.size() != 1) res.pop_back();
    digits = std::move(res);
    return *this;
  }

  BigInt operator*(const BigInt& right) const {
    BigInt copy = *this;
    copy *= right;
    return copy;
  }


  bool operator<(const BigInt& right) const {
    if (!positive && right.positive) return true;
    if (positive && right.positive && (digits.size() < right.digits.size())) return true;
    if (positive && right.positive && digits.size() == right.digits.size()) {
      for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[digits.size() - i - 1] < right.digits[digits.size() - i - 1]) return true;  
      }
    }
    if (!positive && !right.positive && (right.digits.size() < digits.size())) return true;
    if (!positive && !right.positive && (right.digits.size() == digits.size())) {
      for (size_t i = 0; i < digits.size(); ++i) {
        if (right.digits[digits.size() - i - 1] < digits[digits.size() - i - 1]) return true;
      }
    }
    return false;
  }

  bool operator>(const BigInt& right) const {
    return right < *this;
  }

  bool operator==(const BigInt& right) const {
    if (digits.size() == right.digits.size() && positive == right.positive) {
      for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != right.digits[i]) return false;
      }
      return true;
    }
    return false;
  }


  size_t size() const {
    return digits.size();
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
  std::string s1 = "128";
  std::string s2 = "256";
  BigInt a = s1;
  BigInt b = s2;
  std::cout << a << ' ' << b << '\n';
  std::cout << (a *= b) << '\n';
  
  

}

