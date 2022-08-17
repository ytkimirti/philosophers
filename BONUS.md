
There are two philosophers.
They eat for 100ms
They die after 120ms
They sleep for 60ms
There shouldn't be a delay more than 50ms

At first p1 takes the forks.

120HP	p1 F1 F2
120HP	p2 Waiting for F1...

After 100ms...

120HP	p1 Sleeping for 60ms...
 20HP	p2 F1 F2

After 20ms...

100HP	p1 Sleeping for 40ms...
  0HP	p2 Dead!

We should somehow use other processes to keep track of
whether they are dead or not. But since they can't share
memory, there has to be another way.

If we had the threads send *something* when they died, that
wouldn't work in a case like this.

  5HP	p1 Waiting for F1...
120HP	p2 F1 F2 *started now*

  0HP	p1 Died! (0ms passed)
115HP	p2 F1 F2 

  0HP	p1 Died! (50ms passed) **KO!**
 95HP	p2 F1 F2

When p1 dies, it would be still waiting for the forks, since
the main thread of p1's process would be blocked.

But what if p1 had another thread, since they share the
memory, the thread can check if it's parent is dead or not.

```
            |
            O____________________________
            |							|
            |							|
  0ms     philo						   child
            |							|
            |							|
  5ms       |<--------------------------O
            | check	   	   	   	   	  	|
            |	                        |
  10ms      |<--------------------------O
            | check	   	   	   	   	  	|
            |	                        |
  15ms      |<--------------------------O
            | check	   	   	   	   	  	|
            |	                        |
  20ms      |<--------------------------O
            | dead (write to stdout)    |
            |                           X	child commits
  ...       |                               suicide
            | asd
            |
  100ms     O   p2 takes a fork
            |
  100ms     X 	p2 sees it's dead, gives
              forks back, terminates.
```

So after starting the philosopher's process, every
philosopher will open a thread for itself.

That thread will check the `last_eat_time` variable of the
parent every 5ms and will write the death message to stdout
and return.

The parent waits for forks, eats and sleeps as usual, but
there is a check everytime;
- before it takes a fork
- after it takes a fork
- every sleep cycle
that checks if it's dead or reached the max eating count.

If check succeeds, the process terminates.

---

But there is another problem. Let's say

```
      |               |
      X p1 dies       |
                      |
                      |
                      |
                      |
                      O p2 finished eating
                      |

```

So other processes continue printing stuff even
tho one of the philosophers is dead.

Since processes can't communicate with each other or the
main process, you have to use semaphores. But you can't just
read the current value of a semaphore because the function
`sem_getvalue()` is not allowed.

Maybe you can have a semaphore called `closing`. And main
process can wait for it. When a philosopher dies, it can
post to this semaphore.

So after that the main process can just call `kill` on all
of the processes. Before doing so it would wait for the
`sem_writing` to not interfere with stdout.

The problem with this approach is this would still happen.
It would happen for once but it would still happen.

```
             Main process                    
                  |                              
      p1          |						  p2                       
      ------------|------------------------                   
      |           |						  |                      
      |           O	waits for			  |                      
      |           |	sem_closing  		  |                      
      |           |						  |                      
      |           |						  |                      
      X p1 dies   |						  |                      
                  |						  |                      
                  X						  |                      
                  |						  |                      
                  |						  |                      
                  |						  O p2 finished eating   
                  |						  |                      

```











