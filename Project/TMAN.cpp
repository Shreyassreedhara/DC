#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<cmath>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<iomanip>

using namespace std;

// Global variable declaration.

int N, k, i, j;
char t;
vector <int> g;
const double pi = 3.1415926;

// Structure declaration. Each node is a member variable of this structure.
struct nodes
    {
        int userID;
        double angle;
        double x;
        double y;
        vector <int> neighbor_list;
        int sent_node;
        vector <int> nl_sent;
        vector <int> received_list;
        vector <int> combined_array;
        vector <double> distances;
    };

//Function prototyping.
vector <int> initialization(int j);
void evolution();
vector <int> random_numbers(vector<int> &r);
void b_updater(double *upbangle,double *upbx, double *upby, int updb);
void s_updater(double *upsangle,double *upsx, double *upsy, int upds,int N);



int main()
{

    int upd, temp2, temp4, counter = 0, randm, m, f, u, q, nds, n_nds, num_of_times, no_of_times, n_node, storage1 = 0;
    double temp1, temp3, temp5, temp6, x, y, angle;
    vector <int> received;

    // Taking input.
    cout<<"Enter the number of nodes: ";
    cin>>N;
    cout<<"Enter the number of neighbors: ";
    cin>>k;
    cout<<"Enter the topology: ";
    cin>>t;
    cout<<endl;

    //Checking the topology and choosing the part of code to run.
    if( t == 'b')
    {
    // creates N member variables of the structure
    struct nodes node[N];

    //loop which calls initialization function N times and updates the neighbor list of all the nodes
    for(i=0;i<N;i++)
    {
        node[i].userID = i+1;
        received = initialization(i+1);
        node[i].neighbor_list = received;

    }

    //Calculating and printing the sum of distance after the initialization function.
    for(f=0;f<N;f++)
        {
        for(m=0;m<k;m++)
            {
            storage1 = storage1 + node[f].neighbor_list[m];
            }
        }

    cout<<endl<<endl;
    cout<<"**********************************************************************************************"<<endl;
    cout<<"The sum_of_distances after initialization is: "<< storage1 <<endl;
    cout<<"**********************************************************************************************"<<endl;

    //loop which calls the angle updation function N times and updates angle, x and y of all the nodes
    for(i=0;i<N;i++)
        {
        b_updater(&angle,&x,&y,i);
        node[i].angle = angle;
        node[i].x = x;
        node[i].y = y;
        }
    //The loop for number of cycles it should run
    for(num_of_times=0;num_of_times<40;num_of_times++)
        {
        double storage = 0;
        int w;
        counter++;
        // loop for the number of nodes present. Each node will go through evolution phase and then the cycle loop increases.
        for(n_node=0;n_node<N;n_node++)
            {
            int v;
            srand(time(NULL));
            randm = rand()%k;
            //pick random elements from the neighbor list and remember the nodeID of the node ID you picked
            node[n_node].sent_node = node[n_node].neighbor_list[randm];
            //both the nodes exchange and store the neighbor list of other node
            node[n_node].nl_sent = node[n_node].neighbor_list;
            node[n_node].nl_sent[0] = n_node + 1;
            v = node[n_node].sent_node-1;
            node[v].received_list = node[n_node].nl_sent;
            node[n_node].received_list = node[v].neighbor_list;
            //The nodes combine its neighbor list and the neighbor list it received
            node[n_node].combined_array = node[n_node].neighbor_list;
            node[n_node].combined_array.insert(node[n_node].combined_array.end(),node[n_node].received_list.begin(),node[n_node].received_list.end());
            node[v].combined_array = node[v].neighbor_list;
            node[v].combined_array.insert(node[v].combined_array.end(),node[v].received_list.begin(), node[v].received_list.end());
            vector <double> dist_calc1;
            vector <double> dist_calc2;
            int node21;
            int node22;
            double distance1;
            double distance2;

            //loop that calculates distance of nodes in merged array to the node.
            // Special case of its own name, Nth node has been handled by setting their distances as some large value.
            // This ensures that they don't show up in the neighbor list when we pick k nearest elements.
            //Special case for first and last but one node has also been handled
            for(f=0;f<(2*k);f++)
            {
            node21 = node[n_node].combined_array[f];
            if(n_node == N-1)
                {
                if(node21 == 1 || node21 == N-1)
                    {
                    distance1 = 1;
                    dist_calc1.push_back(distance1);
                    }
                else
                    {
                    distance1 = 4000;
                    dist_calc1.push_back(distance1);
                    }
                }
            else if(n_node == node21-1)
                {
                distance1 = 4000;
                dist_calc1.push_back(distance1);
                }

            else
                {
                if(node21 == N)
                    {
                    if(n_node == 0 || n_node == N-2)
                        {
                        distance1 = 1;
                        dist_calc1.push_back(distance1);
                        }
                        else
                        {
                        distance1 = 5000;
                        dist_calc1.push_back(distance1);
                        }
                    }
                else
                    {
                    distance1 = abs(sqrt(pow((node[n_node].x - node[node21 - 1].x),2) + pow((node[n_node].y - node[node21 - 1].y), 2)));
                    dist_calc1.push_back(distance1);
                    }
            }

            node22 = node[v].combined_array[f];
            if(v == N-1)
                {
                if(node22 == 1 || node22 == N-1)
                    {
                    distance2 = 1;
                    dist_calc2.push_back(distance2);
                    }
                else
                    {
                    distance2 = 4000;
                    dist_calc2.push_back(distance2);
                    }
                }

            else if(v == node22-1)
                {
                distance2 = 4000;
                dist_calc2.push_back(distance2);
                }

            else
                {
                if(node22 == N)
                    {
                    if(v == 0 || v == N-2)
                        {
                        distance2 = 1;
                        dist_calc2.push_back(distance2);
                        }
                    else
                        {
                        distance2 = 5000;
                        dist_calc2.push_back(distance2);
                        }
                    }
                else
                    {
                    distance2 = abs(sqrt(pow(node[v].x - node[node22-1].x,2)+pow(node[v].y - node[node22-1].y,2)));
                    dist_calc2.push_back(distance2);
                    }
                }
            }


            for(u=0;u<=(2*k);u++)
                {
                int o = 0;
                int w = 1;
                int m;
                for(m=0;m<(2*k)-1;m++)
                    {
                    if(dist_calc1[o]>dist_calc1[w])
                        {
                        temp1 = dist_calc1[o];
                        dist_calc1[o] = dist_calc1[w];
                        dist_calc1[w] = temp1;
                        temp2 = node[n_node].combined_array[o];
                        node[n_node].combined_array[o] = node[n_node].combined_array[w];
                        node[n_node].combined_array[w] = temp2;
                        o++;
                        w++;
                        }
                    else if(dist_calc1[o] == dist_calc1[w])
                        {
                        if(node[n_node].combined_array[o] == node[n_node].combined_array[w])
                            {
                            dist_calc1[w] = 1000;
                            }
                        o++;
                        w++;
                        }
                    else
                        {
                        o++;
                        w++;
                        }
                    }
                }
            for(q=0;q<=(2*k);q++)
                {
                int o = 0, w = 1, m;
                for(m=0;m<(2*k)-1;m++)
                    {
                    if(dist_calc2[o]>dist_calc2[w])
                        {
                        temp3 = dist_calc2[o];
                        dist_calc2[o] = dist_calc2[w];
                        dist_calc2[w] = temp3;
                        temp4 = node[v].combined_array[o];
                        node[v].combined_array[o] = node[v].combined_array[w];
                        node[v].combined_array[w] = temp4;
                        o++;
                        w++;
                        }
                    else if(dist_calc2[o] == dist_calc2[w])
                        {
                        if(node[v].combined_array[o] == node[v].combined_array[w])
                            {
                            dist_calc2[w] = 1000;
                            }
                        o++;
                        w++;
                        }
                    else
                        {
                        o++;
                        w++;
                        }
                    }
                }

            for(f=0;f<k;f++)
                {
                node[n_node].neighbor_list[f] = node[n_node].combined_array[f];
                }
            for(f=0;f<k;f++)
                {
                node[v].neighbor_list[f] = node[v].combined_array[f];
                }
            dist_calc1.resize(k);
            dist_calc2.resize(k);

            node[n_node].distances = dist_calc1;
            node[v].distances = dist_calc2;

            }

            for(f=0;f<N;f++)
                {
                for(w=0;w<k;w++)
                    {
                    if(node[f].distances[w] < 100)
                        {
                        storage = storage + node[f].distances[w];
                        }
                    }
                }

            if(counter == 1)
                {
                string top1 = "b_";
                string filename1;
                filename1 = top1 + 'N' + '_' + 'k'+ '1';

                ofstream fp1;

                fp1.open( filename1.c_str() );
                fp1 << "Number of nodes: "<< N <<endl;
                fp1 << "Number of neighbors: "<< k <<endl;
                fp1 << "Number of cycle: "<< counter <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp1 << n_nds+1 <<"   [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp1 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp1<<"]"<<endl;
                    }
                fp1.close();

                }

            if(counter == 5)
                {
                string top5 = "b_";
                string filename5;
                filename5 = top5 + 'N' + '_' + 'k' + '5';

                ofstream fp5;

                fp5.open( filename5.c_str() );
                fp5 << "Number of cycle: "<< counter <<endl;
                fp5 << "Number of nodes: "<< N <<endl;
                fp5 << "Number of neighbors: "<< k <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp5 << n_nds+1 << "   [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp5 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp5 <<"]\n";
                    }
                fp5.close();
                }

             if(counter == 10)
                {
                string top10 = "b_";
                string filename10;
                filename10 = top10 + 'N' + '_' + 'k' + "10";

                ofstream fp10;

                fp10.open( filename10.c_str() );
                fp10 << "Number of cycle: "<< counter <<endl;
                fp10 << "Number of nodes: "<< N <<endl;
                fp10 << "Number of neighbors: "<< k <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp10 << n_nds+1 << "    [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp10 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp10<<"]\n";
                    }
                fp10.close();
                }
            if(counter == 15)
                {
                string top15 = "b_";
                string filename15;
                filename15 = top15 + 'N' + '_' + 'k' + "15";

                ofstream fp15;

                fp15.open( filename15.c_str() );
                fp15 << "Number of cycle: "<< counter <<endl;
                fp15 << "Number of nodes: "<< N <<endl;
                fp15 << "Number of neighbors: "<< k <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp15 << n_nds+1<<"   [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp15 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp15<<"\n";
                    }
                fp15.close();
                }

            cout<<endl<<endl;
            cout<<"**********************************************************************************************"<<endl;
            cout<<"The sum_of_distances for "<< counter <<" cycle is: "<< storage <<endl;
            cout<<"**********************************************************************************************"<<endl;

            ofstream fp20;

            fp20.open("distances.txt",ofstream::out| ofstream::app);
            fp20 << counter <<" "<< storage << endl;
            fp20.close();
        }
    }



    else if(t == 's')
        {



        cout<<"This is spectacle"<<endl<<endl;
        struct nodes node[N];

        for(i=0;i<N;i++)
        {
            node[i].userID = i+1;
            received = initialization(i+1);
            node[i].neighbor_list = received;
        }

        for(f=0;f<N;f++)
        {
        for(m=0;m<k;m++)
            {
            storage1 = storage1 + node[f].neighbor_list[m];
            }
        }

        cout<<endl<<endl;
        cout<<"**********************************************************************************************"<<endl;
        cout<<"The sum_of_distances after initialization is: "<< storage1 <<endl;
        cout<<"**********************************************************************************************"<<endl;


        for(i=0;i<N;i++)
        {
        s_updater(&angle,&x,&y,i,N);
        node[i].angle = angle;
        node[i].x = x;
        node[i].y = y;
        }
        cout<<endl;

        for(num_of_times=0;num_of_times<40;num_of_times++)
        {
        double storage = 0;
        int w;
        counter++;
        for(n_node=0;n_node<N;n_node++)
        {
            int v;
            srand(time(NULL));
            randm = rand()%k;
            node[n_node].sent_node = node[n_node].neighbor_list[randm];
            node[n_node].nl_sent = node[n_node].neighbor_list;
            node[n_node].nl_sent[0] = n_node + 1;
            v = node[n_node].sent_node-1;
            node[v].received_list = node[n_node].nl_sent;
            node[n_node].received_list = node[v].neighbor_list;
            node[n_node].combined_array = node[n_node].neighbor_list;
            node[n_node].combined_array.insert(node[n_node].combined_array.end(),node[n_node].received_list.begin(),node[n_node].received_list.end());
            node[v].combined_array = node[v].neighbor_list;
            node[v].combined_array.insert(node[v].combined_array.end(),node[v].received_list.begin(), node[v].received_list.end());

            vector <double> dist_calc1;
            vector <double> dist_calc2;
            int node21;
            int node22;
            double distance1;
            double distance2;

            for(f=0;f<(2*k);f++)
            {
            node21 = node[n_node].combined_array[f];
            if(n_node == node21-1)
                {
                distance1 = 4000;
                dist_calc1.push_back(distance1);
                }
            else
                {
                distance1 = abs(sqrt(pow((node[n_node].x - node[node21 - 1].x),2) + pow((node[n_node].y - node[node21 - 1].y), 2)));
                dist_calc1.push_back(distance1);
                }


            node22 = node[v].combined_array[f];

            if(v == node22-1)
                {
                distance2 = 4000;
                dist_calc2.push_back(distance2);
                }

            else
                {
                distance2 = abs(sqrt(pow(node[v].x - node[node22-1].x,2)+pow(node[v].y - node[node22-1].y,2)));
                dist_calc2.push_back(distance2);
                }
            }

            for(u=0;u<=(2*k);u++)
                {
                int o = 0;
                int w = 1;
                int m;
                for(m=0;m<(2*k)-1;m++)
                    {
                    if(dist_calc1[o]>dist_calc1[w])
                        {
                        temp1 = dist_calc1[o];
                        dist_calc1[o] = dist_calc1[w];
                        dist_calc1[w] = temp1;
                        temp2 = node[n_node].combined_array[o];
                        node[n_node].combined_array[o] = node[n_node].combined_array[w];
                        node[n_node].combined_array[w] = temp2;
                        o++;
                        w++;
                        }
                    else if(dist_calc1[o] == dist_calc1[w])
                        {
                        if(node[n_node].combined_array[o] == node[n_node].combined_array[w])
                            {
                            dist_calc1[w] = 1000;
                            }
                        o++;
                        w++;
                        }
                    else
                        {
                        o++;
                        w++;
                        }
                    }
                }

                for(q=0;q<=(2*k);q++)
                {
                int o = 0;
                int w = 1;
                int m;
                for(m=0;m<(2*k)-1;m++)
                    {
                    if(dist_calc2[o]>dist_calc2[w])
                        {
                        temp3 = dist_calc2[o];
                        dist_calc2[o] = dist_calc2[w];
                        dist_calc2[w] = temp3;
                        temp4 = node[v].combined_array[o];
                        node[v].combined_array[o] = node[v].combined_array[w];
                        node[v].combined_array[w] = temp4;
                        o++;
                        w++;
                        }
                    else if(dist_calc2[o] == dist_calc2[w])
                        {
                        if(node[v].combined_array[o] == node[v].combined_array[w])
                            {
                            dist_calc2[w] = 1000;
                            }
                        o++;
                        w++;
                        }
                    else
                        {
                        o++;
                        w++;
                        }
                    }
                }

                for(f=0;f<k;f++)
                {
                node[n_node].neighbor_list[f] = node[n_node].combined_array[f];
                }

                for(f=0;f<k;f++)
                {
                node[v].neighbor_list[f] = node[v].combined_array[f];
                }

                dist_calc1.resize(k);
                dist_calc2.resize(k);

                node[n_node].distances = dist_calc1;
                node[v].distances = dist_calc2;

        }
        for(f=0;f<N;f++)
                {
                for(w=0;w<k;w++)
                    {
                    if(node[f].distances[w] < 100)
                        {
                        storage = storage + node[f].distances[w];
                        }
                    }
                }

                if(counter == 1)
                {
                string top1 = "s_";
                string filename1;
                filename1 = top1 + 'N' + '_' + 'k'+ '1';

                ofstream fp1;

                fp1.open( filename1.c_str() );
                fp1 << "Number of nodes: "<< N <<endl;
                fp1 << "Number of neighbors: "<< k <<endl;
                fp1 << "Number of cycle: "<< counter <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp1 << n_nds+1 <<"   [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp1 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp1<<"]"<<endl;
                    }
                fp1.close();

                }

            if(counter == 5)
                {
                string top5 = "s_";
                string filename5;
                filename5 = top5 + 'N' + '_' + 'k' + '5';

                ofstream fp5;

                fp5.open( filename5.c_str() );
                fp5 << "Number of cycle: "<< counter <<endl;
                fp5 << "Number of nodes: "<< N <<endl;
                fp5 << "Number of neighbors: "<< k <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp5 << n_nds+1 << "   [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp5 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp5 <<"]\n";
                    }
                fp5.close();
                }

             if(counter == 10)
                {
                string top10 = "s_";
                string filename10;
                filename10 = top10 + 'N' + '_' + 'k' + "10";

                ofstream fp10;

                fp10.open( filename10.c_str() );
                fp10 << "Number of cycle: "<< counter <<endl;
                fp10 << "Number of nodes: "<< N <<endl;
                fp10 << "Number of neighbors: "<< k <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp10 << n_nds+1 << "    [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp10 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp10<<"]\n";
                    }
                fp10.close();
                }
            if(counter == 15)
                {
                string top15 = "s_";
                string filename15;
                filename15 = top15 + 'N' + '_' + 'k' + "15";

                ofstream fp15;

                fp15.open( filename15.c_str() );
                fp15 << "Number of cycle: "<< counter <<endl;
                fp15 << "Number of nodes: "<< N <<endl;
                fp15 << "Number of neighbors: "<< k <<endl;
                for(n_nds=0;n_nds<N;n_nds++)
                    {
                    fp15 << n_nds+1<<"   [";
                    for(nds=0;nds<k;nds++)
                        {
                        fp15 << node[n_nds].neighbor_list[nds]<<" ";
                        }
                    fp15<<"\n";
                    }
                fp15.close();
                }

            cout<<endl<<endl;
            cout<<"**********************************************************************************************"<<endl;
            cout<<"The sum_of_distances for "<< counter <<" cycle is: "<< storage <<endl;
            cout<<"**********************************************************************************************"<<endl;

            ofstream fp20;

            fp20.open("distances1.txt",ofstream::out| ofstream::app);
            fp20 << counter <<" "<< storage << endl;
            fp20.close();

        }

        }



    else
        {
        cout<<"Please enter the topology as either 'b' or 's'"<<endl;
        }
    return 0;
}

