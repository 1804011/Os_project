#include<bits/stdc++.h>
#define f(i,n) for(i=0;i<n;i++)
#define pb push_back
#define pf push_front
using namespace std;
typedef long long ll;
void roundRobin();
void prioritySchedeuling();
void preemptiveSJF();
void preemptivePriority();
void FCFS();
void SJF();
struct process{
    ll arrival,burst,idx;
};
bool fcfs(process x,process y){
     if(x.arrival<y.arrival){
        return 1;
     }
     if(x.arrival==y.arrival){
        return x.idx<y.idx;
     }
     return 0;
}
struct job{
    ll arrival,burst,priority,idx;
};
bool operator<(job x,job y){
    if(x.priority>y.priority)
        return 1;
    if(x.priority==y.priority){
         if(x.arrival>y.arrival)
            return 1;
         if(x.arrival==y.arrival)
            return x.idx>y.idx;
         return 0;
    }
    return 0;
}
bool comp(job x,job y){
    if(x.arrival<y.arrival)
         return 1;
        else if(x.arrival==y.arrival)
              return x.idx<y.idx;
    else return 0;
}
void makeChoice(){
     ll choice;
     cout<<"1: FCFS\n2: Non-Preemptive-SJF\n3: Preemptive-SJF\n4: Non-Preemptive-Priority\n5: Preemptive-Priority\n6: Round-Robin\n7: Our-Proposed-Algorithm\n8: Compare-All\n9: Exit"<<endl;
   cout<<"Enter Your Choice: ";cin>>choice;
   switch(choice){
   case 1:
        FCFS();
        break;
   case 2:
        SJF();
        break;
      case 3:
        preemptiveSJF();
        break;
      case 4:
         prioritySchedeuling();
      case 5:
        preemptivePriority();
        break;
           case 6:
          roundRobin();
        break;
           case 7:
        cout<<"fcfs"<<endl;
        break;
           case 8:
        cout<<"fcfs"<<endl;
        break;
           case 9:
         exit(0);
        break;

   }
   char ch;
   cout<<"Press any key for the home page\n";
   cin>>ch;
   makeChoice();


}
int main(){
     makeChoice();
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
void prioritySchedeuling(){
    vector<job>vct;
priority_queue<job>Q;
ll i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
     cout<<"Enter the number of processes: ";cin>>n;
        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;
            cout<<"Enter the Priority  of P"<<i+1<<": ";cin>>w;
            vct.pb({u,v,w,i});
            arrival[i]=u;
            burst[i]=v;


        }
      sort(vct.begin(),vct.end(),comp);
     cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
      while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
             }

             if(flag==0&&t){
                cout<<0<<" idle ";
                idle+=t;
             }
             else if(t)
                {cout<<"idle "<<t<<" ";
                idle+=t-current;
                }
                current=t;
            while(!Q.empty()){
                job u=Q.top();
                Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    current+=u.burst;

                }
                finish[u.idx]=current;
                for(i=taken+1;i<n;i++){
                    if(vct[i].arrival<=current){
                        Q.push(vct[i]);
                        taken++;
                    }
                }
            }


      }
      cout<<endl;
      cout<<"================================================================================================"<<endl;
      float totalWaiting=0,totalTurnaround=0;
      cout<<endl;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
           cout<<"Process P"<<i+1<<": End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void FCFS(){
    ll n,i,j,u,v;
    vector<process>vct;
