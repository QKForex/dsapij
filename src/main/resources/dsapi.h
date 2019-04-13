/******************************************************************************
*
*	DataStage API Public Header file
*
*	Module:	dsapi.h
*
*	Licensed Materials - Property of IBM
*   	5724-Q36
*	Copyright IBM Corp. 2004, 2013
*
*	Copyright 1997 VMARK Software Inc. - All Rights Reserved
*
*	This is unpublished proprietary source code of VMARK Software Inc.
*	The copyright notice above does not evidence any actual or intended
*	publication of such source code.
*
*******************************************************************************
*
*	Maintenance log - insert most recent change descriptions at top
*
*       Date....  RTC#    WHO Description.........................................
*	06/26/13  170769  CST Added role checking error return code
*  	06/27/13  172570   DW Added LogDetailFull
*	04/12/13  167130  ALC Enable handling of rowcount > MAXINT
*	13-Mar-13 164206   HL  Added DSA_PRJ_AUTOPURGE_ENABLED
*	10-May-12 117137   HL  Added WLM status constants
*   02/12/12 97190    LAG Windows native port
*	28-Nov-11 117137   HL Added DSJE_INVALIDQUEUE
*
*	Date.... Request  WHO Description.........................................
*   	04/18/11    94787 RRD Removed the confidentiality statement
*   	23/04/09 00146856 EAP Added missing prototype for DSGetLogEventIds
*                         Added DSJ_RUNRESTART
*	10/10/08 00129581 CST Add tokens for project protect function
*
*	Date	 ECASE# WHO Description.........................................
*       08/31/07 121347 CST Add DSJS_QUEUED definition
*	11/16/06 111216 PEJ Add code for DSJ.PROJECTPATH
*	07/12/06 100706 HL  Updated for Hawk (8.0)
*
*	02/02/06 88510 PEJ Add Restartable status to -jobinfo
*	09/09/04 59804 PEJ Added DSJ.INSTALLTAG, DSJ.TCPPORT to return DSEngine install details
*	08/24/04 51247 LA  Added missing error numbers and DSA_PRJ_PX_DEPLOY_GENERATE_XML
*	08/19/04 59135 LA  Fix tokens for admin options
*	08/24/04 54826 DJA Added extra repository usage error messages
*	08/19/04 59135 LA  Fix tokens for admin options
*	08/13/04 54826 DJA Changed DSREPOSJOBUSAGE structure
*	08/10/04 54826 DJA Removed BOOL from prototypes for UNIX
*	07/13/04 54826 DJA Added DSGetReposInfo
*	07/07/04 51247 LA  Added administration functions and error codes
*	02/24/04 41612 JRW Added DSSetDisableProjectHandler & DSSetDisableJobHandler
*	11/14/03 39502 DJA Added DSSetGenerateOpMetaData
*	12/13/02  9982 PEJ Added new functions for DSGetJobInfo()
*	08/01/02  8677 AMW HP-UX porting.
*	09/22/02  9543 HL  Added support for job ID
*	09/04/02  9543 EAP More AXCIOM Enhancements
*	07/30/02  9543 EAP AXCIOM Enhancements
*	07/13/01 34570 PEJ Modified to match Kobe version of JOBCONTROL.H
*	11/15/99 25696 EAP Added DSJ_LINKSQLSTATE and DSJ_LINKDBMSCODE
*	09/22/99 23421 ALC Handle user name correctly
*	03/16/99 24009 DJA DSServerMessage now returns message in an already
*	                   allocated buffer.
*	01/21/99 24009 THG Added extra parameter to DSServerMessage() function.
*	11/12/98 24009 THG Added DSServerMessage for NLS
*	10/22/97 21724 AGM Add DSJE_INCOMPATIBLE_SERVER error code
*	10/21/97 21289 DJA Added Extra Error Codes for DSGetParamInfo(Decryption)
*	09/18/97 21380 AGM Module created
*
*******************************************************************************
*
*	WARNING: When editing this file please ensure that the equivalent
*		 tokens in JOBCONTROL.H, DSJ_XFUNCS.H, and dsrconst.bas
*		 are all kept in sync.
*
******************************************************************************/

#ifndef H_DSAPI
#define H_DSAPI

#include <time.h>

