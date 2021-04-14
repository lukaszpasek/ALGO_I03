#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<map>
using namespace std;
typedef long long ll;
ll INF=999999999999999999;
struct point
{
   ll x;
   ll y;
   ll z;
   short int color=0;
};
point base;
  map<ll,vector<ll> > mapa;
   vector<point> G;
     vector<point> T;
bool answer=true;
bool operator <(point a,point b)
{

    a.x-=base.x;
    a.y-=base.y;
    b.x-=base.x;
    b.y-=base.y;
    a.z-=base.z;
    b.z-=base.z;
    if(a.x==0 && a.y==0 && a.z==0) return true;
      if(b.x==0 && b.y==0 && b.z==0) return false;
    if((a.y*b.z-a.z*b.y + (a.z*b.x-a.x*b.z)+a.x*b.y-a.y*b.x)==0)
    {
        if(a.x!=b.x)return a.x<b.x;
        if(a.y!=b.y)return a.y<b.y;
        return a.z<b.z;
    }
    return (a.y*b.z-a.z*b.y + (a.z*b.x-a.x*b.z)+a.x*b.y-a.y*b.x)>0;
}
bool det(point a,point b,point helper,point c)
{
    c.x-=helper.x;
    c.y-=helper.y;
    c.z-=helper.z;
    point w;
   // w.x=a.y*b.z-a.z*b.y;
   // w.y=a.z*b.x-a.x*b.z;
   // w.z=a.x*b.y-a.y*b.x;
   w = {b.x-a.x,b.y-a.y,b.z-a.z};
    point result;
    result.x=w.y*c.z-w.z*c.y;
    result.y=w.z*c.x-w.x*c.z;
    result.z=w.x*c.y-w.y*c.x;
   // cout<<result.x<<" "<<result.y<<" "<<result.z<<endl;
   // cout<<"DET "<<(result.x+result.y+result.z)<<endl;
    return (result.x+result.y+result.z)>=0;
}
ll dist(point a,point b)
{

    return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y)+(b.z-a.z)*(b.z-a.z));
}
void DFS(int n,int dad)
{
    /* cout<<"U.x "<<T[n].x<<" U.y "<<T[n].y<<" U.z "<<T[n].z<<endl;
       cout<<"color "<<T[n].color<<endl;*/
   for(int i=0 ; i<mapa[n].size() ; i++)
   {
       int u=mapa[n][i];
       if(T[u].color+T[n].color==2 && u!=dad) answer=false;
       if(T[u].color==0) {T[u].color=-T[n].color;DFS(u,n);}
   }
}
int main()
{

    ll z;
    cin>>z;
    while(z--)
    {
        ll n;
        cin>>n;
        T.resize(n);
        base.x=INF;
        base.y=INF;
        base.z=INF;
        for(ll i=0 ; i<n ; i++)
        {
         cin>>T[i].x>>T[i].y>>T[i].z;
         if(T[i].x<base.x || (T[i].x==base.x && T[i].y<base.y) || (T[i].x==base.x &&  T[i].y==base.y && T[i].z<base.z))
         {
             base.x=T[i].x;
             base.y=T[i].y;
             base.z=T[i].z;
         }
        }
        sort(T.begin(),T.end());
       /*    cout<<"ORDER "<<endl;
        for(int i=0 ; i<n ; i++)
        {
            cout<<i<<": ";
            cout<<T[i].x<<" "<<T[i].y<<" "<<T[i].z<<endl;
        } */
        vector<point> result;
        result.push_back(T[0]);
        if(n==1) {cout<<"NIE"<<endl;continue;}

        result.push_back(T[1]);
        ll wsk=1;
        point a,b;
           //  cout<<"BASE.x "<<base.x<<" BASE.y "<<base.y<<" BASE.z "<<base.z<<endl;
        for(ll i=2 ; i<n ; i++)
        {
           a=result[wsk];
           b=result[wsk-1];
           while(det(a,b,a,T[i]) && wsk>=1)
           {
               wsk--;
               result.pop_back();
               if(wsk>=1)
               {
                     a=result[wsk];
                     b=result[wsk-1];
               }
               else break;
           }
           wsk++;
           result.push_back(T[i]);
        }

         //cout<<"RIM"<<endl;
      //  for(ll i=0 ; i<result.size() ; i++) cout<<result[i].x<<" "<<result[i].y<<" "<<result[i].z<<endl;
       ll s=result.size();
       if(s==1) {cout<<"NIE"<<endl;continue;}
       ll a1=0,a2=1;
       ll b1=1,b2=2%s;
       a=result[0];
       b=result[1];
       ll maxi=0;
       do
       {
         while(b2!=a2 && det(a,b,result[b1],result[b2])) {b1=(++b1)%s;b2=(++b2)%s;}
         if(b2==a2)
         {
         a2=(++a2)%s;
         a1=(++a1)%s;
         continue;
         }
         ll maxib=maxi;
         maxi=max(maxi,dist(a,result [b1]));
         if(maxi==dist(a,result [b1]) )
         {
             if(dist(a,result [b1])>maxib) {G.clear();mapa.clear();}
           //  G.push_back(a);
            //  G.push_back(result [b1]);
              mapa[a1].push_back(b1);
              mapa[b1].push_back(a1);
         }
         maxib=maxi;
         maxi=max(maxi,dist(a,result [b2]));
          if(maxi==dist(a,result [b2]))
         {
               if(dist(a,result [b2])>maxib)  {G.clear();mapa.clear();}
            // G.push_back(a);
             // G.push_back(result [b2]);
                    mapa[a1].push_back(b2);
              mapa[b2].push_back(a1);
         }
         maxib=maxi;
         maxi=max(maxi,dist(b,result [b1]) );
          if(maxi==dist(b,result [b1]))
         {
               if(dist(b,result[b1])>maxib )  {G.clear();mapa.clear();}
           //  G.push_back(b);
             // G.push_back(result [b1]);
                 mapa[a2].push_back(b1);
              mapa[b1].push_back(a2);
         }
         maxib=maxi;
         maxi=max(maxi,dist(b,result [b2]));
          if(maxi==dist(b,result [b2]) )
         {
               if(dist(b,result [b2])>maxib)  {G.clear();mapa.clear();}
           //  G.push_back(b);
            //  G.push_back(result [b2]);
                    mapa[a2].push_back(b2);
              mapa[b2].push_back(a2);
         }
         a2=(++a2)%s;
         a1=(++a1)%s;
         a=result[a1];
       b=result[a2];
       }while(a2!=1);
      // cout<<"SR"<<endl;
      // for(int i=0 ; i<G.size() ; i++) cout<<G[i].x<<" "<<G[i].y<<" "<<G[i].z<<endl;
       T[0].color=1;
       DFS(0,0);
       if(answer)cout<<"TAK"<<endl;
       else cout<<"NIE"<<endl;
       answer=true;
       T.clear();
       mapa.clear();
    }

    return 0;
}