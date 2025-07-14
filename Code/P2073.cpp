#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int maxn=1000010;
const int inf=1e18;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+(c^48),c=getchar();}
	return x*f;
}

int opt,x,y,ans,ans1;
struct nd{
	int w,c;
	bool operator <(const nd &tmp)const{return c<tmp.c;};
}t;
set<nd> s;
signed main(){
	while(opt=read()){
		set<nd>::iterator it;
		if(opt==-1){
			for(it=s.begin();it!=s.end();it++){
				ans+=(*it).w;
				ans1+=(*it).c;
			}
			printf("%lld %lld",ans,ans1);
			return 0;
		}
		if(opt==1){
			x=read();y=read();
			t={x,y};
			s.insert(t);
		}
		if(opt==2){
			if(s.size())s.erase(--s.end());
		}
		if(opt==3){
			if(s.size())s.erase(s.begin());
		}
	}
}

