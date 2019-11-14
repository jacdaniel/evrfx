#ifndef CONFIG
#define CONFIG

#define DEBUG_POWER_QUALIBRATION 1


#define PARAM_FILENAME "./data/param.txt"

#define MASTER_DATABASE_FILENAME    "./db/dbm.bin"
#define USER_DATABASE_FILENAME      "./db/dbu.bin"
#define SCRIPT_UPDATE_FILENAME      "evrf_update/update_run.sh"

#define MEDIA_ROOT_FILENAME         "/media/pi"
#define MEDIA_ROOT_DESKTOP_FILENAME "/media/linux"

#define TEXT_LENGTH_MAX    200

#define WINDOW_STYLE Qt::FramelessWindowHint
#define MAIN_WINDOW_WIDTH  800
#define MAIN_WINDOW_HEIGHT 480

#define GROUPBOX_RUN_STYLE "border: 1px solid; color: black; background-color: transparent;"

#define BUTTON1_WIDTH  48
#define BUTTON1_HEIGHT 48

#define BCONFIG_POSX 750
#define BCONFIG_POSY 430

#define TITLE_LABEL_FONT_NAME   "Helvetica"
#define TITLE_LABEL_FONT_SIZE   30
#define TITLE_LABEL_FONT_WEIGHT QFont::Bold

#define MAIN_SCREEN_IMAGE   "./data/window_main.jpg"
#define MAIN_SCREEN_IMAGE2   "./data/window_trt.jpg"
#define CONFIG_SCREEN_IMAGE "./data/img0.jpg"

// protocols
#define PROTOCOL_TRANSCUTANEOUS    "./data/protocol_transcutaneous.jpg"
#define PROTOCOL_ENDOVENOUS_CR30   "./data/endovenous_cr30_protocol.jpg"
#define PROTOCOL_ENDOVENOUS_CR45   "./data/endovenous_cr45_protocol.jpg"
#define PROTOCOL_PROCTOLOGY_HPR45i "./data/protology_hpr45i_protocol.jpg"

// quick user guide
#define QUICKUSERGUIDE "./data/quickuserguide.jpg"

// buttons
#define PATIENT_IMAGE       "./data/patient.jpg"
#define DIRECTACCESS_IMAGE  "./data/directaccess.jpg"
#define CONFIG_IMAGE        "./data/config.jpg"
#define BTN1_IMAGE          "./data/btn1.jpg"
#define BTN_PHLEBOLOGY      "./data/phlebology.jpg"
#define BTN_PROCTOLOGY      "./data/proctology.jpg"
#define BTN_ENDOVENOUS      "./data/endovenous.jpg"
#define BTN_TRANSCUTANEOUS  "./data/transcutaneous.jpg"

#define EDIT_IMAGE          "./data/bedit.jpg"
#define ERASE_IMAGE         "./data/berase.jpg"
#define CREATE_IMAGE        "./data/user_add.jpg"
#define CANCEL_IMAGE        "./data/bcancel.jpg"
#define VALID_IMAGE         "./data/bok.jpg"
#define ARROWUP_IMAGE       "./data/arrow_up.jpg"
#define ARROWDOWN_IMAGE     "./data/arrow_down.jpg"
#define ARROWLEFT_IMAGE     "./data/arrow_left.jpg"
#define ARROWRIGHT_IMAGE    "./data/arrow_right.jpg"

#define MINUS_IMAGE         "./data/minus2.jpg"
#define PLUS_IMAGE          "./data/plus2.jpg"
#define PLUSMINUS_SIZE 64

#define SHUTDOWN_IMAGE      "./data/shutdown.jpg"
#define UPGRADE_IMAGE       "./data/upgrade.jpg"
#define PATIENT75_IMAGE     "./data/patient75.jpg"
#define DATABASE_IMAGE      "./data/database.jpg"

#define BTN_ON              "./data/btn_on.png"
#define BTN_OFF             "./data/btn_off.png"

#define BTN_ON2              "./data/sw_on.jpg"
#define BTN_OFF2             "./data/sw_off.jpg"

#define BTN_ON3              "./data/logo_on.jpg"
#define BTN_OFF3             "./data/logo_off.jpg"


#define BTN_CR30             "./data/logo_cr30.jpg"
#define BTN_CR40i            "./data/logo_cr40i.jpg"
#define BTN_CR45i            "./data/logo_cr45i.jpg"
#define BTN_HPR45i           "./data/logo_hpr45i.jpg"


