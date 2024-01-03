# racing-pedals-adapter

This project is a **custom adapter** for an old **PC racing wheel** that has two pedals and a steering wheel with some buttons. Pedals are connected to the wheel through a special connector, and the wheel is connected to the PC through an USB connector.  

For some reason, the wheel isn't correctly broadcasting the pedals position to the PC, so this adapter aims to provide a direct connection between the pedals and the PC, bypassing the malfunctioning wheel. The connection goes through an **ATmega32U4** based **Arduino** board, that sends the pedals potentiometers signals to the PC as PC joystick axes. Also, a small 3D printed case keeps the board and the cables safe.
