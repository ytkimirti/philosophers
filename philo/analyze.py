import sys
import subprocess
import os
import enum

BINARY = "./philo"
    

RST      = '\33[0m'
GRY    = '\33[90m'
BRED    = '\33[91m'
BGRN  = '\33[92m'
BYEL = '\33[93m'
BBLU   = '\33[94m'
BMAG = '\33[95m'
BBEI  = '\33[96m'
BWHT  = '\33[97m'

CBOLD     = '\33[1m'
CITALIC   = '\33[3m'
CURL      = '\33[4m'
CBLINK    = '\33[5m'
CBLINK2   = '\33[6m'
CSELECTED = '\33[7m'

def print_help():
    print("""
        Usage:
        python3 analyze.py count death_time sleep_time eat_time [eat_count]

        NOTE:
        Executing the python file will attempt to execute the binary named ./philo
        in the current directory.
            
        You can also pipe the output of your philo command to this like shown.
        ./philo 2 300 150 150 | python analyze.py 2 300 150 150
        """)

if "--help" in sys.argv or "-h" in sys.argv:
    print_help()

lines = None

args = sys.argv[1:]

if len(args) > 5 or len(args) < 4:
    print_help()
    sys.exit(1)

if not os.isatty(0):
    print(f"{BBLU}Reading lines from stdin{RST}")
    lines = []
    for line in sys.stdin:
        lines.append(line)
else:
    has_args = True
    print(f"{BBLU}Executing binary ./philo{RST}")
    p = subprocess.Popen([BINARY, *args], stdout=subprocess.PIPE)
    out, err = p.communicate()
    out = out.decode("utf-8") 
    if p.returncode != 0:
        print(out)
        print(f"{BRED}{BINARY} exited with code {p.returncode}{RST}")
        sys.exit(1)
    lines = out.split('\n')


[philo_count, death_time, sleep_time, eat_time] = args[0:4]
max_eat_count = None
if len(args) == 5:
    max_eat_count = int(args[4])
eat_time = int(eat_time)
sleep_time = int(sleep_time)
death_time = int(death_time)
philo_count = int(philo_count)

data = {}

for line in lines:
    if not line:
        continue
    [time, id, *msg] = line.split()
    msg = ' '.join(msg)

    time = int(time)
    id = int(id)
    if id not in data:
        data[id] = []
    data[id].append((time, msg))

min_time = None
for id, lines in data.items():
    for (time, msg) in lines:
        if not min_time or time < min_time:
            min_time = time

encountered_error = False

def print_error(str):
    global encountered_error
    encountered_error = True
    print(f"\t{BRED}{str}{RST}")

def find_message_type(str):
    if str.find("think") != -1:
        return "think"
    elif str.find("sleep") != -1:
        return "sleep"
    elif str.find("eat") != -1:
        return "eat"
    elif str.find("fork") != -1:
        return "fork"
    elif str.find("die") != -1:
        return "die"
    else:
        print_error(f"Couldn't figure out what '{str}' means. Please use 'think' 'sleep' 'eat' or 'die' in your messages")

for id, lines in data.items():

    if id <= 0 or id > philo_count:
        print_error(f"Philosopher with id {id} doesn't exist!")
        continue

    last_time = None
    last_msg = None
    last_msg_type = None
    last_eat_time = None
    curr_fork = 0
    print(f"===== {BGRN}philosopher: {id}{RST} =====")
    for i, (time, msg) in enumerate(lines):
        if not last_eat_time:
            last_eat_time = time
        if i == 0 and time - min_time > 0:
            print(f"{BYEL}Wait {time - min_time}ms{RST}")
        diff_time = 0
        if last_time is not None:
            diff_time = time - last_time
        if diff_time > 0:
            print(f"{BYEL}Wait {diff_time}ms{RST}")

        msg_type = find_message_type(msg)

        # print("Type is", BGRN, msg_type, RST)

        # Check for order
        if msg_type == "fork":
            curr_fork += 1;
        elif msg_type == "eat":
            if curr_fork != 2:
                print_error(f"Philo currently has {curr_fork} fork but needs 2 forks to eat")
            last_eat_time = time
        elif msg_type == "sleep":
            if diff_time < sleep_time:
                print_error(f"Philo should wait for at least {eat_time}ms before sleeping but it only waited for {diff_time}ms")
            if last_msg_type != "eat":
                print_error(f"Philo should first eat to sleep")
            curr_fork = 0
        elif msg_type == "die":
            eat_diff = time - last_eat_time
            die_latency = eat_diff - death_time
            if die_latency > 10:
                print_error(f"Philo died after {eat_diff}ms and death_time was {death_time}ms.\n\tSo latency of death is {die_latency} which is bigger than 10ms!")
    
        print(f"{msg}")
        last_time = time
        last_msg = msg
        last_msg_type = msg_type

if encountered_error:
    print(f"{BRED}** Encountered errors, exiting with 1 **{RST}")
    sys.exit(1)
