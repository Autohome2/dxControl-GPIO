#ifndef AUX_H
#define AUX_H

void driveOutputs();
void outputaction(uint8_t chanX);
void initialOutputs();
void blinkCEL();

  bool state;
  uint8_t portX;

#define EDITOR_COND_1             0
#define EDITOR_COND_2             1
#define EDITOR_COND_3             2
#define EDITOR_LINK_COND_1        3
#define EDITOR_LINK_COND_2        4

#endif