vector <int> initialization(int j)
{
    int f;
    vector <int> g;
    vector <int> receiver;
    int x;
    int n;
    int z;
    int rand_array[N][N-1];
    int d;
    int a = 0;
    for(z=1;z<=N;z++)
    {
         if(j != z)
        {
            rand_array[j-1][a] = z;
            a++;
        }
        else
        {
            continue;
        }
    }
    for(f=0;f<N-1;f++)
    {
    g.push_back(rand_array[j-1][f]);
    }
    receiver = random_numbers(g);
    return receiver;
}


vector<int> random_numbers(vector <int> &r)
{
int h;
int f;
vector <int> sender;
random_shuffle(r.begin(),r.end());
for(h=1;h<=k;h++)
    {
    sender.push_back(r[h-1]);
    }
return sender;
}

void b_updater(double *upbangle,double *upbx, double *upby, int updb)
{

    *upbangle = ((pi/2) - ((updb+1)-1) * (pi/(N - 2)));
    *upbx = cos(*upbangle);
    *upby = sin(*upbangle);
}

void s_updater(double *upsangle,double *upsx, double *upsy, int upds,int N)
{
if((upds+1)>0 && (upds+1)<=(2*N/5))
    {
    *upsangle = (upds)*((5*pi)/N);
    *upsx = 1 + cos(*upsx);
    *upsy = sin(*upsy);
    }
else if((upds+1)>(2*N/5) && (upds+1)<=(3*N/5))
    {
    *upsangle = (((upds+1) -(2*N/5))*(5*pi/(N+5)));
    *upsx = 3 + cos(*upsangle);
    *upsy = -sin(*upsangle);
    }
else
    {
    *upsangle = pi + ((upds+1)-((3*N)/5)*((5*pi)/N));
    *upsx = (5+cos(*upsangle));
    *upsy = sin(*upsangle);
    }
}



