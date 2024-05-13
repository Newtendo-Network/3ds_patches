# 3DS Patches for the Newtendo Network

This is the 3DS patch code for the Newtendo Network.

It is based on the ``Service Manager`` (sm) of [Luma3DS](). (MIT License).

Modifications:

- ``/source/patches/*``
- ``/source/services.c`` (line 114, function ``RegisterService``)

It patches services when they register themselves to the Service Manager.

All credit go to the Luma 3DS team.

# Installation

- Put the built ``sm.cxi`` in ``sd:/luma/sysmodules/`` (the file path must be ``sd:/luma/sysmodules/sm.cxi``)
- Enable ``Enable loading external FIRMs and modules`` in the Luma3DS settings (hold SELECT while turning the 3DS on to open the Luma settings menu)

# Original README.md

# 3ds_sm
Open source replacement of the Arm11 SM system module.
This is licensed under the MIT license.

# Usage
To run this system module, use a recent release or commit of [Luma3DS](https://github.com/LumaTeam/Luma3DS/), build this project and copy sm.cxi to /luma/sysmodules/.

# Credits
Everyone that helped me fix some of stupid bugs I had been making: @fincs, @Hikari-chin, etc.
