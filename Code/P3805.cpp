// Problem: P3805 【模板】manacher
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P3805
// Memory Limit: 512 MB
// Time Limit: 1000 ms
// Written by yhm.
// Start codeing:2024-09-10 12:50:02
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
using namespace std;
const int maxn=11000100;

int n,ans;
char s[maxn],a[maxn<<1];
int len[maxn<<1];
void change(){
	a[0]='#';a[1]='#';
	for(int i=1;i<=n;i++)a[i<<1]=s[i],a[i<<1|1]='#';
	n=n<<1|1;
}
void manacher(){
	int maxr=0,mid=0;
	for(int i=1;i<=n;i++){
		if(i<maxr)len[i]=min(len[mid*2-i],len[mid]+mid-i);
		else len[i]=1;
		while(a[i+len[i]]==a[i-len[i]])++len[i];
		if(len[i]+i>maxr){
			maxr=len[i]+i;
			mid=i;
		}
	}
}
signed main(){
	scanf("%s",s+1);n=strlen(s+1);
	change();manacher();
	for(int i=1;i<=n;i++)ans=max(ans,len[i]);
	printf("%d",ans-1);
}