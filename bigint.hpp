#include <iostream>
#include <vector>
class BigInt {
private:
  static const int base = 10;
  std::vector<int> digits; 
  bool positive = true;

  void converse();
  void resize(const BigInt& right);
public:
  BigInt() = default;
  BigInt(const std::string& str);
  explicit BigInt(int64_t num);
  BigInt& operator+=(const BigInt& right);
  BigInt& operator-=(const BigInt& right);
  BigInt& operator*=(const BigInt& right);
  size_t size() const;
  bool is_positive() const;
  int operator[](size_t index) const;
  int& operator[](size_t index);
};

std::ostream& operator<<(std::ostream& out, const BigInt& num);

