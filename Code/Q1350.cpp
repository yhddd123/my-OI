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
const int maxn=100010;
const int inf=1e18;
bool mbe;

int n,m,k,q;
char s[maxn],t[maxn];
int len[61];
int f[61][maxn];
char ans[maxn*5];int tp;
void work(){
	scanf("%s%s",s+1,t+1);n=strlen(s+1),m=strlen(t+1);k=read();q=read();
	int num=0;for(int i=1;i<=m;i++)num+=t[i]=='$';
	int pl=0;for(int i=1;i<=m;i++){
		if(t[i]=='$')break;
		pl=i;
	}
	if(num==1){
		auto que=[&](int p){
			int d=min(k,!pl?inf:((p-1)/pl));
			if(d<k)return t[p-d*pl];
			p-=d*pl;
			if(p<=n)return s[p];
			p-=n;
			d=min(k,(p-1)/(m-pl-1));
			return t[pl+1+p-d*(m-pl-1)];
		};
		while(q--){
			int l=read(),r=read();
			for(int i=l;i<=r;i++)printf("%c",que(i));puts("");
		}
	}
	else{
		len[0]=n;int kk=k;
		for(int i=1;i<=k;i++){
			if(len[i-1]>=inf/num)len[i]=inf;
			else len[i]=min(inf,num*len[i-1]+m-num);
			if(len[i]==inf){kk=i;break;}
		}
		for(int i=1;i<=kk;i++){
			int s=0;for(int j=1;j<=m;j++){
				if(t[j]=='$')s+=len[i-1];
				else s++;
				s=min(s,inf);
				f[i][j]=s;
			}
		}
		// cout<<k<<" "<<len[k]<<"\n";
		while(q--){
			int l=read(),r=read();
			tp=0;while(l<=(k-kk)*pl){
				ans[++tp]=t[(l-1)%pl+1];l++;
				if(l>r)break;
			}
			if(l<=r){
				int cnt=r-l+1;
				auto que=[&](auto &&self,int d,int p){
					if(!d){
						int pp=max(1ll,p);
						while(pp<=n&&tp<cnt)ans[++tp]=s[pp++];
						return ;
					}
					int pp=lower_bound(f[d]+1,f[d]+m+1,p)-f[d];
					while(pp<=m&&tp<cnt){
						if(t[pp]=='$')self(self,d-1,p-f[d][pp-1]);
						else ans[++tp]=t[pp];
						// cout<<d<<" "<<pp<<" "<<tp<<"\n";
						pp++;
					}
					return ;
				};
				que(que,kk,l-(k-kk)*pl);
			}
			for(int i=1;i<=tp;i++)printf("%c",ans[i]);puts("");
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