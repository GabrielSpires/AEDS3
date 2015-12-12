/*
 *	File	: dining.c
 *
 *	Title	: Dining Philosophers.
 *
 *	Short	: Solution to the dining philosophers problem.
 *
 *	Long	: Sets up a fifo fifo of threads, and activates threads
 *			as forks become avaliable.
 *
 *	Author	: Andrae Muys
 *
 *	Date	: 18 September 1997
 *
 *	Revised	: 13 May 1998 : Fixed possible deadlock in fifoLock.
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define TABLE 5
#define DELAY 50000
#define DISHES 10

typedef struct node {
	struct node *next;
	pthread_cond_t sleep;
} node;

typedef struct {
	node *head, *tail;
	pthread_mutex_t *mut;
	int runmax;
	int size;
} fifo;

fifo *fifoInit (int runmax);
void fifoDelete (fifo *q);
void fifoLock (fifo *q, pthread_mutex_t *mut, int id);
void fifoUnlock (fifo *q, int id);

void *philosopher (void *id);

pthread_mutex_t forks[TABLE];
pthread_cond_t newfork;
fifo *queue;

int main ()
{
	pthread_t p[TABLE];
	int i;

	queue = fifoInit (TABLE / 2);
	printf ("Queue initialised for %d eaters.\n", TABLE / 2);
	pthread_cond_init (&newfork, NULL);

	for (i = 0; i < TABLE; i++)
		pthread_mutex_init (&(forks[i]), NULL);
	for (i = 0; i < TABLE; i++)
		pthread_create (&p[i], NULL, philosopher, (void *)i);
	for (i = 0; i < TABLE; i++)
		pthread_join (p[i], NULL);
	printf ("Anyone for seconds?\n");
	fifoDelete (queue);
	return 0;
}

void *philosopher (void *num)
{
	int id;
	int i;
	pthread_mutex_t dummy = PTHREAD_MUTEX_INITIALIZER;

	id = (int)num;
	pthread_mutex_lock (&dummy);
	printf ("Philosopher %d sitting down to dinner.\n", id);
	for (i = 0; i < 2; i++) {
		fifoLock (queue, &dummy, id);
		usleep (4 * DELAY);
		fifoUnlock (queue, id);
	}
	for (i = 0; i < DISHES; i++) {
		while (1) {
			printf ("Philosopher %d Starting course %d.\n", id, i);
			fifoLock (queue, &dummy, id);
			if (pthread_mutex_trylock (&(forks[(id+1)%TABLE]))
			    == EBUSY) {
				printf ("Philosopher %d : fork %d taken.\n"
				    , id, (id+1)%TABLE);
				fifoUnlock (queue, id);
				continue;
			}
			printf ("Philosopher %d got fork %d.\n", id,
			    (id+1)%TABLE);
			if (pthread_mutex_trylock (&(forks[id])) == EBUSY) {
				printf ("Philosopher %d : fork %d taken.\n"
				    , id, id);
				pthread_mutex_unlock (&(forks[(id+1)%TABLE]));
				printf ("Philosopher %d returned fork %d.\n"
				    , id, (id+1)%TABLE);
				fifoUnlock (queue, id);
				continue;
			}
			printf ("Philosopher %d got fork %d.\n", id, id);
			printf ("Philosopher %d eating course %d, YUM.\n"
			    , id, i);
			usleep (DELAY * i);
			pthread_mutex_unlock (&(forks[id]));
			pthread_mutex_unlock (&(forks[(id+1)%TABLE]));
			printf ("Philosopher %d returned forks %d and %d.\n"
			    , id, id, (id+1)%TABLE);
			fifoUnlock (queue, id);
			break;
		}
		printf ("Philosopher %d finished course %d.\n", id, i);
	}
	printf ("Philosopher %d finished MEAL.\n", id);
	pthread_mutex_unlock (&dummy);
	pthread_mutex_destroy (&dummy);

	return (NULL);
}

fifo *fifoInit (int runmax)
{
	fifo *q;

	q = (fifo *)malloc (sizeof (fifo));
	if (q == NULL) return (NULL);
	q->mut = (pthread_mutex_t *)malloc (sizeof (pthread_mutex_t));
	if (q->mut == NULL) { free (q); return (NULL); }
	pthread_mutex_init (q->mut, NULL);

	q->runmax = runmax;
	q->head = NULL;
	q->tail = NULL;
	q->size = 0;

	return (q);
}

void fifoDelete (fifo *q)
{
	if (q->head != NULL) {
		printf ("fifoDelete: Things that make you say mmmmm.\n");
		exit (1);
	}
	pthread_mutex_destroy (q->mut);
	free (q->mut);
	free (q);

	return;
}

void fifoLock (fifo *q, pthread_mutex_t *mut, int id)
{
	node *new;

	pthread_mutex_lock (q->mut);
	q->size++;
fprintf (stderr, "Lock %d : size = %d\n", id, q->size);
	if (q->size > q->runmax) {
		new = (node *)malloc (sizeof (node));
		if (new == NULL) {
			printf ("fifoLock: malloc failed.\n");
			exit (1);
		}
		pthread_cond_init (&(new->sleep), NULL);
		new->next = NULL;
		if (q->tail == NULL) {
			q->head = q->tail = new;
		} else {
			q->tail->next = new;
			q->tail = new;
		}
		pthread_mutex_unlock (mut);
fprintf (stderr, "%d Blocked.\n", id);
		pthread_cond_wait (&(new->sleep), q->mut);
		pthread_mutex_unlock (q->mut);
		pthread_mutex_lock (mut);
fprintf (stderr, "%d Woken.\n", id);
	} else {
		pthread_mutex_unlock (q->mut);
	}

	return;
}

void fifoUnlock (fifo *q, int id)
{
	node *old;

	pthread_mutex_lock (q->mut);
	q->size--;
fprintf (stderr, "Unlock : %d size = %d\n", id, q->size);
	if (q->head != NULL) {
		old = q->head;
		q->head = old->next;
		if (q->head == NULL) {
			q->tail = NULL;
		}
		old->next = NULL;
fprintf (stderr, "%d Waking head.\n", id);
		pthread_cond_signal (&(old->sleep));
	}
	pthread_mutex_unlock (q->mut);

	return;
}

