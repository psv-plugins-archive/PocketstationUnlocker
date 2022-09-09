// PocketStationUnlocker
// Created by Li (they/them)

#include <stdio.h>
#include <stdarg.h>
#include <taihen.h>
#include <vitasdkkern.h>

static int is_pocketstation_license_valid_hook = -1;
static int ref_is_pocketstation_license_valid_hook = -1;

static int is_pocketstation_title_hook = -1;
static tai_hook_ref_t ref_is_pocketstation_title_hook;


static int return_1() {
	return 1;
}	

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
	is_pocketstation_title_hook = taiHookFunctionExportForKernel(KERNEL_PID,
		&ref_is_pocketstation_title_hook, 
		"SceCompat",
		0x0F35909D, // SceCompat
		0x7DCFBCCE, // sceCompatIsPocketStationTitle
		return_1);
	
	is_pocketstation_license_valid_hook = taiHookFunctionExportForKernel(KERNEL_PID, 
		&ref_is_pocketstation_license_valid_hook, 
		"SceCompat", 
		0x0F35909D, // SceCompat
		0x96FC2A87,  //sceCompatCheckPocketStation
		return_1);
		
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	if (is_pocketstation_title_hook >= 0) taiHookReleaseForKernel(is_pocketstation_title_hook, ref_is_pocketstation_title_hook);
	if (is_pocketstation_license_valid_hook >= 0) taiHookReleaseForKernel(is_pocketstation_license_valid_hook, ref_is_pocketstation_license_valid_hook);
	
	return SCE_KERNEL_STOP_SUCCESS;
}
