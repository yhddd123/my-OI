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
const int maxn=10000010;
const int inf=1e9;
bool mbe;

int n;
char s[maxn];
void work(){
	n=read();scanf("%s",s+1);
	int p=0;for(int i=1;i<=n;i++)if(s[i]=='1'){p=i;break;}
	if(!p){puts("0");return ;}
	int q=0;for(int i=p;i<=n;i++)if(s[i]=='0'){q=i;break;}
	if(!q){
		if(p>1){
			for(int i=p;i<=n;i++)putchar('1');
		}
		else{
			for(int i=p;i<n;i++)putchar('1');putchar('0');
		}
		puts("");
		return ;
	}
	int l=0;for(int i=q;i<=n&&s[i]=='0';i++)l++;
	l=min(l,q-p);
	for(int i=p;i<q;i++)putchar('1');
	for(int i=q;i<=n;i++)putchar('0'+((s[i]=='1')^(s[i-l]=='1')));
	puts("");
}

bool med;
int T;
signed main(){
	// freopen("help.in","r",stdin);
	// freopen("help.out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=read();
	while(T--)work();
}