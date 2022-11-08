module lfsr #(
    parameter WIDTH = 4
)(
    input  logic             clk,
    input  logic             rst,
    input  logic             en,
    output logic [WIDTH:1]   dout
);

logic [WIDTH:1] sreg = {{WIDTH-1{1'b0}},1'b1};

always_ff @(posedge clk, posedge rst)
    if (rst)       
        sreg <= {WIDTH{1'b1}};
    else if (en)
        sreg <= {sreg[WIDTH-1:1],(sreg[WIDTH]^sreg[WIDTH-1])};

assign dout = sreg;

endmodule
