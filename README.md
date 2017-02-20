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
	1. Symlink or file itself in same dir "p7z_usr.so" is in.
	2. Enviroment variable P7ZUSRWCX_7Z_SO_FILE set to path to it,
	   Ex: "$> export P7ZUSRWCX_7Z_SO_FILE=/path/to/7z.so"
	
	Recomended is symlink or path via enviroment variable. 
	Please avoid keeping multiple copies of "7z.so" in the system.


Build Instructions
-------------------------------
	1. Unpack main P7Z Usr package file ("p7z_usr_xxxxx.zip") into selected directory.
	2. Download P7ZIP version 15.09. Website: http://p7zip.sourceforge.net/
	3. Unpack P7ZIP into "./p7zip/p7zip_15x09", subdirectory of P7Z Usr.
	   (Actually only ./CPP and ./C subdirectories are required for build process).
	4. Locate the "makefile" file in "./projects/01_shared_lib" subdir.
	5. Use this command to compile and build: "make release".
	6. On successful build, shared lib file "p7z_usr.wcx" will be
	   creared in "./projects/01_shared_lib/bin/Release".


Installation
--------------------
	Typically, creeate following new subdir under DCMD root directory:
			"./plugins/wcx/p7z_usr"
	
	Copy following files to it:
		
		* main plugin file: "p7z_usr.wcx".
		* configuration file: "p7z_usr.ini" (optional).

	Make sure "7z.so" can be located either by creating symlink or by providing 
	enviroment variable that gets assigned before DCMD is started.
	Please see the "Library Information" section.
	Default location is same directory "p7z_usr.wcx" is in, in this case:
		"./plugins/wcx/p7z_usr/7z.so"

	In DCMD go to Options then Plugins. In Packer Plugin tab, click 
	the "Add" button and select the "p7z_usr.wcx" file.
	In the "Tweak" dialog box, add the file extensions of file types for this plugin 
	to open, see handlers list below. 
	Notes:
	* this is a read-only plugin, omitting types supported by other dedicated 
	  plugins is recommended.
	* list of file types supported is long, direct DCMD configuration file
	  editing may be a better approach.
	

Formats and suffix list sample
-----------------------------------------
	Below is a dump of formats from "7z.so" version 15.09.
	Actual list is written to the console STDOUT on plugin initialization with debug mode on.
	More descriptive can be found in an official 7-Zip documentation.

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
	[-] read only
	[-] multi volume archives not supported
	[-] no file dates and attributes
	[-] no Rar5 (can only see what files are in archive)


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
		You can try "make 7z" command and if successfull, "7z.so"
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
		find which (if any) handler tried is last in the incomplete list.


Links
-------------------
	http://doublecmd.sourceforge.net/
	http://doublecmd.sourceforge.net/forum/
	http://p7zip.sourceforge.net/
	http://www.7-zip.org/
	http://ikk.byethost9.com/


Changelog
---------------
	v 0.1
		* first release.
	
	v 0.2
		* Ask password for password protected archives.
		* Show message box on unpacking error durning close-archive call.
		* New INI optional configurations
		* Source code file names re-arrangemed.
		* About box.
	
	v 0.3
		* Fixed major error on symbolic links processing.
		* New INI configuration: custom shell command on archive open.
		* Readme file updates.
