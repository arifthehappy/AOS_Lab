#!/bin/bash

#log file
log_file="killLog.csv"

#get time
getTime(){
	echo $(date)
}

#kill process having higher resource utilization
killProcessByCpuUtil(){
	while true;
	do
		process_list=$(ps -eo pid,%cpu,comm --sort=-%cpu --no-headers)
		
		#echo "$process_list"
		
		while read -r pid cpu_usage process_name;
		do
			echo "$cpu_usage > 50" | bc -l
			if (( $(echo "$cpu_usage > 50" | bc -l) ));
			then
				#log
				endtime=$(getTime)
				echo "$pid, $endtime, $cpu_usage%" >> "$log_file"
			
				#kill
				echo "process $pid ($process_name) with cpu usage $cpu_usage killed"
				kill -9 "$pid"
			fi
		done <<< "$process_list"
		
		sleep 5
	done
}

if [ ! -f "$log_file" ];
then
	echo "PID, End_Time, Cpu_Utilized" > "$log_file"
fi

killProcessByCpuUtil
	
			 
		
		
		
		
		
