#include<iostream>

static char buf[1000000],*p1=buf,*p2=buf,rev[15],out[55000000];
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline unsigned read(){
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9'){ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x;
}
unsigned Len=-1;
inline void write(unsigned x){
	unsigned len=-1;
	do{
		rev[++len]=(x%10)^0x30;
		x/=10;
	}while(x);
	while(~len)
	{
		out[++Len]=rev[len--];
	}
	out[++Len]=0xa;
}

int n,m;
unsigned a[1000001],b[1000001],c[1000001];
unsigned val[1000001],sum[1000001],idx[1000001];
unsigned ans[5000001],u,v,w,s;
int l[5000001],r[5000001],num[5000001];
int tot[1000001];
unsigned gcd(int a,int b){
	if(a%b==0)return b;
	return gcd(b,a%b);
}
int pos,i,j;

signed main(){
	n=read();m=read();
	for(i=1;i<=n;++i)a[i]=read();
	for(i=1;i<=n;++i)b[i]=read();
	for(i=1;i<=n;++i)c[i]=read();
	for(i=1;i<=m;++i){
		l[i]=read();r[i]=read();
		++tot[r[i]];
	}
	for(i=1;i<=n;i++)tot[i]+=tot[i-1];
	for(i=1;i<=m;i++){
		++tot[r[i]-1];
		num[tot[r[i]-1]]=i;
	}
	j=1;
	for(i=1;i<=n;++i){
		pos=i-1;
		while(pos){
			u=(a[pos]&a[pos+1]);
			v=(b[pos]|b[pos+1]);
			w=gcd(c[pos],c[pos+1]);
			if(u==a[pos]&&v==b[pos]&&w==c[pos])break;
			a[pos]=u;b[pos]=v;c[pos]=w;
			--pos;
		}
		++pos;
		val[i]=val[i-1]+sum[i-1]*(i-1-idx[i-1]);
		while(pos<=i){
			val[pos]=val[pos]+sum[pos]*(i-1-idx[pos]);
			sum[pos]=sum[pos-1]+a[pos]*b[pos]*c[pos];
			idx[pos]=i-1;
			++pos;
		}
		s=val[i]+sum[i];
		while(j<=tot[i-1]){
			ans[num[j]]=s-(val[l[num[j]]-1]+sum[l[num[j]]-1]*(i-idx[l[num[j]]-1]));
			++j;
		}
	}
	for(i=1;i<=m;++i)write(ans[i]);
	fwrite(out,1,Len,stdout);
	return 0;
}
