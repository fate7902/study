#include <string>
#include <vector>

using namespace std;

int solution(string my_string, string is_suffix) {      
    return is_suffix.size() > my_string.size() ? 0 : my_string.substr(my_string.size() - is_suffix.size(), is_suffix.size()) == is_suffix ? 1 : 0;
}