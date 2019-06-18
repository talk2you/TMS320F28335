################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
src/cpu0_timer.obj: ../src/cpu0_timer.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.7.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.7.LTS/include" --include_path="D:/CCS/base_proj/base_proj/inc" --include_path="D:/CCS/lib/DSP2833x_headers/include" --include_path="D:/CCS/lib/DSP2833x_common/include" -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="src/cpu0_timer.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/main.obj: ../src/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.7.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --opt_for_speed=2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_15.12.7.LTS/include" --include_path="D:/CCS/base_proj/base_proj/inc" --include_path="D:/CCS/lib/DSP2833x_headers/include" --include_path="D:/CCS/lib/DSP2833x_common/include" -g --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="src/main.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


