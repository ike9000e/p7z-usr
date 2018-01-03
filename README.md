# p7z-usr
-------------------------------------------------------
    P7Z Usr - Packer Plugin for DCMD on Linux
-------------------------------------------------------

	Plugin for Double Commander (DCMD) that provides 7-Zip file archiver features.
	Open source, intended for Linux platforms.
	It's nain module is P7ZIP, a port of 7-Zip for POSIX systems.


Library Information
-------------------------
	Internally, P7Z Usr relies on a library file "7z.so".
	
	This is another shared library that is loaded dynamically
	and must be found durning this plugin initialization process.

	Locating "7z.so" library file:
	1. File in the same dir "p7z_usr.wcx" is in.
	2. Enviroment variable P7ZUSRWCX_7Z_SO_FILE containing full path,
	   Ex: "$> export P7ZUSRWCX_7Z_SO_FILE=/path/to/7z.so"
	
	Recomended is #1, that is, keep compatible "7z.so" file in the same 
	directory "p7z_usr.wcx" is in.
	

Build Instructions
-------------------------------
	1. Unpack main P7Z Usr package file ("p7z_usr_xxxxx.zip") into selected directory.
	2. Download P7ZIP version 15.09. Website: http://p7zip.sourceforge.net/
	3. Unpack P7ZIP into "./p7zip/compatible_version", subdirectory of P7Z Usr.
	   (Actually only ./CPP and ./C subdirectories are required for build process).
	4. Locate the "makefile" file in "./projects/01_shared_lib" subdir.
	5. Use this command to compile and build: "make release".
	   (Note: the 'debug' build target is just a placeholder and currently has no use).
	6. On successful build, shared library file "p7z_usr.wcx" will be
	   creared in "./projects/01_shared_lib/bin/Release".


Installation
--------------------
	No special steps required, instructions below just follow standard 
	steps as if to install any other WCX plugin in DCMD.

	Typically, creeate following new subdir under DCMD root directory:
			"./plugins/wcx/p7z_usr"
	
	Copy following files into it:
		
		* main plugin file: "p7z_usr.wcx".
		* configuration file: "p7z_usr.ini" (optional).
		* main P7ZIP library file, "7z.so" (or symlink to the file).

	Make sure "7z.so" library can be located by P7z Usr library,
	in case if using symlink instead of regular file.

	Default location for "7z.so" is the same directory "p7z_usr.wcx" is in, 
	in this case:
		"./plugins/wcx/p7z_usr/7z.so"

	In DCMD go to Options then Plugins. In Packer Plugin tab click 
	the "Add" button and select the "p7z_usr.wcx" file.
	In the "Tweak" dialog box, add the file extensions of file types for this plugin 
	to open, see handlers list below. 
	
	Notes:
	* this is a read-only plugin, omitting types supported by other, archive dedicated,
	  plugins is recommended.
	* list of file types supported is long, direct editing of DCMD configuration file
	  may be a better approach.


Formats and suffix list sample
-----------------------------------------
	Below is a dump of formats from "7z.so" version 15.09.
	Actual list is written to the console STDOUT on plugin initialization with debug mode on.
	More descriptive list can be found in an official 7-Zip documentation.

		7z:       [7z; ]
		APM:      [apm; ]
		Ar:       [ar a deb lib; ]
		Arj:      [arj; ]
		bzip2:    [bz2 bzip2 tbz2 tbz; * * .tar .tar]
		Cab:      [cab; ]
		Chm:      [chm chi chq chw; ]
		Hxs:      [hxs hxi hxr hxq hxw lit; ]
		Compound: [msi msp doc xls ppt; ]
		Cpio:     [cpio; ]
		CramFS:   [cramfs; ]
		Dmg:      [dmg; ]
		ELF:      [elf; ]
		Ext:      [ext ext2 ext3 ext4 img; ]
		FAT:      [fat img; ]
		FLV:      [flv; ]
		gzip:     [gz gzip tgz tpz; * * .tar .tar]
		GPT:      [gpt mbr; ]
		HFS:      [hfs hfsx; ]
		IHex:     [ihex; ]
		Iso:      [iso img; ]
		Lzh:      [lzh lha; ]
		lzma:     [lzma; ]
		lzma86:   [lzma86; ]
		MachO:    [macho; ]
		MBR:      [mbr; ]
		MsLZ:     [mslz; ]
		Mub:      [mub; ]
		Nsis:     [nsis; ]
		NTFS:     [ntfs img; ]
		PE:       [exe dll sys; ]
		TE:       [te; ]
		Ppmd:     [pmd; ]
		QCOW:     [qcow qcow2 qcow2c; ]
		Rar:      [rar r00; ]
		Rar5:     [rar r00; ]
		Rpm:      [rpm; ]
		Split:    [001; ]
		SquashFS: [squashfs; ]
		SWFc:     [swf; ~.swf]
		SWF:      [swf; ]
		tar:      [tar ova; ]
		Udf:      [udf iso img; ]
		UEFIc:    [scap; ]
		UEFIf:    [uefif; ]
		VDI:      [vdi; ]
		VHD:      [vhd; ]
		VMDK:     [vmdk; ]
		wim:      [wim swm esd; ]
		Xar:      [xar pkg; ]
		xz:       [xz txz; * .tar]
		Z:        [z taz; * .tar]
		zip:      [zip zipx jar xpi odt ods docx xlsx epub; ]



