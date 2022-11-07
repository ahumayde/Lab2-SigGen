module counter #(
    parameter WIDTH = 8
)(
    input  logic clk,
    input  logic rst,
    input  logic en,
    input  logic [WIDTH-1:0] incr,
    output logic [WIDTH-1:0] count,
    output logic [WIDTH-1:0] count2
);

always_ff @(posedge clk)
    if (rst)        count <= {WIDTH{1'b0}};
    else 
        begin
            count  <= count +  {{WIDTH-1{1'b0}},en};
            count2 <= count + 2*{incr};
        end

endmodule
