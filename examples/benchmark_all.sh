# $1: timeout

if [ $# -le 0 ]; then
	to=300
else
	to=$2
fi

cd benchmarks
for instance in *.mcsie
do
	echo "
		Executable = ../benchmark_single.sh
		Universe = vanilla
		output = $instance.out
		error = $instance.error
		Log = $instance.log
		Requirements = machine == "node3.kr.tuwien.ac.at"
		request_memory = 4096 
		Initialdir = /mnt/lion/home/redl/hexhex_dlvhex/mcsieplugin/examples/benchmarks/
		notification = never

		# queue
		request_cpus = 1 
		Arguments = $instance $to
		Queue 1
	     " > p.job
	condor_submit p.job
#	./../benchmark_single.sh $instance $to
done