Features and Limitations
---------------------------------
	[+] can browse or extract all archives 7-zip library can open.
	[+] configuration via INI file (documentation provided inside it).
	[+] should be forward compatible with P7ZIP libraries versions >= 15.09
	[-] read only
	[-] multi volume archives not supported
	[-] no file attributes
	[-] no Rar5 (can only see files are in the archive)


FAQ
-----------------------

	Q: What is "7z.so"?
	A: This is a Linux executable shared library, build by compiling P7ZIP project.

	Q: Where to get "7z.so"?
	A: 
		Compile P7ZIP yourself or download from your linux distribution.
		Ubuntu has a binary package named "p7zip-full" that contains "7z.so".
		Note: Generally it is not a good idea to make P7Z Usr use this lib from
		an untested package.

	Q: How to build "7z.so"?
	A:
		See BUILD section in the README file of the P7ZIP.
		You can try the "make 7z" command, and if successfull, "7z.so"
		will be created in "./bin" subdirectory.

	Q: What is a Handler?
	A: 
		It is an internal 7z module that handles particular archive type.
		For example: Iso handler, Chm handler, 7z, zip, ...

	Q: How to fix Access Voilation Errors on archives that should be handled?
	A:
		Some handlers inside some "7z.so" libs can cause theese.
		P7z Usr tries all handlers it finds in the library.
		Turning off problematic internal handlers using INI 
		configuration may fix these problems.

	Q: How to diagnose which handlers aren't working properly?
	A:
		Set P7ZUSRWCX_DEBUG enviroment variable to turn on debug messages:
			$> export P7ZUSRWCX_DEBUG=1
		This causes various debug messages to be printed to the console STDOUT.
		Use Ctrl+PgDn, the "Try open archive" in DCMD, and
		find which (if any) handler tried comes as last in the incomplete list.

	Q: Why opening certain MSI archive file using Ctrl+PgDn yields
	   contents of some CAB archive embeded inside it, rather
	   than contents of MSI file itself?
	A:
		Opening files using Ctrl+PgDn is a method
		that tries handlers in predefined order, that does not take file 
		extension into account.
		The algorithm looks at the begining of the archive file, from adderss 0 up to 
		value specified by 'uCYHTFScanSize', and employs first handler that it finds
		suitable. Because list of handlers is orgainzed in an arbitrary order,
		it may happen that 'Cab' handler is tried before 'Compound' handler.
		Finally, if CAB file in question is embeded within first 8000002 bytes of the 
		archive file, the whole archive file gets "prematurely" opened as 'Cab' archive.
		
		In short:
		* in handlers priority list 'Cab' handler appears before 'Compound' (MSI) handler.
		* CAB file is embeded within first 8000002 bytes of the MSI file.

		Solution 1:
		Edit handlers priority list and put 'Compound' before 'Cab'.
		
		Solution 2:
		Do not use Ctrl+PgDn on the MSI archive file in question.
		Make sure file extension "msi" is added in the plugin configuration, 
		the 'Tweak' button in the DCMD Options in the Plugins section.
		Open MSI archive regural way, using Double-click or Enter key.

		References:
		* 'uCYHTFScanSize' default value is 8000002.
		* handlers priority list can be changed using 'szCYHTFHandlersPriority'.

Links
-------------------
	https://github.com/ikk00/p7z-usr
	http://doublecmd.sourceforge.net/
	http://doublecmd.sourceforge.net/forum/
	http://p7zip.sourceforge.net/
	http://www.7-zip.org/
	http://ikk.byethost9.com/

