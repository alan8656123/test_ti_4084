################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/alan8656/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/home/alan8656/workspace_ccstheia/ti_test" -I"/home/alan8656/workspace_ccstheia/ti_test/Debug" -I"/home/alan8656/ti/mspm0_sdk_2_08_00_03/source/third_party/CMSIS/Core/Include" -I"/home/alan8656/ti/mspm0_sdk_2_08_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1866658520: ../TI_4084.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/alan8656/ti/ccs2040/ccs/utils/sysconfig_1.26.0/sysconfig_cli.sh" -s "/home/alan8656/ti/mspm0_sdk_2_08_00_03/.metadata/product.json" --script "/home/alan8656/workspace_ccstheia/ti_test/TI_4084.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '

device_linker.cmd: build-1866658520 ../TI_4084.syscfg
device.opt: build-1866658520
device.cmd.genlibs: build-1866658520
ti_msp_dl_config.c: build-1866658520
ti_msp_dl_config.h: build-1866658520
Event.dot: build-1866658520

%.o: ./%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/alan8656/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/home/alan8656/workspace_ccstheia/ti_test" -I"/home/alan8656/workspace_ccstheia/ti_test/Debug" -I"/home/alan8656/ti/mspm0_sdk_2_08_00_03/source/third_party/CMSIS/Core/Include" -I"/home/alan8656/ti/mspm0_sdk_2_08_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

startup_mspm0g350x_ticlang.o: /home/alan8656/ti/mspm0_sdk_2_08_00_03/source/ti/devices/msp/m0p/startup_system_files/ticlang/startup_mspm0g350x_ticlang.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"/home/alan8656/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"/home/alan8656/workspace_ccstheia/ti_test" -I"/home/alan8656/workspace_ccstheia/ti_test/Debug" -I"/home/alan8656/ti/mspm0_sdk_2_08_00_03/source/third_party/CMSIS/Core/Include" -I"/home/alan8656/ti/mspm0_sdk_2_08_00_03/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


