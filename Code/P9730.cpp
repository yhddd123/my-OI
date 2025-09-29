#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
	ll x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*fl;
}
const int maxn=200010;
const ll inf=1e18;
bool mbe;

ll s,q;
struct node{
	ll b1,a2,b2;
};
inline bool operator==(const node &u,const node &v){return u.b1==v.b1&&u.a2==v.a2&&u.b2==v.b2;}
struct hsh{
	inline int operator()(const node &u)const{
		return (u.b1 * 666667ll + u.a2 * 10007ll + u.b2) % 1000000007ll;
	}
};
unordered_map<node,int,hsh> mp;
inline bool sovle(ll a1,ll b1,ll a2,ll b2){
	if(a1+b1*s<=0)return 0;
	if(a2>=s){
		if(a1<=0)return 0;
		return !sovle(a2-a1,b2,a1,b1);
	}
	if(a1>=s&&a2<=s)return 1;
	ll s_a1 = s - a1;
	ll s_a2 = s - a2;
	if(a1<=0){
		if(a2<=0){
			ll k=max(1ll,min({b1,b2,(-a1)/s,(-a2)/s}));
			return sovle(a1+k*s,b1-k,a2+k*s,b2-k);
		}
		return !sovle(a2,b2,a1+s,b1-1);
	}
	if(a2<=0){
		if(b1)return !sovle(a2,b2,a1+s,b1-1);
		ll k=(-a2)/s_a1+1;
		if(k>b2)return 1;
		return sovle(a1,b1,a2+k*s_a1,b2-k);
	}
	if(a1+b1*s_a2>=s)return 1;
	if(!b1)return !sovle(a2-a1,b2,a1,b1);
	if(a2-a1+b2*s_a1>=s){
		ll k=max(1ll,min(b1,(a2-a1+b2*s-b2*a1-s)/((b2+1)*s_a1)));
		return sovle(a1+k*s_a2,b1-k,a2,b2);
	}
	if(b1>=8*s||b1*b1>=8*s||b1*b1*(b2+1)>=8*s||b1*b1*(b2+1)*s_a2>=8*s)return 1;
	if(mp.find({b1,a2,b2})!=mp.end())return mp[{b1,a2,b2}]<=a1;
	int l=0,r=s-1,res=1e9;
	while(l<=r){
		int mid=l+r>>1;
		if(!sovle(a2-mid,b2,mid,b1)||!sovle(a2,b2,mid+s,b1-1))res=mid,r=mid-1;
		else l=mid+1;
	}
	mp[{b1,a2,b2}]=res;
	return mp[{b1,a2,b2}]<=a1;
}
void work(){
	s=read();q=read();
	while(q--){
		ll c1=read(),f1=read(),c2=read(),f2=read();
		puts(sovle(c1-f2*s,f2,c2-f1*s,f1)?"YES":"NO");
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