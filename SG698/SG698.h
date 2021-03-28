#ifndef _SG698_H_
#define _SG698_H_

/**************************宏定义*********************************************
*/

#define start1_head  0
#define length_head  1
#define start2_head  5
#define control_head 6
#define address_head 7
#define AFN_head     12
#define SEQ_head     13

/*
*************************宏定义**********************************************/


/*******************************************************************************
变量类型定义，此处定义与DSP平台不同，方便移植特别设定 
*******************************************************************************/

typedef unsigned char   uchar;
typedef unsigned short  uint16;
typedef unsigned int   	uint32;
typedef float           float32;

/*******************************************************************************
通讯变量定义
*******************************************************************************/


/***********************基本控制变量****************************
*/

enum SciCCOMSTATE{
	SciCRECEIVE=0,		//通讯状态接收 
	SciCPROCESS,		//通讯状态处理 
	SciCWAITSEND,		//通讯状态等待 
	SciCSEND			//通讯状态发送 
};

typedef struct{
	uint16 u2_SciCCOMSTATE:2;
	uint16 bFRAMESEND:1;
	uint16 bFRAMERECEIVE:1;
	uint16 bFRAMEPROCESSED:1;
	uint16 bFRAMEERROR:1;
}st_SciCCOM;

typedef union{
	st_SciCCOM bit;
	uint16      all;
}un_SciCCOM;
/*
**********************基本控制变量*****************************/


/***********************长度域****************************
*/
enum LEN{
	LEN_DISABLE=0,	//长度域禁用 
	LEN_ENABLE,		//长度域使用 
	LEN_RESERVE_2,	//长度域保留 
	LEN_RESERVE_3	//长度域保留 
};

typedef struct{
	uint16 u2_status:2;		//BIT00-01:长度域状态[0:禁用,1:使用,2:保留2,3:保留3]
	uint16 u14_length:14;	//BIT02-15:长度域所表示的长度 
}st_length_domain;

typedef union{
	st_length_domain bit;
	uint16 all;
}un_length_domain;
/*
**********************长度域*****************************/



/***********************控制域****************************
*/
enum DIR{
	DIR_DOWN=0,			//控制域下行报文 
	DIR_UP				//控制域上行报文 
};

enum PRM{
	PRM_PASSIVE=0,		//控制域从动站 
	PRM_ACTIVE			//控制域启动站 
};

enum FCB_ACD{
	FCB_0=0,			//控制域帧计数0 
	FCB_1,				//控制域帧计数1 
	ACD_NOT_URGENT = 0,	//控制域请求访问无事件 
	ACD_URGENT			//控制域请求访问重要事件 
};


enum FCV{
	FCV_DISABLE=0,		//控制域帧计数无效 
	FCV_ENABLE			//控制域帧计数使能 
};

enum FUN{						
	//控制域从动站功能码 
	FUN_PASSIVE_ACK=0,		//控制域功能认可 
	FUN_PASSIVE_RESERVE_1,	//控制域功能保留1 
	FUN_PASSIVE_RESERVE_2,	//控制域功能保留2 
	FUN_PASSIVE_RESERVE_3,	//控制域功能保留3 
	FUN_PASSIVE_RESERVE_4,	//控制域功能保留4 
	FUN_PASSIVE_RESERVE_5,	//控制域功能保留5 
	FUN_PASSIVE_RESERVE_6,	//控制域功能保留6 
	FUN_PASSIVE_RESERVE_7,	//控制域功能保留7 
	FUN_PASSIVE_USERDATA,	//控制域功能用户数据 
	FUN_PASSIVE_NEG,		//控制域功能否认 
	FUN_PASSIVE_RESERVE_10,	//控制域功能保留10 
	FUN_PASSIVE_LINKSTATUS,	//控制域功能链路数据 
	FUN_PASSIVE_RESERVE_12,	//控制域功能保留12 
	FUN_PASSIVE_RESERVE_13,	//控制域功能保留13 
	FUN_PASSIVE_RESERVE_14,	//控制域功能保留14 
	FUN_PASSIVE_RESERVE_15,	//控制域功能保留15 
	//控制域主动站功能码
	FUN_ACTIVE_RESERVE0 = 0,	//控制域功能保留0 
	FUN_ACTIVE_RESET,		//控制域功能复位 
	FUN_ACTIVE_RESERVE2,	//控制域功能保留2 
	FUN_ACTIVE_RESERVE3,	//控制域功能保留3 
	FUN_ACTIVE_USERDATA,	//控制域功能用户数据 
	FUN_ACTIVE_RESERVE5,	//控制域功能保留5 
	FUN_ACTIVE_RESERVE6,	//控制域功能保留6 
	FUN_ACTIVE_RESERVE7,	//控制域功能保留7 
	FUN_ACTIVE_RESERVE8,	//控制域功能保留8 
	FUN_ACTIVE_LINKTEST,	//控制域功能链路测试 
	FUN_ACTIVE_REQUIRE1,	//控制域功能请求1级数据 
	FUN_ACTIVE_REQUIRE2,	//控制域功能请求2级数据 
	FUN_ACTIVE_RESERVE12,	//控制域功能保留12 
	FUN_ACTIVE_RESERVE13,	//控制域功能保留13 
	FUN_ACTIVE_RESERVE14,	//控制域功能保留14 
	FUN_ACTIVE_RESERVE15	//控制域功能保留15 
};


