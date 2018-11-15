//Round robin

#include <iostream>
#include <vector>


using namespace std;

int main(){
	int i,n,time,remain,temps=0,time_quantum;

	int wt=0,tat=0;

	cout<<"Enter the total number of process="<<endl;
	cin>>n;

	remain=n;

	vector<int>at(n);
	vector<int>bt(n);
	vector<int>rt(n);

	cout<<"Enter the Arrival time, Burst time for All the processes"<<endl;
	for(i=0;i<n;i++)
	{
		cin>>at[i];
		cin>>bt[i];
		rt[i]=bt[i];
	}

	cout<<"Enter the value of time QUANTUM:"<<endl;
	cin>>time_quantum;

	cout<<"\n\nProcess\t:Turnaround Time:Waiting Time\n\n";
	for(time=0,i=0;remain!=0;)
	{
		if(rt[i]<=time_quantum && rt[i]>0)
		{
			time += rt[i];
			rt[i]=0;
			temps=1;
		}

		else if(rt[i]>0)
		{
			rt[i] -= time_quantum;
			time += time_quantum;
		}

		if(rt[i]==0 && temps==1)
		{
			remain--;
			printf("Process{%d}\t:\t%d\t:\t%d\n",i+1,time-at[i],time-at[i]-bt[i]);
			cout<<endl;

			wt += time-at[i]-bt[i];
			tat += time-at[i];
			temps=0;
		}

		if(i == n-1)
			i=0;
		else if(at[i+1] <= time)
			i++;
		else
			i=0;
	}

	cout<<"Average waiting time "<<wt*1.0/n<<endl;
	cout<<"Average turn around time "<<tat*1.0/n<<endl;;

	return 0;
}


/////////////////////////////////////////////////////////////
// FCFS

#include<iostream> 
using namespace std; 
void findWaitingTime(int processes[], int n, int bt[], 
                                   int wt[], int at[]) 
{ 
    int service_time[n]; 
    service_time[0] = 0; 
    wt[0] = 0; 
    for (int i = 1; i < n ; i++) 
    { 
        service_time[i] = service_time[i-1] + bt[i-1]; 
        wt[i] = service_time[i] - at[i]; 
        if (wt[i] < 0) 
            wt[i] = 0; 
    } 
} 
void findTurnAroundTime(int processes[], int n, int bt[], 
                                      int wt[], int tat[]) 
{ 
    for (int i = 0; i < n ; i++) 
        tat[i] = bt[i] + wt[i]; 
} 
void findavgTime(int processes[], int n, int bt[], int at[]) 
{ 
    int wt[n], tat[n]; 
    findWaitingTime(processes, n, bt, wt, at); 
    findTurnAroundTime(processes, n, bt, wt, tat); 
    cout << "Processes " << " Burst Time " << " Arrival Time "
         << " Waiting Time " << " Turn-Around Time "
         << " Completion Time \n"; 
    int total_wt = 0, total_tat = 0; 
    for (int i = 0 ; i < n ; i++) 
    { 
        total_wt = total_wt + wt[i]; 
        total_tat = total_tat + tat[i]; 
        int compl_time = tat[i] + at[i]; 
        cout << " " << i+1 << "\t\t" << bt[i] << "\t\t"
             << at[i] << "\t\t" << wt[i] << "\t\t "
             << tat[i]  <<  "\t\t " << compl_time << endl; 
    } 
  
    cout << "Average waiting time = "
         << (float)total_wt / (float)n; 
    cout << "\nAverage turn around time = "
         << (float)total_tat / (float)n; 
} 
int main() 
{ 
    int processes[] = {1, 2, 3}; 
    int n = sizeof processes / sizeof processes[0]; 
    int burst_time[] = {5, 9, 6}; 
    int arrival_time[] = {0, 3, 6}; 
  
    findavgTime(processes, n, burst_time, arrival_time); 
  
    return 0; 
} 

//////////////////////////////////////////////////////
//SJF

#include <bits/stdc++.h> 
using namespace std; 
  
