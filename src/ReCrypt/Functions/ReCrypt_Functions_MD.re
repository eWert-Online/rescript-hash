let rotl = (x, n) => {
  x lsl n lor x lsr (64 - n);
};
