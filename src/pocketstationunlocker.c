// PocketStationUnlocker
// Created by SilicaAndPina (she/they)

#include <stdio.h>
#include <stdarg.h>
#include <taihen.h>
#include <vitasdkkern.h>

static int ispstitle = -1;
static tai_hook_ref_t ref_ispstitle;

static int return_1() {
	return 1;
}	

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
	ispstitle = taiHookFunctionExportForKernel(KERNEL_PID,
		&ref_ispstitle, 
		"SceCompat",
		TAI_ANY_LIBRARY,
		0x7DCFBCCE, 
		return_1);
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	if (ispstitle >= 0) taiHookReleaseForKernel(ispstitle, ref_ispstitle);   

	return SCE_KERNEL_STOP_SUCCESS;
}
