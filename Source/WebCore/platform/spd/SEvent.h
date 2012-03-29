/*
 * SEvent.h
 *
 *  Created on: 2012-3-28
 *      Author: jack
 * \brief 本项目实现一个简单的线程安全的事件驱动式编程模型
 *
 */

#ifndef SEVENT_H_
#define SEVENT_H_

typedef int SEventType;

/**
 * \brief 定时器事件
 */
#define SE_TIMER 0

/**
 *  \brief 事件响应函数类型定义
 */
typedef bool (*SEvent_cb)(void *data);

/**
 * \brief 初始化
 */
bool SEvent_init();

/**
 * \brief 创建自定义事件
 */
SEventType SEvent_type_new();

/*
 * \brief 为指定事件增加响应函数,可以添加多个，按先后顺序执行
 */
bool SEvent_handler_add(SEventType,SEvent_cb);

/**
 * \brief 增加一个事件
 */
bool SEvent_add(SEventType, void*);

/**
 * \brief 停止某类事件
 */
bool SEvent_stop(SEventType);

/**
 * \brief 事件处理主循环，除非调用了SEvent_loop_quit()否则不会返回
 */
int SEvent_loop_begin();

/**
 * \brief 退出事件循环
 */
int SEvent_loop_quit();

/**
 * \brief 清除所有未处理的事件，释放资源
 */
int SEvent_shutdown();

#endif /* SEVENT_H_ */
