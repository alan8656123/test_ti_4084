#ifndef LCD_MAP_H_
#define LCD_MAP_H_


#define     LCD_A27              (((struct LCD_Type *) &Lcd_Data[0])->bit7)    /* SEG0 */
#define     LCD_X41  	         (((struct LCD_Type *) &Lcd_Data[0])->bit6)
#define     LCD_X43              (((struct LCD_Type *) &Lcd_Data[0])->bit5)
#define     LCD_9D               (((struct LCD_Type *) &Lcd_Data[0])->bit4)
#define     LCD_A26 		     (((struct LCD_Type *) &Lcd_Data[0])->bit3)    /* SEG1 */
#define     LCD_X42	    	     (((struct LCD_Type *) &Lcd_Data[0])->bit2)
#define     LCD_X44 	    	 (((struct LCD_Type *) &Lcd_Data[0])->bit1)
#define     LCD_10D		         (((struct LCD_Type *) &Lcd_Data[0])->bit0)

#define     LCD_A30              (((struct LCD_Type *) &Lcd_Data[1])->bit7)    /* SEG2 */
#define     LCD_10B  	         (((struct LCD_Type *) &Lcd_Data[1])->bit6)
#define     LCD_A33              (((struct LCD_Type *) &Lcd_Data[1])->bit5)
#define     LCD_10C              (((struct LCD_Type *) &Lcd_Data[1])->bit4)
#define     LCD_A29 		     (((struct LCD_Type *) &Lcd_Data[1])->bit3)    /* SEG3 */
#define     LCD_10A	    	     (((struct LCD_Type *) &Lcd_Data[1])->bit2)
#define     LCD_A25 	    	 (((struct LCD_Type *) &Lcd_Data[1])->bit1)
#define     LCD_10G		         (((struct LCD_Type *) &Lcd_Data[1])->bit0)

#define     LCD_A41              (((struct LCD_Type *) &Lcd_Data[2])->bit7)    /* SEG4 */
#define     LCD_10F  	         (((struct LCD_Type *) &Lcd_Data[2])->bit6)
#define     LCD_A24              (((struct LCD_Type *) &Lcd_Data[2])->bit5)
#define     LCD_10E              (((struct LCD_Type *) &Lcd_Data[2])->bit4)
#define     LCD_A40 		     (((struct LCD_Type *) &Lcd_Data[2])->bit3)    /* SEG5 */
#define     LCD_X45	    	     (((struct LCD_Type *) &Lcd_Data[2])->bit2)
#define     LCD_A23 	    	 (((struct LCD_Type *) &Lcd_Data[2])->bit1)
#define     LCD_14D		         (((struct LCD_Type *) &Lcd_Data[2])->bit0)

#define     LCD_A22              (((struct LCD_Type *) &Lcd_Data[3])->bit7)    /* SEG6 */
#define     LCD_14B  	         (((struct LCD_Type *) &Lcd_Data[3])->bit6)
#define     LCD_A34              (((struct LCD_Type *) &Lcd_Data[3])->bit5)
#define     LCD_14C              (((struct LCD_Type *) &Lcd_Data[3])->bit4)
#define     LCD_A21 		     (((struct LCD_Type *) &Lcd_Data[3])->bit3)    /* SEG7 */
#define     LCD_14A	    	     (((struct LCD_Type *) &Lcd_Data[3])->bit2)
#define     LCD_X46 	    	 (((struct LCD_Type *) &Lcd_Data[3])->bit1)
#define     LCD_14G		         (((struct LCD_Type *) &Lcd_Data[3])->bit0)

