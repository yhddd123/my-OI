static char buf[1000000],*p1=buf,*p2=buf,obuf[1<<22];
#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
inline int read(){int x=0,f=1;char c=getchar();while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=(x<<3)+(x<<1)+c-48;c=getchar();}return x*f;}
static int opos=0;
inline void flush_out(){fwrite(obuf,1,opos,stdout);opos=0;}
inline void pc(char c){if(opos == (1<<22))flush_out();obuf[opos++]=c;}
inline void write(ll x){static char buf[20];static int len=-1;if(x<0)pc('-'),x=-x;do buf[++len]=x%10,x/=10;while(x);while(len>=0)pc(buf[len--]+48);}