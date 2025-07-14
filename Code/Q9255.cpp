#include<bits/stdc++.h>
#define int long long
#define mod 998244353ll
#define pii pair<int,int>
#define fi first
#define se second
#define mems(x,y) memset(x,y,sizeof(x))
#define pb push_back
using namespace std;
const int maxn=200010;
const int inf=1e18;
char ch;
inline int read(){
	int x=0,f=1;ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}
bool Mbe;

int ans;
char s[maxn];
int a,b,c=1,d,e,f=1;
bool fld,fle;
void work(){
	scanf("%s",s+1);
	a=read(),b=read();
	if(ch==',')c=read();
	ch=getchar();while(ch!='(')ch=getchar();
	ch=getchar();
	if((ch>='0'&&ch<='9')||ch=='-'){
		if(ch=='-')d=-read();
		else{
			while(ch>='0'&&ch<='9'){d=d*10+(ch-48);ch=getchar();}		
		}
	}
	else fld=1;
	while(ch!=',')ch=getchar();
	ch=getchar();
	if((ch>='0'&&ch<='9')||ch=='-'){
		if(ch=='-')e=-read();
		else{
			while(ch>='0'&&ch<='9'){e=e*10+(ch-48);ch=getchar();}		
		}
	}
	else fle=1;
	while(ch!=','&&ch!=')')ch=getchar();
	if(ch==',')f=read();
	// cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<" "<<f<<"\n";
	// cout<<fld<<" "<<fle<<"\n";
	if(fld&&fle){puts("0");return ;}
	if(c>0){
		for(int i=a;i<b;i+=c){
			if(fld)d=i;
			if(fle)e=i;
			if(f>0){
				int len=max(0ll,(e-d+f-1)/f);
				ans+=d*len+len*(len-1)/2*f;
			}
			else{
				f=-f;
				int len=max(0ll,(d-e+f-1)/f);
				ans+=d*len-len*(len-1)/2*f;
				f=-f;
			}
		}
	}
	else{
		for(int i=a;i>b;i+=c){
			if(fld)d=i;
			if(fle)e=i;
			if(f>0){
				int len=max(0ll,(e-d+f-1)/f);
				ans+=d*len+len*(len-1)/2*f;
			}
			else{
				f=-f;
				int len=max(0ll,(d-e+f-1)/f);
				ans+=d*len-len*(len-1)/2*f;
				f=-f;
			}
		}		
	}
	printf("%lld\n",ans);
}

// \
444

bool Med;
int T;
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	
//	ios::sync_with_stdio(0);
//	cin.tie(0);cout.tie(0);
	
//	cerr<<(&Mbe-&Med)/1048576.0<<" MB\n";
	
	T=1;
	while(T--)work();
}
