################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
com.obj: ../com.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.7.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -O4 --opt_for_speed=1 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.7.LTS/include" --include_path="D:/CCS/base_proj/TMS320F28335/1. Data_Processing/inc" --include_path="D:/CCS/lib/DSP2833x_headers/include" --include_path="D:/CCS/lib/DSP2833x_common/include" --advice:performance=all -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="com.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


