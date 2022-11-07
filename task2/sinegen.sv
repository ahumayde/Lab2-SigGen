module sinegen #(
    parameter A_WIDTH = 8,
              D_WIDTH = 8
)(
    input  logic clk,
    input  logic rst,
    input  logic en,
    input  logic [A_WIDTH-1:0] incr,
    output logic [D_WIDTH-1:0] dout,
    output logic [D_WIDTH-1:0] dout2
);

    logic [A_WIDTH-1:0] addr;
    logic [A_WIDTH-1:0] addr2;

counter counter (
    .clk    (clk),
    .rst    (rst),
    .en     (en),
    .incr   (incr),
    .count  (addr),
    .count2 (addr2)
);

rom rom (
    .clk   (clk),
    .addr  (addr),
    .addr2 (addr2),
    .dout  (dout),
    .dout2 (dout2)
);

endmodule
