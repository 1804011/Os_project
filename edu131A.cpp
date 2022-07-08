#include<bits/stdc++.h>
#define f(i,n) for(i=0;i<n;i++)
using namespace std;
typedef long long ll;
int main(){
      ll i,n,tc,u,v,arr[4][4],j;
      cin>>tc;
      while(tc--){
            ll cnt=0;
        f(i,2){
            f(j,2)
            {
                cin>>arr[i][j];
                cnt+=arr[i][j];
            }
        }
        if(cnt==0)
            cout<<0<<endl;
        else if(cnt==1)
            cout<<1<<endl;
        else if(cnt==2)
            cout<<1<<endl;
        else if(cnt==3)
            cout<<1<<endl;
        else cout<<2<<endl;

      }
}
