#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* Hooks */
#define configUSE_IDLE_HOOK	            1
#define configUSE_TICK_HOOK				0
#define configCHECK_FOR_STACK_OVERFLOW	2
#define configUSE_MALLOC_FAILED_HOOK    1

/* Peemption */
#define configUSE_PREEMPTION			1
#define configUSE_TIME_SLICING			0

/* MCU/Application */
#define configCPU_CLOCK_HZ				( ( unsigned long ) 80000000 )
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 70 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) (10000) )
#define configMAX_TASK_NAME_LEN			( 12 )
#define configMAX_PRIORITIES			( 10UL )
#define configKERNEL_INTERRUPT_PRIORITY ( 7 << 5 )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( 1 << 5 )

/* Tweaks */
#define configUSE_TICKLESS_IDLE			0
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			0
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/* Task Notifications */
#define configUSE_TASK_NOTIFICATIONS	1

/* Co-routines */
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Mutex */
#define configUSE_MUTEXES				1
#define configUSE_RECURSIVE_MUTEXES		0

/* Queues and Semaphores */
#define configUSE_COUNTING_SEMAPHORES	1
#define configUSE_QUEUE_SETS			1

/* Timer */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		5
#define configTIMER_QUEUE_LENGTH		20
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE * 2 )

/* Debug */
#define configQUEUE_REGISTRY_SIZE				10
#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1
//#define configASSERT( x )     if( ( x ) == 0 ) vAssertCalled( __FILE__, __LINE__ )

/* Compatibility */
#define configENABLE_BACKWARD_COMPATIBILITY 0
#define configUSE_ALTERNATIVE_API			0

/* functions */
#define INCLUDE_vTaskPrioritySet                1
#define INCLUDE_uxTaskPriorityGet               1
#define INCLUDE_vTaskDelete                     1
#define INCLUDE_vTaskSuspend                    1
#define INCLUDE_xResumeFromISR                  1
#define INCLUDE_vTaskDelayUntil                 1
#define INCLUDE_vTaskDelay                      1
#define INCLUDE_xTaskGetSchedulerState          1
#define INCLUDE_xTaskGetCurrentTaskHandle       1
#define INCLUDE_uxTaskGetStackHighWaterMark     1
#define INCLUDE_xTaskGetIdleTaskHandle          1
#define INCLUDE_xTimerGetTimerDaemonTaskHandle  1
#define INCLUDE_pcTaskGetTaskName               1
#define INCLUDE_eTaskGetState                   1
#define INCLUDE_xEventGroupSetBitFromISR        1
#define INCLUDE_xTimerPendFunctionCall          1

#endif /* FREERTOS_CONFIG_H */
