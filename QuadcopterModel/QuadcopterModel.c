/*
 * File: QuadcopterModel.c
 *
 * Code generated for Simulink model 'QuadcopterModel'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 23.2 (R2023b) 01-Aug-2023
 * C/C++ source code generated on : Thu Apr 24 19:04:42 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "QuadcopterModel.h"
#include <math.h>
#include <string.h>
#include "rtwtypes.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

/* Continuous states */
X rtX;

/* Disabled State Vector */
XDis rtXDis;

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/* private model entry point functions */
extern void QuadcopterModel_derivatives(void);

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 18;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  QuadcopterModel_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  QuadcopterModel_step();
  QuadcopterModel_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  QuadcopterModel_step();
  QuadcopterModel_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void QuadcopterModel_step(void)
{
  real_T b_x[9];
  real_T x[9];
  real_T y[9];
  real_T rtb_Add[3];
  real_T rtb_Divide2[3];
  real_T Integrator;
  real_T Integrator2_CSTATE;
  real_T Integrator_0;
  real_T rtb_Divide1;
  real_T rtb_Product6;
  real_T rtb_Tri5;
  real_T t2;
  real_T x_tmp;
  real_T y_tmp;
  real_T y_tmp_0;
  real_T y_tmp_1;
  real_T y_tmp_2;
  int32_T i;
  int32_T p3;
  if (rtmIsMajorTimeStep(rtM)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&rtM->solverInfo,((rtM->Timing.clockTick0+1)*
      rtM->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(rtM)) {
    rtM->Timing.t[0] = rtsiGetT(&rtM->solverInfo);
  }

  /* Integrator: '<S2>/Integrator' */
  rtDW.Integrator[0] = rtX.Integrator_CSTATE[0];
  rtDW.Integrator[1] = rtX.Integrator_CSTATE[1];
  rtDW.Integrator[2] = rtX.Integrator_CSTATE[2];

  /* Product: '<S2>/Divide1' incorporates:
   *  Constant: '<S2>/Constant1'
   *  Gain: '<S5>/Gain'
   *  Inport: '<Root>/w1'
   *  Inport: '<Root>/w2'
   *  Inport: '<Root>/w3'
   *  Inport: '<Root>/w4'
   *  Sum: '<S5>/Sum'
   */
  rtb_Divide1 = (((rtU.w1 + rtU.w2) + rtU.w3) + rtU.w4) * 2.98E-6 / 1.468;

  /* Product: '<S2>/Product2' incorporates:
   *  Constant: '<S2>/Constant4'
   */
  /* Limited  Integrator  */
  t2 = rtDW.Integrator[1];
  Integrator = rtDW.Integrator[0];
  Integrator_0 = rtDW.Integrator[2];
  for (i = 0; i < 3; i++) {
    /* Product: '<S2>/Divide2' incorporates:
     *  Constant: '<S2>/Constant3'
     *  Constant: '<S2>/Constant4'
     *  Product: '<S2>/Product2'
     */
    rtb_Divide2[i] = ((rtConstP.Constant4_Value[i + 3] * t2 +
                       rtConstP.Constant4_Value[i] * Integrator) +
                      rtConstP.Constant4_Value[i + 6] * Integrator_0) / 1.468;

    /* Integrator: '<S1>/Integrator2' */
    Integrator2_CSTATE = rtX.Integrator2_CSTATE[i];
    if (Integrator2_CSTATE >= 1.5707963267948966) {
      Integrator2_CSTATE = 1.5707963267948966;
      rtX.Integrator2_CSTATE[i] = 1.5707963267948966;
    } else if (Integrator2_CSTATE <= -1.5707963267948966) {
      Integrator2_CSTATE = -1.5707963267948966;
      rtX.Integrator2_CSTATE[i] = -1.5707963267948966;
    }

    /* Integrator: '<S1>/Integrator3' */
    rtb_Tri5 = rtX.Integrator3_CSTATE[i];
    if (rtb_Tri5 >= 3.1415926535897931) {
      rtb_Tri5 = 3.1415926535897931;
      rtX.Integrator3_CSTATE[i] = 3.1415926535897931;
    } else if (rtb_Tri5 <= -3.1415926535897931) {
      rtb_Tri5 = -3.1415926535897931;
      rtX.Integrator3_CSTATE[i] = -3.1415926535897931;
    }

    /* Integrator: '<S1>/Integrator4' */
    rtb_Product6 = rtX.Integrator4_CSTATE[i];
    if (rtb_Product6 >= 6.2831853071795862) {
      rtb_Product6 = 6.2831853071795862;
      rtX.Integrator4_CSTATE[i] = 6.2831853071795862;
    } else if (rtb_Product6 <= 0.0) {
      rtb_Product6 = 0.0;
      rtX.Integrator4_CSTATE[i] = 0.0;
    }

    /* Sum: '<S1>/Add' incorporates:
     *  Integrator: '<S1>/Integrator2'
     *  Integrator: '<S1>/Integrator3'
     *  Integrator: '<S1>/Integrator4'
     */
    rtb_Add[i] = (Integrator2_CSTATE + rtb_Tri5) + rtb_Product6;

    /* Integrator: '<S1>/Integrator' */
    Integrator2_CSTATE = rtX.Integrator_CSTATE_g[i];
    if (Integrator2_CSTATE >= 34.906585039886586) {
      Integrator2_CSTATE = 34.906585039886586;
      rtX.Integrator_CSTATE_g[i] = 34.906585039886586;
    } else if (Integrator2_CSTATE <= -34.906585039886586) {
      Integrator2_CSTATE = -34.906585039886586;
      rtX.Integrator_CSTATE_g[i] = -34.906585039886586;
    }

    /* Integrator: '<S1>/Integrator' */
    rtDW.Integrator_c[i] = Integrator2_CSTATE;
  }

  /* Trigonometry: '<S6>/Tri1' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  t2 = cos(rtb_Add[0]);

  /* Trigonometry: '<S6>/Tri2' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  Integrator = sin(rtb_Add[1]);

  /* Trigonometry: '<S6>/Tri5' */
  rtb_Tri5 = cos(rtb_Add[2]);

  /* Trigonometry: '<S6>/Tri4' */
  rtb_Product6 = sin(rtb_Add[2]);

  /* Trigonometry: '<S6>/Tri' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  Integrator_0 = sin(rtb_Add[0]);

  /* Trigonometry: '<S6>/Tri3' incorporates:
   *  MATLAB Function: '<S1>/MATLAB Function'
   */
  Integrator2_CSTATE = cos(rtb_Add[1]);

  /* Sum: '<S2>/Sum1' incorporates:
   *  Constant: '<S7>/Constant1'
   *  Product: '<S2>/Product7'
   *  Product: '<S6>/Product2'
   *  Product: '<S6>/Product3'
   *  Product: '<S6>/Product4'
   *  Product: '<S6>/Product5'
   *  Product: '<S6>/Product6'
   *  Sum: '<S6>/Sum2'
   *  Sum: '<S6>/Sum3'
   *  Trigonometry: '<S6>/Tri'
   *  Trigonometry: '<S6>/Tri1'
   *  Trigonometry: '<S6>/Tri2'
   *  Trigonometry: '<S6>/Tri3'
   */
  rtDW.Sum1[0] = (t2 * Integrator * rtb_Tri5 + rtb_Product6 * Integrator_0) *
    rtb_Divide1 - rtb_Divide2[0];
  rtDW.Sum1[1] = (rtb_Product6 * Integrator * t2 - rtb_Tri5 * Integrator_0) *
    rtb_Divide1 - rtb_Divide2[1];
  rtDW.Sum1[2] = (Integrator2_CSTATE * t2 * rtb_Divide1 - 9.81) - rtb_Divide2[2];

  /* Outport: '<Root>/roll' */
  rtY.roll = rtb_Add[0];

  /* Outport: '<Root>/pitch' */
  rtY.pitch = rtb_Add[1];

  /* Outport: '<Root>/yaw' */
  rtY.yaw = rtb_Add[2];

  /* MATLAB Function: '<S1>/MATLAB Function' incorporates:
   *  Gain: '<S4>/Gain1'
   *  Gain: '<S4>/Gain2'
   *  Gain: '<S4>/Gain3'
   *  Inport: '<Root>/w1'
   *  Inport: '<Root>/w2'
   *  Inport: '<Root>/w3'
   *  Inport: '<Root>/w4'
   *  Sum: '<S4>/Sum1'
   *  Sum: '<S4>/Sum2'
   *  Sum: '<S4>/Sum5'
   *  Trigonometry: '<S6>/Tri2'
   */
  x[0] = 0.004856;
  x[3] = 0.0;
  x[6] = -0.004856 * Integrator;
  x[1] = 0.0;
  rtb_Divide1 = Integrator_0 * Integrator_0;
  rtb_Tri5 = t2 * t2;
  x[4] = rtb_Tri5 * 0.004856 + rtb_Divide1 * 0.008801;
  rtb_Product6 = -0.003945 * t2 * Integrator_0 * Integrator2_CSTATE;
  x[7] = rtb_Product6;
  x[2] = -0.004856 * Integrator;
  x[5] = rtb_Product6;
  x_tmp = Integrator2_CSTATE * Integrator2_CSTATE;
  x[8] = (rtb_Divide1 * 0.004856 * x_tmp + Integrator * Integrator * 0.004856) +
    rtb_Tri5 * 0.008801 * x_tmp;
  y[0] = 0.0;
  y_tmp = rtDW.Integrator_c[1] * t2 * Integrator_0;
  y_tmp_0 = 0.004856 * rtDW.Integrator_c[2] * Integrator2_CSTATE;
  y[3] = ((rtb_Divide1 * rtDW.Integrator_c[2] * Integrator2_CSTATE + y_tmp) *
          -0.003945 + 0.003945 * rtDW.Integrator_c[2] * rtb_Tri5 *
          Integrator2_CSTATE) - y_tmp_0;
  y[6] = 0.003945 * rtDW.Integrator_c[2] * t2 * Integrator_0 * x_tmp;
  y[1] = ((rtDW.Integrator_c[2] * Integrator_0 * Integrator2_CSTATE + y_tmp) *
          0.003945 + -0.003945 * rtDW.Integrator_c[2] * rtb_Tri5 *
          Integrator2_CSTATE) + y_tmp_0;
  y[4] = 0.003945 * rtDW.Integrator_c[0] * t2 * Integrator_0;
  y_tmp_0 = 0.004856 * rtDW.Integrator_c[2] * rtb_Divide1 * Integrator *
    Integrator2_CSTATE;
  y_tmp_1 = 0.008801 * rtDW.Integrator_c[2] * rtb_Tri5 * Integrator *
    Integrator2_CSTATE;
  y[7] = (-0.004856 * rtDW.Integrator_c[2] * Integrator * Integrator2_CSTATE +
          y_tmp_0) + y_tmp_1;
  y_tmp_2 = 0.004856 * rtDW.Integrator_c[1] * Integrator2_CSTATE;
  y[2] = -0.003945 * rtDW.Integrator_c[2] * x_tmp * Integrator_0 * t2 - y_tmp_2;
  y[5] = ((((rtb_Divide1 * rtDW.Integrator_c[0] * Integrator2_CSTATE + y_tmp *
             Integrator) * 0.003945 + -0.003945 * rtDW.Integrator_c[0] *
            rtb_Tri5 * Integrator2_CSTATE) + 0.004856 * rtDW.Integrator_c[2] *
           Integrator * Integrator2_CSTATE) - y_tmp_0) - y_tmp_1;
  y[8] = ((-0.003945 * rtDW.Integrator_c[0] * t2 * Integrator_0 * x_tmp -
           0.004856 * rtDW.Integrator_c[1] * rtb_Divide1 * Integrator2_CSTATE *
           Integrator) - 0.008801 * rtDW.Integrator_c[1] * rtb_Tri5 *
          Integrator2_CSTATE * Integrator) + y_tmp_2 * Integrator;
  memcpy(&b_x[0], &x[0], 9U * sizeof(real_T));
  i = 3;
  p3 = 6;
  b_x[1] = 0.0;
  b_x[2] = x[2] / 0.004856;
  b_x[4] = x[4];
  b_x[5] = rtb_Product6 - 0.0 * b_x[2];
  b_x[7] = rtb_Product6 - x[6] * 0.0;
  b_x[8] = x[8] - b_x[2] * x[6];
  if (fabs(b_x[5]) > fabs(x[4])) {
    i = 6;
    p3 = 3;
    b_x[1] = b_x[2];
    b_x[2] = 0.0;
    b_x[4] = b_x[5];
    b_x[5] = x[4];
    rtb_Divide1 = b_x[7];
    b_x[7] = b_x[8];
    b_x[8] = rtb_Divide1;
  }

  b_x[5] /= b_x[4];
  b_x[8] -= b_x[5] * b_x[7];
  rtb_Divide1 = (b_x[1] * b_x[5] - b_x[2]) / b_x[8];
  t2 = -(b_x[7] * rtb_Divide1 + b_x[1]) / b_x[4];
  x[0] = ((1.0 - 0.0 * t2) - b_x[6] * rtb_Divide1) / 0.004856;
  x[1] = t2;
  x[2] = rtb_Divide1;
  rtb_Divide1 = -b_x[5] / b_x[8];
  t2 = (1.0 - b_x[7] * rtb_Divide1) / b_x[4];
  x[i] = -(0.0 * t2 + b_x[6] * rtb_Divide1) / 0.004856;
  x[i + 1] = t2;
  x[i + 2] = rtb_Divide1;
  rtb_Divide1 = 1.0 / b_x[8];
  t2 = -b_x[7] * rtb_Divide1 / b_x[4];
  x[p3] = -(0.0 * t2 + b_x[6] * rtb_Divide1) / 0.004856;
  x[p3 + 1] = t2;
  x[p3 + 2] = rtb_Divide1;
  t2 = rtDW.Integrator_c[0];
  Integrator = rtDW.Integrator_c[1];
  Integrator_0 = rtDW.Integrator_c[2];
  rtb_Divide2[0] = (rtU.w4 - rtU.w2) * 6.705E-7;
  rtb_Divide2[1] = (rtU.w3 - rtU.w1) * 6.705E-7;
  rtb_Divide2[2] = (((rtU.w2 - rtU.w1) - rtU.w3) + rtU.w4) * 1.14E-7;
  for (i = 0; i < 3; i++) {
    rtb_Add[i] = rtb_Divide2[i] - ((y[i + 3] * Integrator + y[i] * t2) + y[i + 6]
      * Integrator_0);
  }

  t2 = rtb_Add[1];
  Integrator = rtb_Add[0];
  Integrator_0 = rtb_Add[2];
  for (i = 0; i < 3; i++) {
    rtDW.out[i] = (x[i + 3] * t2 + x[i] * Integrator) + x[i + 6] * Integrator_0;
  }

  /* Outport: '<Root>/x' incorporates:
   *  Integrator: '<S2>/Integrator1'
   */
  rtY.x = rtX.Integrator1_CSTATE[0];

  /* Outport: '<Root>/y' incorporates:
   *  Integrator: '<S2>/Integrator1'
   */
  rtY.y = rtX.Integrator1_CSTATE[1];

  /* Outport: '<Root>/z' incorporates:
   *  Integrator: '<S2>/Integrator1'
   */
  rtY.z = rtX.Integrator1_CSTATE[2];
  if (rtmIsMajorTimeStep(rtM)) {
    rt_ertODEUpdateContinuousStates(&rtM->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++rtM->Timing.clockTick0;
    rtM->Timing.t[0] = rtsiGetSolverStopTime(&rtM->solverInfo);

    {
      /* Update absolute timer for sample time: [1.0s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 1.0, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      rtM->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void QuadcopterModel_derivatives(void)
{
  XDot *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot *) rtM->derivs);

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[0] = rtDW.Sum1[0];

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  lsat = (rtX.Integrator2_CSTATE[0] <= -1.5707963267948966);
  usat = (rtX.Integrator2_CSTATE[0] >= 1.5707963267948966);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[0] > 0.0)) || (usat &&
       (rtDW.Integrator_c[0] < 0.0))) {
    _rtXdot->Integrator2_CSTATE[0] = rtDW.Integrator_c[0];
  } else {
    /* in saturation */
    _rtXdot->Integrator2_CSTATE[0] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator3' */
  lsat = (rtX.Integrator3_CSTATE[0] <= -3.1415926535897931);
  usat = (rtX.Integrator3_CSTATE[0] >= 3.1415926535897931);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[1] > 0.0)) || (usat &&
       (rtDW.Integrator_c[1] < 0.0))) {
    _rtXdot->Integrator3_CSTATE[0] = rtDW.Integrator_c[1];
  } else {
    /* in saturation */
    _rtXdot->Integrator3_CSTATE[0] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator4' */
  lsat = (rtX.Integrator4_CSTATE[0] <= 0.0);
  usat = (rtX.Integrator4_CSTATE[0] >= 6.2831853071795862);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[2] > 0.0)) || (usat &&
       (rtDW.Integrator_c[2] < 0.0))) {
    _rtXdot->Integrator4_CSTATE[0] = rtDW.Integrator_c[2];
  } else {
    /* in saturation */
    _rtXdot->Integrator4_CSTATE[0] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator' */
  lsat = (rtX.Integrator_CSTATE_g[0] <= -34.906585039886586);
  usat = (rtX.Integrator_CSTATE_g[0] >= 34.906585039886586);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.out[0] > 0.0)) || (usat &&
       (rtDW.out[0] < 0.0))) {
    _rtXdot->Integrator_CSTATE_g[0] = rtDW.out[0];
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_g[0] = 0.0;
  }

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[0] = rtDW.Integrator[0];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[1] = rtDW.Sum1[1];

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  lsat = (rtX.Integrator2_CSTATE[1] <= -1.5707963267948966);
  usat = (rtX.Integrator2_CSTATE[1] >= 1.5707963267948966);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[0] > 0.0)) || (usat &&
       (rtDW.Integrator_c[0] < 0.0))) {
    _rtXdot->Integrator2_CSTATE[1] = rtDW.Integrator_c[0];
  } else {
    /* in saturation */
    _rtXdot->Integrator2_CSTATE[1] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator3' */
  lsat = (rtX.Integrator3_CSTATE[1] <= -3.1415926535897931);
  usat = (rtX.Integrator3_CSTATE[1] >= 3.1415926535897931);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[1] > 0.0)) || (usat &&
       (rtDW.Integrator_c[1] < 0.0))) {
    _rtXdot->Integrator3_CSTATE[1] = rtDW.Integrator_c[1];
  } else {
    /* in saturation */
    _rtXdot->Integrator3_CSTATE[1] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator4' */
  lsat = (rtX.Integrator4_CSTATE[1] <= 0.0);
  usat = (rtX.Integrator4_CSTATE[1] >= 6.2831853071795862);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[2] > 0.0)) || (usat &&
       (rtDW.Integrator_c[2] < 0.0))) {
    _rtXdot->Integrator4_CSTATE[1] = rtDW.Integrator_c[2];
  } else {
    /* in saturation */
    _rtXdot->Integrator4_CSTATE[1] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator' */
  lsat = (rtX.Integrator_CSTATE_g[1] <= -34.906585039886586);
  usat = (rtX.Integrator_CSTATE_g[1] >= 34.906585039886586);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.out[1] > 0.0)) || (usat &&
       (rtDW.out[1] < 0.0))) {
    _rtXdot->Integrator_CSTATE_g[1] = rtDW.out[1];
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_g[1] = 0.0;
  }

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[1] = rtDW.Integrator[1];

  /* Derivatives for Integrator: '<S2>/Integrator' */
  _rtXdot->Integrator_CSTATE[2] = rtDW.Sum1[2];

  /* Derivatives for Integrator: '<S1>/Integrator2' */
  lsat = (rtX.Integrator2_CSTATE[2] <= -1.5707963267948966);
  usat = (rtX.Integrator2_CSTATE[2] >= 1.5707963267948966);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[0] > 0.0)) || (usat &&
       (rtDW.Integrator_c[0] < 0.0))) {
    _rtXdot->Integrator2_CSTATE[2] = rtDW.Integrator_c[0];
  } else {
    /* in saturation */
    _rtXdot->Integrator2_CSTATE[2] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator3' */
  lsat = (rtX.Integrator3_CSTATE[2] <= -3.1415926535897931);
  usat = (rtX.Integrator3_CSTATE[2] >= 3.1415926535897931);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[1] > 0.0)) || (usat &&
       (rtDW.Integrator_c[1] < 0.0))) {
    _rtXdot->Integrator3_CSTATE[2] = rtDW.Integrator_c[1];
  } else {
    /* in saturation */
    _rtXdot->Integrator3_CSTATE[2] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator4' */
  lsat = (rtX.Integrator4_CSTATE[2] <= 0.0);
  usat = (rtX.Integrator4_CSTATE[2] >= 6.2831853071795862);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.Integrator_c[2] > 0.0)) || (usat &&
       (rtDW.Integrator_c[2] < 0.0))) {
    _rtXdot->Integrator4_CSTATE[2] = rtDW.Integrator_c[2];
  } else {
    /* in saturation */
    _rtXdot->Integrator4_CSTATE[2] = 0.0;
  }

  /* Derivatives for Integrator: '<S1>/Integrator' */
  lsat = (rtX.Integrator_CSTATE_g[2] <= -34.906585039886586);
  usat = (rtX.Integrator_CSTATE_g[2] >= 34.906585039886586);
  if (((!lsat) && (!usat)) || (lsat && (rtDW.out[2] > 0.0)) || (usat &&
       (rtDW.out[2] < 0.0))) {
    _rtXdot->Integrator_CSTATE_g[2] = rtDW.out[2];
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE_g[2] = 0.0;
  }

  /* Derivatives for Integrator: '<S2>/Integrator1' */
  _rtXdot->Integrator1_CSTATE[2] = rtDW.Integrator[2];
}

