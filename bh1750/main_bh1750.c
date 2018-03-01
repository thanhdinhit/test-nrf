#define    PIN_SCL        PIN_B4
#define    PIN_SDA        PIN_B1

#bit TRISB1   =0x86.1
#bit TRISB4   =0x86.4
#bit RB1 =0x06.1
#bit RB4 =0x06.4

#define  CHK_SCL  RB4
#define  CHK_SDA  RB1

#define    TRIS_SCL    TRISB1
#define    TRIS_SDA    TRISB4
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