#define     LCD_A20              (((struct LCD_Type *) &Lcd_Data[4])->bit7)    /* SEG8 */
#define     LCD_14F  	         (((struct LCD_Type *) &Lcd_Data[4])->bit6)
#define     LCD_X47              (((struct LCD_Type *) &Lcd_Data[4])->bit5)
#define     LCD_14E              (((struct LCD_Type *) &Lcd_Data[4])->bit4)
#define     LCD_A19 		     (((struct LCD_Type *) &Lcd_Data[4])->bit3)    /* SEG9 */
#define     LCD_13B	    	     (((struct LCD_Type *) &Lcd_Data[4])->bit2)
#define     LCD_X49 	    	 (((struct LCD_Type *) &Lcd_Data[4])->bit1)
#define     LCD_13C		         (((struct LCD_Type *) &Lcd_Data[4])->bit0)

#define     LCD_A18              (((struct LCD_Type *) &Lcd_Data[5])->bit7)    /* SEG10 */
#define     LCD_13A  	         (((struct LCD_Type *) &Lcd_Data[5])->bit6)
#define     LCD_A35              (((struct LCD_Type *) &Lcd_Data[5])->bit5)
#define     LCD_13G              (((struct LCD_Type *) &Lcd_Data[5])->bit4)
#define     LCD_A17 		     (((struct LCD_Type *) &Lcd_Data[5])->bit3)    /* SEG11 */
#define     LCD_13F	    	     (((struct LCD_Type *) &Lcd_Data[5])->bit2)
#define     LCD_X50 	    	 (((struct LCD_Type *) &Lcd_Data[5])->bit1)
#define     LCD_13E		         (((struct LCD_Type *) &Lcd_Data[5])->bit0)

#define     LCD_A16              (((struct LCD_Type *) &Lcd_Data[6])->bit7)    /* SEG12 */
#define     LCD_X48  	         (((struct LCD_Type *) &Lcd_Data[6])->bit6)
#define     LCD_X51              (((struct LCD_Type *) &Lcd_Data[6])->bit5)
#define     LCD_COL              (((struct LCD_Type *) &Lcd_Data[6])->bit4)
#define     LCD_A15 		     (((struct LCD_Type *) &Lcd_Data[6])->bit3)    /* SEG13 */
#define     LCD_12B	    	     (((struct LCD_Type *) &Lcd_Data[6])->bit2)
#define     LCD_A36 	    	 (((struct LCD_Type *) &Lcd_Data[6])->bit1)
#define     LCD_12C		         (((struct LCD_Type *) &Lcd_Data[6])->bit0)

#define     LCD_A14              (((struct LCD_Type *) &Lcd_Data[7])->bit7)    /* SEG14 */
#define     LCD_12A  	         (((struct LCD_Type *) &Lcd_Data[7])->bit6)
#define     LCD_X52              (((struct LCD_Type *) &Lcd_Data[7])->bit5)
#define     LCD_12G              (((struct LCD_Type *) &Lcd_Data[7])->bit4)
#define     LCD_A13		         (((struct LCD_Type *) &Lcd_Data[7])->bit3)    /* SEG15 */
#define     LCD_12F		         (((struct LCD_Type *) &Lcd_Data[7])->bit2)
#define     LCD_X53  		     (((struct LCD_Type *) &Lcd_Data[7])->bit1)
#define     LCD_12E		         (((struct LCD_Type *) &Lcd_Data[7])->bit0)

#define     LCD_A12              (((struct LCD_Type *) &Lcd_Data[8])->bit7)    /* SEG16 */
#define     LCD_11B  	         (((struct LCD_Type *) &Lcd_Data[8])->bit6)
#define     LCD_X54              (((struct LCD_Type *) &Lcd_Data[8])->bit5)
#define     LCD_12D              (((struct LCD_Type *) &Lcd_Data[8])->bit4)
#define     LCD_A11		         (((struct LCD_Type *) &Lcd_Data[8])->bit3)    /* SEG17 */
#define     LCD_11A		         (((struct LCD_Type *) &Lcd_Data[8])->bit2)
#define     LCD_A37 		     (((struct LCD_Type *) &Lcd_Data[8])->bit1)
#define     LCD_11G		         (((struct LCD_Type *) &Lcd_Data[8])->bit0)

