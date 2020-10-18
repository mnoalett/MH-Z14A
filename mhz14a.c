#include <stdio.h>
#include <string.h>
#include <errno.h>
#include<stdlib.h>
#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int serial_port;
  unsigned char tx_buffer[9] = {0XFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79}; //read gas
  unsigned char rx_buffer[9];
  if ((serial_port = serialOpen ("/dev/serial0", 9600)) < 0)	/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)  /* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(1){

		if(serialDataAvail (serial_port) )
		{
			int count = write(serial_port, tx_buffer, sizeof(tx_buffer));		//Filestream, bytes to write, number of bytes to write
			if (count < 0)
			{
				printf("UART TX error\n");
			} else 
			{
				// Read up to 255 characters from the port if they are there
				int rx_length = read(serial_port, (void*)rx_buffer, 255);		//Filestream, buffer to store in, number of bytes to read (max)
				if (rx_length < 0)
				{
					//An error occured (will occur if there are no bytes)
				}
				else if (rx_length == 0)
				{
					//No data waiting
				}
				else
				{
					//Bytes received
					int co2 = rx_buffer[2]*256+rx_buffer[3];
					printf("read co2: %i\n", co2);
				}
			}	
			delay(60000);
		}
	}
}
