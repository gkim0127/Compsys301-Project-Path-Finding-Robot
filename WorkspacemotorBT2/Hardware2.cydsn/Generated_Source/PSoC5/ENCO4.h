/*******************************************************************************
* File Name: ENCO4.h  
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

#if !defined(CY_PINS_ENCO4_H) /* Pins ENCO4_H */
#define CY_PINS_ENCO4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "ENCO4_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 ENCO4__PORT == 15 && ((ENCO4__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    ENCO4_Write(uint8 value);
void    ENCO4_SetDriveMode(uint8 mode);
uint8   ENCO4_ReadDataReg(void);
uint8   ENCO4_Read(void);
void    ENCO4_SetInterruptMode(uint16 position, uint16 mode);
uint8   ENCO4_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the ENCO4_SetDriveMode() function.
     *  @{
     */
        #define ENCO4_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define ENCO4_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define ENCO4_DM_RES_UP          PIN_DM_RES_UP
        #define ENCO4_DM_RES_DWN         PIN_DM_RES_DWN
        #define ENCO4_DM_OD_LO           PIN_DM_OD_LO
        #define ENCO4_DM_OD_HI           PIN_DM_OD_HI
        #define ENCO4_DM_STRONG          PIN_DM_STRONG
        #define ENCO4_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define ENCO4_MASK               ENCO4__MASK
#define ENCO4_SHIFT              ENCO4__SHIFT
#define ENCO4_WIDTH              1u

/* Interrupt constants */
#if defined(ENCO4__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in ENCO4_SetInterruptMode() function.
     *  @{
     */
        #define ENCO4_INTR_NONE      (uint16)(0x0000u)
        #define ENCO4_INTR_RISING    (uint16)(0x0001u)
        #define ENCO4_INTR_FALLING   (uint16)(0x0002u)
        #define ENCO4_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define ENCO4_INTR_MASK      (0x01u) 
#endif /* (ENCO4__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ENCO4_PS                     (* (reg8 *) ENCO4__PS)
/* Data Register */
#define ENCO4_DR                     (* (reg8 *) ENCO4__DR)
/* Port Number */
#define ENCO4_PRT_NUM                (* (reg8 *) ENCO4__PRT) 
/* Connect to Analog Globals */                                                  
#define ENCO4_AG                     (* (reg8 *) ENCO4__AG)                       
/* Analog MUX bux enable */
#define ENCO4_AMUX                   (* (reg8 *) ENCO4__AMUX) 
/* Bidirectional Enable */                                                        
#define ENCO4_BIE                    (* (reg8 *) ENCO4__BIE)
/* Bit-mask for Aliased Register Access */
#define ENCO4_BIT_MASK               (* (reg8 *) ENCO4__BIT_MASK)
/* Bypass Enable */
#define ENCO4_BYP                    (* (reg8 *) ENCO4__BYP)
/* Port wide control signals */                                                   
#define ENCO4_CTL                    (* (reg8 *) ENCO4__CTL)
/* Drive Modes */
#define ENCO4_DM0                    (* (reg8 *) ENCO4__DM0) 
#define ENCO4_DM1                    (* (reg8 *) ENCO4__DM1)
#define ENCO4_DM2                    (* (reg8 *) ENCO4__DM2) 
/* Input Buffer Disable Override */
#define ENCO4_INP_DIS                (* (reg8 *) ENCO4__INP_DIS)
/* LCD Common or Segment Drive */
#define ENCO4_LCD_COM_SEG            (* (reg8 *) ENCO4__LCD_COM_SEG)
/* Enable Segment LCD */
#define ENCO4_LCD_EN                 (* (reg8 *) ENCO4__LCD_EN)
/* Slew Rate Control */
#define ENCO4_SLW                    (* (reg8 *) ENCO4__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define ENCO4_PRTDSI__CAPS_SEL       (* (reg8 *) ENCO4__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define ENCO4_PRTDSI__DBL_SYNC_IN    (* (reg8 *) ENCO4__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define ENCO4_PRTDSI__OE_SEL0        (* (reg8 *) ENCO4__PRTDSI__OE_SEL0) 
#define ENCO4_PRTDSI__OE_SEL1        (* (reg8 *) ENCO4__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define ENCO4_PRTDSI__OUT_SEL0       (* (reg8 *) ENCO4__PRTDSI__OUT_SEL0) 
#define ENCO4_PRTDSI__OUT_SEL1       (* (reg8 *) ENCO4__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define ENCO4_PRTDSI__SYNC_OUT       (* (reg8 *) ENCO4__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(ENCO4__SIO_CFG)
    #define ENCO4_SIO_HYST_EN        (* (reg8 *) ENCO4__SIO_HYST_EN)
    #define ENCO4_SIO_REG_HIFREQ     (* (reg8 *) ENCO4__SIO_REG_HIFREQ)
    #define ENCO4_SIO_CFG            (* (reg8 *) ENCO4__SIO_CFG)
    #define ENCO4_SIO_DIFF           (* (reg8 *) ENCO4__SIO_DIFF)
#endif /* (ENCO4__SIO_CFG) */

/* Interrupt Registers */
#if defined(ENCO4__INTSTAT)
    #define ENCO4_INTSTAT            (* (reg8 *) ENCO4__INTSTAT)
    #define ENCO4_SNAP               (* (reg8 *) ENCO4__SNAP)
    
	#define ENCO4_0_INTTYPE_REG 		(* (reg8 *) ENCO4__0__INTTYPE)
#endif /* (ENCO4__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_ENCO4_H */


/* [] END OF FILE */
