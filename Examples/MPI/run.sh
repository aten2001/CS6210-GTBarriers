#mpirun -mca btl tcp,self --hostfile mpd.hosts $1
mpirun -n 4  --hostfile mpd.hosts $1
