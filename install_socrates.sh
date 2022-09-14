# Cd to the script directory
cd "${0%/*}"

if [ -d socrates ]; then
	exit
fi

git clone https://github.com/nesvoboda/socrates
cd socrates
python3 -m pip install -r requirements.txt --user
