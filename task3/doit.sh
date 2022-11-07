# cleanup
rm -rf obj_dir
rm -f  sigdelay.vcd

# run verilator
verilator -Wall --cc --trace sigdelay.sv --exe sigdelay_tb.cpp

# built project
make -j -C obj_dir/ -f Vsigdelay.mk Vsigdelay

# run executeable
./obj_dir/Vsigdelay