ll arrival[500],burst[600],waiting[500],turnaround[500],finish[500],flag=0,current=0,idle=0;
float totalWaiting=0,totalTurnaround=0;
    cout<<"Enter the number of processes: ";cin>>n;
    for(i=0;i<n;i++){
         cout<<"Enter arrival time of P"<<i+1<<": ";cin>>u;
         cout<<"Enter burst time of P"<<i+1<<": ";cin>>v;
         vct.pb({u,v,i});
         arrival[i]=u;
         burst[i]=v;


    }
    sort(vct.begin(),vct.end(),fcfs);
    cout<<endl<<"Gantt Chart"<<endl<<"==========================================================================================="<<endl;
    f(i,n){
       if(vct[i].arrival>current){
            idle+=vct[i].arrival-current;
            if(flag==0){
                flag=1;
                cout<<current<<" idle "<<vct[i].arrival<<" ";
            }
            else {
                cout<<"idle "<<vct[i].arrival<<" ";
            }
           cout<<"P"<<vct[i].idx+1<<" "<<vct[i].arrival+vct[i].burst<<" ";
            current=vct[i].arrival+vct[i].burst;
            finish[vct[i].idx]=current;
       }
       else {
            if(flag==0){
                flag=1;
                cout<<current<<" P"<<vct[i].idx+1<<" "<<current+vct[i].burst<<" ";
                current+=vct[i].burst;

            }
            else {
                cout<<"P"<<vct[i].idx+1<<" "<<current+vct[i].burst<<" ";
                current+=vct[i].burst;
            }
            finish[vct[i].idx]=current;
       }
    }
    cout<<endl<<"==========================================================================================="<<endl;
    cout<<endl;
    f(i,n){
        turnaround[i]=finish[i]-arrival[i];
        waiting[i]=turnaround[i]-burst[i];
        cout<<"Process P"<<i+1<<" End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;
        totalWaiting+=waiting[i];
        totalTurnaround+=turnaround[i];

    }
    cout<<"Average Waiting Time: "<<totalWaiting/n<<endl;
    cout<<"Average Turnaround Time: "<<totalTurnaround/n<<endl;
    cout<<"Idle Time: "<<idle<<endl;
    cout<<endl;
}
void preemptivePriority(){
    ll i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
    vector<job>vct;
             cout<<"Enter the number of processes: ";cin>>n;
        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;
            cout<<"Enter the Priority of P"<<i+1<<": ";cin>>w;
            vct.pb({u,v,w,i});
            arrival[i]=u;
            burst[i]=v;

         }
         sort(vct.begin(),vct.end(),comp);
              cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
     priority_queue<job>Q;
     while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
                else break;
             }

             if(flag==0&&t){
                cout<<0<<" idle ";
                idle+=t;
             }
             else if(t)
                {cout<<"idle "<<t<<" ";
                idle+=t-current;
                }
                current=t;
           while(!Q.empty()){
               job u=Q.top();
               if(taken<n-1){
                 ll tq=vct[taken+1].arrival-current;
                 ll mn=min(tq,u.burst);

                        if(flag==0){
                            cout<<current<<" P"<<u.idx+1<<" "<<current+mn<<" ";
                            flag=1;
                        }
                        else {
                            cout<<"P"<<u.idx+1<<" "<<current+mn<<" ";
                        }
                        current+=mn;
                        u.burst-=mn;
                        Q.pop();
                        for(i=taken+1;i<n;i++){
                            if(vct[i].arrival<=current){
                                Q.push(vct[i]);
                                taken++;
                            }
                        }
                        if(u.burst)
                             Q.push(u);
                       else finish[u.idx]=current;


                  }
               else {
                  Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    current+=u.burst;

                }
                finish[u.idx]=current;
                for(i=taken+1;i<n;i++){
                    if(vct[i].arrival<=current){
                        Q.push(vct[i]);
                        taken++;
                    }
                }

               }

           }


     }
     cout<<endl;
      cout<<"================================================================================================"<<endl;
            float totalWaiting=0,totalTurnaround=0;
      cout<<endl;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
           cout<<"Process P"<<i+1<<": End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void SJF(){
    ll i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
    vector<job>vct;
