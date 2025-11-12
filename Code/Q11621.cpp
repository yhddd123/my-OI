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
int ask(int p){
	p%=n;
	cout<<p<<endl;
	char s[10];scanf("%s",s);
	if(s[0]=='M')return 0;
	if(s[0]=='F')return 1;
	if(s[0]=='V')exit(0);
}
void work(){
	n=read();
	int v1=ask(0),v2=ask(n/2);
	// cout<<(v1^v2)<<" "<<n/2<<"\n";
	if((v1^v2)!=((n/2)&1)){
		int l=1,r=n/2-1;
		while(l<=r){
			int mid=l+r>>1;
			int v=ask(mid);
			if((v^v1)!=(mid&1))r=mid-1;
			else l=mid+1;
		}
	}
	else{
		int l=n/2+1,r=n-1;
		while(l<=r){
			int mid=l+r>>1;
			int v=ask(mid);
			if((v^v2)!=((mid-n/2)&1))r=mid-1;
			else l=mid+1;
		}
	}
}

bool med;
int T;
signed main(){
	// freopen(".in","r",stdin);
	// freopen(".out","w",stdout);
	
	// cerr<<(&mbe-&med)/1024.0/1024.0<<"\n";
	
	T=1;
	while(T--)work();
}