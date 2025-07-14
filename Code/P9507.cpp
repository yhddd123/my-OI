// Problem: P9507 [BalkanOI2018] Popa
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P9507
// Memory Limit: 250 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include "popa.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=1010;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

// int query(int a, int b, int c, int d){
	// printf("? %d %d %d %d\n", a, b, c, d);fflush(stdout);
	// int x; x=read(); return x;
// }
int query(int a, int b, int c, int d);
int st[maxn],tp;
int work(int n,int *l,int *r){
	tp=0;
	for(int i=0;i<n;i++){
		l[i]=r[i]=-1;
		while(tp){
			if(query(i,i,st[tp],i)){
				l[i]=st[tp];
				tp--;
			}
			else break;
		}
		if(tp)r[st[tp]]=i;
		st[++tp]=i;
	}
	return st[1];
}

int solve(int N, int* Left, int* Right){return work(N,Left,Right);}

// int main(){
	// int T;
	// scanf("%d", &T);
	// while (T--)	{
		// int n;
		// scanf("%d", &n);
		// int *left = new int[n];
		// int *right = new int[n];
		// int rt = solve(n, left, right);
		// printf("! %d\n", rt);
		// for (int i = 0; i < n; i++)
			// printf("%d%c", left[i], " \n"[i == n - 1]);
		// for (int i = 0; i < n; i++)
			// printf("%d%c", right[i], " \n"[i == n - 1]);
		// fflush(stdout);
		// delete[] left;
		// delete[] right;
	// }
	// // return 0;
// }