using namespace std;

long long solution(int price, int money, int count) {
    long long total = price * (((long long)count + 1) * count / 2);
    long long answer = total - money <= 0 ? 0 : total - money;
    return answer;
}