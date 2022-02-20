# 轻量级WebServer #
## 核心技术 ##
- 同步IO模拟的Proactor模式 作为消息处理模式
- 采用单例模式的线程池提高并发度，并降低创建线程的开销
- 时间堆来管理定时器，支持HTTP长连接和处理非活动连接
- 有限状态机处理HTTP请求
- epoll+非阻塞IO+边缘触发模式+EPOLLONESHOT降低事件触发次数
- 智能指针shared_ptr、unique_ptr和weak_ptr管理内存
- RAII手法封装互斥锁、信号量和各种资源

## 开发计划 ##
- 增加日志系统记录服务器运行状态
- 增加内存池减少内存创建时间
- 提供CGI支持