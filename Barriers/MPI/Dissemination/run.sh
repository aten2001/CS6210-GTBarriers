#mpirun -mca btl tcp,self --hostfile mpd.hosts $1
make clean;
make;
mpirun -n 3  --hostfile mpd.hosts ./test;