struct Process { 
    int pid; 
    int bt;  
    int art; 
}; 
void findWaitingTime(Process proc[], int n, 
                                int wt[]) 
{ 
    int rt[n]; 
    for (int i = 0; i < n; i++) 
        rt[i] = proc[i].bt; 
  
    int complete = 0, t = 0, minm = INT_MAX; 
    int shortest = 0, finish_time; 
    bool check = false; 
    while (complete != n) { 
        for (int j = 0; j < n; j++) { 
            if ((proc[j].art <= t) && 
            (rt[j] < minm) && rt[j] > 0) { 
                minm = rt[j]; 
                shortest = j; 
                check = true; 
            } 
        } 
  
        if (check == false) { 
            t++; 
            continue; 
        } 
        rt[shortest]--; 
        minm = rt[shortest]; 
        if (minm == 0) 
            minm = INT_MAX; 
        if (rt[shortest] == 0) { 
            complete++; 
            check = false; 
            finish_time = t + 1; 
            wt[shortest] = finish_time - 
                        proc[shortest].bt - 
                        proc[shortest].art; 
  
            if (wt[shortest] < 0) 
                wt[shortest] = 0; 
        } 
        t++; 
    } 
} 
void findTurnAroundTime(Process proc[], int n, 
                        int wt[], int tat[]) 
{ 
    for (int i = 0; i < n; i++) 
        tat[i] = proc[i].bt + wt[i]; 
} 
void findavgTime(Process proc[], int n) 
{ 
    int wt[n], tat[n], total_wt = 0, 
                    total_tat = 0; 
    findWaitingTime(proc, n, wt); 
    findTurnAroundTime(proc, n, wt, tat); 
    cout << "Processes "
        << " Burst time "
        << " Waiting time "
        << " Turn around time\n"; 
  
    for (int i = 0; i < n; i++) { 
        total_wt = total_wt + wt[i]; 
        total_tat = total_tat + tat[i]; 
        cout << " " << proc[i].pid << "\t\t"
            << proc[i].bt << "\t\t " << wt[i] 
            << "\t\t " << tat[i] << endl; 
    } 
  
    cout << "\nAverage waiting time = "
        << (float)total_wt / (float)n; 
    cout << "\nAverage turn around time = "
        << (float)total_tat / (float)n; 
} 

int main() 
{ 
    Process proc[] = { { 1, 6, 1 }, { 2, 8, 1 }, 
                    { 3, 7, 2 }, { 4, 3, 3 } }; 
    int n = sizeof(proc) / sizeof(proc[0]); 
  
    findavgTime(proc, n); 
    return 0; 
} 

////////////////////////////////////////////////////
//Dining philospher

#include <pthread.h> 
#include <semaphore.h> 
#include <stdio.h> 
  
#define N 5 
#define THINKING 2 
#define HUNGRY 1 
#define EATING 0 
#define LEFT (phnum + 4) % N 
#define RIGHT (phnum + 1) % N 
  
int state[N]; 
int phil[N] = { 0, 1, 2, 3, 4 }; 
  
sem_t mutex; 
sem_t S[N]; 
  
void test(int phnum) 
{ 
    if (state[phnum] == HUNGRY 
        && state[LEFT] != EATING 
        && state[RIGHT] != EATING) { 
        // state that eating 
        state[phnum] = EATING; 
  
        sleep(2); 
  
        printf("Philosopher %d takes fork %d and %d\n", 
                      phnum + 1, LEFT + 1, phnum + 1); 
  
        printf("Philosopher %d is Eating\n", phnum + 1); 
  
        // sem_post(&S[phnum]) has no effect 
        // during takefork 
        // used to wake up hungry philosophers 
        // during putfork 
        sem_post(&S[phnum]); 
    } 
} 
  
// take up chopsticks 
void take_fork(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    // state that hungry 
    state[phnum] = HUNGRY; 
  
    printf("Philosopher %d is Hungry\n", phnum + 1); 
  
    // eat if neighbours are not eating 
    test(phnum); 
  
    sem_post(&mutex); 
  
    // if unable to eat wait to be signalled 
    sem_wait(&S[phnum]); 
  
    sleep(1); 
} 
  
