// Problem: C. Rabbits
// Contest: Codeforces - Codeforces Global Round 29 (Div. 1 + Div. 2)
// URL: https://codeforces.com/contest/2147/problem/C
// Memory Limit: 256 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-09-22 09:34:13
// 
// Powered by CP Editor (https://cpeditor.org)

#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define db long double
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
void work(){
	n=read();scanf("%s",s+1);
	for(int i=1,j=1;i<=n;i++)if(s[i]=='0'){
		j=i;
		while(j+1<=n&&s[j+1]!=s[j])j++;
		if(s[j]=='1')j--;
		int num=0;for(int k=i;k<=j;k+=2)num+=s[k]=='0';
		if(num&1){
			// cout<<i<<" "<<j<<"\n";
			if((i==1||s[i-1]=='0')||j==n||(s[j+1]=='0')){}
			else{puts("NO");return ;}
		}
		i=j;
	}
	puts("YES");
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}