#define     LCD_A10              (((struct LCD_Type *) &Lcd_Data[9])->bit7)    /* SEG18 */
#define     LCD_11E  	         (((struct LCD_Type *) &Lcd_Data[9])->bit6)
#define     LCD_A9               (((struct LCD_Type *) &Lcd_Data[9])->bit5)
#define     LCD_11C              (((struct LCD_Type *) &Lcd_Data[9])->bit4)
#define     LCD_A7	             (((struct LCD_Type *) &Lcd_Data[9])->bit3)    /* SEG19 */
#define     LCD_11D		         (((struct LCD_Type *) &Lcd_Data[9])->bit2)
#define     LCD_A8  		     (((struct LCD_Type *) &Lcd_Data[9])->bit1)
#define     LCD_13D		         (((struct LCD_Type *) &Lcd_Data[9])->bit0)

#define     LCD_A6               (((struct LCD_Type *) &Lcd_Data[10])->bit7)    /* SEG20 */
#define     LCD_9B 	             (((struct LCD_Type *) &Lcd_Data[10])->bit6)
#define     LCD_A38              (((struct LCD_Type *) &Lcd_Data[10])->bit5)
#define     LCD_9C               (((struct LCD_Type *) &Lcd_Data[10])->bit4)
#define     LCD_A5	             (((struct LCD_Type *) &Lcd_Data[10])->bit3)    /* SEG21 */
#define     LCD_9A	             (((struct LCD_Type *) &Lcd_Data[10])->bit2)
#define     LCD_X55 		     (((struct LCD_Type *) &Lcd_Data[10])->bit1)
#define     LCD_9G	             (((struct LCD_Type *) &Lcd_Data[10])->bit0)

#define     LCD_A4               (((struct LCD_Type *) &Lcd_Data[11])->bit7)    /* SEG22 */
#define     LCD_9F 	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit6)
#define     LCD_X56               (((struct LCD_Type *) &Lcd_Data[11])->bit5)
#define     LCD_9E               (((struct LCD_Type *) &Lcd_Data[11])->bit4)
#define     LCD_A3	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit3)    /* SEG23 */
#define     LCD_8A	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit2)
#define     LCD_X57		         (((struct LCD_Type *) &Lcd_Data[11])->bit1)
#define     LCD_8B	  	         (((struct LCD_Type *) &Lcd_Data[11])->bit0)

#define     LCD_A2               (((struct LCD_Type *) &Lcd_Data[12])->bit7)    /* SEG24 */
#define     LCD_8G 	             (((struct LCD_Type *) &Lcd_Data[12])->bit6)
#define     LCD_A39              (((struct LCD_Type *) &Lcd_Data[12])->bit5)
#define     LCD_8C               (((struct LCD_Type *) &Lcd_Data[12])->bit4)
#define     LCD_A1	             (((struct LCD_Type *) &Lcd_Data[12])->bit3)    /* SEG25 */
#define     LCD_8E	             (((struct LCD_Type *) &Lcd_Data[12])->bit2)
#define     LCD_X26 		     (((struct LCD_Type *) &Lcd_Data[12])->bit1)
#define     LCD_8D	             (((struct LCD_Type *) &Lcd_Data[12])->bit0)

#define     LCD_X36              (((struct LCD_Type *) &Lcd_Data[13])->bit7)    /* SEG26 */
#define     LCD_X37              (((struct LCD_Type *) &Lcd_Data[13])->bit6)
#define     LCD_X38              (((struct LCD_Type *) &Lcd_Data[13])->bit5)
#define     LCD_X39              (((struct LCD_Type *) &Lcd_Data[13])->bit4)
#define     LCD_1E               (((struct LCD_Type *) &Lcd_Data[13])->bit3)    /* SEG27 */
//#define     LCD_10C		         (((struct LCD_Type *) &Lcd_Data[13])->bit2)
#define     LCD_1F               (((struct LCD_Type *) &Lcd_Data[13])->bit1)
///#define     LCD_X12		         (((struct LCD_Type *) &Lcd_Data[13])->bit0)

