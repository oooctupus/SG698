#ifndef _SG698_H_
#define _SG698_H_

/**************************�궨��*********************************************
*/

#define start1_head  0
#define length_head  1
#define start2_head  5
#define control_head 6
#define address_head 7
#define AFN_head     12
#define SEQ_head     13

/*
*************************�궨��**********************************************/


/*******************************************************************************
�������Ͷ��壬�˴�������DSPƽ̨��ͬ��������ֲ�ر��趨 
*******************************************************************************/

typedef unsigned char   uchar;
typedef unsigned short  uint16;
typedef unsigned int   	uint32;
typedef float           float32;

/*******************************************************************************
ͨѶ��������
*******************************************************************************/


/***********************�������Ʊ���****************************
*/

enum SciCCOMSTATE{
	SciCRECEIVE=0,		//ͨѶ״̬���� 
	SciCPROCESS,		//ͨѶ״̬���� 
	SciCWAITSEND,		//ͨѶ״̬�ȴ� 
	SciCSEND			//ͨѶ״̬���� 
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
**********************�������Ʊ���*****************************/


/***********************������****************************
*/
enum LEN{
	LEN_DISABLE=0,	//��������� 
	LEN_ENABLE,		//������ʹ�� 
	LEN_RESERVE_2,	//�������� 
	LEN_RESERVE_3	//�������� 
};

typedef struct{
	uint16 u2_status:2;		//BIT00-01:������״̬[0:����,1:ʹ��,2:����2,3:����3]
	uint16 u14_length:14;	//BIT02-15:����������ʾ�ĳ��� 
}st_length_domain;

typedef union{
	st_length_domain bit;
	uint16 all;
}un_length_domain;
/*
**********************������*****************************/



/***********************������****************************
*/
enum DIR{
	DIR_DOWN=0,			//���������б��� 
	DIR_UP				//���������б��� 
};

enum PRM{
	PRM_PASSIVE=0,		//������Ӷ�վ 
	PRM_ACTIVE			//����������վ 
};

enum FCB_ACD{
	FCB_0=0,			//������֡����0 
	FCB_1,				//������֡����1 
	ACD_NOT_URGENT = 0,	//����������������¼� 
	ACD_URGENT			//���������������Ҫ�¼� 
};


enum FCV{
	FCV_DISABLE=0,		//������֡������Ч 
	FCV_ENABLE			//������֡����ʹ�� 
};

enum FUN{						
	//������Ӷ�վ������ 
	FUN_PASSIVE_ACK=0,		//���������Ͽ� 
	FUN_PASSIVE_RESERVE_1,	//�������ܱ���1 
	FUN_PASSIVE_RESERVE_2,	//�������ܱ���2 
	FUN_PASSIVE_RESERVE_3,	//�������ܱ���3 
	FUN_PASSIVE_RESERVE_4,	//�������ܱ���4 
	FUN_PASSIVE_RESERVE_5,	//�������ܱ���5 
	FUN_PASSIVE_RESERVE_6,	//�������ܱ���6 
	FUN_PASSIVE_RESERVE_7,	//�������ܱ���7 
	FUN_PASSIVE_USERDATA,	//���������û����� 
	FUN_PASSIVE_NEG,		//�������ܷ��� 
	FUN_PASSIVE_RESERVE_10,	//�������ܱ���10 
	FUN_PASSIVE_LINKSTATUS,	//����������·���� 
	FUN_PASSIVE_RESERVE_12,	//�������ܱ���12 
	FUN_PASSIVE_RESERVE_13,	//�������ܱ���13 
	FUN_PASSIVE_RESERVE_14,	//�������ܱ���14 
	FUN_PASSIVE_RESERVE_15,	//�������ܱ���15 
	//����������վ������
	FUN_ACTIVE_RESERVE0 = 0,	//�������ܱ���0 
	FUN_ACTIVE_RESET,		//�������ܸ�λ 
	FUN_ACTIVE_RESERVE2,	//�������ܱ���2 
	FUN_ACTIVE_RESERVE3,	//�������ܱ���3 
	FUN_ACTIVE_USERDATA,	//���������û����� 
	FUN_ACTIVE_RESERVE5,	//�������ܱ���5 
	FUN_ACTIVE_RESERVE6,	//�������ܱ���6 
	FUN_ACTIVE_RESERVE7,	//�������ܱ���7 
	FUN_ACTIVE_RESERVE8,	//�������ܱ���8 
	FUN_ACTIVE_LINKTEST,	//����������·���� 
	FUN_ACTIVE_REQUIRE1,	//������������1������ 
	FUN_ACTIVE_REQUIRE2,	//������������2������ 
	FUN_ACTIVE_RESERVE12,	//�������ܱ���12 
	FUN_ACTIVE_RESERVE13,	//�������ܱ���13 
	FUN_ACTIVE_RESERVE14,	//�������ܱ���14 
	FUN_ACTIVE_RESERVE15	//�������ܱ���15 
};


typedef struct{
	uchar u4_function_code:4;	//BIT00-03:���������� 
	uchar bFCV_RESERVE:1;		//BIT04:������FCV/���� 
	uchar bFCB_ACD:1;			//BIT05:������FCB/ACD 
	uchar bPRM:1;				//BIT06:������PRM 
	uchar bDIR:1;				//BIT07:������DIR 
}st_control_domain;

typedef union{
	st_control_domain bit;
	uchar all;
}un_control_domain;
/*
**********************������*****************************/



/***********************��ַ��****************************
*/

/*
**********************��ַ��*****************************/



/***********************Ӧ�ò�****************************
*/



/***********************Ӧ�ù�������****************************
*/
enum AFN{
	AFN_ACK_NEG=0, 							//Ӧ�ò㹦����ȷ��/���� 
	AFN_RESET,								//Ӧ�ò㹦���븴λ 
	AFN_LINKINTERFACETEST,					//Ӧ�ò㹦������·�ӿڼ�� 
	AFN_RELAYSTATIONCOMMAND,				//Ӧ�ò㹦�����м�վ���� 
	AFN_SETCONFIGURATION,					//Ӧ�ò㹦�������ò��� 
	AFN_CONTROLCOMMAND,						//Ӧ�ò㹦����������� 
	AFN_IDENTIFY_PASSWORDNEGOTIATION,		//Ӧ�ò㹦���������֤����ԿЭ�� 
	AFN_RESERVE7,							//Ӧ�ò㹦���뱸��7 
	AFN_REQUIRETERMINALREPORT,				//Ӧ�ò㹦�������󱻼����ն������ϱ� 
	AFN_REQUIRETERMINALCONFIGURATION,		//Ӧ�ò㹦���������ն����� 
	AFN_QUERYPARAMETER,						//Ӧ�ò㹦�����ѯ���� 
	AFN_RESERVE11,							//Ӧ�ò㹦���뱸��11 
	AFN_REQUIREDATA1,						//Ӧ�ò㹦��������1������ 
	AFN_REQUIREDATA2,						//Ӧ�ò㹦��������2������ 
	AFN_REQUIREDATA3,						//Ӧ�ò㹦��������3������ 
	AFN_FILETRANSMIT,						//Ӧ�ò㹦�����ļ����� 
	AFN_DATARELAY,							//Ӧ�ò㹦��������ת�� 
	AFN_DEFAULT								//Ӧ�ò㹦���뱸�ü� 
};
typedef struct {
	uchar u8_AFN;
}st_AFN_domain;
typedef union {
	st_AFN_domain bit;
}un_AFN_domain;

/*
**********************Ӧ�ù�������*****************************/
  


/***********************֡������****************************
*/

enum TPV{
	TPV_NOTIPS = 0,		//��ʱ���ǩ 
	TPV_TIPS			//��ʱ���ǩ 
};

enum FF{
	MID_MUL=0,			//��֡���м�֡ 
	FIN_MUL,			//��֡������֡ 
	FIR_MUL,			//��֡����һ֡���к���֡ 
	SINGLE				//��֡ 
};

enum CON{
	CON_NEG=0,			//����ȷ�� 
	CON_ACK				//��Ҫȷ�� 
};

typedef struct{
	uchar u4_PSEQ_RSEQ:4;	//BIT00-03:����֡���/��Ӧ֡��� 
	uchar bCON:1;		//BIT04:����ȷ�ϱ�־λ 
	uchar u2_FF:2;			//BIT05-06:��ĩ֡��־ 
	uchar bTPV:1;		//BIT07:ʱ���ǩ��Чλ 
}st_SEQ_domain;

typedef union{
	st_SEQ_domain bit;
	uchar all;
}un_SEQ_domain;

/*
**********************֡������*****************************/


/***********************��Ϣ�����Ϣ��****************************
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
**********************��Ϣ�����Ϣ��*****************************/



/***********************������Ϣ��****************************
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
**********************������Ϣ��*****************************/









/*
**********************Ӧ�ò�*****************************/

#endif
//0000 0001
//0000 0010
//0000 0100
//0000 1000
//