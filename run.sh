

#!/bin/bash


		file_out=resultados.txt


		echo "INICIANDO \c" >> $file_out
		date >> $file_out


		hwloc-bind socket:0.pu:1 ./p >> $file_out


		echo "FINALIZANDO \c" >> $file_out
		date >> $file_out