#define     LCD_1D               (((struct LCD_Type *) &Lcd_Data[14])->bit7)    /* SEG28 */
#define     LCD_1A               (((struct LCD_Type *) &Lcd_Data[14])->bit6)
#define     LCD_1G               (((struct LCD_Type *) &Lcd_Data[14])->bit5)
//#define     LCD_X11             (((struct LCD_Type *) &Lcd_Data[14])->bit4)
#define     LCD_1C               (((struct LCD_Type *) &Lcd_Data[14])->bit3)    /* SEG29 */
#define     LCD_X35              (((struct LCD_Type *) &Lcd_Data[14])->bit2)
#define     LCD_1B               (((struct LCD_Type *) &Lcd_Data[14])->bit1)
#define     LCD_X34              (((struct LCD_Type *) &Lcd_Data[14])->bit0)

#define     LCD_2E               (((struct LCD_Type *) &Lcd_Data[15])->bit7)    /* SEG30 */
//#define     LCD_2F  	         (((struct LCD_Type *) &Lcd_Data[15])->bit6)
#define     LCD_2F               (((struct LCD_Type *) &Lcd_Data[15])->bit5)
//#define     LCD_1C               (((struct LCD_Type *) &Lcd_Data[15])->bit4)
#define     LCD_2D               (((struct LCD_Type *) &Lcd_Data[15])->bit3)    /* SEG31 */
#define     LCD_2A               (((struct LCD_Type *) &Lcd_Data[15])->bit2)
#define     LCD_2G               (((struct LCD_Type *) &Lcd_Data[15])->bit1)
//#define     LCD_2D	             (((struct LCD_Type *) &Lcd_Data[15])->bit0)

#define     LCD_2C               (((struct LCD_Type *) &Lcd_Data[16])->bit7)    /* SEG32 */
//#define     LCD_2G  	         (((struct LCD_Type *) &Lcd_Data[16])->bit6)
#define     LCD_2B           (((struct LCD_Type *) &Lcd_Data[16])->bit5)
//#define     LCD_2C               (((struct LCD_Type *) &Lcd_Data[16])->bit4)
#define     LCD_3E               (((struct LCD_Type *) &Lcd_Data[16])->bit3)    /* SEG33 */
#define     LCD_X32               (((struct LCD_Type *) &Lcd_Data[16])->bit2)
#define     LCD_3F               (((struct LCD_Type *) &Lcd_Data[16])->bit1)
#define     LCD_X33               (((struct LCD_Type *) &Lcd_Data[16])->bit0)

#define     LCD_3D               (((struct LCD_Type *) &Lcd_Data[17])->bit7)    /* SEG34 */
#define     LCD_3A               (((struct LCD_Type *) &Lcd_Data[17])->bit6)
#define     LCD_3G               (((struct LCD_Type *) &Lcd_Data[17])->bit5)
//#define     LCD_3C               (((struct LCD_Type *) &Lcd_Data[17])->bit4)
#define     LCD_3C               (((struct LCD_Type *) &Lcd_Data[17])->bit3)    /* SEG35 */
#define     LCD_X31               (((struct LCD_Type *) &Lcd_Data[17])->bit2)
#define     LCD_3B               (((struct LCD_Type *) &Lcd_Data[17])->bit1)
#define     LCD_X40               (((struct LCD_Type *) &Lcd_Data[17])->bit0)

#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[18])->bit7)    /* SEG36 */
#define     LCD_X30 	         (((struct LCD_Type *) &Lcd_Data[18])->bit6)
#define     LCD_4F               (((struct LCD_Type *) &Lcd_Data[18])->bit5)
#define     LCD_X29              (((struct LCD_Type *) &Lcd_Data[18])->bit4)
#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[18])->bit3)    /* SEG37 */
#define     LCD_4A               (((struct LCD_Type *) &Lcd_Data[18])->bit2)
#define     LCD_4G               (((struct LCD_Type *) &Lcd_Data[18])->bit1)
#define     LCD_X28              (((struct LCD_Type *) &Lcd_Data[18])->bit0)

