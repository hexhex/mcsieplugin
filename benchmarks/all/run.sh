#!/bin/bash

source dlvhex_run_header.sh

# run instances
cd instances
if [[ $all -eq 1 ]]; then
	# run all instances using the benchmark script run insts
	$bmscripts/runinsts.sh "*.mcsie" "$mydir/run.sh" "$mydir/instances" "$to"
else
	# run single instance
	confstr="--flpcheck=explicit --flpcriterion=head;--flpcheck=explicit --extlearn --flpcriterion=head;--flpcheck=ufsm --flpcriterion=head;--flpcheck=ufsm --extlearn --flpcriterion=head;--flpcheck=ufsm --extlearn --ufslearn --flpcriterion=head;--flpcheck=ufs;--flpcheck=ufs --extlearn;--flpcheck=ufs --extlearn --ufslearn;--flpcheck=aufs;--flpcheck=aufs --extlearn;--flpcheck=aufs --extlearn --ufslearn;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=periodic;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=max;--flpcheck=explicit --flpcriterion=head -n=1;--flpcheck=explicit --extlearn --flpcriterion=head -n=1;--flpcheck=ufsm -n=1;--flpcheck=ufsm --extlearn --flpcriterion=head -n=1;--flpcheck=ufsm --extlearn --ufslearn --flpcriterion=head -n=1;--flpcheck=ufs -n=1;--flpcheck=ufs --extlearn -n=1;--flpcheck=ufs --extlearn --ufslearn -n=1;--flpcheck=aufs -n=1;--flpcheck=aufs --extlearn -n=1;--flpcheck=aufs --extlearn --ufslearn -n=1;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=periodic -n=1;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=max -n=1"

	$bmscripts/runconfigs.sh "dlvhex2 --claspconfig=none --plugindir=../../../src/.libs --ieenable --iemode=expl --ieexplain=E CONF INST" "$confstr" "$instance" "$to"
fi

