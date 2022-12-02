module lfsr #(
    parameter WIDTH = 7
)(
    input  logic             clk,
    output logic [WIDTH:1]   dout
);

logic [WIDTH:1] sreg = {{WIDTH-1{1'b0}},1'b1};

always_ff @(posedge clk)
    sreg <= {sreg[WIDTH-1:1],(sreg[WIDTH]^sreg[WIDTH-4])};

assign dout = sreg;

endmodule
