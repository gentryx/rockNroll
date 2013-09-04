#!/bin/bash
#$ -l s_cpu=24:00:00
#$ -l s_rt=24:00:00
#$ -l s_vmem=1024M 
time ./tournament $1 $2 $3
