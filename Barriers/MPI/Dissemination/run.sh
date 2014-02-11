#mpirun -mca btl tcp,self --hostfile mpd.hosts $1
make clean;
make;
mpirun -n 9  --hostfile mpd.hosts ./test;
