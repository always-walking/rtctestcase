//-----------------------------------------------------------------------------
//  File: RTC4expl.cpp               (c) Copyright 2001,... 2013 by SCANLAB AG.
//-----------------------------------------------------------------------------
//
//
//
//  Abstract
//      DLL handling functions for explicitly linking to the RTC4DLL.DLL
//
//  Authors
//      Gerald Schmid, Bernhard Schrems
//
//  Revision History
//      +-----+---------+--------+------------------------------------------+
//      | Mod |  Date   | Author | Description                              |
//      +-----+---------+--------+------------------------------------------+
//      | 0.0 | 15Jan01 | GS, BS | * initial release                        |
//      | 1.0 | 24Jul13 |   GS   | * n_get_serial_number_32 and             |
//      |     |         |        |   get_serial_number_32 added.            |
//      |     |         |        |                                          |
//      +-----+---------+--------+------------------------------------------+
//
//  Function List
//      RTC4open
//      RTC4close
//-----------------------------------------------------------------------------

#include <windows.h>
#include "RTC4expl.h"
#include <tchar.h>

HINSTANCE gLibRTC4 = NULL;

namespace rtc4
{

GETMEMORY getmemory;
N_GET_WAVEFORM n_get_waveform;
GET_WAVEFORM get_waveform;
N_MEASUREMENT_STATUS n_measurement_status;
MEASUREMENT_STATUS measurement_status;
N_LOAD_VARPOLYDELAY n_load_varpolydelay;
LOAD_VARPOLYDELAY load_varpolydelay;
N_LOAD_PROGRAM_FILE n_load_program_file;
LOAD_PROGRAM_FILE load_program_file;
N_LOAD_CORRECTION_FILE n_load_correction_file;
LOAD_CORRECTION_FILE load_correction_file;
N_LOAD_Z_TABLE n_load_z_table;
LOAD_Z_TABLE load_z_table;
N_LIST_NOP n_list_nop;
LIST_NOP list_nop;
N_SET_END_OF_LIST n_set_end_of_list;
SET_END_OF_LIST set_end_of_list;
N_JUMP_ABS_3D n_jump_abs_3d;
JUMP_ABS_3D jump_abs_3d;
N_JUMP_ABS n_jump_abs;
JUMP_ABS jump_abs;
N_MARK_ABS_3D n_mark_abs_3d;
MARK_ABS_3D mark_abs_3d;
N_MARK_ABS n_mark_abs;
MARK_ABS mark_abs;
N_JUMP_REL_3D n_jump_rel_3d;
JUMP_REL_3D jump_rel_3d;
N_JUMP_REL n_jump_rel;
JUMP_REL jump_rel;
N_MARK_REL_3D n_mark_rel_3d;
MARK_REL_3D mark_rel_3d;
N_MARK_REL n_mark_rel;
MARK_REL mark_rel;
N_WRITE_8BIT_PORT_LIST n_write_8bit_port_list;
WRITE_8BIT_PORT_LIST write_8bit_port_list;
N_WRITE_DA_1_LIST n_write_da_1_list;
WRITE_DA_1_LIST write_da_1_list;
N_WRITE_DA_2_LIST n_write_da_2_list;
WRITE_DA_2_LIST write_da_2_list;
N_SET_MATRIX_LIST n_set_matrix_list;
SET_MATRIX_LIST set_matrix_list;
N_SET_DEFOCUS_LIST n_set_defocus_list;
SET_DEFOCUS_LIST set_defocus_list;
N_SET_CONTROL_MODE_LIST n_set_control_mode_list;
SET_CONTROL_MODE_LIST set_control_mode_list;
N_SET_OFFSET_LIST n_set_offset_list;
SET_OFFSET_LIST set_offset_list;
N_LONG_DELAY n_long_delay;
LONG_DELAY long_delay;
N_LASER_ON_LIST n_laser_on_list;
LASER_ON_LIST laser_on_list;
N_SET_JUMP_SPEED n_set_jump_speed;
SET_JUMP_SPEED set_jump_speed;
N_SET_MARK_SPEED n_set_mark_speed;
SET_MARK_SPEED set_mark_speed;
N_SET_LASER_DELAYS n_set_laser_delays;
SET_LASER_DELAYS set_laser_delays;
N_SET_SCANNER_DELAYS n_set_scanner_delays;
SET_SCANNER_DELAYS set_scanner_delays;
N_SET_LIST_JUMP n_set_list_jump;
SET_LIST_JUMP set_list_jump;
N_SET_INPUT_POINTER n_set_input_pointer;
SET_INPUT_POINTER set_input_pointer;
N_LIST_CALL n_list_call;
LIST_CALL list_call;
N_LIST_RETURN n_list_return;
LIST_RETURN list_return;
N_Z_OUT_LIST n_z_out_list;
Z_OUT_LIST z_out_list;
N_SET_STANDBY_LIST n_set_standby_list;
SET_STANDBY_LIST set_standby_list;
N_TIMED_JUMP_ABS n_timed_jump_abs;
TIMED_JUMP_ABS timed_jump_abs;
N_TIMED_MARK_ABS n_timed_mark_abs;
TIMED_MARK_ABS timed_mark_abs;
N_TIMED_JUMP_REL n_timed_jump_rel;
TIMED_JUMP_REL timed_jump_rel;
N_TIMED_MARK_REL n_timed_mark_rel;
TIMED_MARK_REL timed_mark_rel;
N_SET_LASER_TIMING n_set_laser_timing;
SET_LASER_TIMING set_laser_timing;
N_SET_WOBBEL_XY n_set_wobbel_xy;
SET_WOBBEL_XY set_wobbel_xy;
N_SET_WOBBEL n_set_wobbel;
SET_WOBBEL set_wobbel;
N_SET_FLY_X n_set_fly_x;
SET_FLY_X set_fly_x;
N_SET_FLY_Y n_set_fly_y;
SET_FLY_Y set_fly_y;
N_SET_FLY_ROT n_set_fly_rot;
SET_FLY_ROT set_fly_rot;
N_FLY_RETURN n_fly_return;
FLY_RETURN fly_return;
N_CALCULATE_FLY n_calculate_fly;
CALCULATE_FLY calculate_fly;
N_WRITE_IO_PORT_LIST n_write_io_port_list;
WRITE_IO_PORT_LIST write_io_port_list;
N_SELECT_COR_TABLE_LIST n_select_cor_table_list;
SELECT_COR_TABLE_LIST select_cor_table_list;
N_SET_WAIT n_set_wait;
SET_WAIT set_wait;
N_SIMULATE_EXT_START n_simulate_ext_start;
SIMULATE_EXT_START simulate_ext_start;
N_WRITE_DA_X_LIST n_write_da_x_list;
WRITE_DA_X_LIST write_da_x_list;
N_SET_PIXEL_LINE n_set_pixel_line;
SET_PIXEL_LINE set_pixel_line;
N_SET_PIXEL n_set_pixel;
SET_PIXEL set_pixel;
N_SET_EXTSTARTPOS_LIST n_set_extstartpos_list;
SET_EXTSTARTPOS_LIST set_extstartpos_list;
N_LASER_SIGNAL_ON_LIST n_laser_signal_on_list;
LASER_SIGNAL_ON_LIST laser_signal_on_list;
N_LASER_SIGNAL_OFF_LIST n_laser_signal_off_list;
LASER_SIGNAL_OFF_LIST laser_signal_off_list;
N_SET_FIRSTPULSE_KILLER_LIST n_set_firstpulse_killer_list;
SET_FIRSTPULSE_KILLER_LIST set_firstpulse_killer_list;
N_SET_IO_COND_LIST n_set_io_cond_list;
SET_IO_COND_LIST set_io_cond_list;
N_CLEAR_IO_COND_LIST n_clear_io_cond_list;
CLEAR_IO_COND_LIST clear_io_cond_list;
N_LIST_JUMP_COND n_list_jump_cond;
LIST_JUMP_COND list_jump_cond;
N_LIST_CALL_COND n_list_call_cond;
LIST_CALL_COND list_call_cond;
N_SAVE_AND_RESTART_TIMER n_save_and_restart_timer;
SAVE_AND_RESTART_TIMER save_and_restart_timer;
N_SET_EXT_START_DELAY_LIST n_set_ext_start_delay_list;
SET_EXT_START_DELAY_LIST set_ext_start_delay_list;
N_SET_TRIGGER n_set_trigger;
SET_TRIGGER set_trigger;
N_ARC_REL n_arc_rel;
ARC_REL arc_rel;
N_ARC_ABS n_arc_abs;
ARC_ABS arc_abs;
DRILLING drilling;
REGULATION regulation;
FLYLINE flyline;
N_GET_INPUT_POINTER n_get_input_pointer;
GET_INPUT_POINTER get_input_pointer;
SELECT_RTC select_rtc;
RTC4_COUNT_CARDS rtc4_count_cards;
N_GET_STATUS n_get_status;
GET_STATUS get_status;
N_READ_STATUS n_read_status;
READ_STATUS read_status;
N_GET_STARTSTOP_INFO n_get_startstop_info;
GET_STARTSTOP_INFO get_startstop_info;
N_GET_MARKING_INFO n_get_marking_info;
GET_MARKING_INFO get_marking_info;
GET_DLL_VERSION get_dll_version;
N_SET_START_LIST_1 n_set_start_list_1;
SET_START_LIST_1 set_start_list_1;
N_SET_START_LIST_2 n_set_start_list_2;
SET_START_LIST_2 set_start_list_2;
N_SET_START_LIST n_set_start_list;
SET_START_LIST set_start_list;
N_EXECUTE_LIST_1 n_execute_list_1;
EXECUTE_LIST_1 execute_list_1;
N_EXECUTE_LIST_2 n_execute_list_2;
EXECUTE_LIST_2 execute_list_2;
N_EXECUTE_LIST n_execute_list;
EXECUTE_LIST execute_list;
N_WRITE_8BIT_PORT n_write_8bit_port;
WRITE_8BIT_PORT write_8bit_port;
N_WRITE_IO_PORT n_write_io_port;
WRITE_IO_PORT write_io_port;
N_AUTO_CHANGE n_auto_change;
AUTO_CHANGE auto_change;
N_AUTO_CHANGE_POS n_auto_change_pos;
AUTO_CHANGE_POS auto_change_pos;
AUT_CHANGE aut_change;
N_START_LOOP n_start_loop;
START_LOOP start_loop;
N_QUIT_LOOP n_quit_loop;
QUIT_LOOP quit_loop;
N_SET_LIST_MODE n_set_list_mode;
SET_LIST_MODE set_list_mode;
N_STOP_EXECUTION n_stop_execution;
STOP_EXECUTION stop_execution;
N_READ_IO_PORT n_read_io_port;
READ_IO_PORT read_io_port;
N_WRITE_DA_1 n_write_da_1;
WRITE_DA_1 write_da_1;
N_WRITE_DA_2 n_write_da_2;
WRITE_DA_2 write_da_2;
N_SET_MAX_COUNTS n_set_max_counts;
SET_MAX_COUNTS set_max_counts;
N_GET_COUNTS n_get_counts;
GET_COUNTS get_counts;
N_SET_MATRIX n_set_matrix;
SET_MATRIX set_matrix;
N_SET_OFFSET n_set_offset;
SET_OFFSET set_offset;
N_GOTO_XYZ n_goto_xyz;
GOTO_XYZ goto_xyz;
N_GOTO_XY n_goto_xy;
GOTO_XY goto_xy;
N_GET_HEX_VERSION n_get_hex_version;
GET_HEX_VERSION get_hex_version;
N_DISABLE_LASER n_disable_laser;
DISABLE_LASER disable_laser;
N_ENABLE_LASER n_enable_laser;
ENABLE_LASER enable_laser;
N_STOP_LIST n_stop_list;
STOP_LIST stop_list;
N_RESTART_LIST n_restart_list;
RESTART_LIST restart_list;
N_GET_XYZ_POS n_get_xyz_pos;
GET_XYZ_POS get_xyz_pos;
N_GET_XY_POS n_get_xy_pos;
GET_XY_POS get_xy_pos;
N_SELECT_LIST n_select_list;
SELECT_LIST select_list;
N_Z_OUT n_z_out;
Z_OUT z_out;
N_SET_FIRSTPULSE_KILLER n_set_firstpulse_killer;
SET_FIRSTPULSE_KILLER set_firstpulse_killer;
N_SET_STANDBY n_set_standby;
SET_STANDBY set_standby;
N_LASER_SIGNAL_ON n_laser_signal_on;
LASER_SIGNAL_ON laser_signal_on;
N_LASER_SIGNAL_OFF n_laser_signal_off;
LASER_SIGNAL_OFF laser_signal_off;
N_SET_DELAY_MODE n_set_delay_mode;
SET_DELAY_MODE set_delay_mode;
N_SET_PISO_CONTROL n_set_piso_control;
SET_PISO_CONTROL set_piso_control;
N_SELECT_STATUS n_select_status;
SELECT_STATUS select_status;
N_GET_ENCODER n_get_encoder;
GET_ENCODER get_encoder;
N_SELECT_COR_TABLE n_select_cor_table;
SELECT_COR_TABLE select_cor_table;
N_EXECUTE_AT_POINTER n_execute_at_pointer;
EXECUTE_AT_POINTER execute_at_pointer;
N_GET_HEAD_STATUS n_get_head_status;
GET_HEAD_STATUS get_head_status;
N_SIMULATE_ENCODER n_simulate_encoder;
SIMULATE_ENCODER simulate_encoder;
N_SET_HI n_set_hi;
SET_HI set_hi;
N_RELEASE_WAIT n_release_wait;
RELEASE_WAIT release_wait;
N_GET_WAIT_STATUS n_get_wait_status;
GET_WAIT_STATUS get_wait_status;
N_SET_CONTROL_MODE n_set_control_mode;
SET_CONTROL_MODE set_control_mode;
N_SET_LASER_MODE n_set_laser_mode;
SET_LASER_MODE set_laser_mode;
N_SET_EXT_START_DELAY n_set_ext_start_delay;
SET_EXT_START_DELAY set_ext_start_delay;
N_HOME_POSITION n_home_position;
HOME_POSITION home_position;
N_SET_ROT_CENTER n_set_rot_center;
SET_ROT_CENTER set_rot_center;
N_DSP_START n_dsp_start;
DSP_START dsp_start;
N_WRITE_DA_X n_write_da_x;
WRITE_DA_X write_da_x;
N_READ_AD_X n_read_ad_x;
READ_AD_X read_ad_x;
N_READ_PIXEL_AD n_read_pixel_ad;
READ_PIXEL_AD read_pixel_ad;
N_GET_Z_DISTANCE n_get_z_distance;
GET_Z_DISTANCE get_z_distance;
N_GET_IO_STATUS n_get_io_status;
GET_IO_STATUS get_io_status;
N_GET_TIME n_get_time;
GET_TIME get_time;
N_SET_DEFOCUS n_set_defocus;
SET_DEFOCUS set_defocus;
N_SET_SOFTSTART_MODE n_set_softstart_mode;
SET_SOFTSTART_MODE set_softstart_mode;
N_SET_SOFTSTART_LEVEL n_set_softstart_level;
SET_SOFTSTART_LEVEL set_softstart_level;
N_CONTROL_COMMAND n_control_command;
CONTROL_COMMAND control_command;
LOAD_COR load_cor;
LOAD_PRO load_pro;
N_GET_SERIAL_NUMBER n_get_serial_number;
GET_SERIAL_NUMBER get_serial_number;
N_GET_SERIAL_NUMBER_32 n_get_serial_number_32;
GET_SERIAL_NUMBER_32 get_serial_number_32;
N_GET_RTC_VERSION n_get_rtc_version;
GET_RTC_VERSION get_rtc_version;
GET_HI_DATA get_hi_data;
N_AUTO_CAL n_auto_cal;
AUTO_CAL auto_cal;
N_GET_LIST_SPACE n_get_list_space;
GET_LIST_SPACE get_list_space;
TEACHIN teachin;
N_GET_VALUE n_get_value;
GET_VALUE get_value;
N_SET_IO_BIT n_set_io_bit;
SET_IO_BIT set_io_bit;
N_CLEAR_IO_BIT n_clear_io_bit;
CLEAR_IO_BIT clear_io_bit;
SET_DUTY_CYCLE_TABLE set_duty_cycle_table;
N_MOVE_TO n_move_to;
MOVE_TO move_to;

}//namespace