priority_queue<job>Q;
            cout<<"Enter the number of processes: ";cin>>n;
        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;
            vct.pb({u,v,v,i});
            arrival[i]=u;
            burst[i]=v;


        }
      sort(vct.begin(),vct.end(),comp);
     cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
      while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
             }

             if(flag==0&&t){
                cout<<0<<" idle ";
                idle+=t;
             }
             else if(t)
                {cout<<"idle "<<t<<" ";
                idle+=t-current;
                }
                current=t;



            while(!Q.empty()){
                job u=Q.top();
                Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    current+=u.burst;

                }
                finish[u.idx]=current;
                for(i=taken+1;i<n;i++){
                    if(vct[i].arrival<=current){
                        Q.push(vct[i]);
                        taken++;
                    }
                }
            }


      }
      cout<<endl;
      cout<<"================================================================================================"<<endl;
      float totalWaiting=0,totalTurnaround=0;
      cout<<endl;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
           cout<<"Process P"<<i+1<<": End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
void preemptiveSJF(){
    ll i,u,v,w,n,taken=-1,current=0,finish[500],arrival[500],burst[500],turnaround[500],waiting[500],flag=0;
    vector<job>vct;
             cout<<"Enter the number of processes: ";cin>>n;

        f(i,n){
            cout<<"Enter the Arrival Time of P"<<i+1<<": ";cin>>u;
            cout<<"Enter the Burst Time of P"<<i+1<<": ";cin>>v;

            vct.pb({u,v,v,i});
            arrival[i]=u;
            burst[i]=v;

         }
         sort(vct.begin(),vct.end(),comp);
              cout<<"================================================================================================"<<endl;
     cout<<"Gantt chart"<<endl;
     ll idle=0;
     priority_queue<job>Q;
     while(taken<n-1){
             taken++;
             Q.push(vct[taken]);
             ll t=vct[taken].arrival;
             for(i=taken+1;i<n;i++){
                if(vct[i].arrival==t){
                    Q.push(vct[i]);
                    taken++;
                }
                else break;
             }

             if(flag==0&&t){
                cout<<0<<" idle ";
                idle+=t;
             }
             else if(t)
                {cout<<"idle "<<t<<" ";
                idle+=t-current;
                }
                current=t;
           while(!Q.empty()){
               job u=Q.top();
               if(taken<n-1){
                 ll tq=vct[taken+1].arrival-current;
                 ll mn=min(tq,u.burst);

                        if(flag==0){
                            cout<<current<<" P"<<u.idx+1<<" "<<current+mn<<" ";
                            flag=1;
                        }
                        else {
                            cout<<"P"<<u.idx+1<<" "<<current+mn<<" ";
                        }
                        current+=mn;
                        u.burst-=mn;
                        Q.pop();
                        for(i=taken+1;i<n;i++){
                            if(vct[i].arrival<=current){
                                Q.push(vct[i]);
                                taken++;
                            }
                        }
                        if(u.burst)
                             Q.push(u);
                       else finish[u.idx]=current;


                  }
               else {
                  Q.pop();
                if(flag==0){
                    cout<<current<<" P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    flag=1;
                    current+=u.burst;
                }
                else {
                    cout<<"P"<<u.idx+1<<" "<<current+u.burst<<" ";
                    current+=u.burst;

                }
                finish[u.idx]=current;
                for(i=taken+1;i<n;i++){
                    if(vct[i].arrival<=current){
                        Q.push(vct[i]);
                        taken++;
                    }
                }

               }

           }


     }
     cout<<endl;
      cout<<"================================================================================================"<<endl;
            float totalWaiting=0,totalTurnaround=0;
      cout<<endl;
      f(i,n){
           turnaround[i]=finish[i]-arrival[i];
           waiting[i]=turnaround[i]-burst[i];
           totalTurnaround+=turnaround[i];
           totalWaiting+=waiting[i];
           cout<<"Process P"<<i+1<<": End Time: "<<finish[i]<<" Turnaround Time: "<<turnaround[i]<<" Waiting Time: "<<waiting[i]<<endl;

      }
      cout<<"Average waiting time: "<<totalWaiting/n<<endl;
      cout<<"Average turnaround time: "<<totalTurnaround/n<<endl;
      cout<<"Idle Time: "<<idle<<endl;
       cout<<"================================================================================================"<<endl;
}
