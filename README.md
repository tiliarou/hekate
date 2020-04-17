# Kosmos patches (ES & FS including ACID & nocmac)

### What's new?

### 04/10/2020
Updated support for Kosmos 15.4 & Tinfoil 8+ (Kosmos_patches_04_10_2020_bootconfig_tinfoilv8+.zip)
cal0 protection removed on the included ams_mitm.kip (AMS 0.10.5) so Tinfoil v8+ would work with Kosmos

### 03/15/2020
Updated support for Kosmos 15.3 & Tinfoil 8+ (Kosmos_patches_03_15_2020_bootconfig_tinfoilv8+.zip)
cal0 protection removed on the included ams_mitm.kip (AMS 0.10.4) so Tinfoil v8+ would work with Kosmos

### 03/04/2020
Added support for Tinfoil 8+ (Kosmos_patches_03_04_2020_bootconfig_tinfoilv8+.zip)
cal0 protection removed on the included ams_mitm.kip (AMS 0.10.3) so Tinfoil v8+ would work with Kosmos

### 03/02/2020
There's no change on both ES & FS binaries so update wasn't really needed but I'm pushing this anyways so that people would know they do not have to wait for a new release.

The tinfoil support will be updated as soon as the new AMS gets released.

### 02/12/2020
a custom ams_mitm.kip has been added to support the latest tinfoil v8+
(Kosmos_patches_02_12_2020_bootconfig_tinfoilv8+.zip)

### 12/08/2019
Fixed an issue with one of the patches not being applied on boot due to its failure to check the original values.
Thanks to @NicholeMattera for a hotfix :)

### 12/07/2019
ES & FS patches ported for FW v9.1.0
An additional support added for Fusee Primary users (there's a separate archive packed in 7z, hekate won't load this but Fusee Primary will)

### 10/09/2019
an additional note has been added to patches.ini for 9.0.1 support
Zip is used instead of 7z due a compatibility issue with certain updater homebrews
Two versions are available. (one with hekate_ipl.ini for an upcoming change in Kosmos and another without it).
If you do not know how to enable "nosigchk" patches, Please use the version with bootconfig (hekate_ipl.ini included)

### 09/10/2019
ES & FS patches ported for FW v9.0.0

### 08/14/2019
update.bin & update.bin.sig removed since Tinfoil & Lithium no longer have checks.

### 07/06/2019
It now includes the latest version of Hekate 5.0.1 & Nyx 0.8.1 (CTCaer/hekate@101c8bc)

Due to the latest changes on Hekate v5 & Tinfoil/Lithium, I decided to discontinue my custom fork.
Instead, this repo will only maintain FS patches for Hekate and ES patches for atmosphere from now on. (Mainly used for Kosmos)

Simply unpack the provided archive to the root of SDCard will be enough.

### This archive includes following

ES patches for FW 2.0.0 - 9.2.0

ES patches credits:

2.0.0-6.2.0: Rajkosto
7.0.0-7.0.1: Prefers to be unknown
8.0.0-8.1.0: anon
9.0.0-9.2.0: none -(they are the same, back ported from the anonymous 8.1.0 patch)
FS patches for FW 1.0.0 - 9.2.0

Added ACID patches to all FWs (1.0.0-9.2.0) major thanks to @rajkosto and @EliseZeroTwo
Note : ACID patches are part of "nosigchk" patches, so no additional flag is needed to apply these patches.
Added nocmac patches for all FWs up to 6.2.0 (This helps downgrading when you face infamous blackscreen
issue or stuck at Nintendo logo after downgrading to 6.1.0 from 7.x and higher.)
In order to use "nocmac patches", please add "kip1patch=nocmac" in hekate_ipl.ini

