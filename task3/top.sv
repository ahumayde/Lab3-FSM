module top #(
    parameter Nsize = 16,
    parameter Dsize = 8
)(
    input  logic             clk,
    input  logic             rst,
    input  logic             en,
    input  logic [Nsize-1:0] N,
    output logic [Dsize-1:0] dout
);

logic tick;

clktick timer(
    .clk  (clk),
    .rst  (rst),
    .en   (en),
    .N    (N),
    .tick (tick)
);

f1_fsm fsm(
    .clk(clk),
    .rst(rst),
    .en(tick),
    .dout(dout)
);

endmodule;

