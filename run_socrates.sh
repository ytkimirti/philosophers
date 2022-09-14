# Cd to the script directory
cd "${0%/*}"

make -j8 -C philo_bonus
make -j8 -C philo
python3 socrates/socrates.py . $1 $2 $3 $4