#define     LCD_4C               (((struct LCD_Type *) &Lcd_Data[19])->bit7)    /* SEG38 */
//#define     LCD_5G               (((struct LCD_Type *) &Lcd_Data[19])->bit6)
#define     LCD_4B               (((struct LCD_Type *) &Lcd_Data[19])->bit5)
//#define     LCD_5C               (((struct LCD_Type *) &Lcd_Data[19])->bit4)


//#define     LCD_16E		         (((struct LCD_Type *) &Lcd_Data[29])->bit7)    /* SEG58 */
#define     LCD_X1              (((struct LCD_Type *) &Lcd_Data[29])->bit6)
//#define     LCD_16D              (((struct LCD_Type *) &Lcd_Data[29])->bit5)
#define     LCD_X2              (((struct LCD_Type *) &Lcd_Data[29])->bit4)
//#define     LCD_16G              (((struct LCD_Type *) &Lcd_Data[29])->bit3)    /* SEG59 */
#define     LCD_X7  	         (((struct LCD_Type *) &Lcd_Data[29])->bit2)
#define     LCD_X14_C          (((struct LCD_Type *) &Lcd_Data[29])->bit1)
#define     LCD_X8              (((struct LCD_Type *) &Lcd_Data[29])->bit0)

//#define     LCD_BLANK14		     (((struct LCD_Type *) &Lcd_Data[30])->bit7)    /* SEG60 */
#define     LCD_X10              (((struct LCD_Type *) &Lcd_Data[30])->bit6)
//#define     LCD_BLANK15          (((struct LCD_Type *) &Lcd_Data[30])->bit5)
#define     LCD_X9              (((struct LCD_Type *) &Lcd_Data[30])->bit4)
//#define     LCD_X46              (((struct LCD_Type *) &Lcd_Data[30])->bit3)    /* SEG61 */
#define     LCD_X4  	         (((struct LCD_Type *) &Lcd_Data[30])->bit2)
//#define     LCD_X51              (((struct LCD_Type *) &Lcd_Data[30])->bit1)
#define     LCD_X3              (((struct LCD_Type *) &Lcd_Data[30])->bit0)

#define     LCD_X13		         (((struct LCD_Type *) &Lcd_Data[31])->bit7)    /* SEG62 */
#define     LCD_X11              (((struct LCD_Type *) &Lcd_Data[31])->bit6)
#define     LCD_X14_A             (((struct LCD_Type *) &Lcd_Data[31])->bit5)
#define     LCD_X5               (((struct LCD_Type *) &Lcd_Data[31])->bit4)
//#define     LCD_BLANK16          (((struct LCD_Type *) &Lcd_Data[31])->bit3)    /* SEG63 */
#define     LCD_X12  	     (((struct LCD_Type *) &Lcd_Data[31])->bit2)
#define     LCD_X14_B          (((struct LCD_Type *) &Lcd_Data[31])->bit1)
#define     LCD_X6          (((struct LCD_Type *) &Lcd_Data[31])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[32])->bit7)    /* SEG64 */
#define     LCD_X20 	         (((struct LCD_Type *) &Lcd_Data[32])->bit6)
#define     LCD_X19               (((struct LCD_Type *) &Lcd_Data[32])->bit5)
#define     LCD_X15              (((struct LCD_Type *) &Lcd_Data[32])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[32])->bit3)    /* SEG65 */
#define     LCD_X21               (((struct LCD_Type *) &Lcd_Data[32])->bit2)
#define     LCD_X22               (((struct LCD_Type *) &Lcd_Data[32])->bit1)
#define     LCD_X16              (((struct LCD_Type *) &Lcd_Data[32])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[33])->bit7)    /* SEG66 */
#define     LCD_X24 	         (((struct LCD_Type *) &Lcd_Data[33])->bit6)
#define     LCD_X23               (((struct LCD_Type *) &Lcd_Data[33])->bit5)
#define     LCD_X17              (((struct LCD_Type *) &Lcd_Data[33])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[33])->bit3)    /* SEG67 */
#define     LCD_6C               (((struct LCD_Type *) &Lcd_Data[33])->bit2)
//#define     LCD_4G               (((struct LCD_Type *) &Lcd_Data[33])->bit1)
#define     LCD_6B              (((struct LCD_Type *) &Lcd_Data[33])->bit0)

