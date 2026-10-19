This project answers the question of: How can multiple programmers share limited equipment without interfeering with each other or running out of time?

USB dongle: Is a physical device that connects to the computers USB port. In Codexion a USB dongle is a special tool that a programmer needs to perform work. Several programmers may need it, but they cannot use the same dongle simultaneously.

POSIX threads: A thread is a separate path of execution inside the same program. POSIX is a standart defining operating system interfaces.

Mutexes: a mutual exclusion locks the dongle so that the other programmer cannot use it simultaneously.

FIFO: First in first out, whoever requested the dongle first gets served first.

EDF: Earliest Deadline First: Whoever has the closest deadline gets priority.

Concurrency: means multiple tasks can progress during overlapping periods.

Syncronisation: Means coordinating those tasks so that they dont corrupt shared state or interfeere with one another.

Deadlock: happens when threads are permanently blocked because theyre waiting for resources that cannot become available. Deadlock specifically involves a waiting situation that prevents progress.

Argument Example Meaning
number_of_coders 5 Five coder threads, five dongles
time_to_burnout 800 Burnout deadline interval, in ms
time_to_compile 200 Compile for 200 ms
time_to_debug 200 Debug for 200 ms
time_to_refactor 100 Refactor for 100 ms
number_of_compiles_required 3 Each coder must compile 3 times
dongle_cooldown 50 Released dongles unavailable for 50 ms
scheduler fifo Serve requests in arrival order

typedef struct s_request
{
int coder_id;
long long request_time;
long long deadline;
unsigned long arrival_order;
} t_request;
Member Type Purpose
coder_id int Which coder made the request
request_time long long When the request was made, in milliseconds
deadline long long The coder's burnout deadline
arrival_order unsigned long A sequence number to distinguish requests arriving in the same millisecond

An enum is a C type that defines a set of named integer constants.

typedef struct s_heap
{
t_request \*items;
int size;
int capacity;
t_scheduler scheduler;
} t_heap;

Let's understand the members:
Member Purpose
items Pointer to an array of coder requests
size Number of requests currently stored
capacity Maximum number of requests the allocated array can hold
scheduler FIFO or EDF scheduling policy
