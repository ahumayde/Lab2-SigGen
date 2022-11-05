# cleanup
rm -rf obj_dir
rm -f  sinegen.vcd

# run verilator
verilator -Wall --cc --trace sinegen.sv --exe sinegen_tb.cpp

# built project
make -j -C obj_dir/ -f Vsinegen.mk Vsinegen

# run executeable
./obj_dir/Vsinegen