//  RTC4open
//
//  This function explicitly or dynamically links to the RTC4DLL.DLL.
//  Call it before using any RTC4 function.
//
//      Return      Meaning
//
//       0          Success. Using of the RTC4 functions is possible.
//      -1          Error: file RTC4DLL.DLL not found. The RTC4 functions
//                  cannot be used.
//      -2          Error: file RTC4DLL.DLL is already loaded.
int RTC4open(void) {
    if(gLibRTC4)
        return(-2);

    gLibRTC4 = LoadLibrary(_T("RTC4DLL.DLL"));
    if(!gLibRTC4)
		return(-1);

using namespace rtc4;

    // Get the addresses of the DLL-Functions
	getmemory = (GETMEMORY) GetProcAddress(gLibRTC4,"getmemory");
    n_get_waveform = (N_GET_WAVEFORM) GetProcAddress(gLibRTC4,"n_get_waveform");
    get_waveform = (GET_WAVEFORM) GetProcAddress(gLibRTC4,"get_waveform");
    n_measurement_status = (N_MEASUREMENT_STATUS) GetProcAddress(gLibRTC4,"n_measurement_status");
    measurement_status = (MEASUREMENT_STATUS) GetProcAddress(gLibRTC4,"measurement_status");
    n_load_varpolydelay = (N_LOAD_VARPOLYDELAY) GetProcAddress(gLibRTC4,"n_load_varpolydelay");
    load_varpolydelay = (LOAD_VARPOLYDELAY) GetProcAddress(gLibRTC4,"load_varpolydelay");
    n_load_program_file = (N_LOAD_PROGRAM_FILE) GetProcAddress(gLibRTC4,"n_load_program_file");
    load_program_file = (LOAD_PROGRAM_FILE) GetProcAddress(gLibRTC4,"load_program_file");
    n_load_correction_file = (N_LOAD_CORRECTION_FILE) GetProcAddress(gLibRTC4,"n_load_correction_file");
    load_correction_file = (LOAD_CORRECTION_FILE) GetProcAddress(gLibRTC4,"load_correction_file");
    n_load_z_table = (N_LOAD_Z_TABLE) GetProcAddress(gLibRTC4,"n_load_z_table");
    load_z_table = (LOAD_Z_TABLE) GetProcAddress(gLibRTC4,"load_z_table");
    n_list_nop = (N_LIST_NOP) GetProcAddress(gLibRTC4,"n_list_nop");
    list_nop = (LIST_NOP) GetProcAddress(gLibRTC4,"list_nop");
    n_set_end_of_list = (N_SET_END_OF_LIST) GetProcAddress(gLibRTC4,"n_set_end_of_list");
    set_end_of_list = (SET_END_OF_LIST) GetProcAddress(gLibRTC4,"set_end_of_list");
    n_jump_abs_3d = (N_JUMP_ABS_3D) GetProcAddress(gLibRTC4,"n_jump_abs_3d");
    jump_abs_3d = (JUMP_ABS_3D) GetProcAddress(gLibRTC4,"jump_abs_3d");
    n_jump_abs = (N_JUMP_ABS) GetProcAddress(gLibRTC4,"n_jump_abs");
    jump_abs = (JUMP_ABS) GetProcAddress(gLibRTC4,"jump_abs");
    n_mark_abs_3d = (N_MARK_ABS_3D) GetProcAddress(gLibRTC4,"n_mark_abs_3d");
    mark_abs_3d = (MARK_ABS_3D) GetProcAddress(gLibRTC4,"mark_abs_3d");
    n_mark_abs = (N_MARK_ABS) GetProcAddress(gLibRTC4,"n_mark_abs");
    mark_abs = (MARK_ABS) GetProcAddress(gLibRTC4,"mark_abs");
    n_jump_rel_3d = (N_JUMP_REL_3D) GetProcAddress(gLibRTC4,"n_jump_rel_3d");
    jump_rel_3d = (JUMP_REL_3D) GetProcAddress(gLibRTC4,"jump_rel_3d");
    n_jump_rel = (N_JUMP_REL) GetProcAddress(gLibRTC4,"n_jump_rel");
    jump_rel = (JUMP_REL) GetProcAddress(gLibRTC4,"jump_rel");
    n_mark_rel_3d = (N_MARK_REL_3D) GetProcAddress(gLibRTC4,"n_mark_rel_3d");
    mark_rel_3d = (MARK_REL_3D) GetProcAddress(gLibRTC4,"mark_rel_3d");
    n_mark_rel = (N_MARK_REL) GetProcAddress(gLibRTC4,"n_mark_rel");
    mark_rel = (MARK_REL) GetProcAddress(gLibRTC4,"mark_rel");
    n_write_8bit_port_list = (N_WRITE_8BIT_PORT_LIST) GetProcAddress(gLibRTC4,"n_write_8bit_port_list");
    write_8bit_port_list = (WRITE_8BIT_PORT_LIST) GetProcAddress(gLibRTC4,"write_8bit_port_list");
    n_write_da_1_list = (N_WRITE_DA_1_LIST) GetProcAddress(gLibRTC4,"n_write_da_1_list");
    write_da_1_list = (WRITE_DA_1_LIST) GetProcAddress(gLibRTC4,"write_da_1_list");
    n_write_da_2_list = (N_WRITE_DA_2_LIST) GetProcAddress(gLibRTC4,"n_write_da_2_list");
    write_da_2_list = (WRITE_DA_2_LIST) GetProcAddress(gLibRTC4,"write_da_2_list");
    n_set_matrix_list = (N_SET_MATRIX_LIST) GetProcAddress(gLibRTC4,"n_set_matrix_list");
    set_matrix_list = (SET_MATRIX_LIST) GetProcAddress(gLibRTC4,"set_matrix_list");
    n_set_defocus_list = (N_SET_DEFOCUS_LIST) GetProcAddress(gLibRTC4,"n_set_defocus_list");
    set_defocus_list = (SET_DEFOCUS_LIST) GetProcAddress(gLibRTC4,"set_defocus_list");
    n_set_control_mode_list = (N_SET_CONTROL_MODE_LIST) GetProcAddress(gLibRTC4,"n_set_control_mode_list");
    set_control_mode_list = (SET_CONTROL_MODE_LIST) GetProcAddress(gLibRTC4,"set_control_mode_list");
    n_set_offset_list = (N_SET_OFFSET_LIST) GetProcAddress(gLibRTC4,"n_set_offset_list");
    set_offset_list = (SET_OFFSET_LIST) GetProcAddress(gLibRTC4,"set_offset_list");
    n_long_delay = (N_LONG_DELAY) GetProcAddress(gLibRTC4,"n_long_delay");
    long_delay = (LONG_DELAY) GetProcAddress(gLibRTC4,"long_delay");
    n_laser_on_list = (N_LASER_ON_LIST) GetProcAddress(gLibRTC4,"n_laser_on_list");
    laser_on_list = (LASER_ON_LIST) GetProcAddress(gLibRTC4,"laser_on_list");
    n_set_jump_speed = (N_SET_JUMP_SPEED) GetProcAddress(gLibRTC4,"n_set_jump_speed");
    set_jump_speed = (SET_JUMP_SPEED) GetProcAddress(gLibRTC4,"set_jump_speed");
    n_set_mark_speed = (N_SET_MARK_SPEED) GetProcAddress(gLibRTC4,"n_set_mark_speed");
    set_mark_speed = (SET_MARK_SPEED) GetProcAddress(gLibRTC4,"set_mark_speed");
    n_set_laser_delays = (N_SET_LASER_DELAYS) GetProcAddress(gLibRTC4,"n_set_laser_delays");
    set_laser_delays = (SET_LASER_DELAYS) GetProcAddress(gLibRTC4,"set_laser_delays");
    n_set_scanner_delays = (N_SET_SCANNER_DELAYS) GetProcAddress(gLibRTC4,"n_set_scanner_delays");
    set_scanner_delays = (SET_SCANNER_DELAYS) GetProcAddress(gLibRTC4,"set_scanner_delays");
    n_set_list_jump = (N_SET_LIST_JUMP) GetProcAddress(gLibRTC4,"n_set_list_jump");
    set_list_jump = (SET_LIST_JUMP) GetProcAddress(gLibRTC4,"set_list_jump");
    n_set_input_pointer = (N_SET_INPUT_POINTER) GetProcAddress(gLibRTC4,"n_set_input_pointer");
    set_input_pointer = (SET_INPUT_POINTER) GetProcAddress(gLibRTC4,"set_input_pointer");
    n_list_call = (N_LIST_CALL) GetProcAddress(gLibRTC4,"n_list_call");
    list_call = (LIST_CALL) GetProcAddress(gLibRTC4,"list_call");
    n_list_return = (N_LIST_RETURN) GetProcAddress(gLibRTC4,"n_list_return");
    list_return = (LIST_RETURN) GetProcAddress(gLibRTC4,"list_return");
    n_z_out_list = (N_Z_OUT_LIST) GetProcAddress(gLibRTC4,"n_z_out_list");
    z_out_list = (Z_OUT_LIST) GetProcAddress(gLibRTC4,"z_out_list");
    n_set_standby_list = (N_SET_STANDBY_LIST) GetProcAddress(gLibRTC4,"n_set_standby_list");
    set_standby_list = (SET_STANDBY_LIST) GetProcAddress(gLibRTC4,"set_standby_list");
    n_timed_jump_abs = (N_TIMED_JUMP_ABS) GetProcAddress(gLibRTC4,"n_timed_jump_abs");
    timed_jump_abs = (TIMED_JUMP_ABS) GetProcAddress(gLibRTC4,"timed_jump_abs");
    n_timed_mark_abs = (N_TIMED_MARK_ABS) GetProcAddress(gLibRTC4,"n_timed_mark_abs");
    timed_mark_abs = (TIMED_MARK_ABS) GetProcAddress(gLibRTC4,"timed_mark_abs");
    n_timed_jump_rel = (N_TIMED_JUMP_REL) GetProcAddress(gLibRTC4,"n_timed_jump_rel");
    timed_jump_rel = (TIMED_JUMP_REL) GetProcAddress(gLibRTC4,"timed_jump_rel");
    n_timed_mark_rel = (N_TIMED_MARK_REL) GetProcAddress(gLibRTC4,"n_timed_mark_rel");
    timed_mark_rel = (TIMED_MARK_REL) GetProcAddress(gLibRTC4,"timed_mark_rel");
    n_set_laser_timing = (N_SET_LASER_TIMING) GetProcAddress(gLibRTC4,"n_set_laser_timing");
    set_laser_timing = (SET_LASER_TIMING) GetProcAddress(gLibRTC4,"set_laser_timing");
    n_set_wobbel_xy = (N_SET_WOBBEL_XY) GetProcAddress(gLibRTC4,"n_set_wobbel_xy");
    set_wobbel_xy = (SET_WOBBEL_XY) GetProcAddress(gLibRTC4,"set_wobbel_xy");
    n_set_wobbel = (N_SET_WOBBEL) GetProcAddress(gLibRTC4,"n_set_wobbel");
    set_wobbel = (SET_WOBBEL) GetProcAddress(gLibRTC4,"set_wobbel");
    n_set_fly_x = (N_SET_FLY_X) GetProcAddress(gLibRTC4,"n_set_fly_x");
    set_fly_x = (SET_FLY_X) GetProcAddress(gLibRTC4,"set_fly_x");
    n_set_fly_y = (N_SET_FLY_Y) GetProcAddress(gLibRTC4,"n_set_fly_y");
    set_fly_y = (SET_FLY_Y) GetProcAddress(gLibRTC4,"set_fly_y");
    n_set_fly_rot = (N_SET_FLY_ROT) GetProcAddress(gLibRTC4,"n_set_fly_rot");
    set_fly_rot = (SET_FLY_ROT) GetProcAddress(gLibRTC4,"set_fly_rot");
    n_fly_return = (N_FLY_RETURN) GetProcAddress(gLibRTC4,"n_fly_return");
    fly_return = (FLY_RETURN) GetProcAddress(gLibRTC4,"fly_return");
    n_calculate_fly = (N_CALCULATE_FLY) GetProcAddress(gLibRTC4,"n_calculate_fly");
    calculate_fly = (CALCULATE_FLY) GetProcAddress(gLibRTC4,"calculate_fly");
    n_write_io_port_list = (N_WRITE_IO_PORT_LIST) GetProcAddress(gLibRTC4,"n_write_io_port_list");
    write_io_port_list = (WRITE_IO_PORT_LIST) GetProcAddress(gLibRTC4,"write_io_port_list");
    n_select_cor_table_list = (N_SELECT_COR_TABLE_LIST) GetProcAddress(gLibRTC4,"n_select_cor_table_list");
    select_cor_table_list = (SELECT_COR_TABLE_LIST) GetProcAddress(gLibRTC4,"select_cor_table_list");
    n_set_wait = (N_SET_WAIT) GetProcAddress(gLibRTC4,"n_set_wait");
    set_wait = (SET_WAIT) GetProcAddress(gLibRTC4,"set_wait");
    n_simulate_ext_start = (N_SIMULATE_EXT_START) GetProcAddress(gLibRTC4,"n_simulate_ext_start");
    simulate_ext_start = (SIMULATE_EXT_START) GetProcAddress(gLibRTC4,"simulate_ext_start");
    n_write_da_x_list = (N_WRITE_DA_X_LIST) GetProcAddress(gLibRTC4,"n_write_da_x_list");
    write_da_x_list = (WRITE_DA_X_LIST) GetProcAddress(gLibRTC4,"write_da_x_list");
    n_set_pixel_line = (N_SET_PIXEL_LINE) GetProcAddress(gLibRTC4,"n_set_pixel_line");
    set_pixel_line = (SET_PIXEL_LINE) GetProcAddress(gLibRTC4,"set_pixel_line");
    n_set_pixel = (N_SET_PIXEL) GetProcAddress(gLibRTC4,"n_set_pixel");
    set_pixel = (SET_PIXEL) GetProcAddress(gLibRTC4,"set_pixel");
    n_set_extstartpos_list = (N_SET_EXTSTARTPOS_LIST) GetProcAddress(gLibRTC4,"n_set_extstartpos_list");
    set_extstartpos_list = (SET_EXTSTARTPOS_LIST) GetProcAddress(gLibRTC4,"set_extstartpos_list");
    n_laser_signal_on_list = (N_LASER_SIGNAL_ON_LIST) GetProcAddress(gLibRTC4,"n_laser_signal_on_list");
    laser_signal_on_list = (LASER_SIGNAL_ON_LIST) GetProcAddress(gLibRTC4,"laser_signal_on_list");
    n_laser_signal_off_list = (N_LASER_SIGNAL_OFF_LIST) GetProcAddress(gLibRTC4,"n_laser_signal_off_list");
    laser_signal_off_list = (LASER_SIGNAL_OFF_LIST) GetProcAddress(gLibRTC4,"laser_signal_off_list");
    n_set_firstpulse_killer_list = (N_SET_FIRSTPULSE_KILLER_LIST) GetProcAddress(gLibRTC4,"n_set_firstpulse_killer_list");
    set_firstpulse_killer_list = (SET_FIRSTPULSE_KILLER_LIST) GetProcAddress(gLibRTC4,"set_firstpulse_killer_list");
    n_set_io_cond_list = (N_SET_IO_COND_LIST) GetProcAddress(gLibRTC4,"n_set_io_cond_list");
    set_io_cond_list = (SET_IO_COND_LIST) GetProcAddress(gLibRTC4,"set_io_cond_list");
    n_clear_io_cond_list = (N_CLEAR_IO_COND_LIST) GetProcAddress(gLibRTC4,"n_clear_io_cond_list");
    clear_io_cond_list = (CLEAR_IO_COND_LIST) GetProcAddress(gLibRTC4,"clear_io_cond_list");
    n_list_jump_cond = (N_LIST_JUMP_COND) GetProcAddress(gLibRTC4,"n_list_jump_cond");
    list_jump_cond = (LIST_JUMP_COND) GetProcAddress(gLibRTC4,"list_jump_cond");
    n_list_call_cond = (N_LIST_CALL_COND) GetProcAddress(gLibRTC4,"n_list_call_cond");
    list_call_cond = (LIST_CALL_COND) GetProcAddress(gLibRTC4,"list_call_cond");
    n_save_and_restart_timer = (N_SAVE_AND_RESTART_TIMER) GetProcAddress(gLibRTC4,"n_save_and_restart_timer");
    save_and_restart_timer = (SAVE_AND_RESTART_TIMER) GetProcAddress(gLibRTC4,"save_and_restart_timer");
    n_set_ext_start_delay_list = (N_SET_EXT_START_DELAY_LIST) GetProcAddress(gLibRTC4,"n_set_ext_start_delay_list");
    set_ext_start_delay_list = (SET_EXT_START_DELAY_LIST) GetProcAddress(gLibRTC4,"set_ext_start_delay_list");
    n_set_trigger = (N_SET_TRIGGER) GetProcAddress(gLibRTC4,"n_set_trigger");
    set_trigger = (SET_TRIGGER) GetProcAddress(gLibRTC4,"set_trigger");
    n_arc_rel = (N_ARC_REL) GetProcAddress(gLibRTC4,"n_arc_rel");
    arc_rel = (ARC_REL) GetProcAddress(gLibRTC4,"arc_rel");
    n_arc_abs = (N_ARC_ABS) GetProcAddress(gLibRTC4,"n_arc_abs");
    arc_abs = (ARC_ABS) GetProcAddress(gLibRTC4,"arc_abs");
    drilling = (DRILLING) GetProcAddress(gLibRTC4,"drilling");
    regulation = (REGULATION) GetProcAddress(gLibRTC4,"regulation");
    flyline = (FLYLINE) GetProcAddress(gLibRTC4,"flyline");
    n_get_input_pointer = (N_GET_INPUT_POINTER) GetProcAddress(gLibRTC4,"n_get_input_pointer");
    get_input_pointer = (GET_INPUT_POINTER) GetProcAddress(gLibRTC4,"get_input_pointer");
    select_rtc = (SELECT_RTC) GetProcAddress(gLibRTC4,"select_rtc");
    rtc4_count_cards = (RTC4_COUNT_CARDS) GetProcAddress(gLibRTC4,"rtc4_count_cards");
    n_get_status = (N_GET_STATUS) GetProcAddress(gLibRTC4,"n_get_status");
    get_status = (GET_STATUS) GetProcAddress(gLibRTC4,"get_status");
    n_read_status = (N_READ_STATUS) GetProcAddress(gLibRTC4,"n_read_status");
    read_status = (READ_STATUS) GetProcAddress(gLibRTC4,"read_status");
    n_get_startstop_info = (N_GET_STARTSTOP_INFO) GetProcAddress(gLibRTC4,"n_get_startstop_info");
    get_startstop_info = (GET_STARTSTOP_INFO) GetProcAddress(gLibRTC4,"get_startstop_info");
    n_get_marking_info = (N_GET_MARKING_INFO) GetProcAddress(gLibRTC4,"n_get_marking_info");
    get_marking_info = (GET_MARKING_INFO) GetProcAddress(gLibRTC4,"get_marking_info");
    get_dll_version = (GET_DLL_VERSION) GetProcAddress(gLibRTC4,"get_dll_version");
    n_set_start_list_1 = (N_SET_START_LIST_1) GetProcAddress(gLibRTC4,"n_set_start_list_1");
    set_start_list_1 = (SET_START_LIST_1) GetProcAddress(gLibRTC4,"set_start_list_1");
    n_set_start_list_2 = (N_SET_START_LIST_2) GetProcAddress(gLibRTC4,"n_set_start_list_2");
    set_start_list_2 = (SET_START_LIST_2) GetProcAddress(gLibRTC4,"set_start_list_2");
    n_set_start_list = (N_SET_START_LIST) GetProcAddress(gLibRTC4,"n_set_start_list");
    set_start_list = (SET_START_LIST) GetProcAddress(gLibRTC4,"set_start_list");
    n_execute_list_1 = (N_EXECUTE_LIST_1) GetProcAddress(gLibRTC4,"n_execute_list_1");
    execute_list_1 = (EXECUTE_LIST_1) GetProcAddress(gLibRTC4,"execute_list_1");
    n_execute_list_2 = (N_EXECUTE_LIST_2) GetProcAddress(gLibRTC4,"n_execute_list_2");
    execute_list_2 = (EXECUTE_LIST_2) GetProcAddress(gLibRTC4,"execute_list_2");
    n_execute_list = (N_EXECUTE_LIST) GetProcAddress(gLibRTC4,"n_execute_list");
    execute_list = (EXECUTE_LIST) GetProcAddress(gLibRTC4,"execute_list");
    n_write_8bit_port = (N_WRITE_8BIT_PORT) GetProcAddress(gLibRTC4,"n_write_8bit_port");
    write_8bit_port = (WRITE_8BIT_PORT) GetProcAddress(gLibRTC4,"write_8bit_port");
    n_write_io_port = (N_WRITE_IO_PORT) GetProcAddress(gLibRTC4,"n_write_io_port");
    write_io_port = (WRITE_IO_PORT) GetProcAddress(gLibRTC4,"write_io_port");
    n_auto_change = (N_AUTO_CHANGE) GetProcAddress(gLibRTC4,"n_auto_change");
    auto_change = (AUTO_CHANGE) GetProcAddress(gLibRTC4,"auto_change");
    n_auto_change_pos = (N_AUTO_CHANGE_POS) GetProcAddress(gLibRTC4,"n_auto_change_pos");
    auto_change_pos = (AUTO_CHANGE_POS) GetProcAddress(gLibRTC4,"auto_change_pos");
    aut_change = (AUT_CHANGE) GetProcAddress(gLibRTC4,"aut_change");
    n_start_loop = (N_START_LOOP) GetProcAddress(gLibRTC4,"n_start_loop");
    start_loop = (START_LOOP) GetProcAddress(gLibRTC4,"start_loop");
    n_quit_loop = (N_QUIT_LOOP) GetProcAddress(gLibRTC4,"n_quit_loop");
    quit_loop = (QUIT_LOOP) GetProcAddress(gLibRTC4,"quit_loop");
    n_set_list_mode = (N_SET_LIST_MODE) GetProcAddress(gLibRTC4,"n_set_list_mode");
    set_list_mode = (SET_LIST_MODE) GetProcAddress(gLibRTC4,"set_list_mode");
    n_stop_execution = (N_STOP_EXECUTION) GetProcAddress(gLibRTC4,"n_stop_execution");
    stop_execution = (STOP_EXECUTION) GetProcAddress(gLibRTC4,"stop_execution");
    n_read_io_port = (N_READ_IO_PORT) GetProcAddress(gLibRTC4,"n_read_io_port");
    read_io_port = (READ_IO_PORT) GetProcAddress(gLibRTC4,"read_io_port");
    n_write_da_1 = (N_WRITE_DA_1) GetProcAddress(gLibRTC4,"n_write_da_1");
    write_da_1 = (WRITE_DA_1) GetProcAddress(gLibRTC4,"write_da_1");
    n_write_da_2 = (N_WRITE_DA_2) GetProcAddress(gLibRTC4,"n_write_da_2");
    write_da_2 = (WRITE_DA_2) GetProcAddress(gLibRTC4,"write_da_2");
    n_set_max_counts = (N_SET_MAX_COUNTS) GetProcAddress(gLibRTC4,"n_set_max_counts");
    set_max_counts = (SET_MAX_COUNTS) GetProcAddress(gLibRTC4,"set_max_counts");
    n_get_counts = (N_GET_COUNTS) GetProcAddress(gLibRTC4,"n_get_counts");
    get_counts = (GET_COUNTS) GetProcAddress(gLibRTC4,"get_counts");
    n_set_matrix = (N_SET_MATRIX) GetProcAddress(gLibRTC4,"n_set_matrix");
    set_matrix = (SET_MATRIX) GetProcAddress(gLibRTC4,"set_matrix");
    n_set_offset = (N_SET_OFFSET) GetProcAddress(gLibRTC4,"n_set_offset");
    set_offset = (SET_OFFSET) GetProcAddress(gLibRTC4,"set_offset");
    n_goto_xyz = (N_GOTO_XYZ) GetProcAddress(gLibRTC4,"n_goto_xyz");
    goto_xyz = (GOTO_XYZ) GetProcAddress(gLibRTC4,"goto_xyz");
    n_goto_xy = (N_GOTO_XY) GetProcAddress(gLibRTC4,"n_goto_xy");
    goto_xy = (GOTO_XY) GetProcAddress(gLibRTC4,"goto_xy");
    n_get_hex_version = (N_GET_HEX_VERSION) GetProcAddress(gLibRTC4,"n_get_hex_version");
    get_hex_version = (GET_HEX_VERSION) GetProcAddress(gLibRTC4,"get_hex_version");
    n_disable_laser = (N_DISABLE_LASER) GetProcAddress(gLibRTC4,"n_disable_laser");
    disable_laser = (DISABLE_LASER) GetProcAddress(gLibRTC4,"disable_laser");
    n_enable_laser = (N_ENABLE_LASER) GetProcAddress(gLibRTC4,"n_enable_laser");
    enable_laser = (ENABLE_LASER) GetProcAddress(gLibRTC4,"enable_laser");
    n_stop_list = (N_STOP_LIST) GetProcAddress(gLibRTC4,"n_stop_list");
    stop_list = (STOP_LIST) GetProcAddress(gLibRTC4,"stop_list");
    n_restart_list = (N_RESTART_LIST) GetProcAddress(gLibRTC4,"n_restart_list");
    restart_list = (RESTART_LIST) GetProcAddress(gLibRTC4,"restart_list");
    n_get_xyz_pos = (N_GET_XYZ_POS) GetProcAddress(gLibRTC4,"n_get_xyz_pos");
    get_xyz_pos = (GET_XYZ_POS) GetProcAddress(gLibRTC4,"get_xyz_pos");
    n_get_xy_pos = (N_GET_XY_POS) GetProcAddress(gLibRTC4,"n_get_xy_pos");
    get_xy_pos = (GET_XY_POS) GetProcAddress(gLibRTC4,"get_xy_pos");
    n_select_list = (N_SELECT_LIST) GetProcAddress(gLibRTC4,"n_select_list");
    select_list = (SELECT_LIST) GetProcAddress(gLibRTC4,"select_list");
    n_z_out = (N_Z_OUT) GetProcAddress(gLibRTC4,"n_z_out");
    z_out = (Z_OUT) GetProcAddress(gLibRTC4,"z_out");
    n_set_firstpulse_killer = (N_SET_FIRSTPULSE_KILLER) GetProcAddress(gLibRTC4,"n_set_firstpulse_killer");
    set_firstpulse_killer = (SET_FIRSTPULSE_KILLER) GetProcAddress(gLibRTC4,"set_firstpulse_killer");
    n_set_standby = (N_SET_STANDBY) GetProcAddress(gLibRTC4,"n_set_standby");
    set_standby = (SET_STANDBY) GetProcAddress(gLibRTC4,"set_standby");
    n_laser_signal_on = (N_LASER_SIGNAL_ON) GetProcAddress(gLibRTC4,"n_laser_signal_on");
    laser_signal_on = (LASER_SIGNAL_ON) GetProcAddress(gLibRTC4,"laser_signal_on");
    n_laser_signal_off = (N_LASER_SIGNAL_OFF) GetProcAddress(gLibRTC4,"n_laser_signal_off");
    laser_signal_off = (LASER_SIGNAL_OFF) GetProcAddress(gLibRTC4,"laser_signal_off");
    n_set_delay_mode = (N_SET_DELAY_MODE) GetProcAddress(gLibRTC4,"n_set_delay_mode");
    set_delay_mode = (SET_DELAY_MODE) GetProcAddress(gLibRTC4,"set_delay_mode");
    n_set_piso_control = (N_SET_PISO_CONTROL) GetProcAddress(gLibRTC4,"n_set_piso_control");
    set_piso_control = (SET_PISO_CONTROL) GetProcAddress(gLibRTC4,"set_piso_control");
    n_select_status = (N_SELECT_STATUS) GetProcAddress(gLibRTC4,"n_select_status");
    select_status = (SELECT_STATUS) GetProcAddress(gLibRTC4,"select_status");
    n_get_encoder = (N_GET_ENCODER) GetProcAddress(gLibRTC4,"n_get_encoder");
    get_encoder = (GET_ENCODER) GetProcAddress(gLibRTC4,"get_encoder");
    n_select_cor_table = (N_SELECT_COR_TABLE) GetProcAddress(gLibRTC4,"n_select_cor_table");
    select_cor_table = (SELECT_COR_TABLE) GetProcAddress(gLibRTC4,"select_cor_table");
    n_execute_at_pointer = (N_EXECUTE_AT_POINTER) GetProcAddress(gLibRTC4,"n_execute_at_pointer");
    execute_at_pointer = (EXECUTE_AT_POINTER) GetProcAddress(gLibRTC4,"execute_at_pointer");
    n_get_head_status = (N_GET_HEAD_STATUS) GetProcAddress(gLibRTC4,"n_get_head_status");
    get_head_status = (GET_HEAD_STATUS) GetProcAddress(gLibRTC4,"get_head_status");
    n_simulate_encoder = (N_SIMULATE_ENCODER) GetProcAddress(gLibRTC4,"n_simulate_encoder");
    simulate_encoder = (SIMULATE_ENCODER) GetProcAddress(gLibRTC4,"simulate_encoder");
    n_set_hi = (N_SET_HI) GetProcAddress(gLibRTC4,"n_set_hi");
    set_hi = (SET_HI) GetProcAddress(gLibRTC4,"set_hi");
    n_release_wait = (N_RELEASE_WAIT) GetProcAddress(gLibRTC4,"n_release_wait");
    release_wait = (RELEASE_WAIT) GetProcAddress(gLibRTC4,"release_wait");
    n_get_wait_status = (N_GET_WAIT_STATUS) GetProcAddress(gLibRTC4,"n_get_wait_status");
    get_wait_status = (GET_WAIT_STATUS) GetProcAddress(gLibRTC4,"get_wait_status");
    n_set_control_mode = (N_SET_CONTROL_MODE) GetProcAddress(gLibRTC4,"n_set_control_mode");
    set_control_mode = (SET_CONTROL_MODE) GetProcAddress(gLibRTC4,"set_control_mode");
    n_set_laser_mode = (N_SET_LASER_MODE) GetProcAddress(gLibRTC4,"n_set_laser_mode");
    set_laser_mode = (SET_LASER_MODE) GetProcAddress(gLibRTC4,"set_laser_mode");
    n_set_ext_start_delay = (N_SET_EXT_START_DELAY) GetProcAddress(gLibRTC4,"n_set_ext_start_delay");
    set_ext_start_delay = (SET_EXT_START_DELAY) GetProcAddress(gLibRTC4,"set_ext_start_delay");
    n_home_position = (N_HOME_POSITION) GetProcAddress(gLibRTC4,"n_home_position");
    home_position = (HOME_POSITION) GetProcAddress(gLibRTC4,"home_position");
    n_set_rot_center = (N_SET_ROT_CENTER) GetProcAddress(gLibRTC4,"n_set_rot_center");
    set_rot_center = (SET_ROT_CENTER) GetProcAddress(gLibRTC4,"set_rot_center");
    n_dsp_start = (N_DSP_START) GetProcAddress(gLibRTC4,"n_dsp_start");
    dsp_start = (DSP_START) GetProcAddress(gLibRTC4,"dsp_start");
    n_write_da_x = (N_WRITE_DA_X) GetProcAddress(gLibRTC4,"n_write_da_x");
    write_da_x = (WRITE_DA_X) GetProcAddress(gLibRTC4,"write_da_x");
    n_read_ad_x = (N_READ_AD_X) GetProcAddress(gLibRTC4,"n_read_ad_x");
    read_ad_x = (READ_AD_X) GetProcAddress(gLibRTC4,"read_ad_x");
    n_read_pixel_ad = (N_READ_PIXEL_AD) GetProcAddress(gLibRTC4,"n_read_pixel_ad");
    read_pixel_ad = (READ_PIXEL_AD) GetProcAddress(gLibRTC4,"read_pixel_ad");
    n_get_z_distance = (N_GET_Z_DISTANCE) GetProcAddress(gLibRTC4,"n_get_z_distance");
    get_z_distance = (GET_Z_DISTANCE) GetProcAddress(gLibRTC4,"get_z_distance");
    n_get_io_status = (N_GET_IO_STATUS) GetProcAddress(gLibRTC4,"n_get_io_status");
    get_io_status = (GET_IO_STATUS) GetProcAddress(gLibRTC4,"get_io_status");
    n_get_time = (N_GET_TIME) GetProcAddress(gLibRTC4,"n_get_time");
    get_time = (GET_TIME) GetProcAddress(gLibRTC4,"get_time");
    n_set_defocus = (N_SET_DEFOCUS) GetProcAddress(gLibRTC4,"n_set_defocus");
    set_defocus = (SET_DEFOCUS) GetProcAddress(gLibRTC4,"set_defocus");
    n_set_softstart_mode = (N_SET_SOFTSTART_MODE) GetProcAddress(gLibRTC4,"n_set_softstart_mode");
    set_softstart_mode = (SET_SOFTSTART_MODE) GetProcAddress(gLibRTC4,"set_softstart_mode");
    n_set_softstart_level = (N_SET_SOFTSTART_LEVEL) GetProcAddress(gLibRTC4,"n_set_softstart_level");
    set_softstart_level = (SET_SOFTSTART_LEVEL) GetProcAddress(gLibRTC4,"set_softstart_level");
    n_control_command = (N_CONTROL_COMMAND) GetProcAddress(gLibRTC4,"n_control_command");
    control_command = (CONTROL_COMMAND) GetProcAddress(gLibRTC4,"control_command");
    load_cor = (LOAD_COR) GetProcAddress(gLibRTC4,"load_cor");
    load_pro = (LOAD_PRO) GetProcAddress(gLibRTC4,"load_pro");
    n_get_serial_number = (N_GET_SERIAL_NUMBER) GetProcAddress(gLibRTC4,"n_get_serial_number");
    get_serial_number = (GET_SERIAL_NUMBER) GetProcAddress(gLibRTC4,"get_serial_number");
    n_get_serial_number_32 = (N_GET_SERIAL_NUMBER_32) GetProcAddress(gLibRTC4,"n_get_serial_number_32");
    get_serial_number_32 = (GET_SERIAL_NUMBER_32) GetProcAddress(gLibRTC4,"get_serial_number_32");
    n_get_rtc_version = (N_GET_RTC_VERSION) GetProcAddress(gLibRTC4,"n_get_rtc_version");
    get_rtc_version = (GET_RTC_VERSION) GetProcAddress(gLibRTC4,"get_rtc_version");
    get_hi_data = (GET_HI_DATA) GetProcAddress(gLibRTC4,"get_hi_data");
    n_auto_cal = (N_AUTO_CAL) GetProcAddress(gLibRTC4,"n_auto_cal");
    auto_cal = (AUTO_CAL) GetProcAddress(gLibRTC4,"auto_cal");
    n_get_list_space = (N_GET_LIST_SPACE) GetProcAddress(gLibRTC4,"n_get_list_space");
    get_list_space = (GET_LIST_SPACE) GetProcAddress(gLibRTC4,"get_list_space");
    teachin = (TEACHIN) GetProcAddress(gLibRTC4,"teachin");
    n_get_value = (N_GET_VALUE) GetProcAddress(gLibRTC4,"n_get_value");
    get_value = (GET_VALUE) GetProcAddress(gLibRTC4,"get_value");
    n_set_io_bit = (N_SET_IO_BIT) GetProcAddress(gLibRTC4,"n_set_io_bit");
    set_io_bit = (SET_IO_BIT) GetProcAddress(gLibRTC4,"set_io_bit");
    n_clear_io_bit = (N_CLEAR_IO_BIT) GetProcAddress(gLibRTC4,"n_clear_io_bit");
    clear_io_bit = (CLEAR_IO_BIT) GetProcAddress(gLibRTC4,"clear_io_bit");
    set_duty_cycle_table = (SET_DUTY_CYCLE_TABLE) GetProcAddress(gLibRTC4,"set_duty_cycle_table");
    n_move_to = (N_MOVE_TO) GetProcAddress(gLibRTC4,"n_move_to");
    move_to = (MOVE_TO) GetProcAddress(gLibRTC4,"move_to");
    return(0);
}


//  RTC4close
//
//  This function terminates the explicit linking to the RTC4DLL.DLL.
//  Call it when the use of the RTC4 functions is finished.
void RTC4close(void) {
    if(gLibRTC4)
        (void)FreeLibrary(gLibRTC4);

	gLibRTC4 = NULL;
}
