sbit LCD_RS at RD1_bit;
sbit LCD_EN at RD2_bit;
sbit LCD_D4 at RD3_bit;
sbit LCD_D5 at RD4_bit;
sbit LCD_D6 at RD5_bit;
sbit LCD_D7 at RD6_bit;
sbit LED at RD0_bit;

sbit BTN_INC at RB1_bit;
sbit BTN_DEC at RB3_bit;
sbit BTN_MENU at RB2_bit;
sbit BTN_BACK at RB0_bit;
sbit BTN_NEXT at RB4_bit;

sbit LCD_RS_Direction at TRISD1_bit;
sbit LCD_EN_Direction at TRISD2_bit;
sbit LCD_D4_Direction at TRISD3_bit;
sbit LCD_D5_Direction at TRISD4_bit;
sbit LCD_D6_Direction at TRISD5_bit;
sbit LCD_D7_Direction at TRISD6_bit;

unsigned int secs = 0;
int mins = 0;
int hours = 0;

char *time = "Time: 00:00:00";

unsigned int pause = 0;
int page = 0;

unsigned int toggle = 0;

char convert(int value){
     switch (value){
            case 0:
                 return '0';
            case 1:
                 return '1';
            case 2:
                 return '2';
            case 3:
                 return '3';
            case 4:
                 return '4';
            case 5:
                 return '5';
            case 6:
                 return '6';
            case 7:
                 return '7';
            case 8:
                 return '8';
            case 9:
                 return '9';
            default:
                 return '0';
     }
}

void autoset() {
     time[6] = convert(hours / 10);
     time[7] = convert(hours % 10);
     time[9] = convert(mins / 10);
     time[10] = convert(mins % 10);
     time[12] = convert(secs / 10);
     time[13] = convert(secs % 10);

     lcd_out(1, 1, time);
     if (pause == 1) lcd_out(2, 1, "Editing...");
     
     if (pause == 0) {
        if (toggle == 0) {
           toggle = 1;
        } else toggle = 0;
        
        LED = toggle;
     }
}

void setpage(int page) {
     lcd_cmd(_LCD_CLEAR);

     switch (page) {
            case 0:
               lcd_out(1, 1, "Set minutes?");
               break;
            case 1:
               lcd_out(1, 1, "Set hours?");
               break;
     }
}

void count() {
    if (pause == 1) return;

    secs++;

    if (secs >= 60) {
       secs = 0;
       mins++;
    }

    if (mins >= 60) {
       mins = 0;
       hours++;
    }

    if (hours >= 24) {
       secs = 0;
       mins = 0;
       hours = 0;
    }
    
    autoset();
}

void main() {
     TRISB = 0b00011111;
     TRISD = 0b00000000;

     lcd_init();
     lcd_cmd(_LCD_CLEAR);
     lcd_cmd(_LCD_CURSOR_OFF);
  
     LED = 0;
  
     lcd_out(1, 1, "LCD Clock v2");
     delay_ms(1500);
     
     lcd_cmd(_LCD_CLEAR);
     
     while (1) {
        if (BTN_MENU == 1) {
           if (pause == 0) {
              pause = 1;
              
              LED = 0;
              toggle = 0;
              
              setpage(0);
           } else {
              pause = 0;
              lcd_out(2, 1, "                ");
           }
           
           delay_ms(800);
        }
        
        if (pause == 1) {
            if (BTN_NEXT == 1) {
               page++;
               
               if (page > 1) page = 0;
               
               setpage(page);
               
               delay_ms(300);
            }
            
            if (BTN_BACK == 1) {
               page--;

               if (page < 0) page = 1;
               
               setpage(page);
               
               delay_ms(300);
            }
            
            if (BTN_INC == 1 && page == 0) {
               mins++;

               if (mins >= 60) mins = 0;
               
               autoset();
               
               delay_ms(200);
            }
            
            if (BTN_DEC == 1 && page == 0) {
               mins--;

               if (mins < 0) mins = 59;
               
               autoset();

               delay_ms(200);
            }
            
            if (BTN_INC == 1 && page == 1) {
               hours++;

               if (hours >= 24) hours = 0;
               
               autoset();

               delay_ms(200);
            }

            if (BTN_DEC == 1 && page == 1) {
               hours--;

               if (hours < 0) hours = 23;
               
               autoset();

               delay_ms(200);
            }
        };
        
        if (pause == 1) continue;
        
        count();
        
        delay_ms(1000);
        
  }
}
