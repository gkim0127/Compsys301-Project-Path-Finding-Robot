/*******************************************************************************
* File Name: Ground.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Ground_H) /* Pins Ground_H */
#define CY_PINS_Ground_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Ground_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Ground__PORT == 15 && ((Ground__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Ground_Write(uint8 value);
void    Ground_SetDriveMode(uint8 mode);
uint8   Ground_ReadDataReg(void);
uint8   Ground_Read(void);
void    Ground_SetInterruptMode(uint16 position, uint16 mode);
uint8   Ground_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Ground_SetDriveMode() function.
     *  @{
     */
        #define Ground_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Ground_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Ground_DM_RES_UP          PIN_DM_RES_UP
        #define Ground_DM_RES_DWN         PIN_DM_RES_DWN
        #define Ground_DM_OD_LO           PIN_DM_OD_LO
        #define Ground_DM_OD_HI           PIN_DM_OD_HI
        #define Ground_DM_STRONG          PIN_DM_STRONG
        #define Ground_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Ground_MASK               Ground__MASK
#define Ground_SHIFT              Ground__SHIFT
#define Ground_WIDTH              1u

/* Interrupt constants */
#if defined(Ground__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Ground_SetInterruptMode() function.
     *  @{
     */
        #define Ground_INTR_NONE      (uint16)(0x0000u)
        #define Ground_INTR_RISING    (uint16)(0x0001u)
        #define Ground_INTR_FALLING   (uint16)(0x0002u)
        #define Ground_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Ground_INTR_MASK      (0x01u) 
#endif /* (Ground__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Ground_PS                     (* (reg8 *) Ground__PS)
/* Data Register */
#define Ground_DR                     (* (reg8 *) Ground__DR)
/* Port Number */
#define Ground_PRT_NUM                (* (reg8 *) Ground__PRT) 
/* Connect to Analog Globals */                                                  
#define Ground_AG                     (* (reg8 *) Ground__AG)                       
/* Analog MUX bux enable */
#define Ground_AMUX                   (* (reg8 *) Ground__AMUX) 
/* Bidirectional Enable */                                                        
#define Ground_BIE                    (* (reg8 *) Ground__BIE)
/* Bit-mask for Aliased Register Access */
#define Ground_BIT_MASK               (* (reg8 *) Ground__BIT_MASK)
/* Bypass Enable */
#define Ground_BYP                    (* (reg8 *) Ground__BYP)
/* Port wide control signals */                                                   
#define Ground_CTL                    (* (reg8 *) Ground__CTL)
/* Drive Modes */
#define Ground_DM0                    (* (reg8 *) Ground__DM0) 
#define Ground_DM1                    (* (reg8 *) Ground__DM1)
#define Ground_DM2                    (* (reg8 *) Ground__DM2) 
/* Input Buffer Disable Override */
#define Ground_INP_DIS                (* (reg8 *) Ground__INP_DIS)
/* LCD Common or Segment Drive */
#define Ground_LCD_COM_SEG            (* (reg8 *) Ground__LCD_COM_SEG)
/* Enable Segment LCD */
#define Ground_LCD_EN                 (* (reg8 *) Ground__LCD_EN)
/* Slew Rate Control */
#define Ground_SLW                    (* (reg8 *) Ground__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Ground_PRTDSI__CAPS_SEL       (* (reg8 *) Ground__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Ground_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Ground__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Ground_PRTDSI__OE_SEL0        (* (reg8 *) Ground__PRTDSI__OE_SEL0) 
#define Ground_PRTDSI__OE_SEL1        (* (reg8 *) Ground__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Ground_PRTDSI__OUT_SEL0       (* (reg8 *) Ground__PRTDSI__OUT_SEL0) 
#define Ground_PRTDSI__OUT_SEL1       (* (reg8 *) Ground__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Ground_PRTDSI__SYNC_OUT       (* (reg8 *) Ground__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Ground__SIO_CFG)
    #define Ground_SIO_HYST_EN        (* (reg8 *) Ground__SIO_HYST_EN)
    #define Ground_SIO_REG_HIFREQ     (* (reg8 *) Ground__SIO_REG_HIFREQ)
    #define Ground_SIO_CFG            (* (reg8 *) Ground__SIO_CFG)
    #define Ground_SIO_DIFF           (* (reg8 *) Ground__SIO_DIFF)
#endif /* (Ground__SIO_CFG) */

/* Interrupt Registers */
#if defined(Ground__INTSTAT)
    #define Ground_INTSTAT            (* (reg8 *) Ground__INTSTAT)
    #define Ground_SNAP               (* (reg8 *) Ground__SNAP)
    
	#define Ground_0_INTTYPE_REG 		(* (reg8 *) Ground__0__INTTYPE)
#endif /* (Ground__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Ground_H */


/* [] END OF FILE */
