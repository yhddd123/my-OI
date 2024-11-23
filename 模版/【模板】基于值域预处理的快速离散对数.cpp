const int mod=1000000007ll;
int g=5;
inline int ksm(int a,int b=mod-2){
	int ans=1;
	while(b){
		if(b&1)ans=1ll*ans*a%mod;
		a=1ll*a*a%mod;
		b>>=1;
	}
	return ans;
}
const int M=2935019;
namespace fast_bsgs{
	int inc(int u,int v){((u+=v)>=mod-1)&&(u-=mod-1);return u;}
	int B,bas,h0,n;
	struct hsh_table{
		int head[M],tot;
		struct nd{
			int nxt;
			int key;
			int val;
		}e[M];
		int hsh(int u){return u%M;}
		bool find(int key){
			int u=hsh(key);
			for(int i=head[u];i;i=e[i].nxt){
				if(e[i].key==key)return 1;
			}
			return 0;
		}
		int &operator[](int key){
			int u=hsh(key);
			for(int i=head[u];i;i=e[i].nxt){
				if(e[i].key==key)return e[i].val;
			}
			e[++tot]={head[u],key,0};head[u]=tot;
			return e[tot].val;
		}
		void clear(){
			tot=0;
			for(int i=0;i<M;i++)head[i]=0;
		}
	}mp;
	int bsgs(int v){
		int mul=v;
		for(int i=0;i<=mod/B;i++){
			if(mp.find(mul))return i*B+mp[mul];
			mul=1ll*mul*bas%mod;
		}
	}
	/*
	mod=ba+c
	log(a)=log(-c)-log(b)=log(mod-1)+log(c)-log(b)
	log(a)=log(a-c)-log(b+1)
	min(c,a-c)<=a/2
	*/
	int h[maxn];
	int sovle(int a){
		int b=mod/a,c=mod%a;
		if(a<=n)return h[a];
		if(c<a-c)return inc(inc(h0,sovle(c)),(mod-1-h[b]));
		else return inc(sovle(a-c),mod-1-h[b+1]);
	}
	bool vis[maxn];
	int pre[maxn],cnt;
	int a[maxn],b[maxn];
	void init(){
		n=sqrt(mod)+1;B=sqrt(1ll*mod*n/log2(n));
		// cout<<n<<" "<<B<<"\n";
		int mul=1;for(int i=0;i<B;i++){
			mp[mul]=i;
			mul=1ll*mul*g%mod;
		}
		bas=ksm(ksm(g,B));
		h0=bsgs(mod-1);
		h[1]=0;
		for(int i=2;i<=n;i++){
			if(!vis[i]){
				h[i]=bsgs(i);
				pre[++cnt]=i;
			}
			for(int j=1;j<=cnt&&1ll*i*pre[j]<=n;j++){
				vis[i*pre[j]]=0;
				h[i*pre[j]]=(h[i]+h[pre[j]])%(mod-1);
				if(i%pre[j]==0)break;
			}
		}
	}
}
using fast_bsgs::init;
using fast_bsgs::sovle;