#ifdef  __cplusplus
extern "C" {
#endif

/*****************************************************************************/

#define DSAPI_VERSION	1	/* Version number of DSAPI */

/*****************************************************************************/

/*
 * Job information data and keys
 */

typedef struct _DSJOBINFO
{
    int infoType;		/* Key indicating type of information */
    union
    {
	int jobStatus;		/* Current status of job */
	char *jobController;	/* Name of controlling job */
	time_t jobStartTime;	/* Date and time when job started */
	int jobWaveNumber;	/* Wave number of current or last run */
	char *userStatus;	/* Last set user status */
	char *stageList;	/* List of stage names in job */
	char *paramList;	/* List of job parameter names */
	char *jobName;	        /* Name of this job */
	int jobControl;		/* Current job control status */
	int jobPid;		/* Job process id */
	time_t jobLastTime;	/* Date and time when job finished */
        char *jobInvocations;   /* List of job invocation ids */
	int jobInterimStatus;	/* Interim status of job */
        char *jobInvocationId;  /* Job invocation id */
	char *jobDesc;
	char *stageList2;
	char *jobElapsed;
        int jobDMIService ;	/* Job is a DMI (aka WEB) service */
        int jobMultiInvokable ;	/* Job can be multiply invoked    */
        char * jobFullDesc ;    /* Full job description           */
        int    jobRestartable ; /* Job is restartable		  */
    } info;			/* Information value */
} DSJOBINFO;

/* 'infoType' values... */

#define DSJ_JOBSTATUS		1	/* Current status of the job. */
#define DSJ_JOBNAME     	2	/* Name of the job referenced by JobHandle. */
#define DSJ_JOBCONTROLLER	3	/* Name of job controlling the job referenced by JobHandle. */
#define DSJ_JOBSTARTTIMESTAMP	4	/* Date and time when the job started. */
#define DSJ_JOBWAVENO		5	/* Wave number of last or current run. */
#define DSJ_PARAMLIST		6	/* List of job parameter names */
#define DSJ_STAGELIST		7	/* List of names of stages in job */
#define DSJ_USERSTATUS		8	/* Value, if any,  set as the user status by the job. */
#define DSJ_JOBCONTROL          9       /* Job control STOP/SUSPEND/RESUME */
#define DSJ_JOBPID              10      /* Process id of DSD.RUN process */
#define DSJ_JOBLASTTIMESTAMP    11      /* Server date/time of job last finished: "YYYY-MM-DD HH:MM:SS" */
#define DSJ_JOBINVOCATIONS      12      /* Comma-separated list of job invocation ids */
#define DSJ_JOBINTERIMSTATUS    13      /* Current interim status of job  */
#define DSJ_JOBINVOCATIONID     14      /* Invocation name of the job referenced */
#define DSJ_JOBDESC		15	/* Job description */
#define DSJ_STAGELIST2		16	/* list of stages not in DSJ.STAGELIST */
#define DSJ_JOBELAPSED		17	/* Job Elapsed time in seconds */
#define DSJ_JOBEOTCOUNT         18
#define DSJ_JOBEOTTIMESTAMP     19
#define DSJ_JOBDMISERVICE       20	/* Job is a DMI (aka WEB) service */
#define DSJ_JOBMULTIINVOKABLE   21	/* Job can be multiply invoked    */
#define DSJ_JOBFULLDESC         22	/* Full job description           */
#define DSJ_JOBRESTARTABLE	24	/* Job can be restarted	       	  */

/* 'jobStatus' values... */

#define DSJS_RUNNING		0	/* Job running */
#define DSJS_RUNOK		1	/* Job finished a normal run with no warnings */
#define DSJS_RUNWARN		2	/* Job finished a normal run with warnings */
#define DSJS_RUNFAILED		3	/* Job finished a normal run with a fatal error */
#define DSJS_QUEUED		4	/* Job queued waiting for resource allocation */
#define DSJS_VALOK		11	/* Job finished a validation run with no warnings */
#define DSJS_VALWARN		12	/* Job finished a validation run with warnings */
#define DSJS_VALFAILED		13	/* Job failed a validation run  */
#define DSJS_RESET		21	/* Job finished a reset run */
#define DSJS_CRASHED		96	/* Job was stopped by some indeterminate action */
#define DSJS_STOPPED		97	/* Job was stopped by operator intervention (can't tell run type) */
#define DSJS_NOTRUNNABLE 	98	/* Job has not been compiled */
#define DSJS_NOTRUNNING		99	/* Any other status */

/*****************************************************************************/

/*
 * Log detail information data and keys
 */

typedef struct _DSLOGDETAIL
{
    int eventId;		/* Id of this event */
    time_t timestamp;		/* Data and time event occurred */
    int type;			/* Type of event */
    char *username;		/* User name associated with event */
    char *fullMessage;		/* Full description of event */
} DSLOGDETAIL;

/*
 * Log detail information data and keys
 */

typedef struct _DSLOGDETAILFULL
{
    int eventId;        /* Id of this event */
    time_t timestamp;   /* Data and time event occurred */
    int type;           /* Type of event */
    char *username;     /* User name associated with event */
    char *fullMessage;  /* Full description of event */
    char *messageId;    /* Message Id */
    char *invocationId; /* Invocation Id, if any */
} DSLOGDETAILFULL;

/* 'type' values... */

#define DSJ_LOGINFO		1	/* Information message. */
#define DSJ_LOGWARNING		2	/* Warning message. */
#define DSJ_LOGFATAL		3	/* Fatal error message. */
#define DSJ_LOGREJECT		4	/* Rejected row message. */
#define DSJ_LOGSTARTED		5	/* Job started message. */
#define DSJ_LOGRESET		6	/* Job reset message. */
#define DSJ_LOGBATCH		7	/* Batch control */
#define DSJ_LOGOTHER		98	/* Category other than above */
#define DSJ_LOGANY		99	/* Any type of event */

/*****************************************************************************/

/*
 * Log summary information data and keys
 */

typedef struct _DSLOGEVENT
{
    int eventId;		/* Id of this event */
    time_t timestamp;		/* Data and time event occurred */
    int type;			/* Type of event */
    char *message;		/* Short event message */
} DSLOGEVENT;

/* 'type' values are the same as those in the DSLOGDETAIL structure */

/*****************************************************************************/

/*
 * Stage link information data and keys
 */

typedef struct _DSLINKINFO
{
    int infoType;		/* Key indicating type of information */
    union
    {
	DSLOGDETAIL lastError;	/* Last error message from link */
	int rowCount;		/* number of rows that have passed down link */
	char *linkName;	        /* Name of this link */
	char *linkSQLState;	/* SQL state for last error */
	char *linkDBMSCode;	/* DBMC code for last error */
	char *linkDesc;
	char *linkedStage;
	char *rowCountList;
    } info;			/* Information value */
} DSLINKINFO;

/* 'infoType' values... */

#define DSJ_LINKLASTERR		1	/* Last error message reported by link. */
#define DSJ_LINKNAME 	        2	/* Actual name of link */
#define DSJ_LINKROWCOUNT 	3	/* Number of rows that have passed down the link. */
#define DSJ_LINKSQLSTATE	4       /* SQLSTATE value from Last error message */
#define DSJ_LINKDBMSCODE	5       /* DBMSCODE value from Last error message */
#define DSJ_LINKDESC		6	/* Link description */
#define DSJ_LINKSTAGE		7	/* stage at other end of link */
#define DSJ_INSTROWCOUNT	8	/* comma seperated list of rowcounts for each stage instance */
#define DSJ_LINKEOTROWCOUNT     9
#define DSJ_LINKEXTROWCOUNT	10	/* Extended rowcount, using strings */

/*****************************************************************************/

/*
 * Job parameter value and keys
 */

typedef struct _DSPARAM
{
    int paramType;		/* Type of parameter */
    union
    {
	char *pString;		/* String type */
	char *pEncrypt;		/* Encrypted string */
	int pInt;		/* Integer */
	float pFloat;		/* Float */
	char *pPath;		/* Pathname */
	char *pListValue;	/* String from a list */
	char *pDate;		/* Date string */
	char *pTime;		/* Time string */
    } paramValue;		/* Parameter value */
} DSPARAM;

/* 'paramType' values... */

#define DSJ_PARAMTYPE_STRING	0
#define DSJ_PARAMTYPE_ENCRYPTED	1
#define DSJ_PARAMTYPE_INTEGER	2
#define DSJ_PARAMTYPE_FLOAT	3
#define DSJ_PARAMTYPE_PATHNAME	4
#define DSJ_PARAMTYPE_LIST	5
#define DSJ_PARAMTYPE_DATE	6
#define DSJ_PARAMTYPE_TIME	7

/*****************************************************************************/

/*
 * Job parameter data information and keys
 */

typedef struct _DSPARAMINFO
{
    DSPARAM defaultValue;	/* Default value of parameter */
    char *helpText;		/* Description of parameter */
    char *paramPrompt;		/* Prompt for the parameter */
    int paramType;		/* Type of parameter */
    DSPARAM desDefaultValue;	/* Designer set default value of parameter */
    char *listValues;		/* Set of valid strings for List type parameter */
    char *desListValues;	/* Set of designer set valid strings for list type parameter */
    int promptAtRun;		/* Flag indicating prompt required at run time. */
} DSPARAMINFO;

/* 'infoType' values... */

#define DSJ_PARAMDEFAULT	1	/* Current default value */
#define DSJ_PARAMHELPTEXT	2	/* Long description */
#define DSJ_PARAMPROMPT		3	/* Prompt string */
#define DSJ_PARAMTYPE		4	/* Parameter type */
#define DSJ_PARAMVALUE		5	/* Current value */
#define DSJ_PARAMDES_DEFAULT	6	/* Default value set for parameter at design time */
#define DSJ_PARAMLISTVALUES	7	/* Current list of allowed/suggested values for 'list' type parameters */
#define DSJ_PARAMDES_LISTVALUES	8	/* The list of allowed/suggested values for 'list' type parameters as set at design time. */
#define DSJ_PARAMPROMPT_AT_RUN	9	/* Indication that the parameter value should always be prompted for at the start of a job run. */
#define DSJ_PARAMALL		99	/* Everything */

/* 'paramType' values are the same as in the DSPARAM structure */

/*****************************************************************************/

/*
 * Project parameter data information and keys
 */

typedef struct _DSPROJECTINFO
{
    int infoType;		/* Key indicating type of information */
    union
    {
	char *jobList;		/* List of names of all jobs in the project */
	char *projectName;	/* Name of the current project */
	char *projectPath;	/* Directory path of the current project */
	char *hostName;		/* Host name of the server */
        char *installTag ;	/* Install tag of current server engine */
        char *tcpPort ;		/* TCP port    of current server engine */
    } info;			/* Information value */
} DSPROJECTINFO;

/* 'infoType' values... */

#define DSJ_JOBLIST		1	/* List of jobs in project */
#define DSJ_PROJECTNAME		2	/* Name of current project */
#define DSJ_HOSTNAME		3	/* Host name of the server */
#define DSJ_INSTALLTAG		4	/* Install tag of the server DSEngine */
#define DSJ_TCPPORT		5	/* TCP port    of the server DSEngine */
#define DSJ_PROJECTPATH		6	/* Directory path of current project */

/*****************************************************************************/

/*
 * Repos information
 */

struct _DSREPOSJOBINFO;
typedef struct _DSREPOSJOBINFO DSREPOSJOBINFO;

struct _DSREPOSJOBINFO
{
	char* jobname;    /* Includes category */
	int jobtype;      /* InfoType constant */
	DSREPOSJOBINFO* nextjob; /* link to next job */
};

typedef struct _DSREPOSINFO
{
	int infoType;
	union
	{
		DSREPOSJOBINFO* jobs; /* linked list of found jobs */
	} info;
} DSREPOSINFO;

#define DSS_JOBS           1        /* The Object Type to return */
#define DSS_JOB_ALL        15       /* list all jobs */
#define DSS_JOB_SERVER     1        /* list all server jobs */
#define DSS_JOB_PARALLEL   2        /* list all parallel jobs */
#define DSS_JOB_MAINFRAME  4        /* list all mainframe jobs */
#define DSS_JOB_SEQUENCE   8        /* list all sequence jobs */

/*****************************************************************************/

/*
 * Repos Usage
 */

struct _DSREPOSUSAGEJOB;
typedef struct _DSREPOSUSAGEJOB DSREPOSUSAGEJOB;

struct _DSREPOSUSAGEJOB
{
	char *jobname; /* Job and cat name */
	int jobtype;   /* type of job */
	DSREPOSUSAGEJOB *nextjob; /* next job in linked list of jobs at same level */
	DSREPOSUSAGEJOB *childjob; /* first child job in linked list */

};

/*
   Usage structure that can be expanded to include
   other top level repository objects
*/
typedef struct _DSREPOSUSAGE
{
	int infoType;
	union
	{
		DSREPOSUSAGEJOB *jobs; /* linked list of jobs */
	} info;
} DSREPOSUSAGE;

#define DSS_JOB_USES_JOB                    1
#define DSS_JOB_USEDBY_JOB                  2
#define DSS_JOB_HASSOURCE_TABLEDEF          3
#define DSS_JOB_HASTARGET_TABLEDEF          4
#define DSS_JOB_HASSOURCEORTARGET_TABLEDEF  5


/*************************************************************************                           ****/

/*
 * Stage information and keys
 */

typedef struct _DSSTAGEINFO
{
    int infoType;		/* Key indicating type of information */
    union
    {
	DSLOGDETAIL lastError;	/* Last error message (log) from a link */
	char *typeName;		/* Name of stage type */
	int inRowNum;		/* Primary links input row number */
	char *linkList;		/* List of stage link names */
	char *stageName;	/* Name of current stage */
	char *varList;	        /* List of stage variable names */
	time_t stageStartTime;	/* Date and time when stage started  */
	time_t stageEndTime;	/* Date and time when stage finished */
	char *linkTypes;
	char *stageDesc;
	char *instList;
	char *cpuList;
	char *stageElapsed;
	char *pidList;
        int  stageStatus;
	char *custInfoList;     /* List of custom info names */
    } info;			/* Information value */
} DSSTAGEINFO;

/* 'infoType' values... */

#define DSJ_LINKLIST		1	/* List of stage link names */
#define DSJ_STAGELASTERR	2	/* Last error message reported from any link of the stage. */
#define DSJ_STAGENAME	        3	/* Actual name of stage */
#define DSJ_STAGETYPE		4	/* Stage type name. */
#define DSJ_STAGEINROWNUM	5	/* Primary links input row number.   */
#define DSJ_VARLIST	        6	/* list of stage variable names      */
#define DSJ_STAGESTARTTIMESTAMP	7	/* Date and time when stage started  */
#define DSJ_STAGEENDTIMESTAMP	8	/* Date and time when stage finished */
#define DSJ_STAGEDESC		9	/* Stage Description */
#define DSJ_STAGEINST		10	/* Comma-seperated list of stage instance ids */
#define DSJ_STAGECPU		11	/* Comma-seperated list of stage instance CPU in seconds */
#define DSJ_LINKTYPES		12	/* Comma-seperated list of link types */
#define DSJ_STAGEELAPSED	13	/* Stage elapsed time in seconds */
#define DSJ_STAGEPID		14	/* Comma-seperated list of stage instance PIDs */
#define DSJ_STAGESTATUS		15	/* Stage status */
#define DSJ_STAGEEOTCOUNT       16
#define DSJ_STAGEEOTTIMESTAMP   17
#define DSJ_CUSTINFOLIST        18      /* list of custom info names */

/*****************************************************************************/

/*
 * Stage variable information and keys
 */

typedef struct _DSVARINFO
{
    int infoType;		/* Key indicating type of information */
    union
    {
	char *varValue;
	char *varDesc;
    } info;			/* Information value */
} DSVARINFO;

/* 'infoType' values... */

#define DSJ_VARVALUE		1	/* Stage variable value */
#define DSJ_VARDESC		2	/* Stage variable description */

/*****************************************************************************/

/*
 * Stage variable information and keys
 */

typedef struct _DSCUSTINFO
{
    int infoType;		/* Key indicating type of information */
    union
    {
	char *custInfoValue;
	char *custInfoDesc;
    } info;			/* Information value */
} DSCUSTINFO;

/* 'infoType' values... */

#define DSJ_CUSTINFOVALUE		1	/* Custom info value */
#define DSJ_CUSTINFODESC		2	/* custom info description */

/*****************************************************************************/
/*
 * Job report information and keys
 */

typedef struct _DSREPORTINFO
{
	int reportType;
	union
	{
	char *reportText;
	} info;
} DSREPORTINFO;

#define DSJ_REPORT0		0
#define DSJ_REPORT1		1
#define DSJ_REPORT2		2


/*****************************************************************************/

/*
 * Key values for DSRunJob()...
 */

#define DSJ_RUNNORMAL		1	/* Standard job run. */
#define DSJ_RUNRESET		2	/* Job is to be reset. */
#define DSJ_RUNVALIDATE		3	/* Job is to be validated only. */
#define DSJ_RUNRESTART		4   /* Restart job with previous parameters, job must be in Restartable state. */

/*****************************************************************************/

/*
 * Key values for DSSetJobLimit()...
 */

#define DSJ_LIMITWARN		1	/* Job to be stopped after LimitValue warning events */
#define DSJ_LIMITROWS		2	/* Stages to be limited to LimitValue rows */


/*****************************************************************************/

/*
 * Key values for DSSetProjectPropery()...
 */

#define DSA_OSHVISIBLEFLAG		"OSHVisibleFlag"

/* NB: The rest of these MUST match the tokens in DSA_COMMON.H */

#define DSA_PRJ_JOBADMIN_ENABLED	"JobAdminEnabled"
#define DSA_PRJ_RTCP_ENABLED		"RTCPEnabled"
#define DSA_PRJ_PROTECTION_ENABLED	"ProtectionEnabled"
#define DSA_PRJ_PX_ADVANCED_RUNTIME_OPTS	"PXAdvRTOptions"
#define DSA_PRJ_PX_DEPLOY_CUSTOM_ACTION	"PXDeployCustomAction"
#define DSA_PRJ_PX_DEPLOY_JOBDIR_TEMPLATE	"PXDeployJobDirectoryTemplate"
#define DSA_PRJ_PX_BASEDIR		"PXRemoteBaseDirectory"
#define DSA_PRJ_PX_DEPLOY_GENERATE_XML	"PXDeployGenerateXML"
#define DSA_ENVVAR_TYPE_STRING		"String"
#define DSA_ENVVAR_TYPE_ENCRYPTED	"Encrypted"
#define DSA_PRJ_AUTOPURGE_ENABLED       "PurgeEnabled"

/*****************************************************************************/

/*
 * DSAPI Error codes...
 */

/* Errors generated by the DataStage server */

#define DSJE_NOERROR		0	/* No error */
#define DSJE_BADHANDLE		-1	/* Invalid JobHandle. */
#define DSJE_BADSTATE		-2	/* Job is not in the right state (must be compiled & not running). */
#define DSJE_BADPARAM		-3	/* ParamName is not a parameter name in the job. */
#define DSJE_BADVALUE		-4	/* LimitValue is not appropriate for the limiting condition type. */
#define DSJE_BADTYPE		-5	/* Invalid EventType value */
#define DSJE_WRONGJOB		-6	/* Job for this JobHandle was not started from a call to DSRunJob by the current process. */
#define DSJE_BADSTAGE		-7	/* StageName does not refer to a known stage in the job. */
#define DSJE_NOTINSTAGE 	-8	/* INTERNAL TO SERVER */
#define DSJE_BADLINK		-9	/* LinkName does not refer to a known link for the stage in question. */
#define DSJE_JOBLOCKED		-10	/* Job is locked by another user */
#define DSJE_JOBDELETED 	-11	/* Job has been deleted ! */
#define DSJE_BADNAME		-12	/* Job name badly formed */
#define DSJE_BADTIME		-13	/* Timestamp parameter was badly formed */
#define DSJE_TIMEOUT		-14	/* Given up waiting for something to happen */
#define DSJE_DECRYPTERR		-15	/* Decryption of encrypted value failed */
#define DSJE_NOACCESS		-16	/* Cannot get values, Default values or Design Default values
                     		   	   for any job except the current job (Job Handle == DSJ.ME) */
#define DSJE_NOTEMPLATE         -17     /* Cannot find template file */
#define DSJE_BADTEMPLATE        -18     /* Error encountered when processing template file */
#define DSJE_NOPARAM            -19     /* Parameter name missing - field does not look like 'name:value' */
#define DSJE_NOFILEPATH         -20     /* File path name not given */
#define DSJE_CMDERROR           -21     /* Error when executing external command */
#define DSJE_BADVAR             -22     /* Stage Variable name not recognised. */
#define DSJE_NONUNIQUEID        -23     /* Id already exists for a job in this project.*/
#define DSJE_INVALIDID          -24     /* Invalid Job Id */
#define DSJE_INVALIDQUEUE       -25     /* Invalid Queue */
#define DSJE_WLMDISABLED	-26     /* WLM is not enabled */
#define DSJE_WLMNOTRUNNING	-27     /* WLM is not running */
#define DSJE_NOROLEPERMISSIONS	-28     /* User does not have required role permissions to perform this operation */

#define DSJE_REPERROR		-99	/* General server 'other error' */

/* Errors generated from the administration API functions */

#define DSJE_NOTADMINUSER	-100	/* User is not an administrative user */
#define DSJE_ISADMINFAILED	-101	/* Unable to determine if user is an administrative user */
#define DSJE_READPROJPROPERTY	-102	/* Reading project properties failed */
#define DSJE_WRITEPROJPROPERTY	-103	/* Writing project properties failed */
#define DSJE_BADPROPERTY	-104	/* Property name is invalid */
#define DSJE_PROPNOTSUPPORTED	-105	/* Unsupported property */
#define DSJE_BADPROPVALUE	-106	/* Value given is not valid for this property */
#define DSJE_OSHVISIBLEFLAG	-107	/* Failed to set OSHVisible value */
#define DSJE_BADENVVARNAME	-108	/* Invalid environment variable name */
#define DSJE_BADENVVARTYPE	-109	/* Invalid environment variable type */
#define DSJE_BADENVVARPROMPT	-110	/* Missing environment variable prompt */
#define DSJE_READENVVARDEFNS	-111	/* Reading environment variable definitions failed */
#define DSJE_READENVVARVALUES	-112	/* Reading environment variable values failed */
#define DSJE_WRITEENVVARDEFNS	-113	/* Writing environment variable definitions failed */
#define DSJE_WRITEENVVARVALUES	-114	/* Writing environment variable values failed */
#define DSJE_DUPENVVARNAME	-115	/* Environment variable name already exists */
#define DSJE_BADENVVAR		-116	/* Environment variable name not recognised */
#define DSJE_NOTUSERDEFINED	-117	/* Environment variable is not user defined */
#define DSJE_BADBOOLEANVALUE	-118	/* Invalid value given for a boolean environment variable */
#define DSJE_BADNUMERICVALUE	-119	/* Invalid value given for a numeric environment variable */
#define DSJE_BADLISTVALUE	-120	/* Invalid value given for a list environment variable */
#define DSJE_PXNOTINSTALLED	-121	/* PX not installed */
#define DSJE_ISPARALLELLICENCED	-122	/* Failed to find out if PX licensed */
#define DSJE_ENCODEFAILED	-123	/* Encoding of an encrypted value failed */
#define DSJE_DELPROJFAILED	-124	/* Deletion of project definition & SCHEMA failed */
#define DSJE_DELPROJFILESFAILED	-125	/* Deletion of project files & subdirectories failed */
#define DSJE_LISTSCHEDULEFAILED	-126	/* Failed to get list of scheduled jobs for project */
#define DSJE_CLEARSCHEDULEFAILED	-127	/* Failed to clear scheduled jobs for project */
#define DSJE_BADPROJNAME	-128	/* Project name contains invalid characters */
#define DSJE_GETDEFAULTPATHFAILED	-129	/* Failed to get default path for project */
#define DSJE_BADPROJLOCATION	-130 	/* Project location path contains invalid characters */
#define DSJE_INVALIDPROJECTLOCATION	-131	/* Project location is invalid */
#define DSJE_OPENFAILED		-132	/* Failed to open file */
#define DSJE_READUFAILED	-133	/* Failed to lock administration record */
#define DSJE_ADDPROJECTBLOCKED	-134	/* Administration record locked by another user */
#define DSJE_ADDPROJECTFAILED	-135	/* Adding project failed */
#define DSJE_LICENSEPROJECTFAILED	-136	/* Licensing project failed */
#define DSJE_RELEASEFAILED	-137	/* Failed to release administration record */
#define DSJE_DELETEPROJECTBLOCKED	-138   /* Project locked by another user */
#define DSJE_NOTAPROJECT	-139    /* Failed to log to project */
#define DSJE_ACCOUNTPATHFAILED	-140    /* Failed to get account path */
#define DSJE_LOGTOFAILED	-141    /* Failed to log to UV account */
#define DSJE_PROTECTFAILED      -142	/* Protect or unprotect project failed */

/* Errors from the Repository Info and Repository Usage API functions */

#define DSJE_UNKNOWN_JOBNAME -201 /* Could not find the supplied job name */

/* Errors generated with the DSAPI */

#define DSJE_NOMORE		-1001	/* All events matching the filter criteria have been returned. */
#define DSJE_BADPROJECT 	-1002	/* Unknown project name */
#define DSJE_NO_DATASTAGE 	-1003	/* DataStage not installed on server */
#define DSJE_OPENFAIL		-1004	/* Attempt to open job failed */
#define DSJE_NO_MEMORY		-1005	/* Malloc failure */
#define DSJE_SERVER_ERROR 	-1006	/* Server generated error - error msg text desribes it */
#define DSJE_NOT_AVAILABLE	-1007	/* Not data available from server */
#define DSJE_BAD_VERSION	-1008	/* Version is DSOpenProjectEx is invalid */
#define DSJE_INCOMPATIBLE_SERVER -1009	/* Server version incompatible with this version of the DSAPI */
#define DSJE_DOMAINLOGTOFAILED  -1010   /* Failed to authenticate to Domain*/
#define DSJE_NOPRIVILEGE    -1011   /* The isf user does not have sufficient DataStage privileges */


/*****************************************************************************/

/*
 * DSAPI Project Handle (IC Session Handle). This structure is private to the
 * DSAPI and should be considered a 'black box' by any applications making use
 * of the DSAPI. It encapsulates the InterCALL session id.
 */

typedef struct _DSPROJECT
{
    int dsapiVersionNo;		/* Version of DSAPI being used */
    int sessionId;		/* The InterCALL session id */
    unsigned char valueMark;	/* This sessions value mark character */
    unsigned char fieldMark;	/* This sessions field mark character */
} * DSPROJECT;

/*****************************************************************************/

/*
 * DSAPI Job Handle. This structure is private to the DSAPI and should be
 * considered a 'black box' by any applications making use of the DSAPI. Its
 * content is liable to change between revisions of the DSAPI.
 */

typedef struct _DSJOB
{
    DSPROJECT hProject;		/* Reference to project handle for job */
    char *serverJobHandle;	/* Text of handle to job on server */
    char *logData;		/* Cached log summary data */
    int logDataLen;		/* Size of log summary data */
    int logDataPsn;		/* Current position in logData */
} * DSJOB;

/*****************************************************************************/

/*
 * DSAPI Function prototypes...
 */

#define DSOpenProject(X) DSOpenProjectEx(DSAPI_VERSION, X)

#if defined(WIN32) || defined(_WIN32)
#ifdef	DSAPI_DECL
#define DllImport    __declspec( dllexport )
#else
#define DllImport    __declspec( dllimport )
#endif
#define DllExport    __declspec( dllexport )
#else
#define DllImport
#define DllExport
#endif

#if defined(__STDC__) || defined(WIN32) || defined(_WIN32) || defined (hpux)
#define dsproto(x) x
#else
#define dsproto(x) ()
#endif

DllImport int DSServerMessage(const char *MsgIdStr, const char *DefMsg, const char *Prms[10], char *pMessage, int SizeMessage);
DllImport int DSCloseJob dsproto((DSJOB));
DllImport int DSCloseProject dsproto((DSPROJECT));
DllImport int DSFindFirstLogEntry dsproto((DSJOB, int, time_t, time_t, int, DSLOGEVENT *));
DllImport int DSFindNextLogEntry dsproto((DSJOB, DSLOGEVENT *));
DllImport int DSGetJobInfo dsproto((DSJOB, int, DSJOBINFO *));
DllImport int DSGetLastError dsproto((void));
DllImport char *DSGetLastErrorMsg dsproto((DSPROJECT));
DllImport int DSGetLinkInfo dsproto((DSJOB, char *, char *, int, DSLINKINFO *));
DllImport int DSGetVarInfo dsproto((DSJOB, char *, char *, int, DSVARINFO *));
DllImport int DSGetCustInfo dsproto((DSJOB, char *, char *, int, DSCUSTINFO *));
DllImport int DSGetLogEntry dsproto((DSJOB, int, DSLOGDETAIL *));
DllImport int DSGetLogEntryFull dsproto((DSJOB, int, DSLOGDETAILFULL *));
DllImport int DSGetNewestLogId dsproto((DSJOB, int));
DllImport int DSGetParamInfo dsproto((DSJOB, char *, DSPARAMINFO *));
DllImport int DSGetProjectInfo dsproto((DSPROJECT, int, DSPROJECTINFO *));
DllImport char *DSGetProjectList dsproto((void));
DllImport int DSGetReposInfo dsproto((DSPROJECT, int, int, const char *, const char *, int, DSREPOSINFO *));
DllImport int DSGetReposUsage dsproto((DSPROJECT, int, const char *, int, DSREPOSUSAGE *));
DllImport int DSGetStageInfo dsproto((DSJOB, char *, int, DSSTAGEINFO *));
DllImport int DSLockJob dsproto((DSJOB));
DllImport int DSLogEvent dsproto((DSJOB, int, char *, char *));
DllImport DSJOB DSOpenJob dsproto((DSPROJECT, char *));
DllImport DSPROJECT DSOpenProjectEx dsproto((int, char *));
DllImport int DSRunJob dsproto((DSJOB, int));
DllImport int DSSetJobLimit dsproto((DSJOB, int, int));
DllImport int DSSetGenerateOpMetaData dsproto((DSJOB, int));
DllImport int DSSetDisableProjectHandler dsproto((DSJOB, int));
DllImport int DSSetDisableJobHandler dsproto((DSJOB, int));
DllImport int DSSetParam dsproto((DSJOB, char *, DSPARAM *));
DllImport void DSSetServerParams dsproto((char *, char *, char *, char *));
DllImport int DSStopJob dsproto((DSJOB));
DllImport int DSUnlockJob dsproto((DSJOB));
DllImport int DSWaitForJob dsproto((DSJOB));
DllImport int DSMakeJobReport dsproto((DSJOB, int, char *, DSREPORTINFO *));
DllImport char *DSGetIdForJob dsproto((DSPROJECT, char *));
DllImport int DSSetIdForJob dsproto((DSPROJECT, char *, char *));
DllImport char *DSJobNameFromJobId dsproto((DSPROJECT, char *));
DllImport int DSGetLogEventIds dsproto((DSJOB, int, char*, char**));
DllImport int DSSetJobQueue dsproto((DSJOB, char *));
DllImport int DSGetWLMEnabled dsproto((void));
DllImport char *DSGetQueueList dsproto((void));

/* Administration functions - nothing to do with job control - these are
   used by the dsadmin command line tool */

DllImport int DSAddProject dsproto((char *, char *));
DllImport int DSDeleteProject dsproto ((char *));
DllImport int DSSetProjectProperty dsproto((DSPROJECT, char *, char *));
DllImport int DSAddEnvVar dsproto((DSPROJECT, char *, char *, char *, char *));
DllImport int DSSetEnvVar dsproto((DSPROJECT, char *, char *));
DllImport int DSDeleteEnvVar dsproto((DSPROJECT, char *));
DllImport char *DSListProjectProperties dsproto((DSPROJECT));
DllImport char *DSListEnvVars dsproto((DSPROJECT));

#undef dsproto

/*****************************************************************************/

#ifdef  __cplusplus
}
#endif

#endif

/* End of module */

