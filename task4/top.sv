module top #(
    parameter Nsize = 6,
    parameter Ksize = 7,
    parameter Dsize = 8
)(
    input  logic             clk, 
    input  logic             rst,  
    input  logic             trigger, //vbdFlag()
    input  logic [Nsize-1:0] N,       // vbdValue()
    output logic [Dsize-1:0] dout
);

logic [Ksize-1:0] K;
logic tick;
logic time_out;
logic fsm_en;
logic cmd_delay;
logic cmd_seq;

lfsr shift(
    .clk  (clk),
    .dout (K)
);

delay delay(
    .clk      (clk),
    .rst      (rst),
    .trigger  (cmd_delay),
    .K        (K),
    .time_out (time_out)
);

clktick timer(
    .clk  (clk),
    .rst  (rst),
    .en   (cmd_seq),
    .N    (N),
    .tick (tick)
);

always_comb
    fsm_en = cmd_seq ? tick : time_out;

f1_fsm fsm(
    .clk (clk),
    .rst(rst),
    .en(fsm_en),
    .trigger (trigger),
    .cmd_delay(cmd_delay),
    .cmd_seq(cmd_seq),
    .dout (dout)
);

endmodule
