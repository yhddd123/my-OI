#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=200010;
const int inf=1e9;
inline int read(){
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-48);ch=getchar();}
	return x*f;
}

int n,ans,l,r;
struct nd{
	int l,r;
	bool operator <(const nd&tmp)const{return r<tmp.l;} 
};
set<nd> s;
char c;

int T;
signed main(){
	//	freopen(".in","r",stdin);
	//	freopen(".out","w",stdout);
	
	n=read();
	while(n--){
		cin>>c;
		if(c=='A'){
			l=read();r=read();ans=0;
			nd nw={l,r};
			auto it=s.find(nw);
			while(it!=s.end()){
				++ans;
				s.erase(it);
				it=s.find(nw);
			}
			s.insert(nw);
			printf("%lld\n",ans);
		}
		else{
			printf("%lld\n",s.size());
		}
	}
}