// logo
#define LOGO_RFID                  "./data/rfid-signal.jpg"
#define LOGO_CHECKED               "./data/checked.jpg"
#define LOGO_UNCHECKED             "./data/unchecked.jpg"
#define LOGO_CATHETER_CONNECTED    "./data/catheter_on.jpg"
#define LOGO_CATHETER_DISCONNECTED "./data/catheter_off.jpg"
#define LOGO_PAD_CONNECTED         "./data/pad_on.jpg"
#define LOGO_PAD_DISCONNECTED      "./data/pad_off.jpg"
#define LOGO_PULSE                 "./data/pulse.jpg"
#define LOGO_LANGUAGE              "./data/language.jpg"
#define LOGO_CLOCK                 "./data/logo_clock.jpg"
#define LOGO_ENERGY                "./data/logo_energy.jpg"

// main type
#define ENDOVENOUS     0
#define TRANSCUTANEOUS 1
#define PROCTOLOGY     2

// protocols

#define RUN_CR45i          1
#define RUN_CR40i          2
#define RUN_CR30i          3
#define RUN_TRANSCUTANEOUS 0
#define RUN_HPR45i         0
#define RUN_FISTULA        1






// **********************************************************
//
//
// **********************************************************

#define FILE_PARAM (char*)"./data/param.txt"

// fichier de config
#define IDX_FILE_TXT_EN 0
#define IDX_FILE_TXT_FR 1
#define IDX_FILE_TXT_NL 2
#define IDX_FILE_TXT_PT 3

#define FILE_TXT_EN "./data/label_en.txt"
#define FILE_TXT_FR "./data/label_fr.txt"
#define FILE_TXT_NL "./data/label_nl.txt"
#define FILE_TXT_PT "./data/label_pt.txt"


// label idx
#define IDX_LABEL_PATIENT       0
#define IDX_LABEL_DIRECTACCESS  1
#define IDX_PHLEBOLOGY          2
#define IDX_PROCTOLOGY          3
#define IDX_ENDOVENOUS          4
#define IDX_TRANSCUTANEOUS      5
#define IDX_FISTULA             6
#define IDX_POWER               7
#define IDX_PEDAL               8
#define IDX_MANUAL              9
#define IDX_PRESET             10
#define IDX_VEIN_DIAMETER      11
#define IDX_FACE               12
#define IDX_LEGS               13
#define IDX_PULSEWIDTH         14
#define IDX_DELAY              15
#define IDX_CR45i              17
#define IDX_CR40i              18
#define IDX_CR30i              19
#define IDX_TRANSCUTANEOUS0    20
#define IDX_HPR45i             21
#define IDX_FISTULA0           22
#define IDX_ENERGY             23
#define IDX_CONFIGURATION      24
#define IDX_DETAILS            25
#define IDX_NAME               26
#define IDX_AGE                27
#define IDX_CEAP               28
#define IDX_REMARK             29
#define IDX_CATHETER           30
#define IDX_DATE               31
#define IDX_TIME               32
#define IDX_PAD                33
#define IDX_ON                 34
#define IDX_OFF                35



//
#define KEY_0     '0'
#define KEY_1     '1'
#define KEY_2     '2'
#define KEY_3     '3'
#define KEY_4     '4'
#define KEY_5     '5'
#define KEY_6     '6'
#define KEY_7     '7'
#define KEY_8     '8'
#define KEY_9     '9'
#define KEY_A     'A'
#define KEY_B     'B'
#define KEY_C     'C'
#define KEY_D     'D'
#define KEY_E     'E'
#define KEY_F     'F'
#define KEY_G     'G'
#define KEY_H     'H'
#define KEY_I     'I'
#define KEY_J     'J'
#define KEY_K     'K'
#define KEY_L     'L'
#define KEY_M     'M'
#define KEY_N     'N'
#define KEY_O     'O'
#define KEY_P     'P'
#define KEY_Q     'Q'
#define KEY_R     'R'
#define KEY_S     'S'
#define KEY_T     'T'
#define KEY_U     'U'
#define KEY_V     'V'
#define KEY_W     'W'
#define KEY_X     'X'
#define KEY_Y     'Y'
#define KEY_Z     'Z'
#define KEY_LINE  '-'
#define KEY_SPACE ' '
#define KEY_RET   '<'
#define KEY_ENTER 2

#define KEY_000     '\n'



#endif // CONFIG

