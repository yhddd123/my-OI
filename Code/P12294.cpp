#include<bits/stdc++.h>
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
const int inf=1e9;
bool mbe;

int n,q,op[8];
char s[maxn];
struct automation{
	int to;
	int f[110][110][6];
	bool check(int n,int s){
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				for(int o=0;o<6;o++)f[i][j][o]=0;
			}
		}
		for(int i=1;i<=n;i++)f[i][i][(s>>i-1)&1]=1;
		for(int len=2;len<=n;len++){
			for(int i=1,j=len;j<=n;i++,j++){
				for(int k=i;k<j;k++){
					for(int o1=0;o1<6;o1++)if(f[i][k][o1]){
						for(int o2=0;o2<6;o2++)if(f[k+1][j][o2]){
							if(o1<2&&o2<2)f[i][j][(o1|(o2<<1))+2]=1;
							else if(o1<2)f[i][j][op[o1|((o2-2)<<1)]]=1;
							else if(o2<2)f[i][j][op[(o1-2)|(o2<<2)]]=1;
							else{
								f[i][j][(((o1-2)&1)|(op[((o1-2)>>1)|((o2-2)<<1)]<<1))+2]=1;
								f[i][j][(op[(o1-2)|(((o2-2)&1)<<2)]|((o2-2)&2))+2]=1;
							}
						}
					}
				}
			}
		}
		// cout<<n<<" "<<s<<" "<<f[1][n][to]<<"\n";
		return f[1][n][to];
	}
	struct node{
		int len,sta;
		int son[2];
		bool ok;
		__int128 nxt;
	}dfa[55];int idx;
	node init(int l,int s){
		node res; 
		res.len=l,res.sta=s;
		res.son[0]=res.son[1]=0;
		res.ok=check(l,s);
		res.nxt=0;
		for(int i=0,cnt=0;i<=6;i++){
			for(int t=0;t<(1<<i);t++){
				if(check(l+i,s|(t<<l)))res.nxt|=(__int128)1<<cnt;
				cnt++;
			}
		}
		return res;
	}
	void init(int _to){
		to=_to;
		dfa[idx=0]=init(0,0);
		for(int id=0;id<=idx;id++){
			for(int c=0;c<2;c++){
				int l=dfa[id].len+1,s=dfa[id].sta|(c<<l-1);
				node nw=init(l,s);
				int p=-1;for(int j=0;j<=idx;j++)if(nw.nxt==dfa[j].nxt)p=j;
				if(p==-1)dfa[++idx]=nw,p=idx;
				dfa[id].son[c]=p;
			}
			// cout<<dfa[id].len<<" "<<dfa[id].sta<<" "<<dfa[id].son[0]<<" "<<dfa[id].son[1]<<" a\n";
		}
		// cout<<idx<<"\n";
	}
}a[6];
struct sgt{
	#define mid ((l+r)>>1)
	#define ls nd<<1
	#define rs nd<<1|1
	int tree[maxn<<2][55];
	void build(int nd,int l,int r,int o){
		if(l==r){
			for(int i=0;i<=a[o].idx;i++)tree[nd][i]=a[o].dfa[i].son[s[l]-'0'];
			return ;
		}
		build(ls,l,mid,o),build(rs,mid+1,r,o);
		for(int i=0;i<=a[o].idx;i++)tree[nd][i]=tree[rs][tree[ls][i]];
	}
	void query(int nd,int l,int r,int ql,int qr,int &p){
		if(l>=ql&&r<=qr){
			p=tree[nd][p];
			return ;
		}
		if(ql<=mid)query(ls,l,mid,ql,qr,p);
		if(qr>mid)query(rs,mid+1,r,ql,qr,p);
	}
}t[6];
bool chk(int l,int r,int o){
	int p=0;t[o].query(1,1,n,l,r,p);
	return a[o].dfa[p].ok;
}
void sovle(int l,int r,int o){
	if(l==r){putchar(s[l]);return ;}
	if(o<2){
		putchar('(');
		int pl=l,pr=r;
		while(pl<=pr){
			for(int o1=0;o1<6;o1++){
				for(int o2=0;o2<6;o2++){
					if((o1<2&&o2>=2&&op[o1|((o2-2)<<1)]==o)||(o1>=2&&o2<2&&op[(o1-2)|(o2<<2)]==o)){
						if(chk(l,pl,o1)&&chk(pl+1,r,o2)){
							sovle(l,pl,o1),sovle(pl+1,r,o2);
							putchar(')');
							return ;
						}
					}
				}
			}
			for(int o1=0;o1<6;o1++){
				for(int o2=0;o2<6;o2++){
					if((o1<2&&o2>=2&&op[o1|((o2-2)<<1)]==o)||(o1>=2&&o2<2&&op[(o1-2)|(o2<<2)]==o)){
						if(chk(l,pr-1,o1)&&chk(pr,r,o2)){
							sovle(l,pr-1,o1),sovle(pr,r,o2);
							putchar(')');
							return ;
						}
					}
				}
			}
			pl++,pr--;
		}
	}
	else{
		int o1=(o-2)&1,o2=((o-2)&2)>>1;
		// cerr<<l<<" "<<r<<" "<<o1<<" "<<o2<<"\n";
		int pl=l,pr=r;
		while(pl<=pr){
			if(chk(l,pl,o1)&&chk(pl+1,r,o2)){
				sovle(l,pl,o1),sovle(pl+1,r,o2);
				return ;
			}
			if(chk(l,pr-1,o1)&&chk(pr,r,o2)){
				sovle(l,pr-1,o1),sovle(pr,r,o2);
				return ;
			}
			pl++,pr--;
		}
	}
}
void work(){
	scanf("%s",s);
	for(int i=0;i<8;i++)op[i]=s[i]-'0';
	for(int i=0;i<6;i++)a[i].init(i);
	q=read();
	while(q--){
		scanf("%s",s+1);n=strlen(s+1);
		for(int i=0;i<6;i++)t[i].build(1,1,n,i);
		if(!chk(1,n,1)){puts("-1");continue;}
		sovle(1,n,1);puts("");
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