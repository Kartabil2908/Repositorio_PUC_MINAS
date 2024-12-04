module circuit (
    input a, b, c, d,
    output Da, Db, Dc, Ta, Tb, Tc
);
    assign Da = (~b & c & d) | (a & ~b & c & ~d) | (a & b & ~c & d);

    assign Db = (a | b | c | d) & (a | b | c | ~d) & (a | b | ~c | d) & (a | ~b | c | d) & (~a | b | c | d) & (~a | ~b | c | d) & (~a | ~b | ~c | ~d);

    assign Dc = (~a & b & c) | (a & ~b & c) | (a & ~b & ~c & d) | (a & b & ~c & d) | (a & b & c);

    assign Ta = Da;  // O mesmo de Da
    assign Tb = Db;  // O mesmo de Db
    assign Tc = Dc;  // O mesmo de Dc
    
endmodule
