#!/bin/bash

runheader=$(which run_header.sh)
if [[ $runheader == "" ]] || [ $(cat $runheader | grep "run_header.sh Version 1." | wc -l) == 0 ]; then
        echo "Could not find run_header.sh (version 1.x); make sure that the benchmark scripts directory is in your PATH"
        exit 1
fi
source $runheader

# run instances
cd instances
if [[ $all -eq 1 ]]; then
	# run all instances using the benchmark script run insts
	$bmscripts/runinsts.sh "*.mcsie" "$mydir/run.sh" "$mydir/instances" "$to" "" "" "$req"
else
	# run single instance
	confstr="--flpcheck=explicit --extlearn=none --flpcriterion=head;--flpcheck=explicit --extlearn --flpcriterion=head;--flpcheck=ufsm --extlearn=none --ufslearn=none --flpcriterion=head;--flpcheck=ufsm --extlearn --ufslearn=none --flpcriterion=head;--flpcheck=ufsm --extlearn --ufslearn --flpcriterion=head;--flpcheck=ufs --extlearn=none --ufslearn=none;--flpcheck=ufs --extlearn --ufslearn=none;--flpcheck=ufs --extlearn --ufslearn;--flpcheck=aufs --extlearn=none;--flpcheck=aufs --extlearn --ufslearn=none;--flpcheck=aufs --extlearn --ufslearn;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=periodic;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=max;--flpcheck=explicit --extlearn=none --flpcriterion=head -n=1;--flpcheck=explicit --extlearn --flpcriterion=head -n=1;--flpcheck=ufsm --extlearn=none --ufslearn=none -n=1;--flpcheck=ufsm --extlearn --ufslearn=none --flpcriterion=head -n=1;--flpcheck=ufsm --extlearn --ufslearn --flpcriterion=head -n=1;--flpcheck=ufs --extlearn=none --ufslearn=none -n=1;--flpcheck=ufs --extlearn --ufslearn=none -n=1;--flpcheck=ufs --extlearn --ufslearn -n=1;--flpcheck=aufs --extlearn=none --ufslearn=none -n=1;--flpcheck=aufs --extlearn --ufslearn=none -n=1;--flpcheck=aufs --extlearn --ufslearn --ufslearn=none -n=1;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=periodic -n=1;--flpcheck=aufs --extlearn --ufslearn --ufscheckheuristics=max -n=1"

	$bmscripts/runconfigs.sh "dlvhex2 --claspconfig=none --plugindir=../../../src/.libs --ieenable --iemode=expl --ieexplain=E CONF INST" "$confstr" "$instance" "$to"
fi

