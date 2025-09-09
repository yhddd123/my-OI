#include<bits/stdc++.h>
#define int long long
#define lll unsigned __int128
#define mod 998244353ll
using namespace std;
inline int read(){
	int x=0,fl=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fl=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch-'0');ch=getchar();}
	return x*fl;
}
inline lll read128(){
	lll x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
	return x;
}
const int maxn=500010;
const int maxk=110;
const int B=8;
const int C=maxk/B+2;
bool mbe;

int n,k,q1,q2,res;
unsigned __int128 x, y, z, w;
unsigned __int128 get_number() {
    unsigned __int128 t = x ^ (x << 11);
    x = y; y = z; z = w;
    return w = w ^ (w >> 19) ^ t ^ (t >> 8);
}
int a[maxn],b[maxn],m;
int nxt[maxn];
vector<int> pos[maxk];
int val[maxk][maxk];
int popc(lll s){
	return __builtin_popcountll(s>>64)+__builtin_popcountll(s);
}
int v1[C][1<<B],v2[C][C][1<<B][1<<B],ss[C][1<<B],tmp[B],ids[C];
lll S;
int calc(lll s){
    int sz=popc(s);
    if(!sz)return 0;
    if(sz==1)return 1;
    int sum=0,d=0;
    for(int i=0;i*B<k;i++)ids[i]=(s>>(i*B))&((1<<B)-1);
    for(int i=0;i*B<k;i++)sum+=ss[i][ids[i]];
    for(int i=0;i*B<k;i++)d=__gcd(d,v1[i][ids[i]]);
    for(int i=0;i*B<k;i++){
    	for(int j=i+1;j*B<k;j++)d=__gcd(d,v2[i][j][ids[i]][ids[j]]);
    }
    // cout<<(int)s<<" "<<sum<<" "<<d<<" "<<sum/d<<"\n";
    return sum/d;
}
void work(){
	n=read();k=read();q1=read();q2=read();
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]].push_back(i);
	for(int i=0;i<k;i++)if(pos[i].size())S|=(lll)1<<i;
    for(int i=0;i<k;i++)if(pos[i].size()){
    	val[i][i]=pos[i].size();
        for(int j=i+1;j<k;j++)if(pos[j].size()){
            m=0;int p=0,q=0;
            while(p<pos[i].size()&&q<pos[j].size()){
                if(pos[i][p]<pos[j][q])b[++m]=i,p++;
                else b[++m]=j,q++;
            }
            while(p<pos[i].size())b[++m]=i,p++;
            while(q<pos[j].size())b[++m]=j,q++;
            for(int i=2,j=0;i<=m;i++){
                while(j&&b[i]!=b[j+1])j=nxt[j];
                if(b[i]==b[j+1])j++;
                nxt[i]=j;
            }
            int ans=m;for(int i=nxt[m];i;i=nxt[i])if(m%(m-i)==0){ans=m-i;break;}
            val[i][j]=val[j][i]=m/ans;
        }
    }
    for(int i=0;i*B<k;i++){
    	for(int s=0;s<(1<<B);s++){
    		for(int j=0;j<B;j++)if((s&(1<<j))&&pos[i*B+j].size()){
    			ss[i][s]+=pos[i*B+j].size();
    			for(int k=j;k<B;k++)if((s&(1<<k))&&pos[i*B+k].size())v1[i][s]=__gcd(v1[i][s],val[i*B+j][i*B+k]);
    		}
    	}
    }
    for(int i=0;i*B<k;i++){
    	for(int j=i+1;j*B<k;j++){
    		for(int s1=1;s1<(1<<B);s1++)if(ss[i][s1]){
    			for(int q=0;q<B;q++)tmp[q]=0;
    			for(int p=0;p<B;p++)if(s1&(1<<p)){
    				for(int q=0;q<B;q++)tmp[q]=__gcd(tmp[q],val[i*B+p][j*B+q]);
    			}
    			for(int s2=1;s2<(1<<B);s2++)if(ss[j][s2]){
    				int q=__lg(s2&(-s2));
    				v2[i][j][s1][s2]=__gcd(v2[i][j][s1][s2^(1<<q)],tmp[q]);
    			}
    		}
    	}
    }
    // for(int i=0;i<k;i++){
    	// for(int j=0;j<k;j++)cout<<val[i][j]<<" ";cout<<"\n";
    // }
	int mul=1;
	while(q1--){
		lll s=read128()&S;
		(res+=calc(s)*mul)%=mod;
		mul=mul*n%mod;
	}
	x=read128(),y=read128(),z=read128(),w=read128();
	while(q2--){
		lll s=get_number()&S;
		(res+=calc(s)*mul)%=mod;
		mul=mul*n%mod;
	}
	printf("%lld\n",res);
}

bool med;
int T;
signed main(){
	T=1;
	while(T--)work();
}