// put down chopsticks 
void put_fork(int phnum) 
{ 
  
    sem_wait(&mutex); 
  
    // state that thinking 
    state[phnum] = THINKING; 
  
    printf("Philosopher %d putting fork %d and %d down\n", 
           phnum + 1, LEFT + 1, phnum + 1); 
    printf("Philosopher %d is thinking\n", phnum + 1); 
  
    test(LEFT); 
    test(RIGHT); 
  
    sem_post(&mutex); 
} 
  
void* philospher(void* num) 
{ 
  
    while (1) { 
  
        int* i = num; 
  
        sleep(1); 
  
        take_fork(*i); 
  
        sleep(0); 
  
        put_fork(*i); 
    } 
} 
  
int main() 
{ 
  
    int i; 
    pthread_t thread_id[N]; 
  
    // initialize the semaphores 
    sem_init(&mutex, 0, 1); 
  
    for (i = 0; i < N; i++) 
  
        sem_init(&S[i], 0, 0); 
  
    for (i = 0; i < N; i++) { 
  
        // create philosopher processes 
        pthread_create(&thread_id[i], NULL, 
                       philospher, &phil[i]); 
  
        printf("Philosopher %d is thinking\n", i + 1); 
    } 
  
    for (i = 0; i < N; i++) 
  
        pthread_join(thread_id[i], NULL); 
} 

/////////////////////////////////////////////////////
//reader writer

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeblock;
int data = 0,rcount = 0;

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(&mutex);
  rcount = rcount + 1;
  if(rcount==1)
   sem_wait(&writeblock);
  sem_post(&mutex);
  printf("Data read by the reader%d is %d\n",f,data);
  sleep(1);
  sem_wait(&mutex);
  rcount = rcount - 1;
  if(rcount==0)
   sem_post(&writeblock);
  sem_post(&mutex);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&writeblock);
  data++;
  printf("Data writen by the writer%d is %d\n",f,data);
  sleep(1);
  sem_post(&writeblock);
}

int main()
{
  int i,b; 
  pthread_t rtid[5],wtid[5];
  sem_init(&mutex,0,1);
  sem_init(&writeblock,0,1);
  for(i=0;i<=2;i++)
  {
    pthread_create(&wtid[i],NULL,writer,(void *)i);
    pthread_create(&rtid[i],NULL,reader,(void *)i);
  }
  for(i=0;i<=2;i++)
  {
    pthread_join(wtid[i],NULL);
    pthread_join(rtid[i],NULL);
  }
  return 0;
}


/////////////////////////////////////////////////////
// reader priority

#include<stdio.h>  
 #include<semaphore.h>   
 //#include<mutex.h>
 #include<pthread.h>   
 void * reader(void *) ;  
 void *writer (void *) ;  
 sem_t wsem,mutex ;  
 int readcount=0 ;  
 main()  
 {  
  int a=1,b=1;  
     system("clear");  
  sem_init(&wsem,0,1) ;  
  sem_init(&mutex,0,1) ;  
  pthread_t r,w,r1,w1 ;  
  pthread_create(&r,NULL,reader,(void *)a);  
     a++;  
  pthread_create(&w1,NULL,writer,(void *)b);  
     b++;  
  pthread_create(&r1,NULL,reader,(void *)a);  
  pthread_create(&w,NULL,writer,(void *)b);  
  pthread_join(r,NULL);  
  pthread_join(w1,NULL);  
  pthread_join(r1,NULL);  
  pthread_join(w,NULL) ;  
  printf("main terminated\n");  
 }  
 void * reader(void * arg)  
 {  
  int c=(int)arg ;  
  printf("\nreader %d is created",c);  
     sleep(1);  
  sem_wait(&mutex) ;  
     readcount++;  
     if(readcount==1)  
         sem_wait(&wsem) ;  
  sem_post(&mutex) ;  
 /*Critcal Section */  
  printf("\n\nreader %d is reading\n ",c);  
  sleep(1) ;  
  printf("\nreader%d finished reading\n",c);  
 /* critical section completd */  
  sem_wait(&mutex) ;  
     readcount-- ;  
     if(readcount==0)  
         sem_post(&wsem) ;  
  sem_post(&mutex) ;  
 }  
 void * writer(void * arg)  
 {  
  int c=(int)arg ;  
  printf("\nwriter %d is created",c);  
     sleep(1);  
  sem_wait(&wsem) ;  
  printf("\nwriter %d is writing\n",c) ;  
  sleep(1);  
  printf("\nwriter%d finished writing\n",c);  
  sem_post(&wsem) ;  
 }
 
 ////////////////////////////////////////////////////////
 //smokers
 
 #include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<semaphore.h>
