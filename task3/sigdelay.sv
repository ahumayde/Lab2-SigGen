module sigdelay #(
    parameter   A_WIDTH = 8,
                D_WIDTH = 8
)(
    input  logic               clk,
    input  logic               rst,
    input  logic               en,
    input  logic [D_WIDTH-1:0] off,
    input  logic [D_WIDTH-1:0] signal,
    output logic [D_WIDTH-1:0] dout
);

logic [A_WIDTH-1:0] wr_addr;
logic [A_WIDTH-1:0] rd_addr;

counter counter(
    .clk    (clk),
    .rst    (rst),
    .en     (en),
    .incr   (off),
    .count  (wr_addr),
    .count2 (rd_addr)
);

ram ram(
    .clk     (clk),
    .wr_en   (en),
    .rd_en   (en),
    .wr_addr (wr_addr),
    .rd_addr (rd_addr),
    .din     (signal),
    .dout    (dout)
);

endmodule
