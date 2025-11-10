// Problem: B - Minimize Even Palindrome
// Contest: AtCoder - AtCoder Regular Contest 209 (Div. 1)
// URL: https://atcoder.jp/contests/arc209/tasks/arc209_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Written by yhm.
// Start codeing:2025-11-09 20:27:50
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
int t[26];
char ans[maxn];
void work(){
	scanf("%s",s+1);n=strlen(s+1);
	for(int i=0;i<26;i++)t[i]=0;
	for(int i=1;i<=n;i++)t[s[i]-'a']++;
	int p=-1;
	for(int i=0;i<26;i++)if(t[i]>(n+1)/2)p=i;
	if(p==-1){
		for(int i=1,lst=-1;i<=n;i++){
			int p=-1;for(int j=0;j<26;j++)if((p==-1||t[j]>t[p])&&j!=lst)p=j;
			t[p]--;lst=p;
			putchar('a'+p);
		}
		puts("");
	}
	else if(t[p]==n){
		for(int i=1;i<=n;i++)putchar('a'+p);puts("");
	}
	else{
		int x=t[p]/(n-t[p]+1);
		int b=t[p]%(n-t[p]+1),a=n-t[p]+1-b,c=0;
		for(int i=1,lst=-1;i<=n-t[p];i++){
			int q=-1;for(int j=0;j<26;j++)if(t[j]&&(q==-1||t[j]>t[q])&&j!=lst&&j!=p)q=j;
			if(q==-1)q=lst;
			t[q]--;lst=q;
			ans[i]='a'+q;
		}
		int ed=n-t[p];
		for(int i=1;i<n-t[p];i++)if(ans[i]==ans[i+1]){ed=i;break;}
		if(!(x&1)){
			a--;
			int d=max(0ll,(a-ed+1)/2);
			a-=2*d,b+=d,c+=d;
			for(int i=1;i<=n-t[p];i++){
				if(a){
					for(int j=1;j<=x;j++)putchar('a'+p);
					a--;
				}else if(b){
					for(int j=1;j<=x+1;j++)putchar('a'+p);
					b--;
				}else if(c){
					for(int j=1;j<=x-1;j++)putchar('a'+p);
					c--;
				}
				putchar(ans[i]);
			}
			for(int j=1;j<=x;j++)putchar('a'+p);
		}else if(a==n-t[p]+1){
			for(int i=1;i<=n-t[p];i++){
				for(int j=1;j<=x;j++)putchar('a'+p);
				putchar(ans[i]);
			}
			for(int j=1;j<=x;j++)putchar('a'+p);
		}else{
			b--;
			int d=max(0ll,(b-ed+1)/2);
			b-=2*d,a+=d,c+=d;
			for(int i=1;i<=n-t[p];i++){
				if(b){
					for(int j=1;j<=x+1;j++)putchar('a'+p);
					b--;
				}else if(a){
					for(int j=1;j<=x;j++)putchar('a'+p);
					a--;
				}else if(c){
					for(int j=1;j<=x+2;j++)putchar('a'+p);
					c--;
				}
				putchar(ans[i]);
			}
			for(int j=1;j<=x+1;j++)putchar('a'+p);
		}
		puts("");
	}
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