#include<pthread.h>
int table_used=1,generated_item[2],generated=0;
char *item[]={"tubaco","paper","matches"};
sem_t table;
void *agent(void *arg)
{
int i,j,k=0;
int count=0;
while(1)
{
sleep(1);
sem_wait(&table);
if(count==6) exit(0);
if(table_used==1)
{
i=k;
j=i+1;
if(j==3)
j=0;
k=j;
generated_item[0]=i;
generated_item[1]=j;
printf("agent produces %s,%s\n",item[i],item[j]);
generated=1;
table_used=0;
count++;
}
sem_post(&table);

}
}
void *smokeri(void *i)
{
//int count=0;
while(1)
{
sleep(1);
sem_wait(&table);
if(table_used==0)
{
if(generated && generated_item[0]!=(int)i &&
generated_item[1]!=(int)i)
{
printf("SMOKER%d completed his smoking\n",(int)i);
printf("\n");
//count++;
table_used=1;
generated=0;
}
}
sem_post(&table);
//if(count==5) exit(0);
}
}
main()
{
pthread_t smoker1,smoker2,smoker0,agnt;
sem_init(&table,0,1);
printf("SMOKER0 has tobacco\n");
printf("SMOKER1 has paper\n");
printf("SMOKER2 has matches\n");
pthread_create(&agnt,0,agent,0);
pthread_create(&smoker0,0,smokeri,(void*)0);
pthread_create(&smoker1,0,smokeri,(void*)1);
pthread_create(&smoker2,0,smokeri,(void*)2);
while(1);
}


///////////////////////////////////////////////
//LRU cache



#include <bits/stdc++.h> 
using namespace std; 
  
class LRUCache 
{ 
    list<int> dq; 
    unordered_map<int, list<int>::iterator> ma; 
    int csize; 
public: 
    LRUCache(int); 
    void refer(int); 
    void display(); 
}; 
  
LRUCache::LRUCache(int n) 
{ 
    csize = n; 
} 
void LRUCache::refer(int x) 
{ 
    if (ma.find(x) == ma.end()) 
    { 
        if (dq.size() == csize) 
        { 
            int last = dq.back(); 
            dq.pop_back(); 
            ma.erase(last); 
        } 
    } 
    else
        dq.erase(ma[x]); 
    dq.push_front(x); 
    ma[x] = dq.begin(); 
} 
void LRUCache::display() 
{ 
    for (auto it = dq.begin(); it != dq.end(); 
                                        it++) 
        cout << (*it) << " "; 
  
    cout << endl; 
} 
int main() 
{ 
    LRUCache ca(4); 
  
    ca.refer(1); 
    ca.refer(2); 
    ca.refer(3); 
    ca.refer(1); 
    ca.refer(4); 
    ca.refer(5); 
    ca.display(); 
  
    return 0; 
} 








/////////////////////////////////////////////////////////
//safe states


#include <iostream> 
#include <string.h> 
#include <vector> 

#define P 4 
#define R 3 
  
int total = 0; 
  
using namespace std; 
  
bool is_available(int process_id, int allocated[][R], 
                  int max[][R], int need[][R], int available[]) 
{ 
  
    bool flag = true; 
    for (int i = 0; i < R; i++) { 
  
        if (need[process_id][i] > available[i]) 
            flag = false; 
    } 
  
    return flag; 
} 
void safe_sequence(bool marked[], int allocated[][R], int max[][R], 
                   int need[][R], int available[], vector<int> safe) 
{ 
  
    for (int i = 0; i < P; i++) { 
        if (!marked[i] && is_available(i, allocated, max, need, available)) { 
            marked[i] = true; 
            for (int j = 0; j < R; j++) 
                available[j] += allocated[i][j]; 
  
            safe.push_back(i); 
            safe_sequence(marked, allocated, max, need, available, safe); 
            safe.pop_back(); 
            marked[i] = false; 
  
            for (int j = 0; j < R; j++) 
                available[j] -= allocated[i][j]; 
        } 
    } 
  
    if (safe.size() == P) { 
  
        total++; 
        for (int i = 0; i < P; i++) { 
  
            cout << "P" << safe[i] + 1; 
            if (i != (P - 1)) 
                cout << "--> "; 
        } 
  
        cout << endl; 
    } 
} 
  