typedef struct{
	uchar u4_function_code:4;	//BIT00-03:控制域功能码 
	uchar bFCV_RESERVE:1;		//BIT04:控制域FCV/保留 
	uchar bFCB_ACD:1;			//BIT05:控制域FCB/ACD 
	uchar bPRM:1;				//BIT06:控制域PRM 
	uchar bDIR:1;				//BIT07:控制域DIR 
}st_control_domain;

typedef union{
	st_control_domain bit;
	uchar all;
}un_control_domain;
/*
**********************控制域*****************************/



/***********************地址域****************************
*/

/*
**********************地址域*****************************/



/***********************应用层****************************
*/



/***********************应用功能码域****************************
*/
enum AFN{
	AFN_ACK_NEG=0, 							//应用层功能码确认/否认 
	AFN_RESET,								//应用层功能码复位 
	AFN_LINKINTERFACETEST,					//应用层功能码链路接口检测 
	AFN_RELAYSTATIONCOMMAND,				//应用层功能码中继站命令 
	AFN_SETCONFIGURATION,					//应用层功能码设置参数 
	AFN_CONTROLCOMMAND,						//应用层功能码控制命令 
	AFN_IDENTIFY_PASSWORDNEGOTIATION,		//应用层功能码身份认证及密钥协商 
	AFN_RESERVE7,							//应用层功能码备用7 
	AFN_REQUIRETERMINALREPORT,				//应用层功能码请求被级联终端主动上报 
	AFN_REQUIRETERMINALCONFIGURATION,		//应用层功能码请求终端配置 
	AFN_QUERYPARAMETER,						//应用层功能码查询参数 
	AFN_RESERVE11,							//应用层功能码备用11 
	AFN_REQUIREDATA1,						//应用层功能码请求1类数据 
	AFN_REQUIREDATA2,						//应用层功能码请求2类数据 
	AFN_REQUIREDATA3,						//应用层功能码请求3类数据 
	AFN_FILETRANSMIT,						//应用层功能码文件传输 
	AFN_DATARELAY,							//应用层功能码数据转发 
	AFN_DEFAULT								//应用层功能码备用集 
};
typedef struct {
	uchar u8_AFN;
}st_AFN_domain;
typedef union {
	st_AFN_domain bit;
}un_AFN_domain;

/*
**********************应用功能码域*****************************/
  


/***********************帧序列域****************************
*/

enum TPV{
	TPV_NOTIPS = 0,		//无时间标签 
	TPV_TIPS			//有时间标签 
};

enum FF{
	MID_MUL=0,			//多帧：中间帧 
	FIN_MUL,			//多帧：结束帧 
	FIR_MUL,			//多帧：第一帧，有后续帧 
	SINGLE				//单帧 
};

enum CON{
	CON_NEG=0,			//不需确认 
	CON_ACK				//需要确认 
};

typedef struct{
	uchar u4_PSEQ_RSEQ:4;	//BIT00-03:启动帧序号/响应帧序号 
	uchar bCON:1;		//BIT04:请求确认标志位 
	uchar u2_FF:2;			//BIT05-06:首末帧标志 
	uchar bTPV:1;		//BIT07:时间标签有效位 
}st_SEQ_domain;

typedef union{
	st_SEQ_domain bit;
	uchar all;
}un_SEQ_domain;

/*
**********************帧序列域*****************************/


/***********************信息类和信息点****************************
*/

enum DA1 {
	DA1_0 = 0,
	DA1_1 = 1,
	DA1_2 = 2,
	DA1_3 = 4,
	DA1_4 = 8,
	DA1_5 = 16,
	DA1_6 = 32,
	DA1_7 = 64,
	DA1_8 = 128
};

