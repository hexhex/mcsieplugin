#!/bin/bash

source dlvhex_run_header.sh

# run instances
cd instances
if [[ $all -eq 1 ]]; then
	# run all instances using the benchmark script run insts
	$bmscripts/runinsts.sh "*.mcsie" "$mydir/run.sh" "$mydir/instances" "$to"
else
	# run single instance
	confstr=";--extlearn;--welljustified;-n=1;--extlearn -n=1;--welljustified -n=1"

	$bmscripts/runconfigs.sh "dlvhex2 --claspconfig=none --plugindir=../../../src/.libs --ieenable --iemode=expl --ieexplain=E CONF INST" "$confstr" "$instance" "$to"
fi

