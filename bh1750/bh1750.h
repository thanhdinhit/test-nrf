//khai bao i2c
#define _bh1750_
#use delay(crystal=20000000)

#define    PIN_SCL        PIN_A1
#define    PIN_SDA        PIN_A0

//#bit TRISA0   =0x85.0
//#bit TRISA1   =0x85.1
//#bit RA0 =0x05.0
//#bit RA1 =0x05.1

#define  CHK_SCL  RA1
#define  CHK_SDA  RA0

#define    TRIS_SCL    TRISA1
#define    TRIS_SDA    TRISA0
 //==================
///prototype
//===================
void _i2c_start();
void _i2c_stop();
byte _i2c_read(BYTE ack);
        //ack = 1 -> send not ack signal (NACK)
        //ack = 0 -> send ack signal (ACK)
void _i2c_write(int16 data_send); 
 
//=========================================================
//    I2C Start
//=========================================================
void _i2c_start()
{
    TRIS_SCL=0;
    TRIS_SDA=0;
 
    output_high(PIN_SDA);
    output_high(PIN_SCL);
    output_low(PIN_SDA);
    output_low(PIN_SCL);
}
//=========================================================
//  I2C Stop
//=========================================================
void _i2c_stop()
{
    TRIS_SDA=0;
    TRIS_SCL=0;
 
    output_low(PIN_SDA);
    output_high(PIN_SDA);
    output_high(PIN_SCL);   
}
//=========================================================
//    I2C write
//=========================================================
void _i2c_write(int16 data_send)
{
    BYTE i;
 
    TRIS_SDA=0;
    TRIS_SCL=0;
 
    for(i=0;i<=8;i++)
    {
        if(data_send & 0x80)    // MSB fist -> LSB last
            output_high(PIN_SDA);
        else
            output_low(PIN_SDA);
 
        output_high(PIN_SCL);
        data_send <<=1;
        output_low(PIN_SCL);
    }
}         
//=========================================================
//    I2C read
//=========================================================
byte _i2c_read(BYTE ack)
{
    BYTE get_data,i;
 
    output_low(PIN_SCL); 
    TRIS_SDA=1;        //set PIN_SDA as input
 
    for(i=0;i<8;i++)
    {
        get_data<<=1;
        output_high(PIN_SCL);
 
        if(CHK_SDA==1)
            get_data |=1;
 
        output_low(PIN_SCL);
    }
 
    TRIS_SDA=0;        //set PIN_SDA as output
    if(ack)
        output_high(PIN_SDA);    //ack=1 -> send not ack signal (NACK)
    else
        output_low(PIN_SDA);    //ack=0 -> send ack signal (ACK)
 
    output_high(PIN_SCL);
    output_low(PIN_SCL);
 
    return get_data;
}
//
#define  BH1750_address_w 0x46
#define  BH1750_address_r 0x47 
          
#define  power_down 0x00 
#define  power_up 0x01 
#define  reset 0x07 
#define  cont_H_res_mode1 0x10 
#define  cont_H_res_mode2 0x11  
#define  cont_L_res_mode 0x13                                          
#define  one_time_H_res_mode1 0x20 
#define  one_time_H_res_mode2 0x21 
#define  one_time_L_res_mode 0x23                                      
                        

void BH1750_init(); 
void BH1750_write(unsigned char cmd);                                            
unsigned long BH1750_read_word(); 
unsigned long get_lux_value(unsigned char mode, unsigned long delay_time); 


