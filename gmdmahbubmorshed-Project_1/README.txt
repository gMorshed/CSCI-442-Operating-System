Author: Gazi Mahbub Morshed

CUSTOM algorithm design:
1. My custom algorithm consists of five queues. One takes in all threads that has just arrived as in the thread has a THREAD_ARRIVED
    event associated with it. Other threads that comes from other event types goes into system_queue, interactive_queue, normal_queue and batch_queue
    based on their threads propess's priority. For all the queues, threads are dispatched as fast come first serve basis. So, the sooner a thread arrived,
    I will let it go first. Thus, it will give minimum response time for the time slice. 
2. The algorithm does premption based on if there are new threads available in the new_thread_queue. So, I added an additonal condition to time slice part in the 
    simulator. After a process and thread dispatch happens, I check if there are threads in new_thread_queue using a boolean variable. 
    If there is, I preempte the corrent thread and select a new thread from the algorithm. 
3. Next thread to run is choosen from the new_thread_queue as long as there are new_threads tp process. After that threads are given priority 
    based on their process's priority type (SYSTEM > INTERACTIVE > NORMAL >BATCH)
4. As I am letting threads from the new_thread_queue go first, the algorithm will minimize the response time of each thread. Thus, the algorithm 
    will attempt to acheive the minimun average response time possible. 