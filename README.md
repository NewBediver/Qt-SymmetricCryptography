# Qt-SymmetricCryptography

<a alt="Qt-Framework"> <img src="https://img.shields.io/badge/Qt-Framework-red" /> </a>
<a alt="MinGW"> <img src="https://img.shields.io/badge/C%2FC%2B%2B-MinGW-blue" /> </a>

This is my course project on Cryptography Methods course. Here you can find emplementation of [GOST 28147-89](https://files.stroyinf.ru/Data/112/11287.pdf) and [GOST 34.12-2018](https://files.stroyinf.ru/Data/705/70509.pdf) symmetric cryptografy algorithms in modes from GOST 34.11-2018. To run this program you need Qt Framework with minGW 5.12.3 compiler (or you can write me and I will send you desktop version :smirk:).

### Main features:
- Encode/Decode hex data ONLY!!! (You will see warning message on every screen).
- Encoding/Decoding modes implemented for both standarts:
  - ECB
  - CBC
  - Gamming
  - Gamming OFB
  - Gamming CFB
- MAC modes implemented for both standarts:
  - ECB-MAC
  - CBC-MAC
  - Gamming-MAC
  - Gamming OFB-MAC
  - Gamming CFB-MAC
- You can find additional information about me inside About section.

<details>
  <summary>:grinning: Screenshots :kissing_heart:</summary>
  
  ### About submenu
  ![about](/Screenshots/Submenues/About%20submenu.png)
  ### GOST 28147-89 submenu
  ![28174-89](/Screenshots/Submenues/Magma%20submenu.png)
  ### GOST 34.12-2018
  ![34.12-2018](/Screenshots/Submenues/Kuznechik%20submenu.png)

  ***
  
  ### GOST 28147-89 ECB Encode mode
  ![magmaecb](/Screenshots/Modes/Magma%20ECB.png)
  ### GOST 28147-89 CBC Encode mode
  ![magmacbc](/Screenshots/Modes/Magma%20CBC.png)
  ### GOST 34.12-2018 CBC Encode mode
  ![kuznechikcbc](/Screenshots/Modes/Kuznechik%20CBC.png)
  ### GOST 34.12-2018 Gamming Decode mode
  ![kuznechikgamming](/Screenshots/Modes/Kuznechik%20Gamming.png)

  ***
  
  ### GOST 28147-89 ECB Encode GOST test
  ![magmaecbencodetest](/Screenshots/Tests/Magma%20ECB%20Encoding%20GOST%20test.png)
  ### GOST 28147-89 ECB Decode GOST test
  ![magmaecbdecodetest](/Screenshots/Tests/Magma%20ECB%20Decoding%20GOST%20test.png)
  ### GOST 34.12-2018 ECB Encode GOST test
  ![kuznechikecbencodetest](/Screenshots/Tests/Kuznechin%20ECB%20Encoding%20GOST%20test.png)
  ### GOST 34.12-2018 ECB Decode GOST test
  ![kuznechikecbdecodetest](/Screenshots/Tests/Kuznechin%20ECB%20Decoding%20GOST%20test.png)

</details>

### GPL-3.0 LICENSE SYNOPSIS

Here's what the license entails:

```markdown
1. Anyone can copy, modify and distribute this software.
2. You have to include the license and copyright notice with each and every distribution.
3. You can use this software privately.
4. You can use this software for commercial purposes.
5. If you dare build your business solely from this code, you risk open-sourcing the whole code base.
6. If you modify it, you have to indicate changes made to the code.
7. Any modifications of this code base MUST be distributed with the same license, GPLv3.
8. This software is provided without warranty.
9. The software author or license can not be held liable for any damages inflicted by the software.
```

More information on about the [LICENSE can be found here](http://choosealicense.com/licenses/gpl-3.0/).
