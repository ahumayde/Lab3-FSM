module f1_fsm #(
    parameter size = 8
)(
    input  logic            clk,
    input  logic            rst,
    input  logic            en,
    input  logic            trigger,
    output logic            cmd_seq,
    output logic            cmd_delay,
    output logic [size-1:0] dout
);

typedef enum {IDLE,S0,S1,S2,S3,S4,S5,S6,S7,S8} state;
state curr_state, next_state;

always_ff @(posedge clk)
    if (rst) curr_state <= S0;
    else     curr_state <= next_state;

always_comb
    if (en | trigger)
        case (curr_state)
            IDLE:    next_state = S0:
            S0:      next_state = S1; 
            S1:      next_state = S2;
            S3:      next_state = S4;
            S2:      next_state = S3; 
            S4:      next_state = S5; 
            S5:      next_state = S6; 
            S6:      next_state = S7; 
            S7:      next_state = S8;
            S8:      next_state = IDLE;
            default: next_state = S0; 
        endcase
    else
        next_state = curr_state;

always_comb
    begin
        cmd_seq   = (curr_state == S8 || curr_state == S0) ? 1'b0 : 1'b1;
        cmd_delay = (curr_state == S8);
        case (curr_state)
            IDLE:    dout = 8'b0;
            S0:      dout = 8'b0;     
            S1:      dout = 8'b1;        
            S2:      dout = 8'b11;       
            S3:      dout = 8'b111;      
            S4:      dout = 8'b1111;     
            S5:      dout = 8'b11111;    
            S6:      dout = 8'b111111;   
            S7:      dout = 8'b1111111;  
            S8:      dout = 8'b11111111; 
            default: dout = 8'b0;
        endcase
    end

endmodule
