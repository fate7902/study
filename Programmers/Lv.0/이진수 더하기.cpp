string solution(string bin1, string bin2) {
    string answer = "";
    reverse(bin1.begin(), bin1.end());
    reverse(bin2.begin(), bin2.end());

    int plus = 0;
    if (bin1.size() >= bin2.size()) {
        for (int i = 0; i < bin1.size(); i++) {
            if (bin2.size() > i) {
                if ((bin1[i] - '0') + (bin2[i] - '0') + plus >= 2) {
                    answer += to_string((bin1[i] - '0') + (bin2[i] - '0') + plus - 2);
                    plus = 1;
                }
                else {
                    answer += to_string((bin1[i] - '0') + (bin2[i] - '0') + plus);
                    plus = 0;
                }
            }
            else {
                if (bin1[i] - '0' + plus >= 2) {
                    answer += to_string(bin1[i] - '0' + plus - 2);
                    plus = 1;
                }
                else {
                    answer += to_string(bin1[i] - '0' + plus);
                    plus = 0;
                }
            }
        }
    }
    else {
        for (int i = 0; i < bin2.size(); i++) {
            if (bin1.size() > i) {
                if ((bin1[i] - '0') + (bin2[i] - '0') + plus >= 2) {
                    answer += to_string((bin1[i] - '0') + (bin2[i] - '0') + plus - 2);
                    plus = 1;
                }
                else {
                    answer += to_string((bin1[i] - '0') + (bin2[i] - '0') + plus);
                    plus = 0;
                }
            }
            else {
                if (bin2[i] - '0' + plus >= 2) {
                    answer += to_string(bin2[i] - '0' + plus - 2);
                    plus = 1;
                }
                else {
                    answer += to_string(bin2[i] - '0' + plus);
                    plus = 0;
                }
            }
        }
    }
    if (plus != 0) answer += to_string(plus);
    reverse(answer.begin(), answer.end());
    return answer;
}