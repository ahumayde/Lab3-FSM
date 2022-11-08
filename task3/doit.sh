# cleanup
rm -rf obj_dir
rm -f  top.vcd

# run verilator
verilator -Wall --cc --trace top.sv --exe top_tb.cpp

# built project
make -j -C obj_dir/ -f Vtop.mk Vtop

# run executeable
./obj_dir/Vtop
