#include "task_handles.h"


void vTask1 ( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelayms = pdMS_TO_TICKS( (TickType_t) 1000 );
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("Periodic task-1 is running\n");
		vTaskDelayUntil( &xLastWakeTime, xDelayms );
	}

}

void vTask2 ( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelayms = pdMS_TO_TICKS( (TickType_t) 500 );
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("Periodic task-2 is running\n");
		vTaskDelayUntil( &xLastWakeTime, xDelayms );
	}

}

void vTask3 ( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelayms = pdMS_TO_TICKS( (TickType_t) 750 );
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("Periodic task-3 is running\n");
		vTaskDelayUntil( &xLastWakeTime, xDelayms );
	}

}

void vTask4 ( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelayms = pdMS_TO_TICKS( (TickType_t) 250 );
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("Periodic task-4 is running\n");
		vTaskDelayUntil( &xLastWakeTime, xDelayms );
	}

}

void vTask5 ( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelayms = pdMS_TO_TICKS( (TickType_t) 1500 );
	xLastWakeTime = xTaskGetTickCount();

	for(;;)
	{
		printf("Periodic task-5 is running\n");
		vTaskDelayUntil( &xLastWakeTime, xDelayms );
	}

}

