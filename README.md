# Philosophers

An implementation of the classic problem of synchronizing multiple threads
or processes. You can use [philosophers tester](https://github.com/ytkimirti/philosophers-tester) python script to check for delays etc.

```
$ ./philo
Error: Argument count does not match
./philo philo_count time_to_die time_to_eat time_to_sleep [must_eat_count]
$ ./philo 2 3000 150 150 2
1678542363951 1 has taken a fork
1678542363951 1 has taken a fork
1678542363951 1 is eating
1678542364101 1 is sleeping
1678542364101 2 has taken a fork
1678542364101 2 has taken a fork
1678542364101 2 is eating
1678542364251 2 is sleeping
1678542364251 1 is thinking
1678542364251 1 has taken a fork
1678542364251 1 has taken a fork
1678542364251 1 is eating
1678542364401 2 is thinking
1678542364401 2 has taken a fork
1678542364401 2 has taken a fork
1678542364401 2 is eating
```

The analyzed version

```
$ ./philo 2 3000 150 150 2 | python3 ../../philosophers-tester/analyze.py 2 3000 150 150
Reading lines from stdin
===== philosopher: 1 =====
has taken a fork
has taken a fork
is eating
Wait 150ms
is sleeping
Wait 150ms
is thinking
has taken a fork
has taken a fork
is eating
===== philosopher: 2 =====
Wait 150ms
has taken a fork
has taken a fork
is eating
Wait 150ms
is sleeping
Wait 150ms
is thinking
has taken a fork
has taken a fork
is eating
```
