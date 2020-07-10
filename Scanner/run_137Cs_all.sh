#!/bin/bash
source ~/.bash_profile 
COUNTER=0

while [ $COUNTER -lt 6 ]
do
#	g4simple run_scanner30_137Cs.mac;
#	mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/30deg/raw/scanner_137Cs_30deg_0p5mm15mmEA18_temp.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/30deg/raw/scanner_137Cs_30deg_0p5mm15mmEA18_$COUNTER.root 
#	/Users/jgruszko/Dev/g4simple/Example/rootPostProc/postprocroot_wDead_wPSA /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/30deg/raw/scanner_137Cs_30deg_0p5mm15mmEA18_$COUNTER.root 
#        mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/30deg/raw/scanner_137Cs_30deg_0p5mm15mmEA18_$COUNTER_processed_wPSA.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/30deg/processed/scanner_137Cs_30deg_0p5mm15mmEA18_$COUNTER_processed.root 

#	g4simple run_scanner45_137Cs.mac;
#	mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/45deg/raw/scanner_137Cs_45deg_0p5mm15mmEA18_temp.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/45deg/raw/scanner_137Cs_45deg_0p5mm15mmEA18_$COUNTER.root 
#	/Users/jgruszko/Dev/g4simple/Example/rootPostProc/postprocroot_wDead_wPSA /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/45deg/raw/scanner_137Cs_45deg_0p5mm15mmEA18_$COUNTER.root 
#        mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/45deg/raw/scanner_137Cs_45deg_0p5mm15mmEA18_$COUNTER_processed_wPSA.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/45deg/processed/scanner_137Cs_45deg_0p5mm15mmEA18_$COUNTER_processed.root 

	g4simple run_scanner90_137Cs.mac;
	mv  /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/90deg/raw/scanner_137Cs_90deg_0p5mm15mmEA18_realisticSource_temp.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/90deg/raw/scanner_137Cs_90deg_0p5mm15mmEA18_realisticSource_$COUNTER.root 
	/Users/jgruszko/Dev/g4simple/Example/rootPostProc/postprocroot_wDead_wPSA /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/90deg/raw/scanner_137Cs_90deg_0p5mm15mmEA18_realisticSource_$COUNTER.root 
        mv /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/90deg/raw/scanner_137Cs_90deg_0p5mm15mmEA18_realisticSource_$COUNTER\_processed_wPSA.root /Users/jgruszko/Data/LEGEND/SURF_Scanner/sims/WCollimator/0p5mm15mmEA18/137Cs/90deg/processed/scanner_137Cs_90deg_0p5mm15mmEA18_realisticSource_$COUNTER\_processed.root 

	let COUNTER=COUNTER+1
done

