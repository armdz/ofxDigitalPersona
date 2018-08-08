

//****************************************************************************
//**
//** Copyright (c) 2010 DigitalPersona, Inc.
//**
//****************************************************************************
//**
//** version: 5.0.3
//** Built on "Jul 18 2010" "12:01:27"
//**
//****************************************************************************



#ifndef __DPFR_VER__
#define __DPFR_VER__ ((0x5<<8) | 0x0)
#endif //__DPFR_VER__

#pragma once
#ifndef __FT_RC_CODES_H
#define __FT_RC_CODES_H

#ifdef __cplusplus
extern "C" {
#endif

#define FT_RETCODE int


/**************** return codes common to all the toolkit components *****************/
/**************** common return codes are in the range [-4095 4095] *****************/

#define FT_OK                          (0)    /* The function succeeded. */

/* Errors: negative numbers. Range: [-1, -255] */
#define FT_ERR_NO_INIT                 (-1)   /* The fingerprint feature extraction module or the fingerprint 
                                                 comparison module is not initialized. */
#define FT_ERR_INVALID_PARAM           (-2)   /* One or more parameters are not valid. */
#define FT_ERR_NOT_IMPLEMENTED         (-3)   /* The called function was not implemented. */

#define FT_ERR_IO                      (-4)   /* A generic I/O file error occurred. */

#define FT_ERR_NO_MEMORY               (-7)   /* There is not enough memory to perform the action. */
#define FT_ERR_INTERNAL                (-8)   /* An unknown internal error occurred. */
#define FT_ERR_BAD_INI_SETTING         (-9)   /* Initialization settings are corrupted. */

#define FT_ERR_UNKNOWN_DEVICE         (-10)   /* The requested device is not known. */
#define FT_ERR_INVALID_BUFFER         (-11)   /* A buffer is not valid. */
#define FT_ERR_FEAT_LEN_TOO_SHORT     (-16)   /* The specified fingerprint feature set or fingerprint template 
                                                 buffer size is too small.  */
#define FT_ERR_INVALID_CONTEXT        (-17)   /* The given context is not valid. */
#define FT_ERR_INVALID_COLLECTION     (-21)   /* The given collection is invalid. For example feature sets from the different readers were used for enrollment */
#define FT_ERR_INVALID_FTRS_TYPE      (-29)   /* The feature set purpose is not valid. */
#define FT_ERR_FTRS_INVALID           (-32)   /* Decrypted fingerprint features are invalid.  Decryption may have failed. */
#define FT_ERR_UNKNOWN_EXCEPTION      (-33)   /* An unknown exception occurred. */

/* Warnings: positive numbers. Range: [1, 255] */
#define FT_WRN_NO_INIT                 (1)    /* The fingerprint feature extraction module or the fingerprint 
                                                 comparison module are not initialized. */
#define FT_WRN_INTERNAL                (8)    /* An internal error occurred. */
#define FT_WRN_KEY_NOT_FOUND           (9)    /* The fingerprint feature extraction module or the fingerprint 
                                                 comparison module could not find an initialization setting.  */
#define FT_WRN_UNKNOWN_DEVICE         (11)    /* The fingerprint reader is not known.  */
#define FT_WRN_TIMEOUT                (12)    /* The function has timed out. */


#ifdef __cplusplus
}
#endif


#endif // __FT_RC_CODES_H
