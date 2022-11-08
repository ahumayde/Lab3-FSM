# cleanup
rm -rf obj_dir
rm -f  f1_fsm.vcd

# run verilator
verilator -Wall --cc --trace f1_fsm.sv --exe f1_fsm_tb.cpp

# built project
make -j -C obj_dir/ -f Vf1_fsm.mk Vf1_fsm

# run executeable
./obj_dir/Vf1_fsm
