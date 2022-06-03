#include <stdio.h>
#include <windows.h>
#pragma comment(lib, "user32.lib")

int
main(void)
{
	// API says the info is cached when imode is 0, then nonzero references the cache, so can we call ENUM_CURRENT_SETTINGS first?
	DEVMODEW devmode; if (!EnumDisplaySettingsW(NULL, ENUM_CURRENT_SETTINGS, &devmode)) { fputs("toggleresolution: EnumDisplaySettingsW() ENUM_CURRENT_SETTINGS failed\n", stderr); return 1; }
	char is4k = devmode.dmPelsWidth == 3840;
	for (int imode=0; EnumDisplaySettingsW(NULL,imode,&devmode); imode++)
		if (is4k ? devmode.dmPelsWidth==1920&&devmode.dmPelsHeight==1080&&devmode.dmDisplayFrequency==60 : devmode.dmPelsWidth==3840&&devmode.dmPelsHeight==2160&&devmode.dmDisplayFrequency==30) {
			LONG res = ChangeDisplaySettingsW(&devmode, 0); if (res != DISP_CHANGE_SUCCESSFUL) { fprintf(stderr, "toggleresolution: ChangeDisplaySettingsW() failed: %ld\n", res); return 1; }
			goto changedres;
		}
	fputs("toggleresolution: Changing res failed: no matching mode found\n", stderr); return 1;
	changedres:;
}