int main() 
{ 
  
    int allocated[P][R] = { { 0, 1, 0 }, 
                            { 2, 0, 0 }, 
                            { 3, 0, 2 }, 
                            { 2, 1, 1 } }; 
  
    int max[P][R] = { { 7, 5, 3 }, 
                      { 3, 2, 2 }, 
                      { 9, 0, 2 }, 
                      { 2, 2, 2 } }; 
  
    int resources[R] = { 10, 5, 7 }; 
  
    int available[R]; 
  
    for (int i = 0; i < R; i++) { 
  
        int sum = 0; 
        for (int j = 0; j < P; j++) 
            sum += allocated[j][i]; 
  
        available[i] = resources[i] - sum; 
    } 
  
    vector<int> safe; 
  
    bool marked[P]; 
    memset(marked, false, sizeof(marked)); 
  
    int need[P][R]; 
    for (int i = 0; i < P; i++) 
        for (int j = 0; j < R; j++) 
            need[i][j] = max[i][j] - allocated[i][j]; 
  
    cout << "Safe sequences are:" << endl; 
    safe_sequence(marked, allocated, max, need, available, safe); 
  
    cout << "\nThere are total " << total << " safe-sequences" << endl; 
    return 0; 
} 


///////////////////////////////////////////////////////
//deadlock avoidance





#include<iostream> 
using namespace std; 
  
const int P = 5; 
  
const int R = 3; 
  
void calculateNeed(int need[P][R], int maxm[P][R], 
                   int allot[P][R]) 
{ 
    for (int i = 0 ; i < P ; i++) 
        for (int j = 0 ; j < R ; j++) 
  
            need[i][j] = maxm[i][j] - allot[i][j]; 
} 
  
bool isSafe(int processes[], int avail[], int maxm[][R], 
            int allot[][R]) 
{ 
    int need[P][R]; 
    calculateNeed(need, maxm, allot); 
    bool finish[P] = {0}; 
    int safeSeq[P]; 
    int work[R]; 
    for (int i = 0; i < R ; i++) 
        work[i] = avail[i]; 
    int count = 0; 
    while (count < P) 
    { 
        bool found = false; 
        for (int p = 0; p < P; p++) 
        { 
            if (finish[p] == 0) 
            { 
                int j; 
                for (j = 0; j < R; j++) 
                    if (need[p][j] > work[j]) 
                        break; 
  
                if (j == R) 
                { 
                    for (int k = 0 ; k < R ; k++) 
                        work[k] += allot[p][k]; 
                    safeSeq[count++] = p; 
                    finish[p] = 1; 
  
                    found = true; 
                } 
            } 
        } 
        if (found == false) 
        { 
            cout << "System is not in safe state"; 
            return false; 
        } 
    } 
    cout << "System is in safe state.\nSafe"
         " sequence is: "; 
    for (int i = 0; i < P ; i++) 
        cout << safeSeq[i] << " "; 
  
    return true; 
} 

int main() 
{ 
    int processes[] = {0, 1, 2, 3, 4}; 
    int avail[] = {3, 3, 2}; 
  
    int maxm[][R] = {{7, 5, 3}, 
                     {3, 2, 2}, 
                     {9, 0, 2}, 
                     {2, 2, 2}, 
                     {4, 3, 3}}; 
  
    int allot[][R] = {{0, 1, 0}, 
                      {2, 0, 0}, 
                      {3, 0, 2}, 
                      {2, 1, 1}, 
                      {0, 0, 2}}; 
  
    isSafe(processes, avail, maxm, allot); 
  
    return 0; 
} 



///////////////////////////////////////////////
// optimal_page_replacement



