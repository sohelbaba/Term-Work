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

void add_edge(int u ,int v)
{
    adj[u][v]=1;
}
void read_from_file()
{
    FILE *in_file;
    int n,m;

    in_file = fopen("tgraph.txt","r");

    if(in_file == NULL)
    {
        printf("error\n");
    }
    while(fscanf(in_file,"%d %d",&n,&m) != EOF)
    {
       add_edge(n,m);
    }
    fclose(in_file);
}

void Display()
{
    float ps;
    int e,i,j,origin,dest;
    for(i=0;i<=7;i++)
    {
        int indeg=0,outdeg=0;
        for(j=0;j<=7;j++)
        {
            if(adj[j][i] == 1)
            {
                indeg++;
            }
        }
        for(j=0;j<n;j++)
        {
            if(adj[i][j] == 1)
            {
                outdeg++;
            }
        }

        ps=(float)indeg/outdeg;
        if(ps == 2.0)
        {
            printf("person : [ %d ]\t Popular\t Popularity Score : %.2f\t Followed : [ %d ] \tFollows : [ %d ]\t\n",i,ps,indeg,outdeg);
        }
        else if(ps == 3.0)
            printf("person : [ %d ]\t Popular\t Popularity Score : %.2f\t Followed : [ %d ] \tFollows : [ %d ]\t\n",i,ps,indeg,outdeg);
        else if(indeg == 2 && outdeg == 0)
        {
            ps=0;
            printf("person : [ %d ]\t Not Popular\t Popularity Score : %.2f\t Followed : [ %d ] \tFollows : [ %d ]\t\n",i,ps,indeg,outdeg);
        }
        else if(indeg == 3 && outdeg == 0)
        {
            ps=0;
            printf("person : [ %d ]\t Popular\t Popularity Score : %.2f\t Followed : [ %d ] \tFollows : [ %d ]\t\n",i,ps,indeg,outdeg);
        }
        else
            printf("person : [ %d ]\t Not Popular\t Popularity Score : %.2f\t Followed : [ %d ] \tFollows : [ %d ]\t\n",i,ps,indeg,outdeg);
    }
}
void DFS(int i)
{
    int j;
    printf("%d ",i);
    visited[i]=1;
    for(j=0;j<n;j++)
    {
        if(!visited[j] && adj[i][j]==1)
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
    printf("\n\n");
    Display();
}
