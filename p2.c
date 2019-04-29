#include<stdio.h>
#define max 200
#define initial 1
#define waiting 2
#define visit 3

int state[max];
int queue[max], front = -1,rear = -1;
void insert_queue(int vertex);
int delete_queue();
int isEmpty_queue();

int adj[max][max];
int visited[max];
int n,e;

void add_edge(int u ,int v,int w)
{
    //printf("%d \t %d \t %d\n",u,v,w);
    adj[u][v]=w;
    adj[v][u]=w;
}
void read_from_file()
{
    FILE *in_file;
    int n,m,p;

    in_file = fopen("fgraph.txt","r");

    if(in_file == NULL)
    {
        printf("error\n");
    }
    while(fscanf(in_file,"%d %d %d",&n,&m,&p) != EOF)
    {
       add_edge(n,m,p);
    }
    fclose(in_file);
}

void Display()
{
    int i,j,k;
    for(i=0;i<n;i++)
    {
        int deg=0,ans=0;
        for(j=0;j<n;j++)
        {
            if(adj[i][j] != 0)
            {
                deg++;
				for(k=i+1;k<n;k++)
                {
                    if(adj[j][k] != 0)
                    {
                        ans++;
                    }
                }
            }
        }
        printf("person : [ %d ]  has  %d Friends \t\n",i,deg);
    }
}
void DFS(int i)
{
    int j,tot=0;
    printf("%d ",i);
    visited[i]=1;
    for(j=0;j<n;j++)
    {
        if(!visited[j] && adj[i][j] != 0)
        {
           DFS(j);
        }
    }
}

void BFS(int v)
{
	int i;
	insert_queue(v);
	state[v] = waiting;
	while(!isEmpty_queue())
	{
		v = delete_queue( );
		printf("%d ",v);
		state[v] = visit;

		for(i=0; i<n; i++)
		{
			if(state[i] == 0 && adj[v][i] !=0)
			{
				insert_queue(i);
				state[i] = visit;
			}
		}
	}
	printf("\n");
}

void insert_queue(int vertex)
{
	if(rear == max-1)
		printf("Queue Overflow\n");
	else
	{
		if(front == -1)
			front = 0;
		rear = rear+1;
		queue[rear] = vertex ;
	}
}

int isEmpty_queue()
{
	if(front == -1 || front > rear)
		return 1;
	else
		return 0;
}

int delete_queue()
{
	int delete_item;
	if(front == -1 || front > rear)
	{
		printf("Queue Underflow\n");
		exit(1);
	}

	delete_item = queue[front];
	front = front+1;
	return delete_item;
}

void main()
{
    read_from_file();

    int e;
    printf("enter no of noeds :");
    scanf("%d",&n);
    printf("Enter no of edgs ");
    scanf("%d",&e);
    printf("\n\n");

    printf("DFS Traversal : ");
    DFS(0);
    printf("\n\n");
    printf("BFS Traversal : ");
    BFS(0);
    printf("\n");
    Display();
}
