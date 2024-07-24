#define __SFR_OFFSET 0
#include "avr/io.h"

.global start
.global temperature
.global increaseSpeed
.global decreaseSpeed

initDutyCycle = 127 ; duty cycle will start at 50%
maxDutyCycle = 255 ; 100% max 
minDutyCycle = 64 ; 25 % min

start: ; initialize pulse width modulator and temperature analog to digital converter
  CALL initPWM
  CALL initTemperature
  RET

initPWM: ; initialize PWM, controls power to fan
  LDS R23, 0x02FF
  SBI DDRG, 5 ; initializes pwm output port
  LDI R16, 0b00100011 ; fast PWM mode
  OUT TCCR0A, R16 ; non-inverting
  LDI R16, 0b00000101 ; prescaler
  OUT TCCR0B, R16 ; clkIO/256/1024(100101) being prescaled
  LDI R23, initDutyCycle ; initialize duty
  OUT OCR0B, R23 ; cycle at 50% to get rolling
  STS 0x0FF, R23
  RET

; IncreaseSpeed and decreaseSpeed will increment or decrement R23 and update OCR0B,
; respectively, R23 being the register holding the fan's duty cycle, after checking to see 
; if duty cycle is at it's defined max or min. If it is, they will instead branch to
; fanAtLimit, which leaves the duty cycle unchanged

increaseSpeed: 
  LDS R23, 0x02FF ; necessary because of C-Assembly voodoo

  ; check if duty cycle's at max
  ; while 255 is max value of register, it can still inc, which will set register to 0
  ; ^not really 0? is trying to be 100000000, where the 1 is from a carry?
  CPI R23, maxDutyCycle
  BRCC maxLimit ; skip inc if at max

  INC R23 ; increment duty cycle by 1, note duty cycle value is out of 255, not 100%
  OUT OCR0B, R23 ; output updated duty cycle
  maxLimit:
  STS 0x02FF, R23 ; also because of C-Assembly voodoo
  RET

decreaseSpeed: 
  LDS R23, 0x02FF

  ; check if duty cycle's at min
  CPI R23, minDutyCycle
  BRCS minLimit ; skip dec if at min

  DEC R23 ; decrement duty cycle by 1, note duty cycle value is out of 255, not 100%
  OUT OCR0B, R23
  minLimit:
  STS 0x02FF, R23
  RET

temperature: ; gets temperature analog to digital conversion
  CALL SC

EOC: ; end of conversion

  ; see if conversion is done
  LDS R16, ADCSRA 
  SBRS R16, ADIF ; (ADC Interrupt Flag) if set, conversion done
  JMP EOC ; if conversion isn't done, wait until it is
  RET

initTemperature: ; initializes temperature ADC
  LDI R16, 0x00  ; ready R16 as data buffer
  STS ADMUX, R16 ; loads data from buffer to analog to digital converter on Arduino
  LDI R16, 0b10000111 ; (0x87)
  ; ADCSRA is where ADC trigger mode and clock speed is stored, first bit turns it on
  STS ADCSRA, R16 ; sets ADCSRA to 0x87 (trigger mode for when ADC runs conversion)
  LDI R16, 0x00 ; reset buffer
  STS ADCSRB, R16 ; sets ADCSRB to 0 (ADCSRB is data necessary if ADCSRA is set to auto-trigger)
  RET 

SC: ; start conversion, gets data
  LDS R16, ADCSRA ; loads trigger mode value into buffer
  ORI R16, 0b01000000 ; set start conversion bit to high (OR leaves rest of bits from ADCSRA alone)
  STS ADCSRA, R16 ; loads updated mode back into ADCSRA
  RET