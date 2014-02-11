#mpirun -mca btl tcp,self --hostfile mpd.hosts $1
make clean;
make;
mpirun -n 4  --hostfile mpd.hosts ./test;