/* Model initialize function */
void QuadcopterModel_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&rtM->solverInfo, &rtM->Timing.simTimeStep);
    rtsiSetTPtr(&rtM->solverInfo, &rtmGetTPtr(rtM));
    rtsiSetStepSizePtr(&rtM->solverInfo, &rtM->Timing.stepSize0);
    rtsiSetdXPtr(&rtM->solverInfo, &rtM->derivs);
    rtsiSetContStatesPtr(&rtM->solverInfo, (real_T **) &rtM->contStates);
    rtsiSetNumContStatesPtr(&rtM->solverInfo, &rtM->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&rtM->solverInfo,
      &rtM->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&rtM->solverInfo,
      &rtM->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&rtM->solverInfo,
      &rtM->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&rtM->solverInfo, (boolean_T**)
      &rtM->contStateDisabled);
    rtsiSetErrorStatusPtr(&rtM->solverInfo, (&rtmGetErrorStatus(rtM)));
    rtsiSetRTModelPtr(&rtM->solverInfo, rtM);
  }

  rtsiSetSimTimeStep(&rtM->solverInfo, MAJOR_TIME_STEP);
  rtM->intgData.y = rtM->odeY;
  rtM->intgData.f[0] = rtM->odeF[0];
  rtM->intgData.f[1] = rtM->odeF[1];
  rtM->intgData.f[2] = rtM->odeF[2];
  rtM->contStates = ((X *) &rtX);
  rtM->contStateDisabled = ((XDis *) &rtXDis);
  rtM->Timing.tStart = (0.0);
  rtsiSetSolverData(&rtM->solverInfo, (void *)&rtM->intgData);
  rtsiSetIsMinorTimeStepWithModeChange(&rtM->solverInfo, false);
  rtsiSetSolverName(&rtM->solverInfo,"ode3");
  rtmSetTPtr(rtM, &rtM->Timing.tArray[0]);
  rtM->Timing.stepSize0 = 1.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator2' */
  rtX.Integrator2_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator3' */
  rtX.Integrator3_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator4' */
  rtX.Integrator4_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  rtX.Integrator_CSTATE_g[0] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  rtX.Integrator1_CSTATE[0] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator2' */
  rtX.Integrator2_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator3' */
  rtX.Integrator3_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator4' */
  rtX.Integrator4_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  rtX.Integrator_CSTATE_g[1] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  rtX.Integrator1_CSTATE[1] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator' */
  rtX.Integrator_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator2' */
  rtX.Integrator2_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator3' */
  rtX.Integrator3_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator4' */
  rtX.Integrator4_CSTATE[2] = 0.0;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  rtX.Integrator_CSTATE_g[2] = 0.0;

  /* InitializeConditions for Integrator: '<S2>/Integrator1' */
  rtX.Integrator1_CSTATE[2] = 0.0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
