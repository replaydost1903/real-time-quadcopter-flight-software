/*
 * File: flight_stabilization_loop.h
 *
 * Code generated for Simulink model 'flight_stabilization_loop'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Apr 24 02:09:04 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_flight_stabilization_loop_h_
#define RTW_HEADER_flight_stabilization_loop_h_
#ifndef flight_stabilization_loop_COMMON_INCLUDES_
#define flight_stabilization_loop_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                          /* flight_stabilization_loop_COMMON_INCLUDES_ */

#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  real_T Integrator[3];                /* '<S2>/Integrator' */
  real_T Sum1[3];                      /* '<S2>/Sum1' */
  real_T Integrator_c[3];              /* '<S1>/Integrator' */
  real_T out[3];                       /* '<S1>/MATLAB Function' */
} DW;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator2_CSTATE[3];        /* '<S1>/Integrator2' */
  real_T Integrator3_CSTATE[3];        /* '<S1>/Integrator3' */
  real_T Integrator4_CSTATE[3];        /* '<S1>/Integrator4' */
  real_T Integrator_CSTATE_g[3];       /* '<S1>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
} X;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE[3];         /* '<S2>/Integrator' */
  real_T Integrator2_CSTATE[3];        /* '<S1>/Integrator2' */
  real_T Integrator3_CSTATE[3];        /* '<S1>/Integrator3' */
  real_T Integrator4_CSTATE[3];        /* '<S1>/Integrator4' */
  real_T Integrator_CSTATE_g[3];       /* '<S1>/Integrator' */
  real_T Integrator1_CSTATE[3];        /* '<S2>/Integrator1' */
} XDot;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE[3];      /* '<S2>/Integrator' */
  boolean_T Integrator2_CSTATE[3];     /* '<S1>/Integrator2' */
  boolean_T Integrator3_CSTATE[3];     /* '<S1>/Integrator3' */
  boolean_T Integrator4_CSTATE[3];     /* '<S1>/Integrator4' */
  boolean_T Integrator_CSTATE_g[3];    /* '<S1>/Integrator' */
  boolean_T Integrator1_CSTATE[3];     /* '<S2>/Integrator1' */
} XDis;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* Constant parameters (default storage) */
typedef struct {
  /* Expression: [Ax 0 0; 0 Ay 0; 0 0 Az]
   * Referenced by: '<S2>/Constant4'
   */
  real_T Constant4_Value[9];
} ConstP;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T w1;                           /* '<Root>/w1' */
  real_T w2;                           /* '<Root>/w2' */
  real_T w3;                           /* '<Root>/w3' */
  real_T w4;                           /* '<Root>/w4' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T zeta[3];                      /* '<Root>/zeta' */
  real_T eta[3];                       /* '<Root>/eta' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[18];
  real_T odeF[3][18];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Continuous states (default storage) */
extern X rtX;

/* Disabled states (default storage) */
extern XDis rtXDis;

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Constant parameters (default storage) */
extern const ConstP rtConstP;

/* Model entry point functions */
extern void flight_stabilization_loop_initialize(void);
extern void flight_stabilization_loop_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'flight_stabilization_loop'
 * '<S1>'   : 'flight_stabilization_loop/R-Dynamics'
 * '<S2>'   : 'flight_stabilization_loop/T-Dynamics'
 * '<S3>'   : 'flight_stabilization_loop/R-Dynamics/MATLAB Function'
 * '<S4>'   : 'flight_stabilization_loop/R-Dynamics/Subsystem2'
 * '<S5>'   : 'flight_stabilization_loop/T-Dynamics/Subsystem1'
 * '<S6>'   : 'flight_stabilization_loop/T-Dynamics/Subsystem2'
 * '<S7>'   : 'flight_stabilization_loop/T-Dynamics/Subsystem3'
 */
#endif                             /* RTW_HEADER_flight_stabilization_loop_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
