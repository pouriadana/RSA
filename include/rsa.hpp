#include <boost/multiprecision/cpp_int.hpp>

using cpp_int = boost::multiprecision::cpp_int;
class RSA {
public:
    RSA() {}
private:
    // two prime integers each with the size of key_length / 2
    cpp_int p{"0"};
    cpp_int q{"0"};
};