#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
struct job{
    ll arrival,burst,idx;
};
bool comp(job x,job y){
    if(x.arrival<y.arrival)
         return 1;
        else if(x.arrival==y.arrival)
              return x.idx<y.idx;
    else return 0;
}
void roundRobin(){
    ll n,tc,i,u,v,tq;
ll arrival[500],waiting[500],turnaround[500],burst[500],finish[500];


vector<job>vct;
      cout<<"Enter The number Of Processes: ";cin>>n;
      cout<<"Enter Time Quantum: ";cin>>tq;

      for(i=0;i<n;i++){
        cout<<"Enter Arrival Time of P"<<i+1<<": ";cin>>u;
       cout<<"Enter Burst Time of P"<<i+1<<": ";cin>>v;
       vct.pb({u,v,i});
       arrival[i]=u;
       burst[i]=v;

      }
      sort(vct.begin(),vct.end(),comp);


    //  }
    deque<job>Q;

   // Q.push_front(vct[0]);
   cout<<"=========================================="<<endl;
   cout<<"Gantt Chart"<<endl;
    ll time=vct[0].arrival;
    ll taken=-1;
    ll flag=0;
    ll sz=vct.size();
  while(taken<n-1){
        taken++;
        Q.push_front(vct[taken]);
        time=vct[taken].arrival;
        if(flag==0&&time){
            cout<<0<<" "<<"idle ";
        }
        else if(time)
            cout<<"idle "<<time<<" ";

    while(!Q.empty()){
      job top=Q.front();
      if(top.burst<=tq){
            if(flag==0){
        cout<<time<<" "<<"P"<<top.idx+1<<" "<<time+top.burst<<" ";
        flag=1;
            }
            else {
                cout<<"P"<<top.idx+1<<" "<<time+top.burst<<" ";
            }
           finish[top.idx]=time+top.burst;
          Q.pop_front();
          time+=top.burst;

                 for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=time){
                    taken++;
                    Q.pb(vct[i]);

                }

          }

      }
      else{
        if(flag==0){
            cout<<time<<" "<<"P"<<top.idx+1<<" "<<time+tq<<" ";
            flag=1;
        }
        else {
            cout<<"P"<<top.idx+1<<" "<<time+tq<<" ";
        }
        time+=tq;
        top.burst-=tq;
        Q.pop_front();
               for(i=taken+1;i<sz;i++){
        if(vct[i].arrival<=time){
                    taken++;
                    Q.pb(vct[i]);

                }

          }
          Q.pb(top);



      }




    }
  }
     cout<<"\n=========================================="<<endl;

         for(i=0;i<n;i++){
            cout<<"process P"<<i+1<<" End time: "<<finish[i]<<" Turn around Time: "<<finish[i]-arrival[i]<<" Waiting time: "<<finish[i]-arrival[i]-burst[i]<<endl;
         }
}

