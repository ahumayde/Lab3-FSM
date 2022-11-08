# cleanup
rm -rf obj_dir
rm -f  lfsr.vcd

# run verilator
verilator -Wall --cc --trace lfsr.sv --exe lfsr_tb.cpp

# built project
make -j -C obj_dir/ -f Vlfsr.mk Vlfsr

# run executeable
./obj_dir/Vlfsr
