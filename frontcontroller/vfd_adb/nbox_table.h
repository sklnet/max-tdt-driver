static const uint8_t pt6302_nbox_rom_table[256] = {
  0x2e,//0x00, RAM0
  0x8f,//0x01, RAM1
  0xe4,//0x02, RAM2
  0xdd,//0x03, RAM3
  0xdc,//0x04, RAM4
  0x10,//0x05, RAM5
  0x10,//0x06, RAM6 
  0x10,//0x07, RAM7 
  0x10,//0x08, 
  0x10,//0x09, 
  0x10,//0x0a, 
  0x10,//0x0b, 
  0x10,//0x0c, 
  0x10,//0x0d, 
  0x10,//0x0e, 
  0x10,//0x0f, 

  0x10,//0x10, reserved  
  0x11,//0x11, reserved   
  0x12,//0x12, reserved  
  0x13,//0x13, reserved  
  0x14,//0x14, reserved  
  0x15,//0x15, reserved  
  0x16,//0x16, reserved  
  0x17,//0x17, reserved  
  0x18,//0x18, reserved  
  0x19,//0x19, reserved  
  0x1a,//0x1a, reserved   
  0x1b,//0x1b, reserved  
  0x1c,//0x1c, reserved
  0x10,//0x1d, reserved  
  0x10,//0x1e, reserved  
  0x10,//0x1f, reserved
  
  0x20,//0x20, <space>
  0x21,//0x21, !
  0x22,//0x22, "
  0x23,//0x23, #
  0x24,//0x24, $
  0x25,//0x25, %
  0x26,//0x26, &
  0x27,//0x27, '
  0x28,//0x28, (
  0x29,//0x29, )
  0x2a,//0x2a, *
  0x2b,//0x2b, +
  0x2c,//0x2c, ,
  0x2d,//0x2d, -
  0x2e,//0x2e, .
  0x2f,//0x2f, /
  
  0x30,//0x30, 0   
  0x31,//0x31, 1    
  0x32,//0x32, 2    
  0x33,//0x33, 3    
  0x34,//0x34, 4    
  0x35,//0x35, 5    
  0x36,//0x36, 6    
  0x37,//0x37, 7    
  0x38,//0x38, 8    
  0x39,//0x39, 9    
  0x3a,//0x3a, :    
  0x3b,//0x3b, ;    
  0x3c,//0x3c, <    
  0x3d,//0x3d, =    
  0x3e,//0x3e, >    
  0x3f,//0x3f, ?  
  
  0x40,//0x40, @ 
  0x41,//0x41, A 
  0x42,//0x42, B 
  0x43,//0x43, C 
  0x44,//0x44, D 
  0x45,//0x45, E 
  0x46,//0x46, F 
  0x47,//0x47, G 
  0x48,//0x48, H 
  0x49,//0x49, I 
  0x4a,//0x4a, J 
  0x4b,//0x4b, K 
  0x4c,//0x4c, L
  0x4d,//0x4d, M 
  0x4e,//0x4e, N 
  0x4f,//0x4f, O

  0x50,//0x50, P  
  0x51,//0x51, Q  
  0x52,//0x52, R  
  0x53,//0x53, S  
  0x54,//0x54, T  
  0x55,//0x55, U  
  0x56,//0x56, V
  0x57,//0x57, W  
  0x58,//0x58, X  
  0x59,//0x59, Y
  0x5a,//0x5a, Z
  0x5b,//0x5b, [  
  0x5c,//0x5c, <BACKSLASH>
  0x5d,//0x5d, ]  
  0x5e,//0x5e, ^  
  0x5f,//0x5f, _ 
  
  0x60,//0x60, `  
  0x61,//0x61, a  
  0x62,//0x62, b
  0x63,//0x63, c  
  0x64,//0x64, d
  0x65,//0x65, e  
  0x66,//0x66, f 
  0x67,//0x67, g  
  0x68,//0x68, h  
  0x69,//0x69, i  
  0x6a,//0x6a, j  
  0x6b,//0x6b, k  
  0x6c,//0x6c, l
  0x6d,//0x6d, m  
  0x6e,//0x6e, n  
  0x6f,//0x6f, o 

  0x70,//0x70, p  
  0x71,//0x71, q  
  0x72,//0x72, r  
  0x73,//0x73, s  
  0x74,//0x74, t
  0x75,//0x75, u  
  0x76,//0x76, v  
  0x77,//0x77, w  
  0x78,//0x78, x  
  0x79,//0x79, y  
  0x7a,//0x7a, z  
  0x7b,//0x7b, {  
  0x7c,//0x7c, |  
  0x7d,//0x7d, }  
  0x7e,//0x7e, ~  
  0x7f,//0x7f, <DEL>

/*  0x84,//0x80, adiaeresis
  0x94,//0x81, odiaeresis
  0x81,//0x82, udiaeresis
  0x8e,//0x83, Adiaeresis
  0x99,//0x84, Odiaeresis
  0x9a,//0x85, Udiaeresis
  0x63,//0x86, reserved, ć
  0x10,//0x87, reserved  
  0x6c,//0x88, reserved, ł   
  0x10,//0x89, reserved  
  0x10,//0x8a, reserved  
  0x10,//0x8b, reserved  
  0x10,//0x8c, reserved  
  0x5a,//0x8d, reserved, Ź  
  0x10,//0x8e, reserved  
  0x43,//0x8f, reserved, Ć 

  0x10,//0x90, reserved 
  0x10,//0x91, reserved  
  0x10,//0x92, reserved 
  0x10,//0x93, reserved 
  0x10,//0x94, reserved 
  0x10,//0x95, reserved 
  0x10,//0x96, reserved 
  0x53,//0x97, reserved, Ś 
  0x73,//0x98, reserved, ś 
  0x10,//0x99, reserved 
  0x10,//0x9a, reserved  
  0x10,//0x9b, reserved 
  0x10,//0x9c, reserved
  0x4c,//0x9d, reserved, Ł 
  0x10,//0x9e, reserved 

  0x10,//0xa0, reserved  
  0x10,//0xa1, reserved   
  0x10,//0xa2, reserved   
  0x10,//0xa3, reserved   
  0x41,//0xa4, reserved, Ą   
  0x61,//0xa5, reserved, ą   
  0x10,//0xa6, reserved   
  0x10,//0xa7, reserved   
  0x45,//0xa8, reserved, Ę   
  0x65,//0xa9, reserved, ę   
  0x10,//0xaa, reserved   
  0x7a,//0xab, reserved, ź   
  0x10,//0xac, reserved   
  0x10,//0xad, reserved   
  0x10,//0xae, reserved   
  0x10,//0xaf, reserved 

  0x10,//0xb0, reserved 
  0x10,//0xb1, reserved 
  0x10,//0xb2, reserved 
  0x10,//0xb3, reserved 
  0x10,//0xb4, reserved 
  0x10,//0xb5, reserved 
  0x10,//0xb6, reserved 
  0x10,//0xb7, reserved 
  0x10,//0xb8, reserved 
  0x10,//0xb9, reserved 
  0x10,//0xba, reserved 
  0x10,//0xbb, reserved 
  0x10,//0xbc, reserved 
  0x5a,//0xbd, reserved, Ż 
  0x7a,//0xbe, reserved, ż 
  0x10,//0xbf, reserved

  0x10,//0xc0, reserved
  0x10,//0xc1, reserved
  0x10,//0xc2, reserved
  0x10,//0xc3, reserved
  0x10,//0xc4, reserved
  0x10,//0xc5, reserved
  0x10,//0xc6, reserved
  0x10,//0xc7, reserved
  0x10,//0xc8, reserved
  0x10,//0xc9, reserved
  0x10,//0xca, reserved
  0x10,//0xcb, reserved
  0x10,//0xcc, reserved
  0x10,//0xcd, reserved
  0x10,//0xce, reserved
  0x10,//0xcf, reserved
  
  0x10,//0xd0, reserved
  0x10,//0xd1, reserved
  0x10,//0xd2, reserved
  0x10,//0xd3, reserved
  0x10,//0xd4, reserved
  0x10,//0xd5, reserved
  0x10,//0xd6, reserved
  0x10,//0xd7, reserved
  0x10,//0xd8, reserved
  0x10,//0xd9, reserved
  0x10,//0xda, reserved
  0x10,//0xdb, reserved
  0x10,//0xdc, reserved 
  0x10,//0xdd, reserved
  0x10,//0xde, reserved
  0x10,//0xdf, reserved
  
  0x10,//0xe0, reserved
  0x10,//0xe1, reserved
  0x10,//0xe2, reserved
  0x10,//0xe3, reserved
  0x10,//0xe4, reserved
  0x10,//0xe5, reserved
  0x10,//0xe6, reserved
  0x10,//0xe7, reserved
  0x10,//0xe8, reserved
  0x10,//0xe9, reserved
  0x10,//0xea, reserved 
  0x10,//0xeb, reserved 
  0x10,//0xec, reserved  
  0x10,//0xed, reserved 
  0x10,//0xee, reserved 
  0x10,//0xef, reserved 
  
  0x10,//0xf0, reserved
  0x10,//0xf1, reserved
  0x10,//0xf2, reserved
  0x10,//0xf3, reserved
  0x10,//0xf4, reserved
  0x10,//0xf5, reserved
  0x10,//0xf6, reserved
  0x10,//0xf7, reserved
  0x10,//0xf8, reserved
  0x10,//0xf9, reserved
  0x10,//0xfa, reserved
  0x10,//0xfb, reserved
  0x10,//0xfc, reserved
  0x10,//0xfd, reserved
  0x10,//0xfe, reserved
  0x00,//0xff, reserved*/
};