#define     LCD_A31               (((struct LCD_Type *) &Lcd_Data[34])->bit7)    /* SEG68 */
#define     LCD_7G 	         (((struct LCD_Type *) &Lcd_Data[34])->bit6)
#define     LCD_7B               (((struct LCD_Type *) &Lcd_Data[34])->bit5)
#define     LCD_7C              (((struct LCD_Type *) &Lcd_Data[34])->bit4)
#define     LCD_A28               (((struct LCD_Type *) &Lcd_Data[34])->bit3)    /* SEG69 */
#define     LCD_7H               (((struct LCD_Type *) &Lcd_Data[34])->bit2)
#define     LCD_7A               (((struct LCD_Type *) &Lcd_Data[34])->bit1)
#define     LCD_7D               (((struct LCD_Type *) &Lcd_Data[34])->bit0)

#define     LCD_A32               (((struct LCD_Type *) &Lcd_Data[35])->bit7)    /* SEG70 */
#define     LCD_7E  	         (((struct LCD_Type *) &Lcd_Data[35])->bit6)
#define     LCD_7F               (((struct LCD_Type *) &Lcd_Data[35])->bit5)
#define     LCD_X25_B              (((struct LCD_Type *) &Lcd_Data[35])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[35])->bit3)    /* SEG71 */
//#define     LCD_4A               (((struct LCD_Type *) &Lcd_Data[35])->bit2)
//#define     LCD_4G               (((struct LCD_Type *) &Lcd_Data[35])->bit1)
#define     LCD_X25_A              (((struct LCD_Type *) &Lcd_Data[35])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[36])->bit7)    /* SEG72 */
#define     LCD_5F 	             (((struct LCD_Type *) &Lcd_Data[36])->bit6)
#define     LCD_5E               (((struct LCD_Type *) &Lcd_Data[36])->bit5)
#define     LCD_X27              (((struct LCD_Type *) &Lcd_Data[36])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[36])->bit3)    /* SEG73 */
#define     LCD_5G               (((struct LCD_Type *) &Lcd_Data[36])->bit2)
#define     LCD_5D               (((struct LCD_Type *) &Lcd_Data[36])->bit1)
#define     LCD_5A               (((struct LCD_Type *) &Lcd_Data[36])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[37])->bit7)    /* SEG74 */
#define     LCD_5C 	         (((struct LCD_Type *) &Lcd_Data[37])->bit6)
#define     LCD_DP               (((struct LCD_Type *) &Lcd_Data[37])->bit5)
#define     LCD_5B              (((struct LCD_Type *) &Lcd_Data[37])->bit4)
//#define     LCD_4D               (((struct LCD_Type *) &Lcd_Data[37])->bit3)    /* SEG75 */
#define     LCD_6E               (((struct LCD_Type *) &Lcd_Data[37])->bit2)
#define     LCD_X18               (((struct LCD_Type *) &Lcd_Data[37])->bit1)
#define     LCD_6F              (((struct LCD_Type *) &Lcd_Data[37])->bit0)

//#define     LCD_4E               (((struct LCD_Type *) &Lcd_Data[38])->bit7)    /* SEG76 */
#define     LCD_6G 	             (((struct LCD_Type *) &Lcd_Data[38])->bit6)
#define     LCD_6D               (((struct LCD_Type *) &Lcd_Data[38])->bit5)
#define     LCD_6A              (((struct LCD_Type *) &Lcd_Data[38])->bit4)

#define DIST_ODO LCD_X35
#define DIST_TRIP LCD_X35
#define DIST_DP LCD_DP
#define DIST_KM LCD_X22
#define DIST_VOLT LCD_X33
#define DIST_OIL LCD_X34

#endif
