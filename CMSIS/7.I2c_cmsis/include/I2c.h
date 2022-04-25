#ifndef I2C_H
#define I2C_H

void init_i2c (void);
void start_i2c (void);
void stop_i2c (void);
void send_i2c (char);
void init_lcd (void);
void lcd_cmd (char);
void lcd_data (char);
void wait (void);
void lcd_str (char *);
void send_i2c_addr (char);
/*----------------------------*/
void debug_led (void);
void delay_ms (long);

#endif

