#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/resource.h>

/* premises: */
/* source node is always node 0 */
/* all weights are positive, so we don't care about cycles */
/* we enforce that all nodes are connected */

/* settings */

#define MAXSTACK 100000

int nnodos = 700;
double pconn  = 0.3;
int top = 0;
int stack[MAXSTACK];
int printpaths=0;
int printgraph=0;
int rseed = 1;

/* stats */

int nodespushed=0;
int nodeschecked=0;
int distupdated=0;

/* graph */
int ** edge;
int * dist;

int qempty(){
  return !top;
}

void push(int el){
  if (top==MAXSTACK-2){
    fprintf(stderr,"push: stack full!!\n");
  }
  stack[top] = el;
  top ++;
  nodespushed++;
}
 
int pop(){
  if (!top){
    fprintf(stderr,"pop: stack empty!!\n");
  }
  top --;
  return stack[top];
}

int inqueue(int el){
  int i;
  for (i=0; i<top; i++)
    if (stack[i] == el)
      return 1;
  return 0;
}

void usage(){
  fprintf(stderr,"single-source-shortest-path using moore\n");
  fprintf(stderr,"\t-n <intnum>    (number of nodes in graph)\n");
  fprintf(stderr,"\t-c <floatnum>  (connection probability)\n");
  fprintf(stderr,"\t-s             (print shortest paths)\n");
  fprintf(stderr,"\t-g             (print graph)\n");
  fprintf(stderr,"\t-r <intnum>    (random seed)\n");
}

void parse_args(int argc,char ** argv){
     extern char * optarg;
     extern int optind;
     int c ;
     while ((c = getopt(argc, argv, "n:c:sgr:h")) != EOF)
       switch(c) {
         case 'n':
                  nnodos = atoi(optarg);
                  break;
         case 'c':
                  pconn = atof(optarg);
                  break;
         case 's':
                  printpaths = 1;
                  break;
         case 'g':
                  printgraph = 1;
                  break;
         case 'r':
                  rseed = atoi(optarg);
                  break;
         case 'h':
         default: 
                  usage();
                  exit(1);

       }
}
 
void search(){
  int u,v; /* vertex index */
  int newdist;
  u = pop();
  for (v=0; v<nnodos; v++)
    if (edge[u][v]){
      nodeschecked++;
      newdist = dist[u] + edge[u][v];
      if (newdist < dist[v]){
        distupdated++;
        dist[v] = newdist;
        if (!inqueue(v))
          push(v);
      }
    }
}

int main(int argc, char ** argv){
  int i,j, hasone;
  double t;
  struct rusage inicio;
  struct rusage fim;
  struct timeval utime;
  struct timeval stime;

  parse_args(argc,argv);
  srand48((long)(rseed));
  /* generate graph  and initialize dist vector*/
  edge = (int **)malloc(sizeof(int*)*nnodos);
  dist = (int *)malloc(sizeof(int)*nnodos);
  for (i=0; i<nnodos; i++){
    hasone = 0;
    dist[i] = (i ? 1<<30 : 0);
    edge[i] = (int *) malloc(sizeof(int)*nnodos);  
    /* node 0 is a source */
    for (j=0; j<nnodos; j++){
      t = drand48();
#ifdef DEBUG
      printf("%f\n", t);
#endif
      if (j && (j!=i) && (t<pconn)){
        hasone = 1;
        t = drand48();
        edge[i][j] = (int)(t*nnodos*100);
#ifdef DEBUG
        printf("%d %d = %f %d\n",i,j,t,edge[i][j]);
#endif
      }
      else{
        edge[i][j] = 0;
      }
    }
    if (!hasone){ /* disconnected node !! */
      while ((i == (j=(int)(drand48()*nnodos))) || !j);
      edge[i][j] = (int)(drand48()*nnodos*100);
      fprintf(stderr,"%d was disconnected : %d\n",i,j);
    }
  }

  if (printgraph){
    for (i=0; i<nnodos; i++){
      for (j=0; j<nnodos; j++){
        printf("%6d", edge[i][j]);
      }
      printf("\n");
    }
  }
  else
    printf("Iniciando processamento\n");

  getrusage(RUSAGE_SELF, &inicio);
  /* insert s (0) into the queue */
  push(0);
  /* while queue is not empty, search */
  while (!qempty()){
    search();
  }
  getrusage(RUSAGE_SELF, &fim);
  
  utime.tv_sec = fim.ru_utime.tv_sec - inicio.ru_utime.tv_sec;
  utime.tv_usec = fim.ru_utime.tv_usec - inicio.ru_utime.tv_usec;
  if (utime.tv_usec <0){
    utime.tv_sec--;
    utime.tv_usec += 1000000;
  }
  stime.tv_sec = fim.ru_stime.tv_sec - inicio.ru_stime.tv_sec;
  stime.tv_usec = fim.ru_stime.tv_usec - inicio.ru_stime.tv_usec;
  if (stime.tv_usec <0){
    stime.tv_sec--;
    stime.tv_usec += 1000000;
  }
  
  if (printpaths)
    for (i=1; i<nnodos; i++)
      printf("%3d -> %3d = %5d\n",0,i,dist[i]);
  else
    printf("Fim processamento\n");
  printf("System: %ld.%.6ld User: %ld.%.6ld\n", 
          stime.tv_sec, stime.tv_usec, utime.tv_sec, utime.tv_usec);
  printf("Nodes Checked: %6d Nodes pushed: %6d Dist updates: %6d\n",
         nodeschecked, nodespushed, distupdated);
  return 0;
}

