#include <string>
#include <vector>
#include <regex>

using namespace std;

string solution(string new_id) {    
    for(auto& c : new_id) if(isupper(c)) c = tolower(c);
    regex pattern("[^a-zA-Z0-9\\-_.]");
    new_id = regex_replace(new_id, pattern, "");
    while (new_id.find("..") != string::npos) {
        new_id = regex_replace(new_id, regex("\\.{2}"), ".");
    }
    new_id = regex_replace(new_id, regex("^\\."), "");
    new_id = regex_replace(new_id, regex("\\.$"), "");
    if(new_id.empty()) new_id = "a";
    if(new_id.length() >= 16) {
        new_id = new_id.substr(0, 15);
        new_id = regex_replace(new_id, regex("\\.$"), "");
    }
    while(new_id.length() < 3) new_id += new_id.back();
    return new_id;
}