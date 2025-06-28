#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mems(a,x) memset((a),(x),sizeof(a))
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const int inf=2e9;
bool mbe;

int q;
int id[maxn],n;
bool del[maxn];
pii a[maxn][2];
void work(){
	q=read();n=0;
	for(int t=1;t<=q;t++){
		char op[3];scanf("%s",op);
		if(op[0]=='+'){
			id[++n]=t,del[t]=0;
			a[t][0]={read(),read()},a[t][1]={read(),read()};
		}
		else{
			int p=read();del[p]=0;
		}
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