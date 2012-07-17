confstr="--solver=genuinegc --flpcheck=ufs;--solver=genuinegc --flpcheck=none"
IFS=';' read -ra confs <<< "$confstr"
header="#size"
i=0
for c in "${confs[@]}"
do
	timeout[$i]=0
	header="$header   \"$c\""
	let i=i+1
done
echo $header

# for all argu files
cd benchmarks
for instance in *.mcsie
do
	echo -ne $instance

	# for all configurations
	for c in "${confs[@]}"
	do
		echo -ne -e " "
		output=$(timeout 300 dlvhex2 $c --plugindir=../../src/.libs --ieenable --iemode=expl --ieexplain=E $instance --silent | wc -l)
		if [[ $? == 124 ]]; then
			output="---"
		fi
		echo -ne $output

		# make sure that there are no zombies
		pkill -9 -u $USER dlvhex2
		pkill -9 -u $USER dlv
	done
	echo -e -ne "\n"
done
cd ..