enum  DA2{
	DA2_0=0, DA2_1, DA2_2, DA2_3, DA2_4, DA2_5, DA2_6, DA2_7, DA2_8, DA2_9, DA2_10, DA2_11, DA2_12, DA2_13, DA2_14, DA2_15, DA2_16, DA2_17, DA2_18, DA2_19, DA2_20,
	DA2_21, DA2_22, DA2_23, DA2_24, DA2_25, DA2_26, DA2_27, DA2_28, DA2_29, DA2_30, DA2_31, DA2_32, DA2_33, DA2_34, DA2_35, DA2_36, DA2_37, DA2_38, DA2_39, DA2_40,
	DA2_41, DA2_42, DA2_43, DA2_44, DA2_45, DA2_46, DA2_47, DA2_48, DA2_49, DA2_50, DA2_51, DA2_52, DA2_53, DA2_54, DA2_55, DA2_56, DA2_57, DA2_58, DA2_59, DA2_60,
	DA2_61, DA2_62, DA2_63, DA2_64, DA2_65, DA2_66, DA2_67, DA2_68, DA2_69, DA2_70, DA2_71, DA2_72, DA2_73, DA2_74, DA2_75, DA2_76, DA2_77, DA2_78, DA2_79, DA2_80,
	DA2_81, DA2_82, DA2_83, DA2_84, DA2_85, DA2_86, DA2_87, DA2_88, DA2_89, DA2_90, DA2_91, DA2_92, DA2_93, DA2_94, DA2_95, DA2_96, DA2_97, DA2_98, DA2_99, DA2_100,
	DA2_101, DA2_102, DA2_103, DA2_104, DA2_105, DA2_106, DA2_107, DA2_108, DA2_109, DA2_110, DA2_111, DA2_112, DA2_113, DA2_114, DA2_115, DA2_116, DA2_117, DA2_118, DA2_119, DA2_120,
	DA2_121, DA2_122, DA2_123, DA2_124, DA2_125, DA2_126, DA2_127, DA2_128, DA2_129, DA2_130, DA2_131, DA2_132, DA2_133, DA2_134, DA2_135, DA2_136, DA2_137, DA2_138, DA2_139, DA2_140,
	DA2_141, DA2_142, DA2_143, DA2_144, DA2_145, DA2_146, DA2_147, DA2_148, DA2_149, DA2_150, DA2_151, DA2_152, DA2_153, DA2_154, DA2_155, DA2_156, DA2_157, DA2_158, DA2_159, DA2_160,
	DA2_161, DA2_162, DA2_163, DA2_164, DA2_165, DA2_166, DA2_167, DA2_168, DA2_169, DA2_170, DA2_171, DA2_172, DA2_173, DA2_174, DA2_175, DA2_176, DA2_177, DA2_178, DA2_179, DA2_180,
	DA2_181, DA2_182, DA2_183, DA2_184, DA2_185, DA2_186, DA2_187, DA2_188, DA2_189, DA2_190, DA2_191, DA2_192, DA2_193, DA2_194, DA2_195, DA2_196, DA2_197, DA2_198, DA2_199, DA2_200,
	DA2_201, DA2_202, DA2_203, DA2_204, DA2_205, DA2_206, DA2_207, DA2_208, DA2_209, DA2_210, DA2_211, DA2_212, DA2_213, DA2_214, DA2_215, DA2_216, DA2_217, DA2_218, DA2_219, DA2_220,
	DA2_221, DA2_222, DA2_223, DA2_224, DA2_225, DA2_226, DA2_227, DA2_228, DA2_229, DA2_230, DA2_231, DA2_232, DA2_233, DA2_234, DA2_235, DA2_236, DA2_237, DA2_238, DA2_239, DA2_240,
	DA2_241, DA2_242, DA2_243, DA2_244, DA2_245, DA2_246, DA2_247, DA2_248, DA2_249, DA2_250, DA2_251, DA2_252, DA2_253, DA2_254, DA2_255
};

enum DT1
{
	DT1_1 = 1,
	DT1_2 = 2,
	DT1_3 = 4,
	DT1_4 = 8,
	DT1_5 = 16,
	DT1_6 = 32,
	DT1_7 = 64,
	DT1_8 = 128
};

enum DT2
{
	DT2_0=0, DT2_1, DT2_2, DT2_3, DT2_4, DT2_5, DT2_6, DT2_7, DT2_8, DT2_9,DT2_10, 
	DT2_11, DT2_12, DT2_13, DT2_14, DT2_15, DT2_16, DT2_17, DT2_18, DT2_19,DT2_20,
	DT2_21, DT2_22, DT2_23, DT2_24, DT2_25, DT2_26, DT2_27, DT2_28, DT2_29,DT2_30
};

typedef struct {
	uchar u8_DA1;
	uchar u8_DA2;
	uchar u8_DT1;
	uchar u8_DT2;
}st_DADT_domain;

typedef union {
	st_DADT_domain bit;
}un_DADT_domain;


/*
**********************信息类和信息点*****************************/



/***********************附加信息域****************************
*/
typedef struct {
	uchar u8_second;
	uchar u8_minute;
	uchar u8_hour;
	uchar u8_date;
}st_timemark;
typedef struct{
	uchar  u8_urgent_EC;
	uchar  u8_usual_EC;
	uchar  u8_PFC;
	st_timemark timemark;
	uchar  u8_transmitdelay;
}st_AUX_domain;

typedef struct{
	st_AUX_domain bit;
}un_AUX_domain;

/*
**********************附加信息域*****************************/









/*
**********************应用层*****************************/

#endif
//0000 0001
//0000 0010
//0000 0100
//0000 1000
//