#include <bits/stdc++.h> 
using namespace std; 
  
bool search(int key, vector<int>& fr) 
{ 
    for (int i = 0; i < fr.size(); i++) 
        if (fr[i] == key) 
            return true; 
    return false; 
} 
  
int predict(int pg[], vector<int>& fr, int pn, int index) 
{ 
    int res = -1, farthest = index; 
    for (int i = 0; i < fr.size(); i++) { 
        int j; 
        for (j = index; j < pn; j++) { 
            if (fr[i] == pg[j]) { 
                if (j > farthest) { 
                    farthest = j; 
                    res = i; 
                } 
                break; 
            } 
        } 
  
        if (j == pn) 
            return i; 
    } 
  
    return (res == -1) ? 0 : res; 
} 
  
void optimalPage(int pg[], int pn, int fn) 
{ 
    vector<int> fr; 
    int hit = 0; 
    for (int i = 0; i < pn; i++) { 
  
        if (search(pg[i], fr)) { 
            hit++; 
            continue; 
        } 
  
        if (fr.size() < fn) 
            fr.push_back(pg[i]); 
  
        else { 
            int j = predict(pg, fr, pn, i + 1); 
            fr[j] = pg[i]; 
        } 
    } 
    cout << "No. of hits = " << hit << endl; 
    cout << "No. of misses = " << pn - hit << endl; 
} 
  
int main() 
{ 
    int pg[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 }; 
    int pn = sizeof(pg) / sizeof(pg[0]); 
    int fn = 4; 
    optimalPage(pg, pn, fn); 
    return 0; 
} 



////////////////////////////////////////////////////////////////
//FIFO page replacement

#include<bits/stdc++.h> 
using namespace std; 
  
int pageFaults(int pages[], int n, int capacity) 
{ 
    unordered_set<int> s; 
  
    queue<int> indexes; 
  
    int page_faults = 0; 
    for (int i=0; i<n; i++) 
    { 
        if (s.size() < capacity) 
        { 
            if (s.find(pages[i])==s.end()) 
            { 
                s.insert(pages[i]); 
  
                page_faults++; 
  
                indexes.push(pages[i]); 
            } 
        } 
  
        else
        { 
            if (s.find(pages[i]) == s.end()) 
            { 
                int val = indexes.front(); 
  
                indexes.pop(); 
  
                s.erase(val); 
  
                s.insert(pages[i]); 
  
                indexes.push(pages[i]); 
  
                page_faults++; 
            } 
        } 
    } 
  
    return page_faults; 
} 
  
int main() 
{ 
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 
                   2, 3, 0, 3, 2}; 
    int n = sizeof(pages)/sizeof(pages[0]); 
    int capacity = 4; 
    cout << pageFaults(pages, n, capacity); 
    return 0; 
} 








//////////////////////////////////////////////////////////
//LRU pagereplacement



#include<bits/stdc++.h> 
using namespace std; 
  
int pageFaults(int pages[], int n, int capacity) 
{ 
    unordered_set<int> s; 
  
    unordered_map<int, int> indexes; 
  
    int page_faults = 0; 
    for (int i=0; i<n; i++) 
    { 
        if (s.size() < capacity) 
        { 
            if (s.find(pages[i])==s.end()) 
            { 
                s.insert(pages[i]); 
                page_faults++; 
            } 
            indexes[pages[i]] = i; 
        } 
  
        else
        { 
            if (s.find(pages[i]) == s.end()) 
            { 
                int lru = INT_MAX, val; 
                for (auto it=s.begin(); it!=s.end(); it++) 
                { 
                    if (indexes[*it] < lru) 
                    { 
                        lru = indexes[*it]; 
                        val = *it; 
                    } 
                } 
  
                s.erase(val); 
  
                s.insert(pages[i]); 
  
                page_faults++; 
            } 
  
            indexes[pages[i]] = i; 
        } 
    } 
  
    return page_faults; 
} 
  
int main() 
{ 
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; 
    int n = sizeof(pages)/sizeof(pages[0]); 
    int capacity = 4; 
    cout << pageFaults(pages, n, capacity); 
    return 0; 
} 







