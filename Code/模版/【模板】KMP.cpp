// Problem: P3375 【模板】KMP
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3375
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-10 12:52:48
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=1000010;

char s[maxn],q[maxn];
int n,m,nxt[maxn];
int main(){
	scanf("%s%s",s+1,q+1);n=strlen(s+1),m=strlen(q+1);
	for(int i=2,j=0;i<=m;i++){
		while(j&&q[i]!=q[j+1])j=nxt[j];
		if(q[i]==q[j+1])j++;
		nxt[i]=j;
	}
	for(int i=1,j=0;i<=n;i++){
		while(j&&s[i]!=q[j+1])j=nxt[j];
		if(s[i]==q[j+1])j++;
		if(j==m){
			printf("%d\n",i-m+1);
			j=nxt[j];
		}
	}
	for(int i=1;i<=m;i++)printf("%d ",nxt[i]);
}