/*
 * MonitorMgr.h
 *
 *  Created on: Nov 24, 2014
 *      Author: satram
 */

#ifndef MONITORMGR_H_
#define MONITORMGR_H_

#include "Task.h"

class PlaylistInterface;
class VariantPlaylist;


class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool& revparam=true)
    {reverse=revparam;}
  bool operator() (std::shared_ptr<Task>lhs, std::shared_ptr<Task>rhs) const
  {
    if (reverse) return (lhs.get()->get_absolute_time() > rhs.get()->get_absolute_time());
    else return (lhs.get()->get_absolute_time() < rhs.get()->get_absolute_time());
  }
};

typedef std::priority_queue<std::shared_ptr<Task>, std::deque<std::shared_ptr<Task>>, mycomparison> mypq_type;

class MonitorMgr
{

	static MonitorMgr *instance;
	static unsigned int ref_count;

	std::mutex tp_m;
	std::condition_variable tp_cv;
	std::deque<TaskHandler *> task_handlers;
	std::deque<TaskHandler *> available_taskhandlers;

	unsigned int thread_pool_size;
	unsigned int task_handler_count;
	mypq_type scheduled_tasks;
	std::deque<std::shared_ptr<UrlMonitor>> urlMonitorQueue;

	MonitorMgr();
	virtual ~MonitorMgr();

	void create_task_handler();
	TaskHandler * get_task_handler();
    void destroy_task_handlers();

    void timer_thread();
    std::thread *timer;
    bool destroy;
    std::mutex m;
    std::condition_variable cv;

    const std::string currentDateTime();
    void clear_scheduled_tasks();
    void schedule_task(std::shared_ptr<UrlMonitor> url_monitor, bool delayed);
public:

	static MonitorMgr* get_instance()
	{
		if(instance == NULL)
			instance = new MonitorMgr();
		ref_count++;
		return instance;
	}

	void delete_instance()
	{
		ref_count--;
		if(ref_count == 0)
			delete(instance);
	}

	void register_free_task_handler(TaskHandler *th);
	void create_url_monitor(std::string playlist_name, unsigned int poll_interval, PlaylistInterface *playlist, VariantPlaylist *variant_playlist);
	void remove_all_url_monitor();
	void remove_url_monitor(const char * playlist_name);
	void add_task(std::shared_ptr<Task> tk);
};

#endif /* MONITORMGR_H_ */
