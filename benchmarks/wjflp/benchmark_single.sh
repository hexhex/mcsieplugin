# $1: instance
# $2: timeout
export PATH=$1
export LD_LIBRARY_PATH=$2
instance=$3
to=$4

confstr=";--extlearn;--welljustified;-n=1;--extlearn -n=1;--welljustified -n=1"
confstr2=$(cat ../conf)
if [ $? == 0 ]; then
        confstr=$confstr2
fi

# split configurations
IFS=';' read -ra confs <<< "$confstr"
header="#size"
i=0
for c in "${confs[@]}"
do
	header="$header   \"$c\""
	let i=i+1
done
echo $header

# do benchmark
echo -ne "$instance"

# for all configurations
i=0
for c in "${confs[@]}"
do
	echo -ne -e " "
	cmd="timeout $to time -o $instance.time.dat -f %e dlvhex2 $c --plugindir=../../../src/.libs --ieenable --iemode=expl --ieexplain=E $instance"
	$($cmd 2>/dev/null >/dev/null)
	ret=$?
	output=$(cat $instance.time.dat)
	if [[ $ret == 124 ]]; then
		output="---"
	fi
	rm $instance.time.dat
	echo -ne $output
	let i=i+1
done
echo -e -ne "\n"
