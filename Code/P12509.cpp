// Problem: P12509 【模板】通信题
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P12509
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2025-05-12 22:20:35
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;

int Alice(string S){
	int n=S.size();
	int ans=0;for(int i=0;i<n;i++)ans^=(i+1)*(S[i]-'0');
	return ans;
}
int Bob(string T, int X){
	int n=T.size();
	int ans=0;for(int i=0;i<n;i++)ans^=(i+1)*(T[i]-'0');
	return ans^X;
}

// int main() {
    // string s_str, t_str;
    // cin >> s_str >> t_str;
// 
    // int alice_val_x = Alice(s_str);
    // if (alice_val_x < 0 || alice_val_x >= (1 << 20)) {
        // cout << "Wrong Answer" << endl;
        // return 0;
    // }
// 
    // int bob_val_p = Bob(t_str, alice_val_x);
    // if (bob_val_p < 0 || bob_val_p > (int)s_str.size()) {
        // cout << "Wrong Answer" << endl;
        // return 0;
    // }
// 
    // if ((s_str == t_str && bob_val_p != 0) || (s_str != t_str && s_str[bob_val_p - 1] == t_str[bob_val_p - 1])) {
        // cout << "Wrong Answer" << endl;
        // return 0;
    // }
// 
    // cout << "Accepted" << endl;
    // return 0;
// }