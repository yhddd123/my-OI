#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    // 假设程序本来应该用分钟数 294 计算
    int trueMinutes = 4 * 60 + 54; // 294

    // ---------------------------
    // Bug 场景 A：错误地用乘法循环（每分钟 *2，而不是 +rate）
    // ---------------------------
    int x = 1;
    for (int i = 0; i < 31; i++) {
        x *= 2; // 连续倍增，最终变成 -2147483648（int 溢出）
    }
    x = x - 1; // 结果是 2147483647

    double fee = x / 100.0;

    cout << "溢出结果: " << fixed << setprecision(2) << fee << endl;

    // ---------------------------
    // Bug 场景 B：错误地把分钟当作移位位数
    // ---------------------------
    int shifted = (1 << 31) - 1; // (1 << 31) 溢出成负数，再 -1 得到 2147483647
    double fee2 = shifted / 100.0;

    cout << "位移错误结果: " << fixed << setprecision(2) << fee2 << endl;

    return 0;
}
